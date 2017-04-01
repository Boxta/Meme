#include "Vector2.h"
#include <cmath>

/*
INTEGERS
*/

Vector2_Int::Vector2_Int( int x_in,int y_in )
	:
	x( x_in ),
	y( y_in )
{
}

Vector2_Int Vector2_Int::operator+( const Vector2_Int& rhs ) const
{
	return Vector2_Int( x + rhs.x,y + rhs.y );
}

Vector2_Int& Vector2_Int::operator+=( const Vector2_Int& rhs )
{
	return *this = *this + rhs;
}

Vector2_Int Vector2_Int::operator*( int rhs ) const
{
	return Vector2_Int( x * rhs,y * rhs );
}

Vector2_Int& Vector2_Int::operator*=( int rhs )
{
	return *this = *this * rhs;
}

Vector2_Int Vector2_Int::operator-( const Vector2_Int& rhs ) const
{
	return Vector2_Int( x - rhs.x,y - rhs.y );
}

Vector2_Int& Vector2_Int::operator-=( const Vector2_Int& rhs )
{
	return *this = *this - rhs;
}

Vector2_Int Vector2_Int::operator/( int rhs ) const
{
	return Vector2_Int( x / rhs,y / rhs );
}

Vector2_Int& Vector2_Int::operator/=( int rhs )
{
	return *this = *this / rhs;
}

int Vector2_Int::GetLength() const
{
	return (int)std::sqrt( int( GetLengthSq() ) );
}

int Vector2_Int::GetLengthSq() const
{
	return x * x + y * y;
}

/*
FLOATS
*/

Vector2_Float::Vector2_Float(float x_in, float y_in)
	:
	x(x_in),
	y(y_in)
{

}

Vector2_Float Vector2_Float::operator+(const Vector2_Float & rhs) const
{
	return Vector2_Float(x + rhs.x, y + rhs.y);
}

Vector2_Float & Vector2_Float::operator+=(const Vector2_Float & rhs)
{
	return *this = *this + rhs;
}

Vector2_Float Vector2_Float::operator*(float rhs) const
{
	return Vector2_Float(x * rhs, y * rhs);
}

Vector2_Float & Vector2_Float::operator*=(float rhs)
{
	return *this = *this * rhs;
}

Vector2_Float Vector2_Float::operator-(const Vector2_Float & rhs) const
{
	return Vector2_Float(x - rhs.x, y - rhs.y);
}

Vector2_Float & Vector2_Float::operator-=(const Vector2_Float & rhs)
{
	return *this = *this - rhs;
}

Vector2_Float Vector2_Float::operator/(float rhs) const
{
	return Vector2_Float(x / rhs, y / rhs);
}

Vector2_Float & Vector2_Float::operator/=(float rhs)
{
	return *this = *this / rhs;
}

float Vector2_Float::GetLength() const
{
	return std::sqrt(float(GetLengthSq()));
}

float Vector2_Float::GetLengthSq() const
{
	return x * x + y * y;
}
