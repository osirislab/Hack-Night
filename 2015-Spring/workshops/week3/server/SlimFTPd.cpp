/*
 * Copyright (c) 2006, Matt Whitlock and WhitSoft Development
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the names of Matt Whitlock and WhitSoft Development nor the
 *     names of their contributors may be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <winsock.h>
#include <windows.h>
#include <shlwapi.h>
#include <algorithm>
#include "permdb.h"
#include "synclogger.h"
#include "userdb.h"
#include "vfs.h"
#include "tree.cpp"

using namespace std;

#define SERVERID "SlimFTPd 3.181, by WhitSoft Development (www.whitsoftdev.com)"
#define PACKET_SIZE 1452
#define IP_ADDRESS_TYPE_LAN 1
#define IP_ADDRESS_TYPE_WAN 2
#define IP_ADDRESS_TYPE_LOCAL 3
#define SOCKET_FILE_IO_DIRECTION_SEND 1
#define SOCKET_FILE_IO_DIRECTION_RECEIVE 2

// Service functions {
VOID WINAPI ServiceMain(DWORD, LPTSTR);
VOID WINAPI ServiceHandler(DWORD);
bool Startup();
void Cleanup();
// }

// Configuration functions {
void LogConfError(const char *, DWORD, const char *);
bool ConfParseScript(const char *);
bool ConfSetBindInterface(const char *pszArg, DWORD dwLine);
bool ConfSetBindPort(const char *pszArg, DWORD dwLine);
bool ConfSetMaxConnections(const char *pszArg, DWORD dwLine);
bool ConfSetCommandTimeout(const char *pszArg, DWORD dwLine);
bool ConfSetConnectTimeout(const char *pszArg, DWORD dwLine);
bool ConfSetAdminPassword(const char *pszArg, DWORD dwLine);
bool ConfSetLookupHosts(const char *pszArg, DWORD dwLine);
bool ConfAddUser(const char *pszArg, DWORD dwLine);
bool ConfSetUserPassword(const char *pszUser, const char *pszArg, DWORD dwLine);
bool ConfSetMountPoint(const char *pszUser, const char *pszVirtual, const char *pszLocal, DWORD dwLine);
bool ConfSetPermission(DWORD dwMode, const char *pszUser, const char *pszVirtual, const char *pszPerms, DWORD dwLine);
// }

// Network functions {
bool WINAPI ListenThread(LPVOID);
bool WINAPI ConnectionThread(SOCKET);
bool SocketSendString(SOCKET, const char *);
DWORD SocketReceiveString(SOCKET, char *, DWORD);
DWORD SocketReceiveData(SOCKET, char *, DWORD);
SOCKET EstablishDataConnection(SOCKADDR_IN *, SOCKET *);
void LookupHost(IN_ADDR ia, char *pszHostName, size_t stHostName);
bool DoSocketFileIO(SOCKET sCmd, SOCKET sData, HANDLE hFile, DWORD dwDirection, DWORD *pdwAbortFlag);
// }

// Miscellaneous support functions {
DWORD FileReadLine(HANDLE, char *, DWORD);
DWORD SplitTokens(char *);
const char * GetToken(const char *, DWORD);
DWORD GetIPAddressType(IN_ADDR ia);
bool CanUserLogin(const char *pszUser, IN_ADDR iaPeer);
// }

// Global Variables {
HINSTANCE hInst;
SERVICE_STATUS_HANDLE hServiceStatus;
SERVICE_STATUS ServiceStatus;
bool isWinNT, isService;
DWORD dwMaxConnections = 20, dwCommandTimeout = 300, dwConnectTimeout = 15;
bool bLookupHosts = true;
DWORD dwActiveConnections = 0;
SOCKET sListen;
SOCKADDR_IN saiListen;
UserDB *pUsers;
SyncLogger *pLog;
// }

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR pszCmdLine, int nShowCmd)
{
	OSVERSIONINFO ovi;
	SERVICE_TABLE_ENTRY ste[]={ { "SlimFTPd", (LPSERVICE_MAIN_FUNCTION)ServiceMain }, { 0, 0 } };
	HMODULE hKernel32;
	FARPROC RegisterServiceProcess;
	MSG msg;

	hInst = GetModuleHandle(0);

	// Check if Windows NT
	ovi.dwOSVersionInfoSize=sizeof(OSVERSIONINFO);
	GetVersionEx(&ovi);
	isWinNT = (ovi.dwPlatformId == VER_PLATFORM_WIN32_NT);

	// Are we starting as a service?
	if (strstr(GetCommandLine(), "-service") != 0) {
		if (isWinNT) {
			isService = true;
			StartServiceCtrlDispatcher(ste);
			Cleanup();
			return false;
		} else {
			isService = false;
			hKernel32=LoadLibrary("KERNEL32.DLL");
			RegisterServiceProcess=GetProcAddress(hKernel32,"RegisterServiceProcess");
			((DWORD (__stdcall *)(DWORD, DWORD))RegisterServiceProcess)(0,1);
			FreeLibrary(hKernel32);
		}
	} else {
		isService = false;
	}

	if (Startup()) {
		while (GetMessage(&msg,0,0,0)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	} else {
		pLog->Log("An error occurred while starting SlimFTPd.");
	}

	Cleanup();

	return false;
}

VOID WINAPI ServiceMain(DWORD dwArgc, LPTSTR lpszArgv)
{
	// Starting up as a Windows NT service
	hServiceStatus=RegisterServiceCtrlHandler("SlimFTPd",(LPHANDLER_FUNCTION)ServiceHandler);
	ServiceStatus.dwServiceType=SERVICE_WIN32_OWN_PROCESS;
	ServiceStatus.dwCurrentState=SERVICE_RUNNING;
	ServiceStatus.dwControlsAccepted=SERVICE_ACCEPT_STOP|SERVICE_ACCEPT_SHUTDOWN;
	ServiceStatus.dwWin32ExitCode=NO_ERROR;
	ServiceStatus.dwServiceSpecificExitCode=0;
	ServiceStatus.dwCheckPoint=0;
	ServiceStatus.dwWaitHint=0;
	SetServiceStatus(hServiceStatus,&ServiceStatus);

	if (!Startup()) {
		pLog->Log("An error occurred while starting SlimFTPd.");
		ServiceStatus.dwCurrentState=SERVICE_STOPPED;
		SetServiceStatus(hServiceStatus,&ServiceStatus);
	}
}

VOID WINAPI ServiceHandler(DWORD fdwControl)
{
	switch (fdwControl) {
		case SERVICE_CONTROL_INTERROGATE:
			SetServiceStatus(hServiceStatus,&ServiceStatus);
			break;
		case SERVICE_CONTROL_STOP:
			pLog->Log("The SlimFTPd service has received a request to stop.");
			ServiceStatus.dwCurrentState=SERVICE_STOPPED;
			SetServiceStatus(hServiceStatus,&ServiceStatus);
			break;
		case SERVICE_CONTROL_SHUTDOWN:
			pLog->Log("The SlimFTPd service has received notification of a system shutdown.");
			ServiceStatus.dwCurrentState=SERVICE_STOPPED;
			SetServiceStatus(hServiceStatus,&ServiceStatus);
			break;
	}
}

bool Startup()
{
	WSADATA wsad;
	char szLogFile[512], szConfFile[512];
	DWORD dw;

	// Construct log and config filenames
	GetModuleFileName(0,szLogFile,512);
	*strrchr(szLogFile, '\\') = 0;
	strcpy_s(szConfFile,szLogFile);
	strcat_s(szLogFile, "\\SlimFTPd.log");
	strcat_s(szConfFile, "\\SlimFTPd.conf");

	// Start logger thread
	pLog=new SyncLogger(szLogFile);

	// Allocate user database
	pUsers = new UserDB;

	// Log some startup info
	pLog->Log("-------------------------------------------------------------------------------");
	pLog->Log(SERVERID);
	if (isService) pLog->Log("The SlimFTPd service is starting.");
	else pLog->Log("SlimFTPd is starting.");

	// Init listen socket to defaults
	ZeroMemory(&saiListen,sizeof(SOCKADDR_IN));
	saiListen.sin_family=AF_INET;
	saiListen.sin_addr.S_un.S_addr=INADDR_ANY;
	saiListen.sin_port=htons(21);

	// Start Winsock
	WSAStartup(MAKEWORD(1,1),&wsad);

	// Exec config script
	if (!ConfParseScript(szConfFile)) return false;

	// Create and bind the listen socket
	sListen=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (bind(sListen,(SOCKADDR *)&saiListen,sizeof(SOCKADDR_IN))) {
		pLog->Log("Unable to bind socket. Specified port may already be in use.");
		closesocket(sListen);
		return false;
	}
	listen(sListen,SOMAXCONN);

	// Launch the listen thread
	CloseHandle(CreateThread(0,0,(LPTHREAD_START_ROUTINE)ListenThread,0,0,&dw));

	return true;
}

void Cleanup()
{
	// Cleanup Winsock
	WSACleanup();

	// Log the stop of the service
	if (isService) pLog->Log("The SlimFTPd service has stopped.");
	else pLog->Log("SlimFTPd has stopped.");

	// Deallocate the user database
	delete pUsers;

	// Shut down the logger thread
	delete pLog;
}

void LogConfError(const char *pszError, DWORD dwLine, const char *pszArg)
{
	char sz[1024];
	sprintf_s(sz, (string("Error on line %u: ") + pszError).c_str(), dwLine, pszArg);
	pLog->Log(sz);
}

bool ConfParseScript(const char *pszFileName)
{
// Opens and parses a SlimFTPd configuration script file.
// Returns false on error, or true on success.

	char sz[512], *psz, *psz2;
	string strUser;
	DWORD dwLen, dwLine, dwTokens;
	HANDLE hFile;

	sprintf_s(sz,"Executing \"%s\"...",strrchr(pszFileName,'\\')+1);
	pLog->Log(sz);

	// Open config file
	hFile=CreateFile(pszFileName,GENERIC_READ,0,0,OPEN_EXISTING,FILE_FLAG_SEQUENTIAL_SCAN,0);
	if (hFile==INVALID_HANDLE_VALUE) {
		pLog->Log("Unable to open \"SlimFTPd.conf\".");
		return false;
	}

	for (dwLine=1;;dwLine++) {
		dwLen=FileReadLine(hFile, sz, 512);
		if (dwLen==-1) {
			CloseHandle(hFile);
			if (!strUser.empty()) {
				LogConfError("Premature end of script encountered: unterminated User block.",dwLine,0);
				return false;
			} else {
				pLog->Log("Configuration script parsed successfully.");
				return true;
			}
		} else if (dwLen>=512) {
			LogConfError("Line is too long to parse.",dwLine,0);
			break;
		}
		psz=sz;
		while (*psz==' ' || *psz=='\t') psz++;
		if (!*psz || *psz=='#') continue;

		if (*psz=='<') {
			psz2=strchr(psz,'>');
			if (psz2) {
				*(psz2++)=0;
				while (*psz2==' ' || *psz2=='\t') psz2++;
				if (*psz2) {
					LogConfError("Syntax error. Expected end of line after '>'.",dwLine,0);
					break;
				}
				psz++;
			} else {
				LogConfError("Syntax error. Expected '>' before end of line.",dwLine,0);
				break;
			}
		}

		dwTokens=SplitTokens(psz);

		if (!_stricmp(psz,"BindInterface")) {
			if (dwTokens==2) {
				if (!ConfSetBindInterface(GetToken(psz,2),dwLine)) break;
			} else {
				LogConfError("BindInterface directive should have exactly 1 argument.",dwLine,0);
				break;
			}
		}

		else if (!_stricmp(psz,"BindPort")) {
			if (dwTokens==2) {
				if (!ConfSetBindPort(GetToken(psz,2),dwLine)) break;
			} else {
				LogConfError("BindPort directive should have exactly 1 argument.",dwLine,0);
				break;
			}
		}

		else if (!_stricmp(psz,"MaxConnections")) {
			if (dwTokens==2) {
				if (!ConfSetMaxConnections(GetToken(psz,2),dwLine)) break;
			} else {
				LogConfError("MaxConnections directive should have exactly 1 argument.",dwLine,0);
				break;
			}
		}

		else if (!_stricmp(psz,"CommandTimeout")) {
			if (dwTokens==2) {
				if (!ConfSetCommandTimeout(GetToken(psz,2),dwLine)) break;
			} else {
				LogConfError("CommandTimeout directive should have exactly 1 argument.",dwLine,0);
				break;
			}
		}

		else if (!_stricmp(psz,"ConnectTimeout")) {
			if (dwTokens==2) {
				if (!ConfSetConnectTimeout(GetToken(psz,2),dwLine)) break;
			} else {
				LogConfError("ConnectTimeout directive should have exactly 1 argument.",dwLine,0);
				break;
			}
		}

		else if (!_stricmp(psz,"LookupHosts")) {
			if (dwTokens==2) {
				if (!ConfSetLookupHosts(GetToken(psz,2),dwLine)) break;
			} else {
				LogConfError("LookupHosts directive should have exactly 1 argument.",dwLine,0);
				break;
			}
		}

		else if (!_stricmp(psz,"User")) {
			if (!strUser.empty()) {
				LogConfError("<User> directive invalid inside User block.",dwLine,0);
				break;
			} else if (dwTokens==2) {
				if (ConfAddUser(GetToken(psz,2),dwLine)) {
					strUser = GetToken(psz, 2);
				} else {
					break;
				}
			} else {
				LogConfError("<User> directive should have exactly 1 argument.",dwLine,0);
				break;
			}
		}
		
		else if (!_stricmp(psz,"/User")) {
			if (strUser.empty()) {
				LogConfError("</User> directive invalid outside of User block.",dwLine,0);
				break;
			} else if (dwTokens==1) {
				strUser.clear();
			} else {
				LogConfError("</User> directive should not have any arguments.",dwLine,0);
				break;
			}
		}

		else if (!_stricmp(psz,"Password")) {
			if (strUser.empty()) {
				LogConfError("Password directive invalid outside of User block.",dwLine,0);
				break;
			} else if (dwTokens==2) {
				if (!ConfSetUserPassword(strUser.c_str(), GetToken(psz, 2), dwLine)) break;
			} else {
				LogConfError("Password directive should have exactly 1 argument.",dwLine,0);
				break;
			}
		}

		else if (!_stricmp(psz,"Mount")) {
			if (strUser.empty()) {
				LogConfError("Mount directive invalid outside of User block.",dwLine,0);
				break;
			} else if (dwTokens==3) {
				if (!ConfSetMountPoint(strUser.c_str(), GetToken(psz, 2), GetToken(psz, 3), dwLine)) break;
			} else {
				LogConfError("Mount directive should have exactly 2 arguments.",dwLine,0);
				break;
			}
		}

		else if (!_stricmp(psz,"Allow")) {
			if (strUser.empty()) {
				LogConfError("Allow directive invalid outside of User block.",dwLine,0);
				break;
			} else if (dwTokens>=3) {
				if (!ConfSetPermission(1, strUser.c_str(), GetToken(psz, 2), GetToken(psz, 3), dwLine)) break;
			} else {
				LogConfError("Allow directive should have at least 2 arguments.",dwLine,0);
				break;
			}
		}

		else if (!_stricmp(psz,"Deny")) {
			if (strUser.empty()) {
				LogConfError("Deny directive invalid outside of User block.",dwLine,0);
				break;
			} else if (dwTokens>=3) {
				if (!ConfSetPermission(0, strUser.c_str(), GetToken(psz, 2), GetToken(psz, 3), dwLine)) break;
			} else {
				LogConfError("Deny directive should have at least 2 arguments.",dwLine,0);
				break;
			}
		}

		else {
			LogConfError("Directive \"%s\" not recognized.",dwLine,psz);
			break;
		}
	}

	CloseHandle(hFile);
	pLog->Log("Failed parsing configuration script.");
	return false;
}

bool ConfSetBindInterface(const char *pszArg, DWORD dwLine)
{
	char sz[512];
	HOSTENT *phe;
	DWORD dw;

	if (!_stricmp(pszArg,"All")) {
		saiListen.sin_addr.S_un.S_addr=INADDR_ANY;
	} else if (!_stricmp(pszArg,"Local")) {
		saiListen.sin_addr.S_un.S_addr=htonl(INADDR_LOOPBACK);
	} else if (!_stricmp(pszArg,"LAN")) {
		saiListen.sin_addr.S_un.S_addr=INADDR_NONE;
		gethostname(sz,512);
		phe=gethostbyname(sz);
		if (phe) {
			for (dw=0;phe->h_addr_list[dw];dw++) {
				if (GetIPAddressType(*(IN_ADDR*)phe->h_addr_list[dw]) == IP_ADDRESS_TYPE_LAN) {
					saiListen.sin_addr.S_un.S_addr=((IN_ADDR*)phe->h_addr_list[dw])->S_un.S_addr;
					break;
				}
			}
		}
		if (saiListen.sin_addr.S_un.S_addr==INADDR_NONE) {
			LogConfError("BindInterface directive could not find a LAN interface.",dwLine,0);
			return false;
		}
	} else if (!_stricmp(pszArg,"WAN")) {
		saiListen.sin_addr.S_un.S_addr=INADDR_NONE;
		gethostname(sz,512);
		phe=gethostbyname(sz);
		if (phe) {
			for (dw=0;phe->h_addr_list[dw];dw++) {
				if (GetIPAddressType(*(IN_ADDR*)phe->h_addr_list[dw]) == IP_ADDRESS_TYPE_WAN) {
					saiListen.sin_addr.S_un.S_addr=((IN_ADDR*)phe->h_addr_list[dw])->S_un.S_addr;
					break;
				}
			}
		}
		if (saiListen.sin_addr.S_un.S_addr==INADDR_NONE) {
			LogConfError("BindInterface directive could not find a WAN interface.",dwLine,0);
			return false;
		}
	} else {
		saiListen.sin_addr.S_un.S_addr=inet_addr(pszArg);
		if (saiListen.sin_addr.S_un.S_addr==INADDR_NONE) {
			LogConfError("BindInterface directive does not recognize argument \"%s\".",dwLine,pszArg);
			return false;
		}
	}
	return true;
}

bool ConfSetBindPort(const char *pszArg, DWORD dwLine)
{
	WORD wPort;

	wPort = (WORD)StrToInt(pszArg);
	if (wPort) {
		saiListen.sin_port=htons(wPort);
		return true;
	} else {
		LogConfError("BindPort directive does not recognize argument \"%s\".",dwLine,pszArg);
		return false;
	}
}

bool ConfSetMaxConnections(const char *pszArg, DWORD dwLine)
{
	DWORD dw;

	if (!_stricmp(pszArg,"Off")) {
		dwMaxConnections=-1;
		return true;
	} else {
		dw = StrToInt(pszArg);
		if (dw) {
			dwMaxConnections=dw;
			return true;
		} else {
			LogConfError("MaxConnections directive does not recognize argument \"%s\".",dwLine,pszArg);
			return false;
		}
	}
}

bool ConfSetCommandTimeout(const char *pszArg, DWORD dwLine)
{
	DWORD dw;

	dw = StrToInt(pszArg);
	if (dw) {
		dwCommandTimeout=dw;
		return true;
	} else {
		LogConfError("CommandTimeout directive does not recognize argument \"%s\".",dwLine,pszArg);
		return false;
	}
}

bool ConfSetConnectTimeout(const char *pszArg, DWORD dwLine)
{
	DWORD dw;

	dw = StrToInt(pszArg);
	if (dw) {
		dwConnectTimeout=dw;
		return true;
	} else {
		LogConfError("ConnectTimeout directive does not recognize argument \"%s\".",dwLine,pszArg);
		return false;
	}
}

bool ConfSetLookupHosts(const char *pszArg, DWORD dwLine)
{
	if (!_stricmp(pszArg,"Off")) {
		bLookupHosts = false;
		return true;
	} else if (!_stricmp(pszArg,"On")) {
		bLookupHosts = true;
		return true;
	} else {
		LogConfError("LookupHosts directive does not recognize argument \"%s\".",dwLine,pszArg);
		return false;
	}
}

bool ConfAddUser(const char *pszArg, DWORD dwLine)
{
	if (strlen(pszArg)<32) {
		if (pUsers->Add(pszArg)) {
			return true;
		} else {
			LogConfError("User \"%s\" already defined.",dwLine,pszArg);
			return false;
		}
	} else {
		LogConfError("Argument to User directive must be less than 32 characters long.",dwLine,0);
		return false;
	}
}

bool ConfSetUserPassword(const char *pszUser, const char *pszArg, DWORD dwLine)
{
	if (strlen(pszArg)<32) {
		pUsers->SetPassword(pszUser,pszArg);
		return true;
	} else {
		LogConfError("Argument to Password directive must be less than 32 characters long.",dwLine,0);
		return false;
	}
}

bool ConfSetMountPoint(const char *pszUser, const char *pszVirtual, const char *pszLocal, DWORD dwLine)
{
	VFS *pvfs;
	string strVirtual, strLocal;

	VFS::CleanVirtualPath(pszVirtual, strVirtual);

	if (strVirtual.at(0) != '/') {
		LogConfError("Mount directive cannot parse invalid virtual path \"%s\". Virtual paths must begin with a slash.", dwLine, strVirtual.c_str());
		return false;
	}
	if (pszLocal) {
		strLocal = pszLocal;
		replace(strLocal.begin(), strLocal.end(), '/', '\\');
		if (*strLocal.rbegin() == '\\') {
			strLocal = strLocal.substr(0, strLocal.length() - 1);
		}
		if (GetFileAttributes(strLocal.c_str()) == -1) {
			LogConfError("Mount directive cannot find local path \"%s\".", dwLine, strLocal.c_str());
			return false;
		}
	}
	pvfs=pUsers->GetVFS(pszUser);
	if (pvfs) pvfs->Mount(pszVirtual, pszLocal);
	return true;
}

bool ConfSetPermission(DWORD dwMode, const char *pszUser, const char *pszVirtual, const char *pszPerms, DWORD dwLine)
{
	PermDB *pperms;

	string strVirtual;
	VFS::CleanVirtualPath(pszVirtual, strVirtual);

	if (strVirtual.at(0) != '/') {
		if (dwMode) {
			LogConfError("Allow directive cannot parse invalid virtual path \"%s\". Virtual paths must begin with a slash.", dwLine, strVirtual.c_str());
		} else {
			LogConfError("Deny directive cannot parse invalid virtual path \"%s\". Virtual paths must begin with a slash.", dwLine, strVirtual.c_str());
		}
		return false;
	}

	pperms=pUsers->GetPermDB(pszUser);
	if (!pperms) return false;

	while (*pszPerms) {
		if (!_stricmp(pszPerms,"Read")) {
			pperms->SetPerm(strVirtual.c_str(), PERM_READ, dwMode);
		} else if (!_stricmp(pszPerms,"Write")) {
			pperms->SetPerm(strVirtual.c_str(), PERM_WRITE, dwMode);
		} else if (!_stricmp(pszPerms,"List")) {
			pperms->SetPerm(strVirtual.c_str(), PERM_LIST, dwMode);
		} else if (!_stricmp(pszPerms,"Admin")) {
			pperms->SetPerm(strVirtual.c_str(), PERM_ADMIN, dwMode);
		} else if (!_stricmp(pszPerms,"All")) {
			pperms->SetPerm(strVirtual.c_str(), PERM_READ, dwMode);
			pperms->SetPerm(strVirtual.c_str(), PERM_WRITE, dwMode);
			pperms->SetPerm(strVirtual.c_str(), PERM_LIST, dwMode);
			pperms->SetPerm(strVirtual.c_str(), PERM_ADMIN, dwMode);
		} else {
			if (dwMode) {
				LogConfError("Allow directive does not recognize argument \"%s\".",dwLine,pszPerms);
			} else {
				LogConfError("Deny directive does not recognize argument \"%s\".",dwLine,pszPerms);
			}
			return false;
		}
		pszPerms=GetToken(pszPerms,2);
	}
	return true;
}

bool WINAPI ListenThread(LPVOID lParam)
{
	SOCKET sIncoming;
	DWORD dw;

	pLog->Log("Waiting for incoming connections...");

	// Accept incoming connections and pass them to connection threads
	while ((sIncoming=accept(sListen,0,0))!=INVALID_SOCKET) {
		CloseHandle(CreateThread(0,0,(LPTHREAD_START_ROUTINE)ConnectionThread,(void *)sIncoming,0,&dw));
	}

	closesocket(sListen);

	return false;
}

bool WINAPI ConnectionThread(SOCKET sCmd)
{
	SOCKET sData=0, sPasv=0;
	SOCKADDR_IN saiCmd, saiCmdPeer, saiData, saiPasv;
	char szPeerName[64], szOutput[1024], szCmd[512], *pszParam;
	string strUser, strCurrentVirtual, strNewVirtual, strRnFr;
	DWORD dw, dwRestOffset=0;
	bool isLoggedIn = false;
	HANDLE hFile;
	SYSTEMTIME st;
	FILETIME ft;
	VFS *pVFS = NULL;
	PermDB *pPerms = NULL;
	VFS::listing_type listing;
	UINT_PTR i;

	ZeroMemory(&saiData, sizeof(SOCKADDR_IN));

	// Get peer address
	dw=sizeof(SOCKADDR_IN);
	getpeername(sCmd, (SOCKADDR *)&saiCmdPeer, (int *)&dw);
	LookupHost(saiCmdPeer.sin_addr, szPeerName, 64);

	// Log incoming connection
	sprintf_s(szOutput, "[%u] Incoming connection from %s:%u.", sCmd, szPeerName, ntohs(saiCmdPeer.sin_port));
	pLog->Log(szOutput);

	// Send greeting
	sprintf_s(szOutput, "220-%s\r\n220-You are connecting from %s:%u.\r\n220 Proceed with login.\r\n", SERVERID, szPeerName, ntohs(saiCmdPeer.sin_port));
	SocketSendString(sCmd, szOutput);

	// Get host address
	dw=sizeof(SOCKADDR_IN);
	getsockname(sCmd, (SOCKADDR *)&saiCmd, (int *)&dw);

	// Command processing loop
	for (;;) {

		dw=SocketReceiveString(sCmd,szCmd,511);

		if (dw==-1) {
			// Connection dropped or timed out
			SocketSendString(sCmd,"421 Connection timed out.\r\n");
			break;
		} else if (dw>511) {
			SocketSendString(sCmd,"500 Command line too long.\r\n");
			continue;
		}

		// points to first space or the end of the line
		if (pszParam = strchr(szCmd, ' ')) *(pszParam++) = 0;
		else pszParam = szCmd+strlen(szCmd);
		
		// pszparam used to validate # of arguments to command
		if (!_stricmp(szCmd, "USER")) {
			if (!*pszParam) {
				SocketSendString(sCmd, "501 Syntax error in parameters or arguments.\r\n");
				continue;
			} else if (isLoggedIn) {
				SocketSendString(sCmd, "503 Already logged in. Use REIN to change users.\r\n");
				continue;
			} else {
				strUser = pszParam;
				//check if user needs a password?
				if (pUsers->CheckPassword(strUser.c_str(), "")) {
					//szCmd == PASS
					strcpy_s(szCmd, "PASS");
					szCmd[5] = 0;
				} else {
					sprintf_s(szOutput, "331 Need password for user \"%s\".\r\n", strUser.c_str());
					SocketSendString(sCmd, szOutput);
					continue;
				}
			}
		}

		if (!_stricmp(szCmd, "PASS")) {
			if (strUser.empty()) {
				SocketSendString(sCmd, "503 Bad sequence of commands. Send USER first.\r\n");
			} else if (isLoggedIn) {
				SocketSendString(sCmd, "503 Already logged in. Use REIN to change users.\r\n");
			} else {
				if (pUsers->CheckPassword(strUser.c_str(), pszParam)) {
					if (CanUserLogin(strUser.c_str(), saiCmdPeer.sin_addr)) {
						isLoggedIn = true;
						dwActiveConnections++;
						strCurrentVirtual = "/"; 
						sprintf_s(szOutput, "230 User \"%s\" logged in.\r\n", strUser.c_str());
						SocketSendString(sCmd, szOutput);
						sprintf_s(szOutput, "[%u] User \"%s\" logged in.", sCmd, strUser.c_str());
						pLog->Log(szOutput);
						pVFS = pUsers->GetVFS(strUser.c_str());
						pPerms = pUsers->GetPermDB(strUser.c_str());
					} else {
						SocketSendString(sCmd, "421 Your login was refused due to a server connection limit.\r\n");
						sprintf_s(szOutput, "[%u] Login for user \"%s\" refused due to connection limit.", sCmd, strUser.c_str());
						pLog->Log(szOutput);
						break;
					}
				} else {
					SocketSendString(sCmd,"530 Incorrect password.\r\n");
				}
			}
		}

		else if (!_stricmp(szCmd, "REIN")) {
			if (isLoggedIn) {
				isLoggedIn = false;
				dwActiveConnections--;
				sprintf_s(szOutput, "220-User \"%s\" logged out.\r\n", strUser.c_str());
				SocketSendString(sCmd, szOutput);
				sprintf_s(szOutput, "[%u] User \"%s\" logged out.", sCmd, strUser.c_str());
				pLog->Log(szOutput);
				strUser.clear();
			}
			SocketSendString(sCmd, "220 REIN command successful.\r\n");
		}

		else if (!_stricmp(szCmd, "HELP")) {
			SocketSendString(sCmd, "214 For help, please visit www.whitsoftdev.com.\r\n");
		}

		else if (!_stricmp(szCmd, "FEAT")) {
			SocketSendString(sCmd, "211-Extensions supported:\r\n SIZE\r\n REST STREAM\r\n MDTM\r\n TVFS\r\n211 END\r\n");
		}

		else if (!_stricmp(szCmd, "SYST")) {
			sprintf_s(szOutput, "215 WIN32 Type: L8 Version: %s\r\n", SERVERID);
			SocketSendString(sCmd, szOutput);
		}

		else if (!_stricmp(szCmd, "QUIT")) {
			if (isLoggedIn) {
				isLoggedIn = false;
				dwActiveConnections--;
				sprintf_s(szOutput, "221-User \"%s\" logged out.\r\n", strUser.c_str());
				SocketSendString(sCmd, szOutput);
				sprintf_s(szOutput, "[%u] User \"%s\" logged out.", sCmd, strUser.c_str());
				pLog->Log(szOutput);
			}
			SocketSendString(sCmd, "221 Goodbye!\r\n");
			break;
		}

		else if (!_stricmp(szCmd, "NOOP")) {
			SocketSendString(sCmd, "200 NOOP command successful.\r\n");
		}

		else if (!_stricmp(szCmd, "PWD") || !_stricmp(szCmd, "XPWD")) {
			if (!isLoggedIn) {
				SocketSendString(sCmd, "530 Not logged in.\r\n");
			} else {
				sprintf_s(szOutput, "257 \"%s\" is current directory.\r\n", strCurrentVirtual.c_str());
				SocketSendString(sCmd, szOutput);
			}
		}

		else if (!_stricmp(szCmd, "CWD") || !_stricmp(szCmd, "XCWD")) {
			if (!*pszParam) {
				SocketSendString(sCmd, "501 Syntax error in parameters or arguments.\r\n");
			} else if (!isLoggedIn) {
				SocketSendString(sCmd, "530 Not logged in.\r\n");
			} else {
				pVFS->ResolveRelative(strCurrentVirtual.c_str(), pszParam, strNewVirtual);
				if (pVFS->IsFolder(strNewVirtual.c_str())) {
					strCurrentVirtual = strNewVirtual;
					sprintf_s(szOutput, "250 \"%s\" is now current directory.\r\n", strNewVirtual.c_str());
					SocketSendString(sCmd, szOutput);
				} else {
					sprintf_s(szOutput, "550 \"%s\": Path not found.\r\n", strNewVirtual.c_str());
					SocketSendString(sCmd, szOutput);
				}
			}
		}

		else if (!_stricmp(szCmd, "CDUP") || !_stricmp(szCmd, "XCUP")) {
			if (!isLoggedIn) {
				SocketSendString(sCmd, "530 Not logged in.\r\n");
			} else {
				pVFS->ResolveRelative(strCurrentVirtual.c_str(), "..", strNewVirtual);
				strCurrentVirtual = strNewVirtual;
				sprintf_s(szOutput,"250 \"%s\" is now current directory.\r\n", strCurrentVirtual.c_str());
				SocketSendString(sCmd, szOutput);
			}
		}

		else if (!_stricmp(szCmd,"TYPE")) {
			if (!*pszParam) {
				SocketSendString(sCmd, "501 Syntax error in parameters or arguments.\r\n");
			} else if (!isLoggedIn) {
				SocketSendString(sCmd, "530 Not logged in.\r\n");
			} else {
				SocketSendString(sCmd, "200 TYPE command successful.\r\n");
			}
		}

		else if (!_stricmp(szCmd, "REST")) {
			if (!*pszParam || (!(dw = StrToInt(pszParam)) && (*pszParam!='0'))) {
				SocketSendString(sCmd, "501 Syntax error in parameters or arguments.\r\n");
			} else if (!isLoggedIn) {
				SocketSendString(sCmd, "530 Not logged in.\r\n");
			} else {
				dwRestOffset = dw;
				sprintf_s(szOutput, "350 Ready to resume transfer at %u bytes.\r\n", dwRestOffset);
				SocketSendString(sCmd, szOutput);
			}
		}

		else if (!_stricmp(szCmd, "PORT")) {
			if (!*pszParam) {
				SocketSendString(sCmd, "501 Syntax error in parameters or arguments.\r\n");
			} else if (!isLoggedIn) {
				SocketSendString(sCmd, "530 Not logged in.\r\n");
			} else {
				ZeroMemory(&saiData, sizeof(SOCKADDR_IN));
				saiData.sin_family = AF_INET;
				for (dw = 0; dw < 6; dw++) {
					if (dw < 4) ((unsigned char *)&saiData.sin_addr)[dw] = (unsigned char)StrToInt(pszParam);
					else ((unsigned char *)&saiData.sin_port)[dw-4] = (unsigned char)StrToInt(pszParam);
					if (!(pszParam = strchr(pszParam, ','))) break;
					pszParam++;
				}
				if (dw == 5) {
					if (sPasv) {
						closesocket(sPasv);
						sPasv = 0;
					}
					SocketSendString(sCmd, "200 PORT command successful.\r\n");
				} else {
					SocketSendString(sCmd, "501 Syntax error in parameters or arguments.\r\n");
					ZeroMemory(&saiData, sizeof(SOCKADDR_IN));
				}
			}
		}

		else if (!_stricmp(szCmd, "PASV")) {
			if (!isLoggedIn) {
				SocketSendString(sCmd, "530 Not logged in.\r\n");
			} else {
				if (sPasv) closesocket(sPasv);
				ZeroMemory(&saiPasv, sizeof(SOCKADDR_IN));
				saiPasv.sin_family = AF_INET;
				saiPasv.sin_addr.S_un.S_addr = INADDR_ANY;
				saiPasv.sin_port = 0;
				sPasv = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
				bind(sPasv, (SOCKADDR *)&saiPasv, sizeof(SOCKADDR_IN));
				listen(sPasv, 1);
				dw = sizeof(SOCKADDR_IN);
				getsockname(sPasv, (SOCKADDR *)&saiPasv, (int *)&dw);
				sprintf_s(szOutput, "227 Entering Passive Mode (%u,%u,%u,%u,%u,%u)\r\n", saiCmd.sin_addr.S_un.S_un_b.s_b1, saiCmd.sin_addr.S_un.S_un_b.s_b2, saiCmd.sin_addr.S_un.S_un_b.s_b3, saiCmd.sin_addr.S_un.S_un_b.s_b4, ((unsigned char *)&saiPasv.sin_port)[0], ((unsigned char *)&saiPasv.sin_port)[1]);
				SocketSendString(sCmd, szOutput);
			}
		}

		else if (!_stricmp(szCmd, "LIST") || !_stricmp(szCmd, "NLST")) {
			if (!isLoggedIn) {
				SocketSendString(sCmd, "530 Not logged in.\r\n");
			} else {
				if (*pszParam == '-') if (pszParam = strchr(pszParam, ' ')) pszParam++;
				if (pszParam && *pszParam) {
					pVFS->ResolveRelative(strCurrentVirtual.c_str(), pszParam, strNewVirtual);
				}
				else {
					strNewVirtual = strCurrentVirtual;
				}
				if (pPerms->GetPerm(strNewVirtual.c_str(), PERM_LIST) == 1) {
					if (pVFS->GetDirectoryListing(strNewVirtual.c_str(), strcmp(szCmd, "LIST"), listing)) {
						sprintf_s(szOutput, "150 Opening %s mode data connection for listing of \"%s\".\r\n", sPasv ? "passive" : "active", strNewVirtual.c_str());
						SocketSendString(sCmd, szOutput);
						sData = EstablishDataConnection(&saiData, &sPasv);
						if (sData) { 
							for (VFS::listing_type::const_iterator it = listing.begin(); it != listing.end(); ++it) {
								SocketSendString(sData, it->second.c_str());
							}
							listing.clear();
							closesocket(sData);
							sprintf_s(szOutput, "226 %s command successful.\r\n", _stricmp(szCmd, "NLST") ? "LIST" : "NLST");
							SocketSendString(sCmd, szOutput);
						} else {
							listing.clear();
							SocketSendString(sCmd, "425 Can't open data connection.\r\n");
						}
					} else {
						sprintf_s(szOutput, "550 \"%s\": Path not found.\r\n", strNewVirtual.c_str());
						SocketSendString(sCmd, szOutput);
					}
				} else {
					sprintf_s(szOutput, "550 \"%s\": List permission denied.\r\n", strNewVirtual.c_str());
					SocketSendString(sCmd, szOutput);
				}
			}
		}

		else if (!_stricmp(szCmd, "STAT")) {
			if (!isLoggedIn) {
				SocketSendString(sCmd, "530 Not logged in.\r\n");
			} else {
				if (*pszParam == '-') if (pszParam = strchr(pszParam, ' ')) pszParam++;
				if (pszParam && *pszParam) {
					pVFS->ResolveRelative(strCurrentVirtual.c_str(), pszParam, strNewVirtual);
				}
				else {
					strNewVirtual = strCurrentVirtual;
				}
				if (pPerms->GetPerm(strNewVirtual.c_str(), PERM_LIST) == 1) {
					if (pVFS->GetDirectoryListing(strNewVirtual.c_str(), 1, listing)) {
						sprintf_s(szOutput, "212-Sending directory listing of \"%s\".\r\n", strNewVirtual.c_str());
						SocketSendString(sCmd,szOutput);
						for (VFS::listing_type::const_iterator it = listing.begin(); it != listing.end(); ++it) {
							SocketSendString(sCmd, it->second.c_str());
						}
						listing.clear();
						SocketSendString(sCmd, "212 STAT command successful.\r\n");
					} else {
						sprintf_s(szOutput, "550 \"%s\": Path not found.\r\n", strNewVirtual.c_str());
						SocketSendString(sCmd, szOutput);
					}
				} else {
					sprintf_s(szOutput ,"550 \"%s\": List permission denied.\r\n", strNewVirtual.c_str());
					SocketSendString(sCmd, szOutput);
				}
			}
		}

		else if (!_stricmp(szCmd, "RETR")) {
			if (!*pszParam) {
				SocketSendString(sCmd, "501 Syntax error in parameters or arguments.\r\n");
			} else if (!isLoggedIn) {
				SocketSendString(sCmd, "530 Not logged in.\r\n");
			} else {
				pVFS->ResolveRelative(strCurrentVirtual.c_str(), pszParam, strNewVirtual);
				if (pPerms->GetPerm(strNewVirtual.c_str(), PERM_READ) == 1) {
					hFile = pVFS->CreateFile(strNewVirtual.c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, OPEN_EXISTING);
					if (hFile == INVALID_HANDLE_VALUE) {
						sprintf_s(szOutput, "550 \"%s\": Unable to open file.\r\n", strNewVirtual.c_str());
						SocketSendString(sCmd, szOutput);
					} else {
						if (dwRestOffset) {
							SetFilePointer(hFile, dwRestOffset, 0, FILE_BEGIN);
							dwRestOffset = 0;
						}
						sprintf_s(szOutput, "150 Opening %s mode data connection for \"%s\".\r\n", sPasv ? "passive" : "active", strNewVirtual.c_str());
						SocketSendString(sCmd, szOutput);
						sData = EstablishDataConnection(&saiData, &sPasv);
						if (sData) {
							sprintf_s(szOutput, "[%u] User \"%s\" began downloading \"%s\".", sCmd, strUser.c_str(), strNewVirtual.c_str());
							pLog->Log(szOutput);
							if (DoSocketFileIO(sCmd, sData, hFile, SOCKET_FILE_IO_DIRECTION_SEND, &dw)) {
								sprintf_s(szOutput, "226 \"%s\" transferred successfully.\r\n", strNewVirtual.c_str());
								SocketSendString(sCmd, szOutput);
								sprintf_s(szOutput, "[%u] Download completed.", sCmd);
								pLog->Log(szOutput);
							} else {
								SocketSendString(sCmd, "426 Connection closed; transfer aborted.\r\n");
								if (dw) SocketSendString(sCmd, "226 ABOR command successful.\r\n");
								sprintf_s(szOutput, "[%u] Download aborted.", sCmd);
								pLog->Log(szOutput);
							}
							closesocket(sData);
						} else {
							SocketSendString(sCmd,"425 Can't open data connection.\r\n");
						}
						CloseHandle(hFile);
					}
				} else {
					sprintf_s(szOutput, "550 \"%s\": Read permission denied.\r\n", strNewVirtual.c_str());
					SocketSendString(sCmd, szOutput);
				}
			}
		}

		else if (!_stricmp(szCmd, "STOR") || !_stricmp(szCmd, "APPE")) {
			if (!*pszParam) {
				SocketSendString(sCmd,"501 Syntax error in parameters or arguments.\r\n");
			} else if (!isLoggedIn) {
				SocketSendString(sCmd,"530 Not logged in.\r\n");
			} else {
				pVFS->ResolveRelative(strCurrentVirtual.c_str(), pszParam, strNewVirtual);
				if (pPerms->GetPerm(strNewVirtual.c_str(), PERM_WRITE) == 1) {
					hFile = pVFS->CreateFile(strNewVirtual.c_str(), GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, OPEN_ALWAYS);
					if (hFile == INVALID_HANDLE_VALUE) {
						sprintf_s(szOutput, "550 \"%s\": Unable to open file.\r\n", strNewVirtual.c_str());
						SocketSendString(sCmd, szOutput);
					} else {
						if (_stricmp(szCmd, "APPE") == 0) {
							SetFilePointer(hFile, 0, 0, FILE_END);
						}
						else {
							SetFilePointer(hFile, dwRestOffset, 0, FILE_BEGIN);
							SetEndOfFile(hFile);
						}
						dwRestOffset = 0;
						sprintf_s(szOutput, "150 Opening %s mode data connection for \"%s\".\r\n", sPasv ? "passive" : "active", strNewVirtual.c_str());
						SocketSendString(sCmd, szOutput);
						sData = EstablishDataConnection(&saiData, &sPasv);
						if (sData) {
							sprintf_s(szOutput, "[%u] User \"%s\" began uploading \"%s\".", sCmd, strUser.c_str(), strNewVirtual.c_str());
							pLog->Log(szOutput);
							if (DoSocketFileIO(sCmd, sData, hFile, SOCKET_FILE_IO_DIRECTION_RECEIVE, 0)) {
								sprintf_s(szOutput, "226 \"%s\" transferred successfully.\r\n", strNewVirtual.c_str());
								SocketSendString(sCmd, szOutput);
								sprintf_s(szOutput, "[%u] Upload completed.", sCmd);
								pLog->Log(szOutput);
							} else {
								SocketSendString(sCmd, "426 Connection closed; transfer aborted.\r\n");
								sprintf_s(szOutput, "[%u] Upload aborted.", sCmd);
								pLog->Log(szOutput);
							}
							closesocket(sData);
						} else {
							SocketSendString(sCmd,"425 Can't open data connection.\r\n");
						}
						CloseHandle(hFile);
					}
				} else {
					sprintf_s(szOutput, "550 \"%s\": Write permission denied.\r\n", strNewVirtual.c_str());
					SocketSendString(sCmd, szOutput);
				}
			}
		}

		else if (!_stricmp(szCmd, "ABOR")) {
			if (sPasv) {
				closesocket(sPasv);
				sPasv = 0;
			}
			dwRestOffset = 0;
			SocketSendString(sCmd,"200 ABOR command successful.\r\n");
		}

		else if (!_stricmp(szCmd, "SIZE")) {
			if (!*pszParam) {
				SocketSendString(sCmd, "501 Syntax error in parameters or arguments.\r\n");
			} else if (!isLoggedIn) {
				SocketSendString(sCmd, "530 Not logged in.\r\n");
			} else {
				pVFS->ResolveRelative(strCurrentVirtual.c_str(), pszParam, strNewVirtual);
				if (pPerms->GetPerm(strNewVirtual.c_str(), PERM_READ) == 1) {
					hFile = pVFS->CreateFile(strNewVirtual.c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, OPEN_EXISTING);
					if (hFile == INVALID_HANDLE_VALUE) {
						sprintf_s(szOutput, "550 \"%s\": File not found.\r\n", strNewVirtual.c_str());
						SocketSendString(sCmd, szOutput);
					} else {
						sprintf_s(szOutput, "213 %u\r\n", GetFileSize(hFile, 0));
						SocketSendString(sCmd, szOutput);
						CloseHandle(hFile);
					}
				} else {
					sprintf_s(szOutput, "550 \"%s\": Read permission denied.\r\n", strNewVirtual.c_str());
					SocketSendString(sCmd, szOutput);
				}
			}
		}

		else if (!_stricmp(szCmd, "MDTM")) {
			if (!*pszParam) {
				SocketSendString(sCmd, "501 Syntax error in parameters or arguments.\r\n");
			} else if (!isLoggedIn) {
				SocketSendString(sCmd, "530 Not logged in.\r\n");
			} else {
				for (i = 0; i < 14; i++) {
					if ((pszParam[i] < '0') || (pszParam[i] > '9')) {
						break;
					}
				}
				//moving time into output buffer
				if ((i == 14) && (pszParam[14] == ' ')) {
					strncpy_s(szOutput, pszParam, 4);
					szOutput[4] = 0;
					st.wYear = StrToInt(szOutput);
					strncpy_s(szOutput, pszParam + 4, 2);
					szOutput[2] = 0;
					st.wMonth = StrToInt(szOutput);
					strncpy_s(szOutput, pszParam + 6, 2);
					st.wDay = StrToInt(szOutput);
					strncpy_s(szOutput, pszParam + 8, 2);
					st.wHour = StrToInt(szOutput);
					strncpy_s(szOutput, pszParam + 10, 2);
					st.wMinute = StrToInt(szOutput);
					strncpy_s(szOutput, pszParam + 12, 2);
					st.wSecond = StrToInt(szOutput);
					pszParam += 15;
					dw = 1;
				} else {
					dw = 0;
				}
				pVFS->ResolveRelative(strCurrentVirtual.c_str(), pszParam, strNewVirtual);
				if (dw) {
					if (pPerms->GetPerm(strNewVirtual.c_str(), PERM_WRITE) == 1) {
						hFile = pVFS->CreateFile(strNewVirtual.c_str(), GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, OPEN_EXISTING);
						if (hFile == INVALID_HANDLE_VALUE) {
							sprintf_s(szOutput, "550 \"%s\": File not found.\r\n", strNewVirtual.c_str());
							SocketSendString(sCmd, szOutput);
						} else {
							SystemTimeToFileTime(&st, &ft);
							SetFileTime(hFile, 0, 0, &ft);
							CloseHandle(hFile);
							SocketSendString(sCmd, "250 MDTM command successful.\r\n");
						}
					} else {
						sprintf_s(szOutput, "550 \"%s\": Write permission denied.\r\n", strNewVirtual.c_str());
						SocketSendString(sCmd, szOutput);
					}
				} else {
					if (pPerms->GetPerm(strNewVirtual.c_str(), PERM_READ) == 1) {
						hFile = pVFS->CreateFile(strNewVirtual.c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, OPEN_EXISTING);
						if (hFile == INVALID_HANDLE_VALUE) {
							sprintf_s(szOutput, "550 \"%s\": File not found.\r\n", strNewVirtual.c_str());
							SocketSendString(sCmd, szOutput);
						} else {
							GetFileTime(hFile, 0, 0, &ft);
							CloseHandle(hFile);
							FileTimeToSystemTime(&ft, &st);
							sprintf_s(szOutput, "213 %04u%02u%02u%02u%02u%02u\r\n", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
							SocketSendString(sCmd, szOutput);
						}
					} else {
						sprintf_s(szOutput, "550 \"%s\": Read permission denied.\r\n", strNewVirtual.c_str());
						SocketSendString(sCmd, szOutput);
					}
				}
			}
		}

		else if (!_stricmp(szCmd, "DELE")) {
			if (!*pszParam) {
				SocketSendString(sCmd, "501 Syntax error in parameters or arguments.\r\n");
			} else if (!isLoggedIn) {
				SocketSendString(sCmd, "530 Not logged in.\r\n");
			} else {
				pVFS->ResolveRelative(strCurrentVirtual.c_str(), pszParam, strNewVirtual);
				if (pPerms->GetPerm(strNewVirtual.c_str(), PERM_ADMIN) == 1) {
					if (pVFS->FileExists(strNewVirtual.c_str())) {
						if (pVFS->DeleteFile(strNewVirtual.c_str())) {
							sprintf_s(szOutput, "250 \"%s\" deleted successfully.\r\n", strNewVirtual.c_str());
							SocketSendString(sCmd, szOutput);
							sprintf_s(szOutput, "[%u] User \"%s\" deleted \"%s\".", sCmd, strUser.c_str(), strNewVirtual.c_str());
							pLog->Log(szOutput);
						} else {
							sprintf_s(szOutput, "550 \"%s\": Unable to delete file.\r\n", strNewVirtual.c_str());
							SocketSendString(sCmd, szOutput);
						}
					} else {
						sprintf_s(szOutput, "550 \"%s\": File not found.\r\n", strNewVirtual.c_str());
						SocketSendString(sCmd, szOutput);
					}
				} else {
					sprintf_s(szOutput, "550 \"%s\": Admin permission denied.\r\n", strNewVirtual.c_str());
					SocketSendString(sCmd,szOutput);
				}
			}
		}

		else if (!_stricmp(szCmd, "RNFR")) {
			if (!*pszParam) {
				SocketSendString(sCmd, "501 Syntax error in parameters or arguments.\r\n");
			} else if (!isLoggedIn) {
				SocketSendString(sCmd, "530 Not logged in.\r\n");
			} else {
				pVFS->ResolveRelative(strCurrentVirtual.c_str(), pszParam, strNewVirtual);
				if (pPerms->GetPerm(strNewVirtual.c_str(), PERM_ADMIN) == 1) {
					if (pVFS->FileExists(strNewVirtual.c_str())) {
						strRnFr = strNewVirtual;
						sprintf_s(szOutput, "350 \"%s\": File exists; proceed with RNTO.\r\n", strNewVirtual.c_str());
						SocketSendString(sCmd, szOutput);
					} else {
						sprintf_s(szOutput, "550 \"%s\": File not found.\r\n", strNewVirtual.c_str());
						SocketSendString(sCmd, szOutput);
					}
				} else {
					sprintf_s(szOutput, "550 \"%s\": Admin permission denied.\r\n", strNewVirtual.c_str());
					SocketSendString(sCmd, szOutput);
				}
			}
		}

		else if (!_stricmp(szCmd, "RNTO")) {
			if (!*pszParam) {
				SocketSendString(sCmd, "501 Syntax error in parameters or arguments.\r\n");
			} else if (!isLoggedIn) {
				SocketSendString(sCmd, "530 Not logged in.\r\n");
			} else if (strRnFr.length() == 0) {
				SocketSendString(sCmd, "503 Bad sequence of commands. Send RNFR first.\r\n");
			} else {
				pVFS->ResolveRelative(strCurrentVirtual.c_str(), pszParam, strNewVirtual);
				if (pPerms->GetPerm(strNewVirtual.c_str(), PERM_ADMIN) == 1) {
					if (pVFS->MoveFile(strRnFr.c_str(), strNewVirtual.c_str())) {
						SocketSendString(sCmd, "250 RNTO command successful.\r\n");
						sprintf_s(szOutput, "[%u] User \"%s\" renamed \"%s\" to \"%s\".", sCmd, strUser.c_str(), strRnFr.c_str(), strNewVirtual.c_str());
						pLog->Log(szOutput);
						strRnFr.clear();
					} else {
						sprintf_s(szOutput, "553 \"%s\": Unable to rename file.\r\n", strNewVirtual.c_str());
						SocketSendString(sCmd, szOutput);
					}
				} else {
					SocketSendString(sCmd, "550 Admin permission denied.\r\n");
				}
			}
		}

		else if (!_stricmp(szCmd, "MKD") || !_stricmp(szCmd, "XMKD")) {
			if (!*pszParam) {
				SocketSendString(sCmd, "501 Syntax error in parameters or arguments.\r\n");
			} else if (!isLoggedIn) {
				SocketSendString(sCmd, "530 Not logged in.\r\n");
			} else {
				pVFS->ResolveRelative(strCurrentVirtual.c_str(), pszParam, strNewVirtual);
				if (pPerms->GetPerm(strNewVirtual.c_str(), PERM_WRITE) == 1) {
					if (pVFS->CreateDirectory(strNewVirtual.c_str())) {
						sprintf_s(szOutput, "250 \"%s\" created successfully.\r\n", strNewVirtual.c_str());
						SocketSendString(sCmd, szOutput);
						sprintf_s(szOutput, "[%u] User \"%s\" created directory \"%s\".", sCmd, strUser.c_str(), strNewVirtual.c_str());
						pLog->Log(szOutput);
					} else {
						sprintf_s(szOutput, "550 \"%s\": Unable to create directory.\r\n", strNewVirtual.c_str());
						SocketSendString(sCmd, szOutput);
					}
				} else {
					sprintf_s(szOutput, "550 \"%s\": Write permission denied.\r\n", strNewVirtual.c_str());
					SocketSendString(sCmd, szOutput);
				}
			}
		}

		else if (!_stricmp(szCmd, "RMD") || !_stricmp(szCmd, "XRMD")) {
			if (!*pszParam) {
				SocketSendString(sCmd, "501 Syntax error in parameters or arguments.\r\n");
			} else if (!isLoggedIn) {
				SocketSendString(sCmd, "530 Not logged in.\r\n");
			} else {
				pVFS->ResolveRelative(strCurrentVirtual.c_str(), pszParam, strNewVirtual);
				if (pPerms->GetPerm(strNewVirtual.c_str(), PERM_ADMIN) == 1) {
					if (pVFS->RemoveDirectory(strNewVirtual.c_str())) {
						sprintf_s(szOutput, "250 \"%s\" removed successfully.\r\n", strNewVirtual.c_str());
						SocketSendString(sCmd, szOutput);
						sprintf_s(szOutput, "[%u] User \"%s\" removed directory \"%s\".", sCmd, strUser.c_str(), strNewVirtual.c_str());
						pLog->Log(szOutput);
					} else {
						sprintf_s(szOutput, "550 \"%s\": Unable to remove directory.\r\n", strNewVirtual.c_str());
						SocketSendString(sCmd, szOutput);
					}
				} else {
					sprintf_s(szOutput, "550 \"%s\": Admin permission denied.\r\n", strNewVirtual.c_str());
					SocketSendString(sCmd, szOutput);
				}
			}
		}

		else {
			sprintf_s(szOutput,"500 Syntax error, command \"%s\" unrecognized.\r\n",szCmd);
			SocketSendString(sCmd,szOutput);
		}

	}

	if (sPasv) closesocket(sPasv);
	closesocket(sCmd);

	if (isLoggedIn) {
		dwActiveConnections--;
	}

	sprintf_s(szOutput,"[%u] Connection closed.",sCmd);
	pLog->Log(szOutput);

	return false;
}

bool SocketSendString(SOCKET s, const char *psz)
{
	if (send(s,psz,(INT)strlen(psz),0)==SOCKET_ERROR) return false;
	else return true;
}

DWORD SocketReceiveString(SOCKET s, char *psz, DWORD dwMaxChars)
{
	DWORD dw, dwBytes;
	TIMEVAL tv;
	fd_set fds;

	tv.tv_sec=dwCommandTimeout;
	tv.tv_usec=0;
	for (dwBytes=0;;dwBytes++) {
		FD_ZERO(&fds);
		FD_SET(s,&fds);
		dw=select(0,&fds,0,0,&tv);
		if (dw==SOCKET_ERROR || dw==0) return -1; // Timeout
		dw=recv(s,psz,1,0);
		if (dw==SOCKET_ERROR || dw==0) return -1; // Network error
		if (*psz=='\r') *psz=0;
		else if (*psz=='\n') {
			*psz=0;
			return dwBytes;
		}
		if (dwBytes<dwMaxChars) psz++;
	}
}

DWORD SocketReceiveData(SOCKET s, char *psz, DWORD dwBytesToRead)
{
	DWORD dw;
	TIMEVAL tv;
	fd_set fds;

	tv.tv_sec=dwConnectTimeout;
	tv.tv_usec=0;
	FD_ZERO(&fds);
	FD_SET(s,&fds);
	dw=select(0,&fds,0,0,&tv);
	if (dw==SOCKET_ERROR || dw==0) return -1; // Timeout
	dw=recv(s,psz,dwBytesToRead,0);
	if (dw==SOCKET_ERROR) return -1; // Network error
	return dw;
}

SOCKET EstablishDataConnection(SOCKADDR_IN *psaiData, SOCKET *psPasv)
{
	SOCKET sData;
	DWORD dw;
	TIMEVAL tv;
	fd_set fds;

	if (psPasv && *psPasv) {
		tv.tv_sec=dwConnectTimeout;
		tv.tv_usec=0;
		FD_ZERO(&fds);
		FD_SET(*psPasv,&fds);
		dw=select(0,&fds,0,0,&tv);
		if (dw && dw!=SOCKET_ERROR) {
			dw=sizeof(SOCKADDR_IN);
			sData=accept(*psPasv,(SOCKADDR *)psaiData,(int *)&dw);
		} else {
			sData=0;
		}
		closesocket(*psPasv);
		*psPasv=0;
		return sData;
	} else {
		sData=socket(AF_INET,SOCK_STREAM, IPPROTO_TCP);
		if (connect(sData,(SOCKADDR *)psaiData,sizeof(SOCKADDR_IN))) {
			closesocket(sData);
			return false;
		} else {
			return sData;
		}
	}
}

void LookupHost(IN_ADDR ia, char *pszHostName, size_t stHostName)
// Performs a reverse DNS lookup on ia. If no host name could be resolved, or
// if LookupHosts is Off, pszHostName will contain a string representation of
// the given IP address.
{
	HOSTENT *phe;

	if (bLookupHosts) {
		phe = gethostbyaddr((const char *)&ia, sizeof(IN_ADDR), AF_INET);
		if (phe) strcpy_s(pszHostName, stHostName, phe->h_name);
	}
	if (!bLookupHosts || !phe) {
		strcpy_s(pszHostName, stHostName, inet_ntoa(ia));
	}
}

bool DoSocketFileIO(SOCKET sCmd, SOCKET sData, HANDLE hFile, DWORD dwDirection, DWORD *pdwAbortFlag)
{
	char szBuffer[PACKET_SIZE];
	DWORD dw;

	if (pdwAbortFlag) *pdwAbortFlag = 0;
	switch (dwDirection) {
	case SOCKET_FILE_IO_DIRECTION_SEND:
		for (;;) {
			if (!ReadFile(hFile, szBuffer, PACKET_SIZE, &dw, 0)) return false;
			if (!dw) return true;
			if (send(sData, szBuffer, dw, 0) == SOCKET_ERROR) return false;
			ioctlsocket(sCmd, FIONREAD, &dw);
			if (dw) {
				SocketReceiveString(sCmd, szBuffer, 511);
				if (!_stricmp(szBuffer, "ABOR")) {
					*pdwAbortFlag = 1;
					return false;
				} else {
					SocketSendString(sCmd, "500 Only command allowed at this time is ABOR.\r\n");
				}
			}
		}
		break;
	case SOCKET_FILE_IO_DIRECTION_RECEIVE:
		for (;;) {
			dw = SocketReceiveData(sData, szBuffer, PACKET_SIZE);
			if (dw == -1) return false;
			if (dw == 0) return true;
			if (!WriteFile(hFile, szBuffer, dw, &dw, 0)) return false;
		}
		break;
	default:
		return false;
	}
}

DWORD FileReadLine(HANDLE hFile, char *pszBuf, DWORD dwBufLen)
{
// Reads a line from an open text file into a character buffer, discarding the
// trailing CR/LF, up to dwBufLen bytes. Any additional bytes are discarded.
// Returns the number of characters in the line, excluding the CR/LF, or -1 if
// the end of the file was reached. May be greater than dwBufLen to indicate
// that bytes were discarded. Note that a return value of 0 does not
// necessarily indicate an error; it could mean a blank line was read.

	DWORD dw, dwBytesRead, dwCount;

	for (dwCount=0;;) {
		dw=ReadFile(hFile,pszBuf,1,&dwBytesRead,0);
		if (!dw || (dw && !dwBytesRead && !dwCount)) return -1;
		if (!dwBytesRead || *pszBuf=='\n') break;
		if (*pszBuf!='\r') {
			dwCount++;
			if (dwCount<dwBufLen) pszBuf++;
		}
	}
	*pszBuf=0;

	return dwCount;
}

DWORD SplitTokens(char *pszIn)
{
// Processes a string into a null-separated list of its tokens. A quoted
// substring will be treated as a single token. Backslashes may be used to
// escape special characters within quoted substrings.
// Returns the number of tokens split from the string.

	DWORD dwCount=0;
	char *pszOut;

	pszOut=pszIn;
	while (*pszIn==' ' || *pszIn=='\t') pszIn++;
	while (*pszIn) {
		dwCount++;
		if (*pszIn=='"') {
			pszIn++;
			for (;;pszOut++,pszIn++) {
				if (*pszIn=='\\') {
					pszIn++;
					if (*pszIn=='n') *pszIn='\n';
					else if (*pszIn=='r') *pszIn='\r';
					else if (*pszIn=='t') *pszIn='\t';
					*pszOut=*pszIn;
					continue;
				} else if (!*pszIn || *pszIn=='"') {
					break;
				} else {
					*pszOut=*pszIn;
				}
			}
			pszIn++;
		} else {
			do {
				*pszOut=*pszIn;
				pszOut++;
				pszIn++;
			} while (*pszIn && *pszIn!=' ' && *pszIn!='\t');
		}
		while (*pszIn==' ' || *pszIn=='\t') pszIn++;
		*pszOut=0;
		pszOut++;
	}
	*pszOut=0;
	return dwCount;
}

const char *GetToken(const char *pszTokens, DWORD dwToken) {
// Returns a pointer to the one-based dwToken'th null-separated token in
// pszTokens.

	DWORD dw;

	for (dw=1;dw<dwToken;dw++,pszTokens++) {
		pszTokens+=strlen(pszTokens);
	}
	return pszTokens;
}

DWORD GetIPAddressType(IN_ADDR ia)
// Returns one of the predefined IP address types, according to ia.
{
	if (((ia.S_un.S_un_b.s_b1 == 192) && (ia.S_un.S_un_b.s_b2 == 168)) || ((ia.S_un.S_un_b.s_b1 == 169) && (ia.S_un.S_un_b.s_b2 == 254)) || (ia.S_un.S_un_b.s_b1 == 10)) {
		return IP_ADDRESS_TYPE_LAN;
	} else if ((ia.S_un.S_un_b.s_b1 == 127) && (ia.S_un.S_un_b.s_b2 == 0) && (ia.S_un.S_un_b.s_b3 == 0) && (ia.S_un.S_un_b.s_b4 == 1)) {
		return IP_ADDRESS_TYPE_LOCAL;
	} else {
		return IP_ADDRESS_TYPE_WAN;
	}
}

inline bool CanUserLogin(const char *pszUser, IN_ADDR iaPeer)
{
	return (dwActiveConnections < dwMaxConnections);
}




