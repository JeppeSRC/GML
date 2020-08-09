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

namespace gml {

template<typename T>
class alignas(CalcVecAlignment<T>(3)) _vec3 {
private:
	typedef _vec3<T> t;
public:
	T x, y, z;


	_vec3(T init = 0) : x(init), y(init), z(init) {}
	_vec3(T x, T y, T z) : x(x), y(y), z(z) {}

	_vec3<T>& Add(const _vec3<T>& other) { x += other.x; y += other.y; z += other.z; return *this; }
	_vec3<T>& Sub(const _vec3<T>& other) { x -= other.x; y -= other.y; z -= other.z; return *this; }
	_vec3<T>& Mul(const _vec3<T>& other) { x *= other.x; y *= other.y; z *= other.z; return *this; }
	_vec3<T>& Div(const _vec3<T>& other) { x /= other.x; y /= other.y; z /= other.z; return *this; }

	_vec3<T>& Add(T other) { x += T; y += T; z += T; return *this; }
	_vec3<T>& Sub(T other) { x -= T; y -= T; z -= T; return *this; }
	_vec3<T>& Mul(T other) { x *= T; y *= T; z *= T; return *this; }
	_vec3<T>& Div(T other) { x /= T; y /= T; z /= T; return *this; }


	_vec3<T> Normalize() const { float a = sqrt(x * x + y * y + z * z); return _vec3<T>(x / a, y / a, z / a); }
	T Dot(const _vec3<T>& other) const { return x * other.x + y * other.y + z * other.z; }
	_vec3<T> Cross(const _vec3<float>& other) const {
		T x = y * other.z - z * other.y;
		T y = z * other.x - x * other.z;
		T z = x * other.y - y * other.x;

		return _vec3<T>(x, y, z);
	}

	inline _vec3<T> operator+(const _vec3<T>& other) const { return _vec3<T>(*this).Add(other); }
	inline _vec3<T> operator-(const _vec3<T>& other) const { return _vec3<T>(*this).Sub(other); }
	inline _vec3<T> operator*(const _vec3<T>& other) const { return _vec3<T>(*this).Mul(other); }
	inline _vec3<T> operator/(const _vec3<T>& other) const { return _vec3<T>(*this).Div(other); }
	inline _vec3<T>& operator+=(const _vec3<T>& other) { return Add(other); }
	inline _vec3<T>& operator-=(const _vec3<T>& other) { return Sub(other); }
	inline _vec3<T>& operator*=(const _vec3<T>& other) { return Mul(other); }
	inline _vec3<T>& operator/=(const _vec3<T>& other) { return Div(other); }

	inline _vec3<T> operator+(T other) const { return _vec3<T>(*this).Add(other); }
	inline _vec3<T> operator-(T other) const { return _vec3<T>(*this).Sub(other); }
	inline _vec3<T> operator*(T other) const { return _vec3<T>(*this).Mul(other); }
	inline _vec3<T> operator/(T other) const { return _vec3<T>(*this).Div(other); }
	inline _vec3<T>& operator+=(T other) { return Add(other); }
	inline _vec3<T>& operator-=(T other) { return Sub(other); }
	inline _vec3<T>& operator*=(T other) { return Mul(other); }
	inline _vec3<T>& operator/=(T other) { return Div(other); }
};

#ifdef GML_VEC3_SSE
#define GML_VEC3F_SSE
#define GML_VEC3D_SSE
#define GML_VEC3I_SSE
#define GML_VEC3L_SSE
#endif


#include "impl/vec3d.h"
#include "impl/vec3f.h"
#include "impl/vec3i.h"
#include "impl/vec3l.h"

typedef _vec3<float> vec3;
typedef _vec3<double> vec3d;
typedef _vec3<int> vec3i; 
typedef _vec3<long long> vec3l;

}