#pragma once

#include "Graphics.h"
#include "Circle.h"
#include "Codex.h"
#include "Animation.h"

// If player touches this they actually lose the level.
class LevelEnder
{
public:
	LevelEnder( const Vec2& pos );

	void Update( float dt );
	void Draw( Graphics& gfx ) const;

	const Circle& GetColl() const;
private:
	static constexpr int radius = 16;
	Circle coll;
	CSurfPtr sprSheet = SurfCodex::Fetch( "Images/LevelEnder.bmp" );
	Animation spin;
};