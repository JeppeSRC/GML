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


#ifdef GML_VEC3I_SSE

_vec3<int>& _vec3<int>::Add(const _vec3<int>& other) {
	__m128i mask = _mm_set_epi32(0, -1, -1, -1);
	__m128i v1, v2;

	constexpr int alignment = alignof(t) % 16 == 0;

	if constexpr (alignment) {
		v1 = _mm_load_si128((const __m128i*) & x);
		v2 = _mm_load_si128((const __m128i*) & other.x);
	} else {
		v1 = _mm_maskload_epi32(&x, mask);
		v2 = _mm_maskload_epi32(&other.x, mask);
	}

	__m128i res = _mm_add_epi32(v1, v2);

	if constexpr (alignment) {
		_mm_store_si128((__m128i*) & x, res);
	} else {
		_mm_maskstore_epi32(&x, mask, res);
	}

	return *this;
}

_vec3<int>& _vec3<int>::Sub(const _vec3<int>& other) {
	__m128i mask = _mm_set_epi32(0, -1, -1, -1);
	__m128i v1, v2;

	constexpr int alignment = alignof(t) % 16 == 0;

	if constexpr (alignment) {
		v1 = _mm_load_si128((const __m128i*) & x);
		v2 = _mm_load_si128((const __m128i*) & other.x);
	} else {
		v1 = _mm_maskload_epi32(&x, mask);
		v2 = _mm_maskload_epi32(&other.x, mask);
	}

	__m128i res = _mm_sub_epi32(v1, v2);

	if constexpr (alignment) {
		_mm_store_si128((__m128i*) & x, res);
	} else {
		_mm_maskstore_epi32(&x, mask, res);
	}

	return *this;
}

_vec3<int>& _vec3<int>::Mul(const _vec3<int>& other) {
	__m128i mask = _mm_set_epi32(0, -1, -1, -1);
	__m128i v1, v2;

	constexpr int alignment = alignof(t) % 16 == 0;

	if constexpr (alignment) {
		v1 = _mm_load_si128((const __m128i*) & x);
		v2 = _mm_load_si128((const __m128i*) & other.x);
	} else {
		v1 = _mm_maskload_epi32(&x, mask);
		v2 = _mm_maskload_epi32(&other.x, mask);
	}

	__m128i res = _mm_mul_epi32(v1, v2);

	if constexpr (alignment) {
		_mm_store_si128((__m128i*) & x, res);
	} else {
		_mm_maskstore_epi32(&x, mask, res);
	}

	return *this;
}

_vec3<int>& _vec3<int>::Div(const _vec3<int>& other) {
	__m128i mask = _mm_set_epi32(0, -1, -1, -1);
	__m128i v1, v2;

	constexpr int alignment = alignof(t) % 16 == 0;

	if constexpr (alignment) {
		v1 = _mm_load_si128((const __m128i*) & x);
		v2 = _mm_load_si128((const __m128i*) & other.x);
	} else {
		v1 = _mm_maskload_epi32(&x, mask);
		v2 = _mm_maskload_epi32(&other.x, mask);
	}

	__m128i res = _mm_div_epi32(v1, v2);

	if constexpr (alignment) {
		_mm_store_si128((__m128i*) & x, res);
	} else {
		_mm_maskstore_epi32(&x, mask, res);
	}

	return *this;
}

_vec3<int>& _vec3<int>::Add(int other) {
	__m128i mask = _mm_set_epi32(0, -1, -1, -1);
	__m128i v1;

	constexpr bool alignment = alignof(t) % 16 == 0;

	if constexpr (alignment) {
		v1 = _mm_load_si128((__m128i*) & x);
	} else {
		v1 = _mm_maskload_epi32(&x, mask);
	}

	__m128i v2 = _mm_set1_epi32(other);
	__m128i res = _mm_add_epi32(v1, v2);

	if constexpr (alignment) {
		_mm_store_si128((__m128i*) & x, res);;
	} else {
		_mm_maskstore_epi32(&x, mask, res);
	}

	return *this;
}

_vec3<int>& _vec3<int>::Sub(int other) {
	__m128i mask = _mm_set_epi32(0, -1, -1, -1);
	__m128i v1;

	constexpr bool alignment = alignof(t) % 16 == 0;

	if constexpr (alignment) {
		v1 = _mm_load_si128((__m128i*) & x);
	} else {
		v1 = _mm_maskload_epi32(&x, mask);
	}

	__m128i v2 = _mm_set1_epi32(other);
	__m128i res = _mm_sub_epi32(v1, v2);

	if constexpr (alignment) {
		_mm_store_si128((__m128i*) & x, res);
	} else {
		_mm_maskstore_epi32(&x, mask, res);
	}

	return *this;
}

_vec3<int>& _vec3<int>::Mul(int other) {
	__m128i mask = _mm_set_epi32(0, -1, -1, -1);
	__m128i v1;

	constexpr bool alignment = alignof(t) % 16 == 0;

	if constexpr (alignment) {
		v1 = _mm_load_si128((__m128i*) & x);
	} else {
		v1 = _mm_maskload_epi32(&x, mask);
	}

	__m128i v2 = _mm_set1_epi32(other);
	__m128i res = _mm_mul_epi32(v1, v2);

	if constexpr (alignment) {
		_mm_store_si128((__m128i*) & x, res);
	} else {
		_mm_maskstore_epi32(&x, mask, res);
	}

	return *this;
}

_vec3<int>& _vec3<int>::Div(int other) {
	__m128i mask = _mm_set_epi32(0, -1, -1, -1);
	__m128i v1;

	constexpr bool alignment = alignof(t) % 16 == 0;

	if constexpr (alignment) {
		v1 = _mm_load_si128((__m128i*) & x);
	} else {
		v1 = _mm_maskload_epi32(&x, mask);
	}

	__m128i v2 = _mm_set1_epi32(other);
	__m128i res = _mm_div_epi32(v1, v2);

	if constexpr (alignment) {
		_mm_store_si128((__m128i*) & x, res);
	} else {
		_mm_maskstore_epi32(&x, mask, res);
	}

	return *this;
}

#endif