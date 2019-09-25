#pragma once

#include "Circle.h"
#include "Codex.h"
#include "Graphics.h"

class GravRotator
{
public:
	GravRotator( const Vec2& pos );

	void Draw( Graphics& gfx ) const;

	const Circle& GetColl() const;
private:
	static constexpr int radius = 32;
	Circle coll;
	CSurfPtr img = SurfCodex::Fetch( "Images/GravityRotator.bmp" );
};