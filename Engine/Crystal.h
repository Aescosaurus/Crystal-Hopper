#pragma once

#include "Vec2.h"
#include "Graphics.h"
#include "Circle.h"
#include "Surface.h"
#include "Codex.h"
#include "Animation.h"
#include "Timer.h"
#include "Explosion.h"
#include "Random.h"

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
protected:
	Crystal( const Vec2& pos,CSurfPtr surfSheet,Explosion::Type explType );
public:
	Explosion::Type explType;
private:
	static constexpr int radius = 24;
	Vec2 pos;
	bool collected = false;
	Animation sparkle;
	Timer sparkleHold = 1.0f;
	float wobble = float( Random{ 0.0f,10.0f } );
	static constexpr float wobblePower = 6.0f;
	static constexpr float wobbleSpeed = 2.0f;
	CSoundPtr pickupSound = SoundCodex::Fetch( "Audio/Crystal.wav" );
};