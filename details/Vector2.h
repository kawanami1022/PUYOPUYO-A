#include "../Vector2.h"

template <class T>
Vector2Temple<T>::Vector2Temple()
{
	x = 0;
	y = 0;
}

template <class T>
Vector2Temple<T>::Vector2Temple(T x, T y)
{
	Vector2Temple::x = x;
	Vector2Temple::y = y;
}

template <class T>
Vector2Temple<T>::~Vector2Temple()
{
}

template <class T>
Vector2Temple<T>& Vector2Temple<T>::operator=(const Vector2Temple<T>& vec)
{
	x = vec.x;
	y = vec.y;

	// TODO: return ステートメントをここに挿入します
	return (*this);
}

template <class T>
T& Vector2Temple<T>::operator[](int no)
{
	if (no==0)
	{
		return x;
	}
	else if(no==1)
	{
		return y;
	}
	else
	{
		return x;
	}
}

template <class T>
Vector2Temple<T>& Vector2Temple<T>::operator+=(const Vector2Temple& vec)
{
	x += vec.x;
	y += vec.y;
	return  (*this);
}

template <class T>
Vector2Temple<T>& Vector2Temple<T>::operator-=(const Vector2Temple& vec)
{
	x -= vec.x;
	y -= vec.y;
	// TODO: return ステートメントをここに挿入します
	return (*this);

}

template <class T>
Vector2Temple<T>& Vector2Temple<T>::operator+=(T k)
{
	// TODO: return ステートメントをここに挿入します
	x += k;
	y += k;
	return (*this);
}

template <class T>
Vector2Temple<T>& Vector2Temple<T>::operator*=(T k)
{
	x *= k;
	y *= k;
	// TODO: return ステートメントをここに挿入します
	return (*this);
}

template<class T>
Vector2Temple<T>& Vector2Temple<T>::operator*=(T& k)
{
	x *= k;
	y *= k;
	// TODO: return ステートメントをここに挿入します
	return (*this);
}

template <class T>
Vector2Temple<T>& Vector2Temple<T>::operator/=(T k)
{
	x /= k;
	y /= k;
	// TODO: return ステートメントをここに挿入します
	return *this;
}

template<class T>
Vector2Temple<T>& Vector2Temple<T>::operator++()
{
	this->x++;
	this->y ++;
	// TODO: return ステートメントをここに挿入します
	return (*this);
}

template<class T>
Vector2Temple<T> Vector2Temple<T>::operator+() const
{
	// TODO: return ステートメントをここに挿入します
	return (*this);
}

template <class T>
Vector2Temple<T> Vector2Temple<T>::operator-() const
{
	// TODO: return ステートメントをここに挿入します
	return {-this->x, -this->y};
}

template <class T>
bool Vector2Temple<T>::operator==(const Vector2Temple& vec) const
{
	return ((this->x == vec.x) && (this->y == vec.y));
}

template <class T>
bool Vector2Temple<T>::operator!=(const Vector2Temple& vec) const
{
	return ((this->x != vec.x) || (this->y != vec.y));
}

template <class T>
bool Vector2Temple<T>::operator<=(const Vector2Temple& vec) const
{
	return ((this->x <= vec.x) || (this->y <= vec.y));;
}

template <class T>
bool Vector2Temple<T>::operator<(const Vector2Temple& vec) const
{
	return ((this->x < vec.x) && (this->y <vec.y));;
}

template<class T>
Vector2Temple<T> operator+(const Vector2Temple<T>& u, T v)
{
	return {u.x+v,u.y + v };
}

template <class T>
Vector2Temple<T> operator-(const Vector2Temple<T>& u, T v)
{
	return { u.x - v,u.y - v };;
}

template <class T>
Vector2Temple<T> operator*(const Vector2Temple<T>& u, T v)
{
	return { u.x * v,u.y * v };
}

template<class T>
Vector2Temple<T> operator*(const Vector2Temple<T>& u, Vector2Temple<T>& v)
{
	return { u.x * v.y,u.y * v.y };
}

template <class T>
Vector2Temple<T> operator/(const Vector2Temple<T>& u, T v)
{

	return { u.x / v,u.y / v };
}

template <class T>
Vector2Temple<T> operator%(const Vector2Temple<T>& u, T v)
{
	return { u.x % v,u.y % v };
}

template <class T>
Vector2Temple<T> operator+(const Vector2Temple<T>& u, Vector2Temple<T> v)
{
	return { u.x + v.x,u.y + v.y };

}

template <class T>
Vector2Temple<T> operator-(const Vector2Temple<T>& u, Vector2Temple<T> v)
{
	return { u.x - v.x,u.y - v.y };
}



