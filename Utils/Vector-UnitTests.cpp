#include "Vector.h"
#include "Matrix.h"
#include "gtest\gtest.h"

TEST(Vector, TestInitialiseEmpty)
{
	Vertex4f v;

	EXPECT_EQ(0.0f, v.x());
	EXPECT_EQ(0.0f, v.y());
	EXPECT_EQ(0.0f, v.z());
	EXPECT_EQ(0.0f, v.w());
}

TEST(Vector, TestInitialiseValues)
{
	Vertex4f v(1.0f, 2.0f, 3.0f, 4.0f);

	EXPECT_EQ(1.0f, v.x());
	EXPECT_EQ(2.0f, v.y());
	EXPECT_EQ(3.0f, v.z());
	EXPECT_EQ(4.0f, v.w());
}

TEST(Vector, TestMultiply)
{
	Matrix4f	m;
	m.setIdentity();

	Vertex4f	v(1.0f, 2.0f, 3.0f, 4.0f);

	Vertex4f v2 = v * m;

	EXPECT_EQ(1.0f, v2.x());
	EXPECT_EQ(2.0f, v2.y());
	EXPECT_EQ(3.0f, v2.z());
	EXPECT_EQ(4.0f, v2.w());
}

TEST(Vector, TestMultiply2)
{
	Matrix4f	m{ 2.0f };
	Vertex4f	v(1.0f, 2.0f, 3.0f, 4.0f);

	Vertex4f v2 = v * m;

	EXPECT_EQ(20.0f, v2.x());
	EXPECT_EQ(20.0f, v2.y());
	EXPECT_EQ(20.0f, v2.z());
	EXPECT_EQ(20.0f, v2.w());
}