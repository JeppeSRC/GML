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

#ifdef GML_VEC3D_SSE

_vec3<double> _vec3<double>::Normalize() const {
	_vec3<double> tmp;
	__m256i mask = _mm256_set_epi64x(0, -1, -1, -1);
	__m256d v;

	constexpr bool alignment = alignof(t) % 16 == 0;

	if constexpr (alignment) {
		v = _mm256_load_pd(&x);
	} else {
		v = _mm256_maskload_pd(&x, mask);
	}

	__m256d res = _mm256_mul_pd(v, v);

	res = _mm256_hadd_pd(res, res);
	res = _mm256_hadd_pd(res, res);
	res = _mm256_sqrt_pd(res);

	res = _mm256_div_pd(v, res);

	if constexpr (alignment) {
		_mm256_store_pd(&tmp.x, res);
	} else {
		_mm256_maskstore_pd(&tmp.x, mask, res);
	}

	return tmp;
}

double _vec3<double>::Dot(const _vec3<double>& other) const {
	__m256i mask = _mm256_set_epi64x(0, -1, -1, -1);
	__m256d v1, v2;

	constexpr bool alignment = alignof(t) % 16 == 0;

	if constexpr (alignment) {
		v1 = _mm256_load_pd(&x);
		v2 = _mm256_load_pd(&other.x);
	} else {
		v1 = _mm256_maskload_pd(&x, mask);
		v2 = _mm256_maskload_pd(&other.x, mask);
	}

	__m256d res = _mm256_mul_pd(v1, v2);

	res = _mm256_hadd_pd(res, res);
	res = _mm256_hadd_pd(res, res);

	return res.m256d_f64[0];
}

_vec3<double>& _vec3<double>::Add(const _vec3<double>& other) {
	__m256i mask = _mm256_set_epi64x(0, -1, -1, -1);
	__m256d v1, v2;

	constexpr bool alignment = alignof(t) % 16 == 0;

	if constexpr (alignment) {
		v1 = _mm256_load_pd(&x);
		v2 = _mm256_load_pd(&other.x);
	} else {
		v1 = _mm256_maskload_pd(&x, mask);
		v2 = _mm256_maskload_pd(&other.x, mask);
	}

	__m256d res = _mm256_add_pd(v1, v2);

	if constexpr (alignment) {
		_mm256_store_pd(&x, res);
	} else {
		_mm256_maskstore_pd(&x, mask, res);
	}

	return *this;
}

_vec3<double>& _vec3<double>::Sub(const _vec3<double>& other) {
	__m256i mask = _mm256_set_epi64x(0, -1, -1, -1);
	__m256d v1, v2;

	constexpr bool alignment = alignof(t) % 16 == 0;

	if constexpr (alignment) {
		v1 = _mm256_load_pd(&x);
		v2 = _mm256_load_pd(&other.x);
	} else {
		v1 = _mm256_maskload_pd(&x, mask);
		v2 = _mm256_maskload_pd(&other.x, mask);
	}

	__m256d res = _mm256_sub_pd(v1, v2);

	if constexpr (alignment) {
		_mm256_store_pd(&x, res);
	} else {
		_mm256_maskstore_pd(&x, mask, res);
	}

	return *this;
}

_vec3<double>& _vec3<double>::Mul(const _vec3<double>& other) {
	__m256i mask = _mm256_set_epi64x(0, -1, -1, -1);
	__m256d v1, v2;

	constexpr bool alignment = alignof(t) % 16 == 0;

	if constexpr (alignment) {
		v1 = _mm256_load_pd(&x);
		v2 = _mm256_load_pd(&other.x);
	} else {
		v1 = _mm256_maskload_pd(&x, mask);
		v2 = _mm256_maskload_pd(&other.x, mask);
	}

	__m256d res = _mm256_mul_pd(v1, v2);

	if constexpr (alignment) {
		_mm256_store_pd(&x, res);
	} else {
		_mm256_maskstore_pd(&x, mask, res);
	}

	return *this;
}

_vec3<double>& _vec3<double>::Div(const _vec3<double>& other) {
	__m256i mask = _mm256_set_epi64x(0, -1, -1, -1);
	__m256d v1, v2;

	constexpr bool alignment = alignof(t) % 16 == 0;

	if constexpr (alignment) {
		v1 = _mm256_load_pd(&x);
		v2 = _mm256_load_pd(&other.x);
	} else {
		v1 = _mm256_maskload_pd(&x, mask);
		v2 = _mm256_maskload_pd(&other.x, mask);
	}

	__m256d res = _mm256_div_pd(v1, v2);

	if constexpr (alignment) {
		_mm256_store_pd(&x, res);
	} else {
		_mm256_maskstore_pd(&x, mask, res);
	}

	return *this;
}

_vec3<double>& _vec3<double>::Add(double other) {
	__m256i mask = _mm256_set_epi64x(0, -1, -1, -1);
	__m256d v1;

	constexpr bool alignment = alignof(t) % 16 == 0;

	if constexpr (alignment) {
		v1 = _mm256_load_pd(&x);
	} else {
		v1 = _mm256_maskload_pd(&x, mask);
	}

	__m256d v2 = _mm256_set1_pd(other);
	__m256d res = _mm256_add_pd(v1, v2);

	if constexpr (alignment) {
		_mm256_store_pd(&x, res);
	} else {
		_mm256_maskstore_pd(&x, mask, res);
	}

	return *this;
}

_vec3<double>& _vec3<double>::Sub(double other) {
	__m256i mask = _mm256_set_epi64x(0, -1, -1, -1);
	__m256d v1;

	constexpr bool alignment = alignof(t) % 16 == 0;

	if constexpr (alignment) {
		v1 = _mm256_load_pd(&x);
	} else {
		v1 = _mm256_maskload_pd(&x, mask);
	}

	__m256d v2 = _mm256_set1_pd(other);
	__m256d res = _mm256_sub_pd(v1, v2);

	if constexpr (alignment) {
		_mm256_store_pd(&x, res);
	} else {
		_mm256_maskstore_pd(&x, mask, res);
	}

	return *this;
}

_vec3<double>& _vec3<double>::Mul(double other) {
	__m256i mask = _mm256_set_epi64x(0, -1, -1, -1);
	__m256d v1;

	constexpr bool alignment = alignof(t) % 16 == 0;

	if constexpr (alignment) {
		v1 = _mm256_load_pd(&x);
	} else {
		v1 = _mm256_maskload_pd(&x, mask);
	}

	__m256d v2 = _mm256_set1_pd(other);
	__m256d res = _mm256_mul_pd(v1, v2);

	if constexpr (alignment) {
		_mm256_store_pd(&x, res);
	} else {
		_mm256_maskstore_pd(&x, mask, res);
	}

	return *this;
}

_vec3<double>& _vec3<double>::Div(double other) {
	__m256i mask = _mm256_set_epi64x(0, -1, -1, -1);
	__m256d v1;

	constexpr bool alignment = alignof(t) % 16 == 0;

	if constexpr (alignment) {
		v1 = _mm256_load_pd(&x);
	} else {
		v1 = _mm256_maskload_pd(&x, mask);
	}

	__m256d v2 = _mm256_set1_pd(other);
	__m256d res = _mm256_div_pd(v1, v2);

	if constexpr (alignment) {
		_mm256_store_pd(&x, res);
	} else {
		_mm256_maskstore_pd(&x, mask, res);
	}

	return *this;
}


#endif
