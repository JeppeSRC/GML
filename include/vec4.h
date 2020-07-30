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
class alignas(CalcVecAlignment<T>(4)) _vec4 {
public:
	T x, y, z, w;

	_vec4(T init = 0) : x(init), y(init), z(init), w(init) {}
	_vec4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}

	_vec4<T>& Add(const _vec4<T>& other) { x += other.x; y += other.y; z += other.z; w += other.w; return *this; }
	_vec4<T>& Sub(const _vec4<T>& other) { x -= other.x; y -= other.y; z -= other.z; w -= other.w; return *this; }
	_vec4<T>& Mul(const _vec4<T>& other) { x *= other.x; y *= other.y; z *= other.z; w *= other.w; return *this; }
	_vec4<T>& Div(const _vec4<T>& other) { x /= other.x; y /= other.y; z /= other.z; w /= other.w; return *this; }

	_vec4<T>& Add(T other) { x += T; y += T; z += T; w += T; return *this; }
	_vec4<T>& Sub(T other) { x -= T; y -= T; z -= T; w -= T; return *this; }
	_vec4<T>& Mul(T other) { x *= T; y *= T; z *= T; w *= T; return *this; }
	_vec4<T>& Div(T other) { x /= T; y /= T; z /= T; w /= T; return *this; }


	_vec4<T> Normalize() const { float a = sqrt(x * x + y * y + z * z + w * w); return _vec4<T>(x / a, y / a, z / a, w / a); }
	T Dot(const _vec4<T>& other) const { return x * other.x + y * other.y + z * other.z + w * other.w; }

	inline _vec4<T> operator+(const _vec4<T>& other) const { return _vec4<T>(*this).Add(other); }
	inline _vec4<T> operator-(const _vec4<T>& other) const { return _vec4<T>(*this).Sub(other); }
	inline _vec4<T> operator*(const _vec4<T>& other) const { return _vec4<T>(*this).Mul(other); }
	inline _vec4<T> operator/(const _vec4<T>& other) const { return _vec4<T>(*this).Div(other); }
	inline _vec4<T>& operator+=(const _vec4<T>& other) { return Add(other); }
	inline _vec4<T>& operator-=(const _vec4<T>& other) { return Sub(other); }
	inline _vec4<T>& operator*=(const _vec4<T>& other) { return Mul(other); }
	inline _vec4<T>& operator/=(const _vec4<T>& other) { return Div(other); }

	inline _vec4<T> operator+(T other) const { return _vec4<T>(*this).Add(other); }
	inline _vec4<T> operator-(T other) const { return _vec4<T>(*this).Sub(other); }
	inline _vec4<T> operator*(T other) const { return _vec4<T>(*this).Mul(other); }
	inline _vec4<T> operator/(T other) const { return _vec4<T>(*this).Div(other); }
	inline _vec4<T>& operator+=(T other) { return Add(other); }
	inline _vec4<T>& operator-=(T other) { return Sub(other); }
	inline _vec4<T>& operator*=(T other) { return Mul(other); }
	inline _vec4<T>& operator/=(T other) { return Div(other); }
};


#pragma region float
#ifndef GML_VEC4_SSE

_vec4<float> _vec4<float>::Normalize() const {
	_vec4<float> tmp;
	__m128 v = _mm_load_ps(&x);
	__m128 res = _mm_mul_ps(v, v);

	res = _mm_hadd_ps(res, res);
	res = _mm_hadd_ps(res, res);
	res = _mm_sqrt_ss(res);
	
	res = _mm_div_ps(v, res);
	
	_mm_store_ps(&tmp.x, res);

	return tmp;
}

float _vec4<float>::Dot(const _vec4<float>& other) const {
	__m128 v1 = _mm_load_ps(&x);
	__m128 v2 = _mm_load_ps(&other.x);

	__m128 res = _mm_mul_ps(v1, v2);

	res = _mm_hadd_ps(res, res);
	res = _mm_hadd_ps(res, res);

	return res.m128_f32[0];
}

_vec4<float>& _vec4<float>::Add(const _vec4<float>& other) {
	__m128 v1 = _mm_load_ps(&x);
	__m128 v2 = _mm_load_ps(&other.x);

	__m128 res = _mm_add_ps(v1, v2);

	_mm_store_ps(&x, res);

	return *this;
}

_vec4<float>& _vec4<float>::Sub(const _vec4<float>& other) {
	__m128 v1 = _mm_load_ps(&x);
	__m128 v2 = _mm_load_ps(&other.x);

	__m128 res = _mm_sub_ps(v1, v2);

	_mm_store_ps(&x, res);

	return *this;
}

_vec4<float>& _vec4<float>::Mul(const _vec4<float>& other) {
	__m128 v1 = _mm_load_ps(&x);
	__m128 v2 = _mm_load_ps(&other.x);

	__m128 res = _mm_mul_ps(v1, v2);

	_mm_store_ps(&x, res);

	return *this;
}

_vec4<float>& _vec4<float>::Div(const _vec4<float>& other) {
	__m128 v1 = _mm_load_ps(&x);
	__m128 v2 = _mm_load_ps(&other.x);

	__m128 res = _mm_div_ps(v1, v2);

	_mm_store_ps(&x, res);

	return *this;
}

