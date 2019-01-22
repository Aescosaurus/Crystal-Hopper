#pragma once

#include "Floor.h"

class MovingFloor
	:
	public Floor
{
public:
	MovingFloor( const Vec2& pos,float angle,
		int leftStop,int rightStop,float speed );

	void Update( float dt ) override;
private:
	int leftPos;
	int rightPos;
	Vec2 vel;
	int dir = -1;
};