#pragma once

#include "Vector2.h"

class Rectangle_Int
{
public:
	Rectangle_Int() = default;
	Rectangle_Int( int left_in,int right_in,int top_in,int bottom_in );
	Rectangle_Int( const Vector2_Int& topLeft,const Vector2_Int& bottomRight );
	Rectangle_Int( const Vector2_Int& topLeft,int width,int height );
	bool IsOverlappingWith( const Rectangle_Int& other ) const;
	bool IsContainedBy( const Rectangle_Int& other ) const;
	static Rectangle_Int FromCenter( const Vector2_Int& center,int halfWidth,int halfHeight );
	Rectangle_Int GetExpanded( int offset ) const;
	Vector2_Int GetCenter() const;
public:
	int left;
	int right;
	int top;
	int bottom;
};

class Rectangle_Float
{
public:
	Rectangle_Float() = default;
	Rectangle_Float(float left_in, float right_in, float top_in, float bottom_in);
	Rectangle_Float(const Vector2_Float& topLeft, const Vector2_Float& bottomRight);
	Rectangle_Float(const Vector2_Float& topLeft, float width, float height);
	bool IsOverlappingWith(const Rectangle_Float& other) const;
	bool IsContainedBy(const Rectangle_Float& other) const;
	static Rectangle_Float FromCenter(const Vector2_Float& center, float halfWidth, float halfHeight);
	Rectangle_Float GetExpanded(float offset) const;
	Vector2_Float GetCenter() const;
public:
	float left;
	float right;
	float top;
	float bottom;
};