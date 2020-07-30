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

template<typename T>
class alignas(CalcVecAlignment<T>(3)) _vec3 {
public:
	T x, y, z;

	_vec3(T init = 0) : x(init), y(init), z(init) {}
	_vec3(T x, T y, T z) : x(x), y(y), z(z) {}

	_vec3<T>& Add(_vec3<T> other) { x += other.x; y += other.y; z += other.z; return *this; }
	_vec3<T>& Sub(_vec3<T> other) { x -= other.x; y -= other.y; z -= other.z; return *this; }
	_vec3<T>& Mul(_vec3<T> other) { x *= other.x; y *= other.y; z *= other.z; return *this; }
	_vec3<T>& Div(_vec3<T> other) { x /= other.x; y /= other.y; z /= other.z; return *this; }

	_vec3<T>& Add(T other) { x += T; y += T; z += T; return *this; }
	_vec3<T>& Sub(T other) { x -= T; y -= T; z -= T; return *this; }
	_vec3<T>& Mul(T other) { x *= T; y *= T; z *= T; return *this; }
	_vec3<T>& Div(T other) { x /= T; y /= T; z /= T; return *this; }


	_vec3<T> Normalize() const { float a = sqrt(x * x + y * y + z * z); return _vec3<T>(x / a, y / a, z / a); }
	T Dot(_vec3<T> other) const { return x * other.x + y * other.y + z * other.z; }

	inline _vec3<T> operator+(_vec3<T> other) const { return _vec3<T>(*this).Add(other); }
	inline _vec3<T> operator-(_vec3<T> other) const { return _vec3<T>(*this).Sub(other); }
	inline _vec3<T> operator*(_vec3<T> other) const { return _vec3<T>(*this).Mul(other); }
	inline _vec3<T> operator/(_vec3<T> other) const { return _vec3<T>(*this).Div(other); }
	inline _vec3<T>& operator+=(_vec3<T> other) { return Add(other); }
	inline _vec3<T>& operator-=(_vec3<T> other) { return Sub(other); }
	inline _vec3<T>& operator*=(_vec3<T> other) { return Mul(other); }
	inline _vec3<T>& operator/=(_vec3<T> other) { return Div(other); }

	inline _vec3<T> operator+(T other) const { return _vec3<T>(*this).Add(other); }
	inline _vec3<T> operator-(T other) const { return _vec3<T>(*this).Sub(other); }
	inline _vec3<T> operator*(T other) const { return _vec3<T>(*this).Mul(other); }
	inline _vec3<T> operator/(T other) const { return _vec3<T>(*this).Div(other); }
	inline _vec3<T>& operator+=(T other) { return Add(other); }
	inline _vec3<T>& operator-=(T other) { return Sub(other); }
	inline _vec3<T>& operator*=(T other) { return Mul(other); }
	inline _vec3<T>& operator/=(T other) { return Div(other); }
};


#pragma region float
#ifndef GML_VEC3_SSE

_vec3<float> _vec3<float>::Normalize() const {
	_vec3<float> tmp;
	__m128 mask = _mm_set_ps(0, -1.0f, -1.0f, -1.0f);
	__m128 v;

	constexpr bool alignment = alignof(_vec3<float>) % 16 == 0;

	if constexpr (alignment) {
		v = _mm_load_ps(&x);
	} else {
		v = _mm_maskload_ps(&x, *(__m128i*) & mask);
	}

	__m128 res = _mm_mul_ps(v, v);

	res = _mm_hadd_ps(res, res);
	res = _mm_hadd_ps(res, res);
	res = _mm_sqrt_ss(res);

	res = _mm_div_ps(v, res);

	if constexpr (alignment) {
		_mm_store_ps(&tmp.x, res);
	} else {
		_mm_maskstore_ps(&tmp.x, *(__m128i*)&mask, res);
	}

	return tmp;
}

float _vec3<float>::Dot(_vec3<float> other) const {
	__m128 mask = _mm_set_ps(0, -1.0f, -1.0f, -1.0f);
	__m128 v1, v2;

	constexpr bool alignment = alignof(_vec3<float>) % 16 == 0;

	if constexpr (alignment) {
		v1 = _mm_load_ps(&x);
		v2 = _mm_load_ps(&other.x);
	} else {
		v1 = _mm_maskload_ps(&x, *(__m128i*)&mask);
		v2 = _mm_maskload_ps(&other.x, *(__m128i*)&mask);
	}
	
	__m128 res = _mm_mul_ps(v1, v2);

	res = _mm_hadd_ps(res, res);
	res = _mm_hadd_ps(res, res);

	return res.m128_f32[0];
}

