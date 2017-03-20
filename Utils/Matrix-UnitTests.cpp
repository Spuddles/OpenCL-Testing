#include "Matrix.h"
#include "gtest\gtest.h"

TEST(Matrix, TestInitialiseEmpty)
{
	Matrix4f m;

	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			EXPECT_EQ(m.get(x, y), 0.0f);
		}
	}
}

TEST(Matrix, TestInitiliseSingleValue)
{
	Matrix4f m(345.0f);

	for (int i = 0; i < 16; i++)
	{
		EXPECT_EQ(345.0f, m.get(i % 4, i / 4));
	}
}

TEST(Matrix, TestInitialiseAllValues)
{
	float values[16] = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f,
		9.0f, 10.0f, 11.0f, 12.0f, 13.0f, 14.0f, 15.0f, 16.0f };

	Matrix4f m(values);

	for (int i = 0; i < 16; i++)
	{
		EXPECT_EQ(values[i], m.get(i % 4, i / 4));
	}
}
	
TEST(Matrix, TestSetValue)
{
	Matrix4f m(1.0f);
	m.set(0, 0, 123.0f);
	EXPECT_EQ(123.0f, m.get(0, 0));
}

TEST(Matrix, TestGetValue)
{
	Matrix4f	m(123.0f);

	for (int i = 0; i < 16; i++)
	{
		EXPECT_EQ(123.0f, m.get(i % 4, i / 4));
	}
}

TEST(Matrix, TestIdentity)
{
	Matrix4f m;
	m.setIdentity();

	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			if (x == y)
			{
				EXPECT_EQ(m.get(x, y),1.0f);
			}
			else
			{
				EXPECT_EQ(m.get(x, y),0.0f);
			}
		}
	}
}

TEST(Matrix, TestTransform)
{
	Matrix4f m;

	m.transform(3.0f, 4.0f, 5.0f);

	EXPECT_EQ(3.0f, m.get(0, 3));
	EXPECT_EQ(4.0f, m.get(1, 3));
	EXPECT_EQ(5.0f, m.get(2, 3));
}

TEST(Matrix, TestTransformX)
{
	Matrix4f m;

	m.transformX(3.0f);

	EXPECT_EQ(3.0f, m.get(0, 3));
}

TEST(Matrix, TestTransformY)
{
	Matrix4f m;

	m.transformY(4.0f);

	EXPECT_EQ(4.0f, m.get(1, 3));
}

TEST(Matrix, TestTransformZ)
{
	Matrix4f m;

	m.transformZ(5.0f);

	EXPECT_EQ(5.0f, m.get(2, 3));
}

TEST(Matrix, TestRotateX1)
{
	Matrix4f m(1.0f);

	// Test roation by 90 degrees
	m.rotateX(90.0);
}

TEST(Matrix, TestEquality)
{
	Matrix4f	m1(1.0f);
	Matrix4f	m2(2.0f);
	Matrix4f	m3(1.0f);

	EXPECT_EQ(true, m1 == m3);
	EXPECT_EQ(false, m1 == m2);
}

TEST(Matrix, TestInequality)
{
	Matrix4f	m1(1.0f);
	Matrix4f	m2(2.0f);
	Matrix4f	m3(1.0f);

	EXPECT_EQ(true, m1 != m2);
	EXPECT_EQ(false, m1 != m3);
}

TEST(Matrix, TestAddition)
{
	Matrix4f	m1(1.0f);
	Matrix4f	m2(2.0f);
	Matrix4f	answer(3.0f);

	Matrix4f	m3 = m1 + m2;

	EXPECT_EQ(true, m3 == answer);
}

TEST(Matrix, TestSubtraction)
{
	Matrix4f	m1(3.0f);
	Matrix4f	m2(2.0f);
	Matrix4f	answer(1.0f);

	Matrix4f	m3 = m1 - m2;

	EXPECT_EQ(true, m3 == answer);
}

TEST(Matrix, TestMultiplication)
{
	Matrix4f	m1(3.0f);
	Matrix4f	m2(2.0f);
	Matrix4f	answer(24.0f);

	Matrix4f	m3 = m1 * m2;

	EXPECT_EQ(true, m3 == answer);
}
