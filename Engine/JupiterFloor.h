#pragma once

#include "Floor.h"

class JupiterFloor
	:
	public Floor
{
public:
	JupiterFloor( const Vec2& pos,float angle )
		:
		Floor( pos,angle,SurfCodex::Fetch(
			"Images/JupiterPlatform.bmp" ) )
	{}
};