#pragma once

#include "Floor.h"

class FallingFloor
	:
	public Floor
{
public:
	FallingFloor( const Vec2& pos,float angle,float gravAcc );

	void Update( float dt ) override;
	void Draw( Graphics& gfx ) const override;

	bool HandleColl( class Player& guy,float dt ) override;
private:
	bool falling = false;
	float grav = 0.0f;
	float gravAcc;
	static constexpr float jumpPower = 3.4f;
};