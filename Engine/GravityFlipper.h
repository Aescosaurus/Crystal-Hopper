#pragma once

#include "Circle.h"
#include "Graphics.h"
#include "Codex.h"

class GravityFlipper
{
public:
	GravityFlipper( const Vec2& pos );

	void Draw( Graphics& gfx ) const;

	const Circle& GetColl() const;
private:
	static constexpr float radius = 32;
	Circle coll;
	CSurfPtr img = SurfCodex::Fetch( "Images/GravityFlipper.bmp" );
};