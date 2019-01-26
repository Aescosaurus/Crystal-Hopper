#pragma once

#include "Floor.h"

class LunarFloor
	:
	public Floor
{
public:
	LunarFloor( const Vec2& pos,float angle )
		:
		Floor( pos,angle,SurfCodex
			::Fetch( "Images/MoonPlatform.bmp" ) )
	{}
};