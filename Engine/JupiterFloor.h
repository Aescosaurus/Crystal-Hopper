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

	void Update( std::vector<std::unique_ptr<Explosion>>& particles,float dt )
	{
		particles.emplace_back( std::make_unique<Explosion>(
			lines[int( Random{ 0,int( lines.size() ) - 1 } )]
			.GetRandSpot(),
			Explosion::Type::ParticleDissipate,
			Explosion::Behavior::Falling
			) );
	}
};