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

#ifdef GML_MAT4F_SSE

extern "C" int MATMul(const _mat4<float>*, const _mat4<float>*, _mat4<float>*);

_mat4<float> _mat4<float>::Multiply(const _mat4<float>& other) const {
	_mat4<float> res;

	__m128 c0 = _mm_load_ps(other.data);
	__m128 c1 = _mm_load_ps(other.data + 4);
	__m128 c2 = _mm_load_ps(other.data + 8);
	__m128 c3 = _mm_load_ps(other.data + 12);

	for (int i = 0; i < 4; i++) {
		__m128 r = _mm_set_ps(data[3 * 4 + i], data[2 * 4 + i], data[1 * 4 + i], data[0 * 4 + i]);

		res.data[0 * 4 + i] = _mm_dp_ps(r, c0, 0xFF).m128_f32[0];
		res.data[1 * 4 + i] = _mm_dp_ps(r, c1, 0xFF).m128_f32[0];
		res.data[2 * 4 + i] = _mm_dp_ps(r, c2, 0xFF).m128_f32[0];
		res.data[3 * 4 + i] = _mm_dp_ps(r, c3, 0xFF).m128_f32[0];
	}

	
	return res;
}


_vec4<float> _mat4<float>::Multiply(const _vec4<float>& other) const {
	__m128 col0 = _mm_load_ps(data);
	__m128 col1 = _mm_load_ps(data + 16);
	__m128 col2 = _mm_load_ps(data + 32);
	__m128 col3 = _mm_load_ps(data + 48);

	__m128 res = _mm_mul_ps(col0, _mm_set_ps1(other.x));
	res = _mm_fmadd_ps(col1, _mm_set_ps1(other.y), res);
	res = _mm_fmadd_ps(col2, _mm_set_ps1(other.z), res);
	res = _mm_fmadd_ps(col3, _mm_set_ps1(other.w), res);

	_vec4<float> tmp;

	_mm_store_ps(&tmp.x, res);

	return tmp;
}

#endif