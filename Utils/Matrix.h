#pragma once
#include <chrono>

class Matrix4f
{
public:
			Matrix4f();
			Matrix4f(float value);
			Matrix4f(float values[16]);
			~Matrix4f();

	// Access
	float	get(unsigned int x, unsigned int y) const;

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
	void	setIdentity();

	// Operator overloads
	bool operator==(const Matrix4f &m);

/*	Matrix& operator+(const Matrix &m);
	Matrix& operator+(const Matrix &m);
	Matrix& operator+(const Matrix &m);
	Matrix& operator+(const Matrix &m);
	*/

private:
	float	m_Data[16] = { 0.0f };
};



