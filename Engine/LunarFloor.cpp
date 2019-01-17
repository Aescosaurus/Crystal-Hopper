#include "LunarFloor.h"

LunarFloor::LunarFloor( const Vec2& pos,float angle )
	:
	Floor( pos,angle,SurfCodex::Fetch( "Images/LunarFloor.bmp" ) )
{}
