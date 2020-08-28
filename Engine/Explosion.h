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
		DustDissipate,
		JumpRestore,
		PlayerOuch,
		Count
	};
public:
	Explosion( const Vec2& pos,Type t );

	void Update( const ExplosionUpdateInfo& exInfo,float dt );
	void Draw( Graphics& gfx ) const;

	bool Done() const;
protected:
	virtual void UpdateChild( const ExplosionUpdateInfo& exInfo,float dt ) {}
protected:
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
};

class MovingExplosion
	:
	public Explosion
{
public:
	MovingExplosion( const Vec2& pos,Type t,
		const Vec2& vel );
protected:
	void UpdateChild( const ExplosionUpdateInfo& exInfo,float dt ) override;
protected:
	Vec2 vel;
};

class GravityExplosion
	:
	public MovingExplosion
{
public:
	GravityExplosion( const Vec2& pos,Type t,float grav );
protected:
	void UpdateChild( const ExplosionUpdateInfo& exInfo,float dt ) override;
private:
	float gravAcc;
	static constexpr float fallSpeed = 500.0f;
};