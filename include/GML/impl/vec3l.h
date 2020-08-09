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

#ifdef GML_VEC3L_SSE

_vec3<long long>& _vec3<long long>::Add(const _vec3<long long>& other) {
	__m256i mask = _mm256_set_epi64x(0, -1, -1, -1);
	__m256i v1, v2;

	constexpr int alignment = alignof(t) % 16 == 0;

	if constexpr (alignment) {
		v1 = _mm256_load_si256((__m256i*) & x);
		v2 = _mm256_load_si256((__m256i*) & other.x);
	} else {
		v1 = _mm256_maskload_epi64(&x, mask);
		v2 = _mm256_maskload_epi64(&other.x, mask);
	}

	__m256i res = _mm256_add_epi64(v1, v2);

	if constexpr (alignment) {
		_mm256_store_si256((__m256i*) & x, res);
	} else {
		_mm256_maskstore_epi64(&x, mask, res);
	}

	return *this;
}

_vec3<long long>& _vec3<long long>::Sub(const _vec3<long long>& other) {
	__m256i mask = _mm256_set_epi64x(0, -1, -1, -1);
	__m256i v1, v2;

	constexpr int alignment = alignof(t) % 16 == 0;

	if constexpr (alignment) {
		v1 = _mm256_load_si256((__m256i*) & x);
		v2 = _mm256_load_si256((__m256i*) & other.x);
	} else {
		v1 = _mm256_maskload_epi64(&x, mask);
		v2 = _mm256_maskload_epi64(&other.x, mask);
	}

	__m256i res = _mm256_sub_epi64(v1, v2);

	if constexpr (alignment) {
		_mm256_store_si256((__m256i*) & x, res);
	} else {
		_mm256_maskstore_epi64(&x, mask, res);
	}

	return *this;
}

_vec3<long long>& _vec3<long long>::Mul(const _vec3<long long>& other) {
	__m256i mask = _mm256_set_epi64x(0, -1, -1, -1);
	__m256i v1, v2;

	constexpr int alignment = alignof(t) % 16 == 0;

	if constexpr (alignment) {
		v1 = _mm256_load_si256((__m256i*) & x);
		v2 = _mm256_load_si256((__m256i*) & other.x);
	} else {
		v1 = _mm256_maskload_epi64(&x, mask);
		v2 = _mm256_maskload_epi64(&other.x, mask);
	}

	__m256i ac = _mm256_mul_epu32(v1, v2);
	__m256i b = _mm256_srli_epi64(v1, 32);
	__m256i bc = _mm256_mul_epu32(b, v2);
	__m256i d = _mm256_srli_epi64(v2, 32);
	__m256i ad = _mm256_mul_epu32(v1, d);
	__m256i high = _mm256_add_epi64(bc, ad);
	high = _mm256_slli_epi64(high, 32);
	__m256i res = _mm256_add_epi64(high, ac);

	if constexpr (alignment) {
		_mm256_store_si256((__m256i*) & x, res);
	} else {
		_mm256_maskstore_epi64(&x, mask, res);
	}

	return *this;
}

_vec3<long long>& _vec3<long long>::Div(const _vec3<long long>& other) {
	__m256i mask = _mm256_set_epi64x(0, -1, -1, -1);
	__m256i v1, v2;

	constexpr int alignment = alignof(t) % 16 == 0;

	if constexpr (alignment) {
		v1 = _mm256_load_si256((__m256i*) & x);
		v2 = _mm256_load_si256((__m256i*) & other.x);
	} else {
		v1 = _mm256_maskload_epi64(&x, mask);
		v2 = _mm256_maskload_epi64(&other.x, mask);
	}

	__m256i res = _mm256_div_epi64(v1, v2);

	if constexpr (alignment) {
		_mm256_store_si256((__m256i*) & x, res);
	} else {
		_mm256_maskstore_epi64(&x, mask, res);
	}

	return *this;
}

_vec3<long long>& _vec3<long long>::Add(long long other) {
	__m256i mask = _mm256_set_epi64x(0, -1, -1, -1);
	__m256i v1;
	__m256i v2 = _mm256_set1_epi64x(other);

	constexpr int alignment = alignof(t) % 16 == 0;

	if constexpr (alignment) {
		v1 = _mm256_load_si256((__m256i*) & x);
	} else {
		v1 = _mm256_maskload_epi64(&x, mask);
	}

	__m256i res = _mm256_add_epi64(v1, v2);

	if constexpr (alignment) {
		_mm256_store_si256((__m256i*) & x, res);
	} else {
		_mm256_maskstore_epi64(&x, mask, res);
	}

	return *this;
}

_vec3<long long>& _vec3<long long>::Sub(long long other) {
	__m256i mask = _mm256_set_epi64x(0, -1, -1, -1);
	__m256i v1;
	__m256i v2 = _mm256_set1_epi64x(other);

	constexpr int alignment = alignof(t) % 16 == 0;

	if constexpr (alignment) {
		v1 = _mm256_load_si256((__m256i*) & x);
	} else {
		v1 = _mm256_maskload_epi64(&x, mask);
	}

	__m256i res = _mm256_sub_epi64(v1, v2);

	if constexpr (alignment) {
		_mm256_store_si256((__m256i*) & x, res);
	} else {
		_mm256_maskstore_epi64(&x, mask, res);
	}

	return *this;
}

_vec3<long long>& _vec3<long long>::Mul(long long other) {
	__m256i mask = _mm256_set_epi64x(0, -1, -1, -1);
	__m256i v1;
	__m256i v2 = _mm256_set1_epi64x(other);

	constexpr int alignment = alignof(t) % 16 == 0;

	if constexpr (alignment) {
		v1 = _mm256_load_si256((__m256i*) & x);
	} else {
		v1 = _mm256_maskload_epi64(&x, mask);
	}

	__m256i ac = _mm256_mul_epu32(v1, v2);
	__m256i b = _mm256_srli_epi64(v1, 32);
	__m256i bc = _mm256_mul_epu32(b, v2);
	__m256i d = _mm256_srli_epi64(v2, 32);
	__m256i ad = _mm256_mul_epu32(v1, d);
	__m256i high = _mm256_add_epi64(bc, ad);
	high = _mm256_slli_epi64(high, 32);
	__m256i res = _mm256_add_epi64(high, ac);

	if constexpr (alignment) {
		_mm256_store_si256((__m256i*) & x, res);
	} else {
		_mm256_maskstore_epi64(&x, mask, res);
	}

	return *this;
}

_vec3<long long>& _vec3<long long>::Div(long long other) {
	__m256i mask = _mm256_set_epi64x(0, -1, -1, -1);
	__m256i v1;
	__m256i v2 = _mm256_set1_epi64x(other);

	constexpr int alignment = alignof(t) % 16 == 0;

	if constexpr (alignment) {
		v1 = _mm256_load_si256((__m256i*) & x);
	} else {
		v1 = _mm256_maskload_epi64(&x, mask);
	}

	__m256i res = _mm256_div_epi64(v1, v2);

	if constexpr (alignment) {
		_mm256_store_si256((__m256i*) & x, res);
	} else {
		_mm256_maskstore_epi64(&x, mask, res);
	}

	return *this;
}

#endif
