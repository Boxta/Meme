#pragma once
class Vector2_Int
{
public:
	Vector2_Int() = default;
	Vector2_Int(int x_in, int y_in);
	Vector2_Int operator+(const Vector2_Int& rhs) const;
	Vector2_Int& operator+=(const Vector2_Int& rhs);
	Vector2_Int operator*(int rhs) const;
	Vector2_Int& operator*=(int rhs);
	Vector2_Int operator-(const Vector2_Int& rhs) const;
	Vector2_Int& operator-=(const Vector2_Int& rhs);
	Vector2_Int operator/(int rhs) const;
	Vector2_Int& operator/=(int rhs);
	float GetLength() const;
	int GetLengthSq() const;
public:
	int x;
	int y;
};
class Vector2_Float
{
public:
	Vector2_Float() = default;
	Vector2_Float(int x_in, int y_in);
	Vector2_Float operator+(const Vector2_Float& rhs) const;
	Vector2_Float& operator+=(const Vector2_Float& rhs);
	Vector2_Float operator*(int rhs) const;
	Vector2_Float& operator*=(int rhs);
	Vector2_Float operator-(const Vector2_Float& rhs) const;
	Vector2_Float& operator-=(const Vector2_Float& rhs);
	Vector2_Float operator/(int rhs) const;
	Vector2_Float& operator/=(int rhs);
	float GetLength() const;
	int GetLengthSq() const;
public:
	float x;
	float y;
};