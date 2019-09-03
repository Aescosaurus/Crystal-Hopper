#pragma once

#include "Circle.h"
#include "Graphics.h"
#include "Codex.h"

class GravSlowField
{
public:
	GravSlowField( const Vec2& pos );

	void Draw( Graphics& gfx ) const;

	const Circle& GetColl() const;
private:
	static constexpr int radius = 32;
	Circle coll;
	CSurfPtr img = SurfCodex::Fetch( "Images/GravitySlowField.bmp" );
};