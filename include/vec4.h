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

#ifdef GML_VEC4_SSE
#define GML_VEC4F_SSE
#define GML_VEC4D_SSE
#define GML_VEC4I_SSE
#define GML_VEC4L_SSE
#endif

#include "impl/vec4f.h"
#include "impl/vec4d.h"
#include "impl/vec4i.h"
#include "impl/vec4l.h"

typedef _vec4<float> vec4;
typedef _vec4<double> vec4d;
typedef _vec4<int> vec4i;
typedef _vec4<long long> vec4l;