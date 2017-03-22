#include "Vector.h"
#include "Matrix.h"

Vertex4f::Vertex4f()
{
}

Vertex4f::Vertex4f(float x, float y, float z, float w)
{
	m_Data[0] = x;
	m_Data[1] = y;
	m_Data[2] = z;
	m_Data[3] = w;
}

Vertex4f::~Vertex4f()
{
}

void Vertex4f::set(float x, float y, float z, float w)
{
	m_Data[0] = x;
	m_Data[1] = y;
	m_Data[2] = z;
	m_Data[3] = w;
}

Vertex4f Vertex4f::operator*(const Matrix4f &m)
{
	Vertex4f v;

	for (int i = 0; i < 4; i++)
	{
		v.m_Data[i] = m_Data[0] * m.get(0, 0); // TODO
	}
	return v;
}

Vertex4f Vertex4f::operator+(const Vertex4f &v)
{
	Vertex4f retv;

	float x, y, z, w;

	x = m_Data[0] + v.x();
	y = m_Data[1] + v.y();
	z = m_Data[2] + v.z();
	w = m_Data[3] + v.w();

	retv.set(x, y, z, w);
	return retv;
}