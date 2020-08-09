/*
MIT License

Copyright (c) 2020 Jesper

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once

#include "mat4.h"

namespace gml {

template<typename T = float>
_mat4<T> Translate(const _vec3<T>& translation) {
	_mat4<T> res(1);
	
	res.Set(0, 3, translation.x);
	res.Set(1, 3, translation.y);
	res.Set(2, 3, translation.z);
	res.Set(3, 3, 1);

	return res;
}

template<typename T = float>
_mat4<T> Scale(const _vec3<T>& other) {
	_mat4<T> res(1);

	res.Set(0, 0, other.x);
	res.Set(1, 1, other.y);
	res.Set(2, 2, other.z);

	return res;
}

}