#pragma once

#include "Vec2.h"
#include "Graphics.h"
#include "Circle.h"
#include "Surface.h"
#include "Codex.h"
#include "Animation.h"
#include "Timer.h"

// Collect these to complete the level.
class Crystal
{
public:
	Crystal( const Vec2& pos );

	void Update( float dt );
	void Draw( Graphics& gfx ) const;

	void Collect();

	Circle GetCollider() const;
	bool WillRemove() const;
	const Vec2& GetPos() const;
private:
	static constexpr int radius = 24;
	Vec2 pos;
	bool collected = false;
	CSurfPtr surfSheet = SurfCodex::Fetch( "Images/CrystalAnim.bmp" );
	Animation sparkle;
	Timer sparkleHold = 1.0f;
};