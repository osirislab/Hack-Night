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

#ifndef _INCL_VFS_H
#define _INCL_VFS_H

#include <windows.h>
#include <map>
#include <string>
#include "tree.h"

using namespace std;

class VFS
{
private:
	struct MOUNTPOINT {
		string strVirtual;
		string strLocal;
	};
	struct FINDDATA {
		string strVirtual;
		string strFilespec;
		HANDLE hFind;
		tree<MOUNTPOINT> *ptree;
	};

	tree<MOUNTPOINT> _root;

	static DWORD Map(const char *pszVirtual, string &strLocal, tree<MOUNTPOINT> *ptree);
	static tree<MOUNTPOINT> * FindMountPoint(const char *pszVirtual, tree<MOUNTPOINT> *ptree);
	static bool WildcardMatch(const char *pszFilespec, const char *pszFilename);
	static void GetMountPointFindData(tree<MOUNTPOINT> *ptree, WIN32_FIND_DATA *pw32fd);

public:
	typedef map<string, string> listing_type;
	VFS();
	void Mount(const char *pszVirtual, const char *pszLocal);
	DWORD GetDirectoryListing(const char *pszVirtual, DWORD dwIsNLST, listing_type &listing);
	bool FileExists(const char *pszVirtual);
	bool IsFolder(const char *pszVirtual);
	LPVOID FindFirstFile(const char *pszVirtual, WIN32_FIND_DATA *pw32fd);
	bool FindNextFile(LPVOID lpFindHandle, WIN32_FIND_DATA *pw32fd);
	void FindClose(LPVOID lpFindHandle);
	HANDLE CreateFile(const char *pszVirtual, DWORD dwDesiredAccess, DWORD dwShareMode, DWORD dwCreationDisposition);
	BOOL DeleteFile(const char *pszVirtual);
	BOOL MoveFile(const char *pszOldVirtual, const char *pszNewVirtual);
	BOOL CreateDirectory(const char *pszVirtual);
	BOOL RemoveDirectory(const char *pszVirtual);
	static void CleanVirtualPath(const char *pszVirtual, string &strNewVirtual);
	static void ResolveRelative(const char *pszCurrentVirtual, const char *pszRelativeVirtual, string &strNewVirtual);
	static void strtr(char *psz, char cFrom, char cTo);
};

#endif