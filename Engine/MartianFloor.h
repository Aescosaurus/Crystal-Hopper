#pragma once

#include "Floor.h"

class MartianFloor
	:
	public Floor
{
public:
	MartianFloor( const Vec2& pos,float angle )
		:
		Floor( pos,angle,SurfCodex
			::Fetch( "Images/MartianPlatform.bmp" ) )
	{}
};