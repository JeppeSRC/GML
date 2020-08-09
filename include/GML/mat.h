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
#include <type_traits>

namespace gml {

template<typename T = float>
_mat4<T> Translate(const _vec3<T>& translation) {
	_mat4<T> res(1);
	
	res.Set(3, 0, translation.x);
	res.Set(3, 1, translation.y);
	res.Set(3, 2, translation.z);
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

template<typename T = float>
_mat4<T> RotateX(T angle) {
	_mat4<T> res(1);

	T xcos, xsin;

	if constexpr (std::is_same_v<T, double>) {
		xcos = cos(angle);
		xsin = sin(angle);
	} else {
		xcos = cosf(angle);
		xsin = sinf(angle);
	}

	res.Set(1, 1, xcos);
	res.Set(1, 2, xsin);
	res.Set(2, 1, -xsin);
	res.Set(2, 2, xcos);

	return res;
}

template<typename T = float>
_mat4<T> RotateY(T angle) {
	_mat4<T> res(1);

	T ycos, ysin;

	if constexpr (std::is_same_v<T, double>) {
		ycos = cos(angle);
		ysin = sin(angle);
	} else {
		ycos = cosf(angle);
		ysin = sinf(angle);
	}

	res.Set(0, 0, ycos);
	res.Set(0, 2, ysin);
	res.Set(2, 0, -ysin);
	res.Set(2, 2, ycos);

	return res;
}

template<typename T = float>
_mat4<T> RotateZ(T angle) {
	_mat4<T> res(1);

	T zcos, zsin;

	if constexpr (std::is_same_v<T, double>) {
		zcos = cos(angle);
		zsin = sin(angle);
	} else {
		zcos = cosf(angle);
		zsin = sinf(angle);
	}

	res.Set(0, 0, zcos);
	res.Set(0, 1, zsin);
	res.Set(1, 0, -zsin);
	res.Set(1, 1, zcos);

	return res;
}

template<typename T = float>
_mat4<T> Rotate(const _vec3<T>& rotation) {
	return RotateX(rotation.x) * RotateY(rotation.y) * RotateZ(rotation.z);
}

}