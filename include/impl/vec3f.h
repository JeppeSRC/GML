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

#ifdef GML_VEC3F_SSE

_vec3<float> _vec3<float>::Normalize() const {
	_vec3<float> tmp;
	__m128i mask = _mm_set_epi32(0, -1, -1, -1);
	__m128 v;

	constexpr bool alignment = alignof(t) % 16 == 0;

	if constexpr (alignment) {
		v = _mm_load_ps(&x);
	} else {
		v = _mm_maskload_ps(&x, mask);
	}

	__m128 res = _mm_mul_ps(v, v);

	res = _mm_hadd_ps(res, res);
	res = _mm_hadd_ps(res, res);
	res = _mm_sqrt_ss(res);

	res = _mm_div_ps(v, res);

	if constexpr (alignment) {
		_mm_store_ps(&tmp.x, res);
	} else {
		_mm_maskstore_ps(&tmp.x, mask, res);
	}

	return tmp;
}

float _vec3<float>::Dot(const _vec3<float>& other) const {
	__m128i mask = _mm_set_epi32(0, -1, -1, -1);
	__m128 v1, v2;

	constexpr bool alignment = alignof(t) % 16 == 0;

	if constexpr (alignment) {
		v1 = _mm_load_ps(&x);
		v2 = _mm_load_ps(&other.x);
	} else {
		v1 = _mm_maskload_ps(&x, mask);
		v2 = _mm_maskload_ps(&other.x, mask);
	}

	__m128 res = _mm_mul_ps(v1, v2);

	res = _mm_hadd_ps(res, res);
	res = _mm_hadd_ps(res, res);

	return res.m128_f32[0];
}

_vec3<float>& _vec3<float>::Add(const _vec3<float>& other) {
	__m128i mask = _mm_set_epi32(0, -1, -1, -1);
	__m128 v1, v2;

	constexpr bool alignment = alignof(t) % 16 == 0;

	if constexpr (alignment) {
		v1 = _mm_load_ps(&x);
		v2 = _mm_load_ps(&other.x);
	} else {
		v1 = _mm_maskload_ps(&x, mask);
		v2 = _mm_maskload_ps(&other.x, mask);
	}

	__m128 res = _mm_add_ps(v1, v2);

	if constexpr (alignment) {
		_mm_store_ps(&x, res);
	} else {
		_mm_maskstore_ps(&x, mask, res);
	}

	return *this;
}

_vec3<float>& _vec3<float>::Sub(const _vec3<float>& other) {
	__m128i mask = _mm_set_epi32(0, -1, -1, -1);
	__m128 v1, v2;

	constexpr bool alignment = alignof(t) % 16 == 0;

	if constexpr (alignment) {
		v1 = _mm_load_ps(&x);
		v2 = _mm_load_ps(&other.x);
	} else {
		v1 = _mm_maskload_ps(&x, mask);
		v2 = _mm_maskload_ps(&other.x, mask);
	}

	__m128 res = _mm_sub_ps(v1, v2);

	if constexpr (alignment) {
		_mm_store_ps(&x, res);
	} else {
		_mm_maskstore_ps(&x, mask, res);
	}

	return *this;
}

_vec3<float>& _vec3<float>::Mul(const _vec3<float>& other) {
	__m128i mask = _mm_set_epi32(0, -1, -1, -1);
	__m128 v1, v2;

	constexpr bool alignment = alignof(t) % 16 == 0;

	if constexpr (alignment) {
		v1 = _mm_load_ps(&x);
		v2 = _mm_load_ps(&other.x);
	} else {
		v1 = _mm_maskload_ps(&x, mask);
		v2 = _mm_maskload_ps(&other.x, mask);
	}

	__m128 res = _mm_mul_ps(v1, v2);

	if constexpr (alignment) {
		_mm_store_ps(&x, res);
	} else {
		_mm_maskstore_ps(&x, mask, res);
	}

	return *this;
}

_vec3<float>& _vec3<float>::Div(const _vec3<float>& other) {
	__m128i mask = _mm_set_epi32(0, -1, -1, -1);
	__m128 v1, v2;

	constexpr bool alignment = alignof(t) % 16 == 0;

	if constexpr (alignment) {
		v1 = _mm_load_ps(&x);
		v2 = _mm_load_ps(&other.x);
	} else {
		v1 = _mm_maskload_ps(&x, mask);
		v2 = _mm_maskload_ps(&other.x, mask);
	}

	__m128 res = _mm_div_ps(v1, v2);

	if constexpr (alignment) {
		_mm_store_ps(&x, res);
	} else {
		_mm_maskstore_ps(&x, mask, res);
	}

	return *this;
}

_vec3<float>& _vec3<float>::Add(float other) {
	__m128i mask = _mm_set_epi32(0, -1, -1, -1);
	__m128 v1;

	constexpr bool alignment = alignof(t) % 16 == 0;

	if constexpr (alignment) {
		v1 = _mm_load_ps(&x);
	} else {
		v1 = _mm_maskload_ps(&x, mask);
	}

	__m128 v2 = _mm_set_ps1(other);
	__m128 res = _mm_add_ps(v1, v2);

	if constexpr (alignment) {
		_mm_store_ps(&x, res);
	} else {
		_mm_maskstore_ps(&x, mask, res);
	}

	return *this;
}

_vec3<float>& _vec3<float>::Sub(float other) {
	__m128i mask = _mm_set_epi32(0, -1, -1, -1);
	__m128 v1;

	constexpr bool alignment = alignof(t) % 16 == 0;

	if constexpr (alignment) {
		v1 = _mm_load_ps(&x);
	} else {
		v1 = _mm_maskload_ps(&x, mask);
	}

	__m128 v2 = _mm_set_ps1(other);
	__m128 res = _mm_sub_ps(v1, v2);

	if constexpr (alignment) {
		_mm_store_ps(&x, res);
	} else {
		_mm_maskstore_ps(&x, mask, res);
	}

	return *this;
}

_vec3<float>& _vec3<float>::Mul(float other) {
	__m128i mask = _mm_set_epi32(0, -1, -1, -1);
	__m128 v1;

	constexpr bool alignment = alignof(t) % 16 == 0;

	if constexpr (alignment) {
		v1 = _mm_load_ps(&x);
	} else {
		v1 = _mm_maskload_ps(&x, mask);
	}

	__m128 v2 = _mm_set_ps1(other);
	__m128 res = _mm_mul_ps(v1, v2);

	if constexpr (alignment) {
		_mm_store_ps(&x, res);
	} else {
		_mm_maskstore_ps(&x, mask, res);
	}

	return *this;
}

_vec3<float>& _vec3<float>::Div(float other) {
	__m128i mask = _mm_set_epi32(0, -1, -1, -1);
	__m128 v1;

	constexpr bool alignment = alignof(t) % 16 == 0;

	if constexpr (alignment) {
		v1 = _mm_load_ps(&x);
	} else {
		v1 = _mm_maskload_ps(&x, mask);
	}

	__m128 v2 = _mm_set_ps1(other);
	__m128 res = _mm_div_ps(v1, v2);

	if constexpr (alignment) {
		_mm_store_ps(&x, res);
	} else {
		_mm_maskstore_ps(&x, mask, res);
	}

	return *this;
}

#endif