_vec4<float>& _vec4<float>::Add(float other) {
	__m128 v1 = _mm_load_ps(&x);
	__m128 v2 = _mm_set_ps1(other);

	__m128 res = _mm_add_ps(v1, v2);

	_mm_store_ps(&x, res);

	return *this;
}

_vec4<float>& _vec4<float>::Sub(float other) {
	__m128 v1 = _mm_load_ps(&x);
	__m128 v2 = _mm_set_ps1(other);

	__m128 res = _mm_sub_ps(v1, v2);

	_mm_store_ps(&x, res);

	return *this;
}

_vec4<float>& _vec4<float>::Mul(float other) {
	__m128 v1 = _mm_load_ps(&x);
	__m128 v2 = _mm_set_ps1(other);

	__m128 res = _mm_mul_ps(v1, v2);

	_mm_store_ps(&x, res);

	return *this;
}

_vec4<float>& _vec4<float>::Div(float other) {
	__m128 v1 = _mm_load_ps(&x);
	__m128 v2 = _mm_set_ps1(other);

	__m128 res = _mm_div_ps(v1, v2);

	_mm_store_ps(&x, res);

	return *this;
}

#endif

#pragma endregion

#pragma region double

#ifndef GML_VEC4D_NO_SSE

_vec4<double> _vec4<double>::Normalize() const {
	_vec4<double> tmp;
	__m256d v = _mm256_load_pd(&x);
	__m256d res = _mm256_mul_pd(v, v);

	res = _mm256_hadd_pd(res, res);
	res = _mm256_hadd_pd(res, res);
	res = _mm256_sqrt_pd(res);

	res = _mm256_div_pd(v, res);

	_mm256_store_pd(&tmp.x, res);

	return tmp;
}

double _vec4<double>::Dot(const _vec4<double>& other) const {
	__m256d v1 = _mm256_load_pd(&x);
	__m256d v2 = _mm256_load_pd(&other.x);

	__m256d res = _mm256_mul_pd(v1, v2);

	res = _mm256_hadd_pd(res, res);
	res = _mm256_hadd_pd(res, res);

	return res.m256d_f64[0];
}

_vec4<double>& _vec4<double>::Add(const _vec4<double>& other) {
	__m256d v1 = _mm256_load_pd(&x);
	__m256d v2 = _mm256_load_pd(&other.x);

	__m256d res = _mm256_add_pd(v1, v2);

	_mm256_store_pd(&x, res);

	return *this;
}

_vec4<double>& _vec4<double>::Sub(const _vec4<double>& other) {
	__m256d v1 = _mm256_load_pd(&x);
	__m256d v2 = _mm256_load_pd(&other.x);

	__m256d res = _mm256_sub_pd(v1, v2);

	_mm256_store_pd(&x, res);

	return *this;
}

_vec4<double>& _vec4<double>::Mul(const _vec4<double>& other) {
	__m256d v1 = _mm256_load_pd(&x);
	__m256d v2 = _mm256_load_pd(&other.x);

	__m256d res = _mm256_mul_pd(v1, v2);

	_mm256_store_pd(&x, res);

	return *this;
}

_vec4<double>& _vec4<double>::Div(const _vec4<double>& other) {
	__m256d v1 = _mm256_load_pd(&x);
	__m256d v2 = _mm256_load_pd(&other.x);

	__m256d res = _mm256_div_pd(v1, v2);

	_mm256_store_pd(&x, res);

	return *this;
}
#endif
#pragma endregion

#pragma region int32

#ifndef GML_VEC4I_NO_SSE

_vec4<int>& _vec4<int>::Add(const _vec4<int>& other) {
	__m128i v1 = _mm_load_si128((__m128i*)&x);
	__m128i v2 = _mm_load_si128((__m128i*)&other.x);

	__m128i res = _mm_add_epi32(v1, v2);

	_mm_store_si128((__m128i*)&x, res);

	return *this;
}

_vec4<int>& _vec4<int>::Sub(const _vec4<int>& other) {
	__m128i v1 = _mm_load_si128((__m128i*)&x);
	__m128i v2 = _mm_load_si128((__m128i*)&other.x);

	__m128i res = _mm_sub_epi32(v1, v2);

	_mm_store_si128((__m128i*)&x, res);

	return *this;
}

_vec4<int>& _vec4<int>::Mul(const _vec4<int>& other) {
	__m128i v1 = _mm_load_si128((__m128i*)&x);
	__m128i v2 = _mm_load_si128((__m128i*)&other.x);

	__m128i res = _mm_mul_epi32(v1, v2);

	_mm_store_si128((__m128i*)&x, res);

	return *this;
}

_vec4<int>& _vec4<int>::Div(const _vec4<int>& other) {
	__m128i v1 = _mm_load_si128((__m128i*)&x);
	__m128i v2 = _mm_load_si128((__m128i*)&other.x);

	__m128i res = _mm_div_epi32(v1, v2);

	_mm_store_si128((__m128i*)&x, res);

	return *this;
}

#endif
#pragma endregion

typedef _vec4<float> vec4;
typedef _vec4<double> vec4d;
typedef _vec4<int> vec4i;