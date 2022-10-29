#pragma once
#include <cmath>
#include <memory.h>
#include <limits>

namespace Math
{ 

	const float Pi= 3.1415926535f;
	const float TwoPi = Pi * 2.0f;
	const float PiOver2 = Pi / 2.0f;
	const float Infinity = std::numeric_limits<float>::infinity();
	const float NeInfinity=-std::numeric_limits<float>::infinity();

	inline float ToRadians(float degrees)
	{
		return degrees * Pi / 180.f;
	}

	inline float ToDegrees(float radians)
	{
		return radians * 180.0f / Pi;
	}

	inline bool NearZero(float val, float epsilon = 0.001f)
	{
		if (fabs(val) <= epsilon)
			return true;
		return false;
	}

	template<typename T>
	T Max(const T& a, const T& b)
	{
		return (a < b ? b : a);
	}

	template<typename T>
	T Min(const T& a, const T& b)
	{
		return (a < b ? a : b);
	}

	template<typename T>
	T Clamp(const T& value, const T& lower, const T& upper)
	{
		return Min(Max(lower, value),upper);
	}

	inline float Abs(float value)
	{
		return fabs(value);
	}

	inline  float Cos(float angle)
	{
		return cosf(angle);
	}

	inline  float Sin(float angle)
	{
		return sinf(angle);
	}

	inline  float Tan(float angle)
	{
		return tanf(angle);
	}

	inline float Acos(float value)
	{
		return acosf(value);
	}

	inline float Atan2(float y, float x)
	{
		return atan2f(y, x);
	}

	inline float Cot(float angle)
	{
		return 1.0f / Tan(angle);
	}

	inline float Lerp(float a, float b, float f)//fȡֵ��ΧΪ[0,1]
	{
		return a + f * (b - a);
	}

	inline float Sqrt(float value)
	{
		return sqrtf(value);
	}

	inline float Fmod(float numer, float denom)//����
	{
		return fmod(numer, denom);
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