#pragma once
#include <chrono>

class Matrix4f
{
public:
			Matrix4f();
			~Matrix4f();

	// Access
	float	get(int x, int y) const;

	// Rotations
	void	rotateX(float d);
	void	rotateY(float d);
	void	rotateZ(float d);

	// Translations
	void	transform(float X, float Y, float Z);
	void	transformX(float X);
	void	transformY(float Y);
	void	transformZ(float Z);
	
	// Set the identity matrix
	void	setIndentity();

	// Operator overloads
/*	Matrix& operator+(const Matrix& m);
	Matrix& operator+(const Matrix& m);
	Matrix& operator+(const Matrix& m);
	Matrix& operator+(const Matrix& m);
	*/

private:
	float	m_Data[16];
};

class Vertex4f
{
public:
			Vertex4f();
			~Vertex4f();

	Vertex4f operator*(const Matrix4f &m);

private:
	float	m_Data[4];
};

