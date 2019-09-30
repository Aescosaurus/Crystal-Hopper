#pragma once

#include "Vec2.h"
#include "Graphics.h"
#include "Animation.h"
#include "Codex.h"

class ExplosionUpdateInfo
{
public:
	Vec2 gravity;
};

class Explosion
{
public:
	enum class Type
	{
		Explosion = 0,
		Confetti,
		CrystalDissolve,
		MoonCrystalDissolve,
		MarsCrystalDissolve,
		JupiterCrystalDissolve,
		CometDust,
		GroundBounce,
		MarsTurretBoop,
		ParticleDissipate,
		Count
	};
	enum class Behavior
	{
		Static,
		Falling
	};
public:
	Explosion( const Vec2& pos,Type t,
		Behavior b = Behavior::Static );

	void Update( const ExplosionUpdateInfo& exInfo,float dt );
	void Draw( Graphics& gfx ) const;

	bool Done() const;
private:
	static constexpr Vei2 size = { 32,32 };
	Vec2 pos;
	// CSurfPtr surfSheet = SurfCodex::Fetch( "Images/ExplodeAnim.bmp" );
	static CSurfPtr surfSheets[int( Type::Count )];
	// static constexpr char* sources[int( Type::Count )]
	// {
	// 	"Images/ExplodeAnim.bmp",
	// 	"Images/ConfettiAnim.bmp"
	// };
	Animation fadeAway;
	bool willDestroy = false;
	Behavior behavior; // Wow how imaginitive.
	static constexpr float fallSpeed = 110.0f;
	Vec2 fallDir = { 0.0f,0.0f };
};