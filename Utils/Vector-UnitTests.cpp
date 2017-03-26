#include "Vector.h"
#include "Matrix.h"
#include "gtest\gtest.h"

TEST(Vector, TestInitialiseEmpty)
{
	Vector4f v;

	EXPECT_EQ(0.0f, v.x());
	EXPECT_EQ(0.0f, v.y());
	EXPECT_EQ(0.0f, v.z());
	EXPECT_EQ(0.0f, v.w());
}

TEST(Vector, TestInitialiseValues)
{
	Vector4f v(1.0f, 2.0f, 3.0f, 4.0f);

	EXPECT_EQ(1.0f, v.x());
	EXPECT_EQ(2.0f, v.y());
	EXPECT_EQ(3.0f, v.z());
	EXPECT_EQ(4.0f, v.w());
}

TEST(Vector, TestMultiply)
{
	Matrix4f	m;
	m.setIdentity();

	Vector4f	v(1.0f, 2.0f, 3.0f, 4.0f);

	Vector4f v2 = v * m;

	EXPECT_EQ(1.0f, v2.x());
	EXPECT_EQ(2.0f, v2.y());
	EXPECT_EQ(3.0f, v2.z());
	EXPECT_EQ(4.0f, v2.w());
}

TEST(Vector, TestMultiply2)
{
	Matrix4f	m{ 2.0f };
	Vector4f	v(1.0f, 2.0f, 3.0f, 4.0f);

	Vector4f v2 = v * m;

	EXPECT_EQ(20.0f, v2.x());
	EXPECT_EQ(20.0f, v2.y());
	EXPECT_EQ(20.0f, v2.z());
	EXPECT_EQ(20.0f, v2.w());
}

TEST(Vector, TestAddition)
{
	Vector4f	a(1.0f, 1.0f, 1.0f, 1.0f);
	Vector4f	b(3.0f, 4.0f, 5.0f, 6.0f);

	Vector4f	c = a + b;

	EXPECT_EQ(4.0f, c.x());
	EXPECT_EQ(5.0f, c.y());
	EXPECT_EQ(6.0f, c.z());
	EXPECT_EQ(7.0f, c.w());
}

TEST(Vector, TestSubtraction)
{
	Vector4f	a(3.0f, 4.0f, 5.0f, 6.0f);
	Vector4f	b(1.0f, 1.0f, 1.0f, 1.0f);

	Vector4f	c = a - b;

	EXPECT_EQ(2.0f, c.x());
	EXPECT_EQ(3.0f, c.y());
	EXPECT_EQ(4.0f, c.z());
	EXPECT_EQ(5.0f, c.w());
}