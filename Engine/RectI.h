#pragma once

#include "Vector2.h"

class RectI
{
public:
	RectI() = default;
	RectI( int left_in,int right_in,int top_in,int bottom_in );
	RectI( const Vector2_Int& topLeft,const Vector2_Int& bottomRight );
	RectI( const Vector2_Int& topLeft,int width,int height );
	bool IsOverlappingWith( const RectI& other ) const;
	bool IsContainedBy( const RectI& other ) const;
	static RectI FromCenter( const Vector2_Int& center,int halfWidth,int halfHeight );
	RectI GetExpanded( int offset ) const;
	Vector2_Int GetCenter() const;
public:
	int left;
	int right;
	int top;
	int bottom;
};