_vec3<float>& _vec3<float>::Add(_vec3<float> other) {
	__m128 mask = _mm_set_ps(0, -1.0f, -1.0f, -1.0f);
	__m128 v1, v2;

	constexpr bool alignment = alignof(_vec3<float>) % 16 == 0;

	if constexpr (alignment) {
		v1 = _mm_load_ps(&x);
		v2 = _mm_load_ps(&other.x);
	} else {
		v1 = _mm_maskload_ps(&x, *(__m128i*) & mask);
		v2 = _mm_maskload_ps(&other.x, *(__m128i*) & mask);
	}

	__m128 res = _mm_add_ps(v1, v2);

	_mm_store_ps(&x, res);

	return *this;
}

_vec3<float>& _vec3<float>::Sub(_vec3<float> other) {
	__m128 mask = _mm_set_ps(0, -1.0f, -1.0f, -1.0f);
	__m128 v1, v2;

	constexpr bool alignment = alignof(_vec3<float>) % 16 == 0;

	if constexpr (alignment) {
		v1 = _mm_load_ps(&x);
		v2 = _mm_load_ps(&other.x);
	} else {
		v1 = _mm_maskload_ps(&x, *(__m128i*) & mask);
		v2 = _mm_maskload_ps(&other.x, *(__m128i*) & mask);
	}

	__m128 res = _mm_sub_ps(v1, v2);

	_mm_store_ps(&x, res);

	return *this;
}

_vec3<float>& _vec3<float>::Mul(_vec3<float> other) {
	__m128 mask = _mm_set_ps(0, -1.0f, -1.0f, -1.0f);
	__m128 v1, v2;

	constexpr bool alignment = alignof(_vec3<float>) % 16 == 0;

	if constexpr (alignment) {
		v1 = _mm_load_ps(&x);
		v2 = _mm_load_ps(&other.x);
	} else {
		v1 = _mm_maskload_ps(&x, *(__m128i*) & mask);
		v2 = _mm_maskload_ps(&other.x, *(__m128i*) & mask);
	}

	__m128 res = _mm_mul_ps(v1, v2);

	_mm_store_ps(&x, res);

	return *this;
}

_vec3<float>& _vec3<float>::Div(_vec3<float> other) {
	__m128 mask = _mm_set_ps(0, -1.0f, -1.0f, -1.0f);
	__m128 v1, v2;

	constexpr bool alignment = alignof(_vec3<float>) % 16 == 0;

	if constexpr (alignment) {
		v1 = _mm_load_ps(&x);
		v2 = _mm_load_ps(&other.x);
	} else {
		v1 = _mm_maskload_ps(&x, *(__m128i*) & mask);
		v2 = _mm_maskload_ps(&other.x, *(__m128i*) & mask);
	}

	__m128 res = _mm_div_ps(v1, v2);

	_mm_store_ps(&x, res);

	return *this;
}

_vec3<float>& _vec3<float>::Add(float other) {
	__m128 mask = _mm_set_ps(0, -1.0f, -1.0f, -1.0f);
	__m128 v1;

	constexpr bool alignment = alignof(_vec3<float>) % 16 == 0;

	if constexpr (alignment) {
		v1 = _mm_load_ps(&x);
	} else {
		v1 = _mm_maskload_ps(&x, *(__m128i*) & mask);
	}

	__m128 v2 = _mm_set_ps1(other);
	__m128 res = _mm_add_ps(v1, v2);

	_mm_store_ps(&x, res);

	return *this;
}

_vec3<float>& _vec3<float>::Sub(float other) {
	__m128 mask = _mm_set_ps(0, -1.0f, -1.0f, -1.0f);
	__m128 v1;

	constexpr bool alignment = alignof(_vec3<float>) % 16 == 0;

	if constexpr (alignment) {
		v1 = _mm_load_ps(&x);
	} else {
		v1 = _mm_maskload_ps(&x, *(__m128i*) & mask);
	}

	__m128 v2 = _mm_set_ps1(other);
	__m128 res = _mm_sub_ps(v1, v2);

	_mm_store_ps(&x, res);

	return *this;
}

_vec3<float>& _vec3<float>::Mul(float other) {
	__m128 mask = _mm_set_ps(0, -1.0f, -1.0f, -1.0f);
	__m128 v1;

	constexpr bool alignment = alignof(_vec3<float>) % 16 == 0;

	if constexpr (alignment) {
		v1 = _mm_load_ps(&x);
	} else {
		v1 = _mm_maskload_ps(&x, *(__m128i*) & mask);
	}

	__m128 v2 = _mm_set_ps1(other);
	__m128 res = _mm_mul_ps(v1, v2);

	_mm_store_ps(&x, res);

	return *this;
}

