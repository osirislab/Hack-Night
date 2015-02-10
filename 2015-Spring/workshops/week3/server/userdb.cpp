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

#include "userdb.h"

#include "tree.cpp"

bool UserDB::Add(const char *pszUsername)
{
	if (_users.find(pszUsername) == _users.end()) {
		_users.insert(std::make_pair(pszUsername, USERDBRECORD()));
		return true;
	} else {
		return false;
	}
}

bool UserDB::SetPassword(const char *pszUsername, const char *pszPassword)
{
	map_type::iterator it = _users.find(pszUsername);
	if (it != _users.end()) {
		it->second.strPassword = pszPassword;
		return true;
	}
	return false;
}

VFS * UserDB::GetVFS(const char *pszUsername)
{
	map_type::iterator it = _users.find(pszUsername);
	if (it != _users.end()) {
		return &it->second.vfs;
	}
	return NULL;
}

PermDB * UserDB::GetPermDB(const char *pszUsername)
{
	map_type::iterator it = _users.find(pszUsername);
	if (it != _users.end()) {
		return &it->second.perms;
	}
	return NULL;
}

bool UserDB::CheckPassword(const char *pszUsername, const char *pszPassword)
{
	map_type::iterator it = _users.find(pszUsername);
	//ensure user exists and compare his password to the provided one
	return (it != _users.end()) && (it->second.strPassword == pszPassword);
}
