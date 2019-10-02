#pragma once

#include "Floor.h"
#include "Random.h"

class JupiterFloor
	:
	public Floor
{
public:
	JupiterFloor( const Vec2& pos,float angle )
		:
		Floor( pos,angle,SurfCodex::Fetch(
			"Images/JupiterPlatform.bmp" ) )
	{}

	void Update( FloorUpdateInfo& flInfo,float dt )
	{
		if( int( Random{ 0,100 } ) < particleSpawnChance )
		{
			flInfo.particles.emplace_back( std::make_unique<MovingExplosion>(
				lines[int( Random{ 0,int( lines.size() ) - 1 } )]
				.GetRandSpot(),
				Explosion::Type::ParticleDissipate,
				flInfo.curGravity * particleFallSpeed
				) );
		}
	}
private:
	static constexpr int particleSpawnChance = 30;
	static constexpr float particleFallSpeed = 110.0f;
};