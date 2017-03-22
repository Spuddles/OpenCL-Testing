#pragma once

class Matrix4f;

class Vertex4f
{
public:
	Vertex4f();
	Vertex4f(float x, float y, float z, float w);
	~Vertex4f();

	void	set(float x, float y, float z, float w);
	float	x() const { return m_Data[0]; }
	float	y() const { return m_Data[1]; }
	float	z() const { return m_Data[2]; }
	float	w() const { return m_Data[3]; }

	Vertex4f operator*(const Matrix4f &m);
	Vertex4f operator+(const Vertex4f &v);

private:
	float	m_Data[4] = { 0.0f };
};