#include "Rectangle.h"

/*
INTEGERS
*/
Rectangle_Int::Rectangle_Int( int left_in,int right_in,int top_in,int bottom_in )
	:
	left( left_in ),
	right( right_in ),
	top( top_in ),
	bottom( bottom_in )
{
}

Rectangle_Int::Rectangle_Int( const Vector2_Int& topLeft,const Vector2_Int & bottomRight )
	:
	Rectangle_Int( topLeft.x,bottomRight.x,topLeft.y,bottomRight.y )
{
}

Rectangle_Int::Rectangle_Int( const Vector2_Int& topLeft,int width,int height )
	:
	Rectangle_Int( topLeft,topLeft + Vector2_Int( width,height ) )
{
}

bool Rectangle_Int::IsOverlappingWith( const Rectangle_Int& other ) const
{
	return right > other.left && left < other.right
		&& bottom > other.top && top < other.bottom;
}

bool Rectangle_Int::IsContainedBy( const Rectangle_Int & other ) const
{
	return left >= other.left && right <= other.right &&
		top >= other.top && bottom <= other.bottom;
}

Rectangle_Int Rectangle_Int::FromCenter( const Vector2_Int & center,int halfWidth,int halfHeight )
{
	const Vector2_Int half( halfWidth,halfHeight );
	return Rectangle_Int( center - half,center + half );
}

Rectangle_Int Rectangle_Int::GetExpanded( int offset ) const
{
	return Rectangle_Int( left - offset,right + offset,top - offset,bottom + offset );
}

Vector2_Int Rectangle_Int::GetCenter() const
{
	return Vector2_Int( (left + right) / 2,(top + bottom) / 2 );
}

/*
FLOATS
*/
Rectangle_Float::Rectangle_Float(float left_in, float right_in, float top_in, float bottom_in)
	:
	left(left_in),
	right(right_in),
	top(top_in),
	bottom(bottom_in)
{
}

Rectangle_Float::Rectangle_Float(const Vector2_Float & topLeft, const Vector2_Float & bottomRight)

	:
	Rectangle_Float(topLeft.x, bottomRight.x, topLeft.y, bottomRight.y)
{
}

Rectangle_Float::Rectangle_Float(const Vector2_Float & topLeft, float width, float height)
	:
	Rectangle_Float(topLeft, topLeft + Vector2_Float(width, height))
{
}

bool Rectangle_Float::IsOverlappingWith(const Rectangle_Float & other) const
{
	return right > other.left && left < other.right
		&& bottom > other.top && top < other.bottom;
}

bool Rectangle_Float::IsContainedBy(const Rectangle_Float & other) const
{
	return left >= other.left && right <= other.right &&
		top >= other.top && bottom <= other.bottom;
}

Rectangle_Float Rectangle_Float::FromCenter(const Vector2_Float & center, float halfWidth, float halfHeight)
{
	const Vector2_Float half(halfWidth, halfHeight);
	return Rectangle_Float(center - half, center + half);
}

Rectangle_Float Rectangle_Float::GetExpanded(float offset) const
{
	return Rectangle_Float(left - offset, right + offset, top - offset, bottom + offset);
}

Vector2_Float Rectangle_Float::GetCenter() const
{
	return Vector2_Float((left + right) / 2, (top + bottom) / 2);
}
