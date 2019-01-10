#pragma once

#include "Vec2.h"
#include "Graphics.h"
#include "Circle.h"
#include "Surface.h"

// Spike ball or enemy or something to avoid.
class SpikyBoi
{
public:
	SpikyBoi( const Vei2& pos );

	void Update( float dt );
	void Draw( Graphics& gfx ) const;

	Circle GetCollider() const;
public:
	static constexpr int pointValue = 100;
private:
	static constexpr int radius = 32;
	Vec2 pos;
	const Surface img = "Images/SpikyBoi.bmp";
};