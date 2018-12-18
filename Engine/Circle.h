#pragma once

#include "Vec2.h"

class Circle
{
public:
	Circle() = default;
	Circle( const Vec2& pos,float radius )
		:
		pos( pos ),
		radius( radius )
	{}
public:
	Vec2 pos;
	float radius;
};