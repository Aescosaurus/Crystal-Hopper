#pragma once

#include "Crystal.h"

class MartianCrystal
	:
	public Crystal
{
public:
	MartianCrystal( const Vec2& pos )
		:
		Crystal( pos,SurfCodex::Fetch( "Images/MarsCrystalAnim.bmp" ),
			Explosion::Type::MarsCrystalDissolve )
	{}
};