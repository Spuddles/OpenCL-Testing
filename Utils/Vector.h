#pragma once

class Matrix4f;

class Vertex4f
{
public:
	Vertex4f();
	~Vertex4f();

	Vertex4f operator*(const Matrix4f &m);

private:
	float	m_Data[4];
};