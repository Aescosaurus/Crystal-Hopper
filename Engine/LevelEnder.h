#pragma once

#include "Graphics.h"
#include "Circle.h"
#include "Codex.h"
#include "Animation.h"
#include "Explosion.h"

// If player touches this they actually lose the level.
class LevelEnder
{
public:
	LevelEnder( const Vec2& pos,
		std::vector<std::unique_ptr<Explosion>>& particles );

	void Update( float dt );
	void Draw( Graphics& gfx ) const;

	const Circle& GetColl() const;
private:
	static constexpr int radius = 16;
	Circle coll;
	CSurfPtr sprSheet = SurfCodex::Fetch( "Images/LevelEnder.bmp" );
	Animation spin;
	std::vector<std::unique_ptr<Explosion>>* particles;
	static constexpr int particleSpawnChance = 30;
	static constexpr float particleMoveSpeed = 50.0f;
};