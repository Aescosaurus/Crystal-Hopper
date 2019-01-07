#pragma once

#include "Vec2.h"
#include "Graphics.h"
#include "Animation.h"
#include "Codex.h"

class Explosion
{
public:
	Explosion( const Vec2& pos );

	void Update( float dt );
	void Draw( Graphics& gfx ) const;

	bool Done() const;
private:
	static constexpr Vei2 size = { 32,32 };
	Vei2 pos;
	CSurfPtr surfSheet = SurfCodex::Fetch( "Images/ExplodeAnim.bmp" );
	Animation fadeAway;
	bool willDestroy = false;
};