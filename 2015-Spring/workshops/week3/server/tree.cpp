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

template <class T>
tree<T>::tree()
{
	_pup=0;
	_pleft=0;
	_pright=0;
	_pdown=0;
}

template <class T>
tree<T>::tree(tree *pparent)
{
	if (pparent->_pdown) {
		_pleft=pparent->_pdown;
		while (_pleft->_pright) _pleft=_pleft->_pright;
		_pleft->_pright=this;
	} else {
		pparent->_pdown=this;
		_pleft=0;
	}
	_pup=pparent;
	_pright=0;
	_pdown=0;
}

template <class T>
tree<T>::~tree()
{
	while (_pdown) delete _pdown;
	if (_pleft) _pleft->_pright=_pright;
	if (_pright) _pright->_pleft=_pleft;
	if (_pup && _pup->_pdown==this) _pup->_pdown=_pright;
}
