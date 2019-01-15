#pragma once

#include "Floor.h"

class MovingFloor
	:
	public Floor
{
public:
	MovingFloor( const Vec2& pos,float angle,
		float leftStop,float rightStop,float speed );

	void Update( float dt ) override;
	void Draw( Graphics& gfx ) const override;
private:
	void MoveBy( const Vec2& amount );
private:
	float leftPos;
	float rightPos;
	Vec2 vel;
	int dir = -1;
};