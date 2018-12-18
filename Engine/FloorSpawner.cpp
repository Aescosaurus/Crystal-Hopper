#include "FloorSpawner.h"
#include "ChiliUtils.h"

FloorSpawner::FloorSpawner( std::vector<Floor>& floors )
	:
	rng( std::random_device{}() ),
	floors( floors ),
	respawn( minSpawnDist )
{}

void FloorSpawner::Update( float pixelsMoved )
{
	if( pixelsMoved > 0.0f )
	{
		respawn.Update( pixelsMoved );

		if( respawn.IsDone() )
		{
			ResetRespawn();

			const auto xSize = GetRand( minSize.x,maxSize.x );
			const auto ySize = GetRand( minSize.y,maxSize.y );
			const auto rads = GetRand( 0.0f,chili::pi * 2.0f );
			const auto xPos = GetRand( xSize / 1.5f,
				float( Graphics::ScreenWidth ) - xSize / 1.5f );
			const auto yPos = -100.0f;

			floors.emplace_back( Floor{ { xPos,yPos },
				{ xSize,ySize },rads } );
		}
	}
}

void FloorSpawner::ResetRespawn()
{
	respawn.SetNewMax( GetRand( minSpawnDist,
		maxSpawnDist ) );
	respawn.Reset();
}

float FloorSpawner::GetRand( float min,float max ) const
{
	std::uniform_real_distribution<float> dist( min,max );
	return( dist( rng ) );
}
