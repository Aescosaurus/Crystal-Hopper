#pragma once

#include "Crystal.h"

class JupiterCrystal
	:
	public Crystal
{
public:
	JupiterCrystal( const Vec2& pos )
		:
		Crystal( pos,SurfCodex::Fetch( "Images/JupiterCrystalAnim.bmp" ),
			Explosion::Type::JupiterCrystalDissolve )
	{}
};