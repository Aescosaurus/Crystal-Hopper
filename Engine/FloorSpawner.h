#pragma once

#include <vector>
#include "Floor.h"
#include "Timer.h"
#include <random>

class FloorSpawner
{
public:
	FloorSpawner( std::vector<Floor>& floors );

	void Update( float pixelsMoved );
private:
	void ResetRespawn();

	float GetRand( float min,float max ) const;
private:
	mutable std::mt19937 rng;
	std::vector<Floor>& floors;
	static constexpr float minSpawnDist = 140.0f;
	static constexpr float maxSpawnDist = 300.0f;
	Timer respawn;
	static constexpr Vec2 minSize = { 120.0f,30.0f };
	static constexpr Vec2 maxSize = { 170.0f,70.0f };
};