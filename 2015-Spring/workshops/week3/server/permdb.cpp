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

#include "permdb.h"
#include "tree.h"
#include "tree.cpp"

PermDB::PermDB()
{
	_root._data.dwPerms[PERM_READ] = 0;
	_root._data.dwPerms[PERM_WRITE] = 0;
	_root._data.dwPerms[PERM_LIST] = 0;
	_root._data.dwPerms[PERM_ADMIN] = 0;
}

void PermDB::SetPerm(const char *pszVirtual, DWORD dwPermId, DWORD dwStatus)
{
	tree<FTPPERM> *ptree, *pparent;
	char sz[512], *psz, *pszCut;

	ptree = &_root;
	strcpy_s(sz, pszVirtual + 1);
	psz = sz;
	while (*psz) {
		if (pszCut = strchr(psz, '/')) *pszCut = 0;
		pparent = ptree;
		ptree = ptree->_pdown;
		while (ptree && _stricmp(ptree->_data.strVirtual.c_str(), psz)) ptree = ptree->_pright;
		if (!ptree) {
			ptree=new tree<FTPPERM>(pparent);
			ptree->_data.strVirtual = psz;
			ptree->_data.dwPerms[PERM_READ] = -1;
			ptree->_data.dwPerms[PERM_WRITE] = -1;
			ptree->_data.dwPerms[PERM_LIST] = -1;
			ptree->_data.dwPerms[PERM_ADMIN] = -1;
		}
		if (!pszCut) break;
		psz = pszCut + 1;
	}
	ptree->_data.strVirtual = psz;
	ptree->_data.dwPerms[dwPermId] = dwStatus;
}

DWORD PermDB::GetPerm(const char *pszVirtual, DWORD dwPermId)
{
	return GetPermFunc(pszVirtual, dwPermId, &_root);
}

DWORD PermDB::GetPermFunc(const char *pszVirtual, DWORD dwPermId, tree<FTPPERM> *ptree)
{
	const char *psz;
	DWORD dw;
	UINT_PTR dwLen;

	psz = strchr(pszVirtual, '/');
	if (psz) dwLen = psz - pszVirtual;
	else dwLen = strlen(pszVirtual);
	while (ptree) {
		if ((ptree->_data.strVirtual.length() == dwLen) && (!dwLen || !_strnicmp(pszVirtual, ptree->_data.strVirtual.c_str(), dwLen))) {
			if (psz) {
				dw = GetPermFunc(psz + 1, dwPermId, ptree->_pdown);
				if (dw != -1) return dw;
				else return ptree->_data.dwPerms[dwPermId];
			} else {
				return ptree->_data.dwPerms[dwPermId];
			}
		} else {
			ptree = ptree->_pright;
		}
	}
	return -1;
}
