#pragma once

#include "Vec2.h"
#include "Graphics.h"
#include "Circle.h"
#include "Timer.h"

class Comet
{
public:
	Comet( const Vei2& pos,float dir );

	void Update( float dt );
	void Draw( Graphics& gfx ) const;

	Circle GetCollider() const;
	const Vec2& GetVel() const;
private:
	bool OverlapsScreen() const;
public:
	static constexpr int pointValue = 100;
private:
	static constexpr int radius = 32;
	static constexpr float speed = 360.5f;
	Vec2 pos;
	Vec2 startPos;
	Vec2 vel;
	Timer respawn = 1.6f;
};