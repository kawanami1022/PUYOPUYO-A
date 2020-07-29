#pragma once


template <class T>
class Vector2Temple
{
public:
	Vector2Temple();
	Vector2Temple(T x, T y);
	~Vector2Temple();
	T x;
	T y;
	// ”äŠr‰‰ŽZŽq
	Vector2Temple& operator=(const Vector2Temple& vec);
	T& operator[](int no);
	Vector2Temple& operator+=(const Vector2Temple& vec);
	Vector2Temple& operator-=(const Vector2Temple& vec);
	Vector2Temple& operator+=(T k);
	Vector2Temple& operator*=(T k);
	Vector2Temple& operator*=(T& k);
	Vector2Temple& operator/=(T k);
	Vector2Temple operator+()const;
	Vector2Temple operator-()const;

	bool operator==(const Vector2Temple& vec)const;
	bool operator!=(const Vector2Temple& vec)const;
	bool operator<=(const Vector2Temple& vec)const;
	bool operator<(const Vector2Temple& vec)const;
};
template <class T>
Vector2Temple<T> operator+(const Vector2Temple<T>& u, T v);
template <class T>
Vector2Temple<T> operator-(const Vector2Temple<T>& u, T v);
template <class T>
Vector2Temple<T> operator*(const Vector2Temple<T>& u, T v);
template <class T>
Vector2Temple<T> operator/(const Vector2Temple<T>& u, T v);
template <class T>
Vector2Temple<T> operator*(const T& u, Vector2Temple<T>& v);
template <class T>
Vector2Temple<T> operator%(const Vector2Temple<T>& u, T v);
template <class T>
Vector2Temple<T> operator+(const Vector2Temple<T>& u, T v);
template <class T>
Vector2Temple<T> operator+(const Vector2Temple<T>& u, Vector2Temple<T> v);
template <class T>
Vector2Temple<T> operator-(const Vector2Temple<T>& u, Vector2Temple<T> v);

using Vector2 = Vector2Temple<int>;
using Vector2Dbl = Vector2Temple<double>;
using Vector2Flt = Vector2Temple<float>;
using Vector2Lg = Vector2Temple<long>;

//Vector2 operator+(const Vector2& u, int v);
//Vector2 operator+(const Vector2& u, int v);
//Vector2 operator+(const Vector2& u, int v);
//Vector2 operator+(const Vector2& u, int v);
//Vector2 operator+(const Vector2& u, int v);

#include "./details/Vector2.h"