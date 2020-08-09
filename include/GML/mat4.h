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
#include <memory>

namespace gml {

template<typename T>
class alignas(64) _mat4 {
public:
	T data[16];

	_mat4() = default;
	_mat4(T diagonal) {
		memset(data, 0, sizeof(data));
		data[0] = diagonal;
		data[5] = diagonal;
		data[10] = diagonal;
		data[15] = diagonal;
	}

	inline T Get(size_t col, size_t row) const { return data[col * 4 + row]; }
	inline void Set(size_t col, size_t row, T value) { data[col * 4 + row] = value; }

	_mat4<T> Multiply(const _mat4<T>& other) const
	{
		_mat4<T> res;

		for (int r = 0; r < 4; r++) {
			for (int c = 0; c < 4; c++) {
				T r0 = data[0 * 4 + r] * other.data[c * 4 + 0];
				T r1 = data[1 * 4 + r] * other.data[c * 4 + 1];
				T r2 = data[2 * 4 + r] * other.data[c * 4 + 2];
				T r3 = data[3 * 4 + r] * other.data[c * 4 + 3];

				res.data[r * 4 + c] = (r0 + r1) + (r2 + r3);
			}
		}

		return res;
	}

	_vec4<T> Multiply(const _vec4<T>& other) const {
		T x = Get(0, 0) * other.x + Get(1, 0) * other.y + Get(2, 0) * other.z + Get(3, 0) * other.w;
		T y = Get(0, 1) * other.x + Get(1, 1) * other.y + Get(2, 1) * other.z + Get(3, 1) * other.w;
		T z = Get(0, 2) * other.x + Get(1, 2) * other.y + Get(2, 2) * other.z + Get(3, 2) * other.w;
		T w = Get(0, 3) * other.x + Get(1, 3) * other.y + Get(2, 3) * other.z + Get(3, 3) * other.w;

		return _vec4<T>(x, y, z, w);
	}

	_mat4<T> operator*(const _mat4<T>& other) const { return Multiply(other); }
	_vec4<T> operator*(const _vec4<T>& other) const { return Multiply(other); }

	inline T& operator[](size_t index) { return data[index]; }
	inline T operator[](size_t index) const { return data[index]; }
};

#ifdef GML_MAT4_SSE
#define GML_MAT4F_SSE
#endif

#include "impl/mat4f.h"

typedef _mat4<float> mat4;

}