#pragma once

#include "Crystal.h"

class LunarCrystal
	:
	public Crystal
{
public:
	LunarCrystal( const Vec2& pos )
		:
		Crystal( pos,SurfCodex::Fetch( "Images/MoonCrystalAnim.bmp" ),
			Explosion::Type::MoonCrystalDissolve )
	{}
};