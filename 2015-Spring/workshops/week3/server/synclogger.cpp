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

#include "synclogger.h"

SyncLogger::SyncLogger(const char *pszFilename)
{
	_hLogFile=CreateFile(pszFilename,GENERIC_WRITE,FILE_SHARE_READ,0,OPEN_ALWAYS,0,0);
	if (_hLogFile) {
		SetFilePointer(_hLogFile,0,0,FILE_END);
		_hLoggerThread=CreateThread(0,0,(LPTHREAD_START_ROUTINE)SyncLoggerThread,this,0,&_dwLoggerThreadId);
	}
}

SyncLogger::~SyncLogger()
{
	if (_hLoggerThread) {
		PostThreadMessage(_dwLoggerThreadId,WM_QUIT,0,0);
		WaitForSingleObject(_hLoggerThread,INFINITE);
		CloseHandle(_hLoggerThread);
	}
	if (_hLogFile) CloseHandle(_hLogFile);
}

void SyncLogger::Log(const char *pszText)
{
	char *psz;
	DWORD dwDateLen, dwTimeLen;

	if (_hLogFile && _dwLoggerThreadId && pszText) {
		dwDateLen=GetDateFormat(LOCALE_SYSTEM_DEFAULT,DATE_SHORTDATE,0,0,0,0);
		dwTimeLen=GetTimeFormat(LOCALE_SYSTEM_DEFAULT,0,0,0,0,0);
		size_t buflen = dwDateLen+dwTimeLen+strlen(pszText)+5;
		psz=new char[buflen];
		psz[0]='[';
		GetDateFormat(LOCALE_SYSTEM_DEFAULT,DATE_SHORTDATE,0,0,psz+1,dwDateLen);
		psz[dwDateLen]=' ';//1
		GetTimeFormat(LOCALE_SYSTEM_DEFAULT,0,0,0,psz+dwDateLen+1,dwTimeLen);
		strcat_s(psz, buflen, "] ");//2
		strcat_s(psz, buflen, pszText);
		strcat_s(psz, buflen, "\r\n");//4
		while (!PostThreadMessage(_dwLoggerThreadId,WM_USER,0,(LPARAM)psz)) Sleep(0);
	}
}

DWORD WINAPI SyncLogger::SyncLoggerThread(SyncLogger *pthis)
{
	MSG msg;
	DWORD dw;

	PeekMessage(&msg,0,0,0,PM_NOREMOVE);
	while (GetMessage(&msg,0,0,0)) {
		switch (msg.message) {
		case WM_USER:
			WriteFile(pthis->_hLogFile, (char *)msg.lParam, (DWORD)strlen((char *)msg.lParam), &dw, 0);
			delete (char *)msg.lParam;
		}
	}

	return 0;
}
