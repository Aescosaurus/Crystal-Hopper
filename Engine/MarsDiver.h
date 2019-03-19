#pragma once

#include "Vec2.h"
#include "Graphics.h"
#include "Circle.h"
#include "Timer.h"

// An enemy that sits still until player comes within range
//  of it, then moves fast towards player to try and hit
//  them.  Player loses lots of points if this happens.

// Lights up and angles towards player when they come near.
class MarsDiver
{
public:
	MarsDiver( const Vec2& pos );

	void Update( const Vec2& playerPos,float dt );
	void Draw( Graphics& gfx ) const;

	Circle GetCollider() const;
private:
	static constexpr int radius = 32;
	static constexpr float activationRange = 305.1f;
	static constexpr float jumpRange = 201.1f;
	static constexpr float speed = 781.4f;
	Vec2 pos;
	Vec2 vel = { 0.0f,0.0f };
	Vec2 target;
	float angle = 0.0f;
	static constexpr float velDecay = 0.04f;
	Timer retarget = 2.6f;
};