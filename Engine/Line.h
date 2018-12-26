#pragma once

#include "Vec2.h"

class Line
{
public:
	Line() = default;
	Line( const Vec2& first,const Vec2& second )
		:
		start( first ),
		end( second )
	{}
	void ShrinkBy( float amount )
	{
		const auto diff = GetDiff().GetNormalized();

		start += diff * amount;
		end -= diff * amount;
	}
	// Gives difference vector not normalized.
	Vec2 GetDiff() const
	{
		return( end - start );
	}
public:
	Vec2 start;
	Vec2 end;
};