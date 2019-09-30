#pragma once

#include "Vec2.h"
#include "Random.h"

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
	Vec2 GetRandSpot() const
	{
		const auto diff = GetDiff();
		return( start + diff * float( Random{ 0.0f,1.0f } ) );
	}
public:
	Vec2 start;
	Vec2 end;
};