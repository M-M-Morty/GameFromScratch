#pragma once
#include <cmath>

namespace Math
{ 

	const float Pi= 3.1415926535f;








	inline float ToDegrees(float radians)
	{
		return radians * 180.0f / Pi;
	}


	inline float Sqrt(float value)
	{
		return sqrtf(value);
	}









}




//2D����
class Vector2
{
public:
	float x;
	float y;

	Vector2()
		:x(0.0f)
		,y(0.0f)
	{}

	explicit Vector2(float inX,float inY)
		:x(inX)
		,y(inY)
	{}

	//��������vector2����������ֵ
	void Set(float inX, float inY)
	{
		x = inX;
		y = inY;
	}

	//����vector2���
	friend Vector2 operator+(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x + b.x, a.y + b.y);
	}

	//����vector2���
	friend Vector2 operator-(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x - b.x, a.y - b.y);
	}

	//����vector2���
	friend Vector2 operator*(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x * b.x, a.y * b.y);
	}

	//����һ������������ֵ�ں�
	friend Vector2 operator*(const Vector2& vec, float scalar)
	{
		return Vector2(vec.x * scalar, vec.y * scalar);
	}

	//����һ������������ֵ��ǰ
	friend Vector2 operator*(float scalar,const Vector2& vec)
	{
		return Vector2(vec.x * scalar, vec.y * scalar);
	}

	//*=һ������ֵ
	Vector2& operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;
		return *this;
	}

	//+=��һ��vector2
	Vector2& operator+=(const Vector2& right)
	{
		x += right.x;
		y += right.y;
		return *this;
	}

	//-=��һ��vector2
	Vector2& operator-=(const Vector2& right)
	{
		x -= right.x;
		y -= right.y;
		return *this;
	}

	//��ȡvector2���ȵ�ƽ��
	float LengthSq() const
	{
		return (x * x + y * y);
	}

	//��ȡvector2�ĳ���
	float Length()const
	{
		return (Math::Sqrt(LengthSq()));
	}

	//��׼��vector2
	void Normalize()
	{
		float length = Length();
		x /= length;
		y /= length;
	}

	//�õ�һ��vector2�ı�׼��ֵ������
	static Vector2 Normalize(const Vector2& vec)
	{
		Vector2 temp = vec;
		temp.Normalize();
		return temp;
	}

	//�õ���������vector2�ĵ��ֵ
	static float Dot(const Vector2& a, const Vector2& b)
	{
		return (a.x * b.x + a.y * b.y);
	}

	//��a��b�������Բ�ֵ���ٸ���f�õ������ֵ������
	static Vector2 Lerp(const Vector2& a, const Vector2& b, float f)
	{
		return(a + f * (b - a));
	}

	//����һ����׼���ķ�����n����һ����������v�õ�һ����������������
	static Vector2 Reflect(const Vector2& v, const Vector2& n)
	{
		return v - 2.0f * Vector2::Dot(v, n) * n;
	}


	//���ݾ�����������б任
	static Vector2 Transform(const Vector2& vec, const class Matrix3& mat, float w = 1.0f);

	static const Vector2 Zero;//����һ��������
	static const Vector2 UnitX;
	static const Vector2 UnitY;
	static const Vector2 NegUnitX;
	static const Vector2 NegUnitY;
};