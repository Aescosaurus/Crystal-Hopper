#pragma once

#include "Vec2.h"
#include "Graphics.h"
#include "Circle.h"
#include "Timer.h"
#include "Codex.h"
#include "Animation.h"
#include "Matrix.h"
#include "Random.h"
#include "Explosion.h"

class Comet
{
public:
	Comet( const Vei2& pos,float dir,
		std::vector<Explosion>& particles );

	void Update( float dt );
	void Draw( Graphics& gfx ) const;

	void Destroy();
	void CreateDust();
	void CreateDustAt( const Vec2& loc );

	Circle GetCollider() const;
	const Vec2& GetVel() const;
private:
	bool OverlapsScreen( int screenExpand ) const;
public:
	static constexpr int pointValue = 100;
private:
	static constexpr int radius = 32;
	static constexpr float speed = 360.5f;
	std::vector<Explosion>* particles;
	Vec2 pos;
	Vec2 startPos;
	Vec2 vel;
	Timer respawn = 1.6f;
	Timer startMoving = Random{ 0.0f,1.1f };
	// Matrix rotMat;
	CSurfPtr surfSheet = SurfCodex::Fetch( "Images/CometAnim.bmp" );
	Animation rotate;
	Timer spawnDust = 0.6f;
};