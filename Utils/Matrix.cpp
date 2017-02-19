#include "Matrix.h"


Matrix::Matrix()
{
}

Matrix::~Matrix()
{
}

void Matrix::RotateZ(float &x, float &y, float time)
{
	float x1 = x*std::cos(time) - y*std::sin(time);
	float y1 = x*std::sin(time) + y*std::cos(time);
	x = x1;
	y = y1;
}