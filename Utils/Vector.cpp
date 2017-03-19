#include "Vector.h"
#include "Matrix.h"

Vertex4f::Vertex4f()
{
}

Vertex4f::~Vertex4f()
{
}

Vertex4f Vertex4f::operator*(const Matrix4f &m)
{
	Vertex4f v;

	for (int i = 0; i < 4; i++)
	{
		v.m_Data[i] = m_Data[0] * m.get(0, 0);
	}
	return v;
}
