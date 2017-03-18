#pragma once

template <class T>
class Point
{
public:
	Point();
	Point(T X, T Y);
	~Point();

	Point<T>& operator+(const Point<T> p);

	T	x{ 0 };
	T	y{ 0 };
};

template <class T>
Point<T>::Point()
{
}

template <class T>
Point<T>::Point(T X, T Y) :
	x{ X }, y{ Y }
{
}

template <class T>
Point<T>::~Point()
{
}

template <class T>
Point<T>& Point<T>::operator+(const Point<T> p)
{
	x += p.x;
	y += p.y;
	return this;
}