_vec3<float>& _vec3<float>::Div(float other) {
	__m128 mask = _mm_set_ps(0, -1.0f, -1.0f, -1.0f);
	__m128 v1;

	constexpr bool alignment = alignof(_vec3<float>) % 16 == 0;

	if constexpr (alignment) {
		v1 = _mm_load_ps(&x);
	} else {
		v1 = _mm_maskload_ps(&x, *(__m128i*) & mask);
	}

	__m128 v2 = _mm_set_ps1(other);
	__m128 res = _mm_div_ps(v1, v2);

	_mm_store_ps(&x, res);

	return *this;
}

#endif

#pragma endregion

#pragma region double

#ifndef GML_VEC3D_NO_SSE

_vec3<double> _vec3<double>::Normalize() const {
	_vec3<double> tmp;
	__m256d v = _mm256_load_pd(&x);
	__m256d res = _mm256_mul_pd(v, v);

	res = _mm256_hadd_pd(res, res);
	res = _mm256_hadd_pd(res, res);
	res = _mm256_sqrt_pd(res);

	res = _mm256_div_pd(v, res);

	_mm256_store_pd(&tmp.x, res);

	return tmp;
}

double _vec3<double>::Dot(_vec3<double> other) const {
	__m256d v1 = _mm256_load_pd(&x);
	__m256d v2 = _mm256_load_pd(&other.x);

	__m256d res = _mm256_mul_pd(v1, v2);

	res = _mm256_hadd_pd(res, res);
	res = _mm256_hadd_pd(res, res);

	return res.m256d_f64[0];
}

_vec3<double>& _vec3<double>::Add(_vec3<double> other) {
	__m256d v1 = _mm256_load_pd(&x);
	__m256d v2 = _mm256_load_pd(&other.x);

	__m256d res = _mm256_add_pd(v1, v2);

	_mm256_store_pd(&x, res);

	return *this;
}

_vec3<double>& _vec3<double>::Sub(_vec3<double> other) {
	__m256d v1 = _mm256_load_pd(&x);
	__m256d v2 = _mm256_load_pd(&other.x);

	__m256d res = _mm256_sub_pd(v1, v2);

	_mm256_store_pd(&x, res);

	return *this;
}

_vec3<double>& _vec3<double>::Mul(_vec3<double> other) {
	__m256d v1 = _mm256_load_pd(&x);
	__m256d v2 = _mm256_load_pd(&other.x);

	__m256d res = _mm256_mul_pd(v1, v2);

	_mm256_store_pd(&x, res);

	return *this;
}

_vec3<double>& _vec3<double>::Div(_vec3<double> other) {
	__m256d v1 = _mm256_load_pd(&x);
	__m256d v2 = _mm256_load_pd(&other.x);

	__m256d res = _mm256_div_pd(v1, v2);

	_mm256_store_pd(&x, res);

	return *this;
}
#endif
#pragma endregion

#pragma region int32

#ifndef GML_VEC3I_NO_SSE

_vec3<int>& _vec3<int>::Add(_vec3<int> other) {
	__m128i v1 = _mm_load_si128((__m128i*) & x);
	__m128i v2 = _mm_load_si128((__m128i*) & other.x);

	__m128i res = _mm_add_epi32(v1, v2);

	_mm_store_si128((__m128i*) & x, res);

	return *this;
}

_vec3<int>& _vec3<int>::Sub(_vec3<int> other) {
	__m128i v1 = _mm_load_si128((__m128i*) & x);
	__m128i v2 = _mm_load_si128((__m128i*) & other.x);

	__m128i res = _mm_sub_epi32(v1, v2);

	_mm_store_si128((__m128i*) & x, res);

	return *this;
}

_vec3<int>& _vec3<int>::Mul(_vec3<int> other) {
	__m128i v1 = _mm_load_si128((__m128i*) & x);
	__m128i v2 = _mm_load_si128((__m128i*) & other.x);

	__m128i res = _mm_mul_epi32(v1, v2);

	_mm_store_si128((__m128i*) & x, res);

	return *this;
}

_vec3<int>& _vec3<int>::Div(_vec3<int> other) {
	__m128i v1 = _mm_load_si128((__m128i*) & x);
	__m128i v2 = _mm_load_si128((__m128i*) & other.x);

	__m128i res = _mm_div_epi32(v1, v2);

	_mm_store_si128((__m128i*) & x, res);

	return *this;
}

#endif
#pragma endregion

typedef _vec3<float> vec3;
typedef _vec3<double> vec3d;
typedef _vec3<int> vec3i; 
