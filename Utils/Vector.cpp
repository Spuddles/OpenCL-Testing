#include "Vector.h"
#include "Matrix.h"

Vector4f::Vector4f()
{
}

Vector4f::Vector4f(float x, float y, float z, float w)
{
	m_Data[0] = x;
	m_Data[1] = y;
	m_Data[2] = z;
	m_Data[3] = w;
}

Vector4f::~Vector4f()
{
}

void Vector4f::set(float x, float y, float z, float w)
{
	m_Data[0] = x;
	m_Data[1] = y;
	m_Data[2] = z;
	m_Data[3] = w;
}

Vector4f Vector4f::operator*(const Matrix4f &m)
{
	Vector4f v;

	for (int i = 0; i < 4; i++)
	{
		v.m_Data[i] = (m_Data[0] * m.get(i, 0))
			+ (m_Data[1] * m.get(i, 1))
			+ (m_Data[2] * m.get(i, 2))
			+ (m_Data[3] * m.get(i, 3));
	}
	return v;
}

Vector4f Vector4f::operator+(const Vector4f &v)
{
	Vector4f retv;

	float x, y, z, w;

	x = m_Data[0] + v.x();
	y = m_Data[1] + v.y();
	z = m_Data[2] + v.z();
	w = m_Data[3] + v.w();

	retv.set(x, y, z, w);
	return retv;
}

Vector4f Vector4f::operator-(const Vector4f &v)
{
	Vector4f retv;

	float x, y, z, w;

	x = m_Data[0] - v.x();
	y = m_Data[1] - v.y();
	z = m_Data[2] - v.z();
	w = m_Data[3] - v.w();

	retv.set(x, y, z, w);
	return retv;
}

float Vector4f::dotProduct(const Vector4f &v) const
{
	float result = (x() * v.x()) +
		(y() * v.y()) +
		(z() * v.z()) +
		(w() * v.w());
	return result;
}

Vector4f Vector4f::crossProduct(const Vector4f &v) const
{
	Vector4f	result;

	float X = (y()*v.z()) - (z()*v.y());
	float Y = (z()*v.x()) - (x()*v.z());
	float Z = (x()*v.y()) - (y()*v.x());
	result.set(X, Y, Z, 0.0f);
	return result;

}
