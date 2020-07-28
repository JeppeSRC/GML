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
#include <intrin.h>
#include <math.h>

template<typename T>
class alignas(16) _vec4 {
public:
	T x, y, z, w;

	_vec4(T init = 0) : x(init), y(init), z(init), w(init) {}
	_vec4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}

	_vec4<T>& Add(_vec4<T> other);
	_vec4<T>& Sub(_vec4<T> other);
	_vec4<T>& Mul(_vec4<T> other);
	_vec4<T>& Div(_vec4<T> other);

	_vec4<T> Normalize() const;
	T Dot(_vec4<T> other) const;

	inline _vec4<T> operator+(_vec4<T> other) const { return _vec4<T>(*this).Add(other); }

	inline _vec4<T> operator-(_vec4<T> other) const { return _vec4<T>(*this).Sub(other); }

	inline _vec4<T> operator*(_vec4<T> other) const { return _vec4<T>(*this).Sub(other); }

	inline _vec4<T> operator/(_vec4<T> other) const { return _vec4<T>(*this).Div(other); }

	inline _vec4<T>& operator+=(_vec4<T> other) { return Add(other); }

	inline _vec4<T>& operator-=(_vec4<T> other) { return Sub(other); }

	inline _vec4<T>& operator*=(_vec4<T> other) { return Mul(other); }

	inline _vec4<T>& operator/=(_vec4<T> other) { return Div(other); }
};

#pragma region float

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

float _vec4<float>::Dot(_vec4<float> other) const {
	__m128 v1 = _mm_load_ps(&x);
	__m128 v2 = _mm_load_ps(&other.x);

	__m128 res = _mm_mul_ps(v1, v2);

	res = _mm_hadd_ps(res, res);
	res = _mm_hadd_ps(res, res);

	return res.m128_f32[0];
}

_vec4<float>& _vec4<float>::Add(_vec4<float> other) {
	__m128 v1 = _mm_load_ps(&x);
	__m128 v2 = _mm_load_ps(&other.x);

	__m128 res = _mm_add_ps(v1, v2);

	_mm_store_ps(&x, res);

	return *this;
}

_vec4<float>& _vec4<float>::Sub(_vec4<float> other) {
	__m128 v1 = _mm_load_ps(&x);
	__m128 v2 = _mm_load_ps(&other.x);

	__m128 res = _mm_sub_ps(v1, v2);

	_mm_store_ps(&x, res);

	return *this;
}

_vec4<float>& _vec4<float>::Mul(_vec4<float> other) {
	__m128 v1 = _mm_load_ps(&x);
	__m128 v2 = _mm_load_ps(&other.x);

	__m128 res = _mm_mul_ps(v1, v2);

	_mm_store_ps(&x, res);

	return *this;
}

_vec4<float>& _vec4<float>::Div(_vec4<float> other) {
	__m128 v1 = _mm_load_ps(&x);
	__m128 v2 = _mm_load_ps(&other.x);

	__m128 res = _mm_div_ps(v1, v2);

	_mm_store_ps(&x, res);

	return *this;
}

#pragma endregion

typedef _vec4<float> vec4;
typedef _vec4<double> vec4d;
typedef _vec4<int> vec4i;