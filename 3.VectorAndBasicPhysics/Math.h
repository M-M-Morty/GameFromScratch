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

	inline float Lerp(float a, float b, float f)//f取值范围为[0,1]
	{
		return a + f * (b - a);
	}

	inline float Sqrt(float value)
	{
		return sqrtf(value);
	}

	inline float Fmod(float numer, float denom)//整除
	{
		return fmod(numer, denom);
	}
}




//2D向量
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

	//重新设置vector2的两个参数值
	void Set(float inX, float inY)
	{
		x = inX;
		y = inY;
	}

	//两个vector2相加
	friend Vector2 operator+(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x + b.x, a.y + b.y);
	}

	//两个vector2相减
	friend Vector2 operator-(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x - b.x, a.y - b.y);
	}

	//两个vector2相乘
	friend Vector2 operator*(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x * b.x, a.y * b.y);
	}

	//缩放一个向量，缩放值在后
	friend Vector2 operator*(const Vector2& vec, float scalar)
	{
		return Vector2(vec.x * scalar, vec.y * scalar);
	}

	//缩放一个向量，缩放值在前
	friend Vector2 operator*(float scalar,const Vector2& vec)
	{
		return Vector2(vec.x * scalar, vec.y * scalar);
	}

	//*=一个缩放值
	Vector2& operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;
		return *this;
	}

	//+=另一个vector2
	Vector2& operator+=(const Vector2& right)
	{
		x += right.x;
		y += right.y;
		return *this;
	}

	//-=另一个vector2
	Vector2& operator-=(const Vector2& right)
	{
		x -= right.x;
		y -= right.y;
		return *this;
	}

	//获取vector2长度的平方
	float LengthSq() const
	{
		return (x * x + y * y);
	}

	//获取vector2的长度
	float Length()const
	{
		return (Math::Sqrt(LengthSq()));
	}

	//标准化vector2
	void Normalize()
	{
		float length = Length();
		x /= length;
		y /= length;
	}

	//得到一个vector2的标准化值并返回
	static Vector2 Normalize(const Vector2& vec)
	{
		Vector2 temp = vec;
		temp.Normalize();
		return temp;
	}

	//得到两个给定vector2的点乘值
	static float Dot(const Vector2& a, const Vector2& b)
	{
		return (a.x * b.x + a.y * b.y);
	}

	//对a到b进行线性插值，再根据f得到具体的值并返回
	static Vector2 Lerp(const Vector2& a, const Vector2& b, float f)
	{
		return(a + f * (b - a));
	}

	//根据一个标准化的法向量n，和一个入射向量v得到一个反射向量并返回
	static Vector2 Reflect(const Vector2& v, const Vector2& n)
	{
		return v - 2.0f * Vector2::Dot(v, n) * n;
	}


	//根据矩阵对向量进行变换
	static Vector2 Transform(const Vector2& vec, const class Matrix3& mat, float w = 1.0f);

	static const Vector2 Zero;//返回一个零向量
	static const Vector2 UnitX;
	static const Vector2 UnitY;
	static const Vector2 NegUnitX;
	static const Vector2 NegUnitY;
};