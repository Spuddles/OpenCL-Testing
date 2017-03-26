#pragma once

class Matrix4f;

class Vector4f
{
public:
	Vector4f();
	Vector4f(float x, float y, float z, float w);
	~Vector4f();

	void	set(float x, float y, float z, float w);
	float	x() const { return m_Data[0]; }
	float	y() const { return m_Data[1]; }
	float	z() const { return m_Data[2]; }
	float	w() const { return m_Data[3]; }

	Vector4f operator*(const Matrix4f &m);
	Vector4f operator+(const Vector4f &v);
	Vector4f operator-(const Vector4f &v);
	float	 dotProduct(const Vector4f &v) const;
	Vector4f crossProduct(const Vector4f &v) const;


private:
	float	m_Data[4] = { 0.0f };
};