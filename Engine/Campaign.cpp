#include "Campaign.h"
#include "ChiliUtils.h"
#include <functional>
#include <string>
#include <fstream>
#include <cassert>
#include "Logger.h"

Campaign::Campaign( Keyboard& kbd,
	Mouse& mouse,Graphics& gfx )
	:
	kbd( kbd ),
	mouse( mouse ),
	gfx( gfx ),
	guy( mouse )
{
	GotoNextLevel();
}

void Campaign::Update()
{
	const float origDt = time.Mark();
	// if( origDt > 1.0f / 15.0f ) dt = 0.0f;
	// else dt *= 60.0f;
	const float dt = ( origDt > 1.0f / 15.0f )
		? 0.0f : origDt * 60.0f;

	// if( origDt > 1.0f / 15.0f ) return;

	switch( gameState )
	{
	case State::Gameplay:
	{
		guy.Update( dt );

		// Remove points for jumping and hitting obstacles.
		points -= guy.GetPointLoss();
		guy.ResetLostPoints();

		// Remove points over time.
		pointSubtracter.Update( origDt );
		if( pointSubtracter.IsDone() )
		{
			pointSubtracter.Reset();
			points -= timePointVal;
		}

		// Find which line or corner to collide with.
		float shortest = 9999.0f;
		const Line* closestLine = nullptr;
		const Circle* closestCorner = nullptr;
		// For all platforms in the level.
		for( const auto& plat : floors )
		{
			// Check line collisions.
			for( const auto& curLine : plat.GetLines() )
			{
				auto curDist = -1.0f;
				if( guy.CheckColl( curLine,curDist ) )
				{
					if( curDist < shortest )
					{
						shortest = curDist;
						closestLine = &curLine;
					}
				}
			}
			// Only check corners if no collision with line.
			if( closestLine == nullptr )
			{
				for( const auto& curCorner : plat.GetCorners() )
				{
					auto curDist = -1.0f;
					if( guy.CheckColl( curCorner,curDist ) )
					{
						if( curDist < shortest )
						{
							shortest = curDist;
							closestCorner = &curCorner;
						}
					}
				}
			}
		}
		// Prefer to collide with a line, collide with a
		//  corner only if no lines are available.
		if( closestLine != nullptr )
		{
			guy.CollideWith( *closestLine,dt );
		}
		else if( closestCorner != nullptr )
		{ // else if might be important here.
			guy.CollideWith( *closestCorner,dt );
		}

		// Find out if you need to collect a crystal.
		for( auto& cry : crystals )
		{
			float tempDist = -1.0f;
			if( guy.CheckColl( cry.GetCollider(),tempDist ) )
			{
				// TODO: Give points or something.
				cry.Collect();
			}
		}

		// Remove crystals that have been collected.
		chili::remove_erase_if( crystals,
			std::mem_fn( &Crystal::WillRemove ) );

		// Bring up end level menu when we've collected
		//  all the crystals.
		if( crystals.size() == 0 )
		{
			endLevelTimer.Update( origDt );

			if( endLevelTimer.IsDone() )
			{
				endLevelTimer.Reset();
				const auto percent = float( points ) / startPoints;
#if !NDEBUG
				Logger::Write( std::to_string( points ) + "pts | " +
					std::to_string( int( percent * 100.0f ) ) + "%" );
#endif

				endLevelScreen.UpdatePoints( percent );
				points = startPoints;

				gameState = State::EndLevel;
			}
		}
		break;
	}
	case State::EndLevel:
	{
		endLevelScreen.Update( mouse );

		if( endLevelScreen.PressedContinue() )
		{
			gameState = State::Gameplay;
			GotoNextLevel();
		}
		else if( endLevelScreen.PressedRetry() )
		{
			gameState = State::Gameplay;
			--curLevel; // Lets us reload the same level.
			GotoNextLevel();
		}
		break;
	}
	}
}

void Campaign::Draw()
{
	for( const auto& flr : floors ) flr.Draw( gfx );

	for( const auto& cry : crystals ) cry.Draw( gfx );

	guy.Draw( gfx );

	if( gameState == State::EndLevel )
	{
		endLevelScreen.Draw( gfx );
	}
}

void Campaign::GotoNextLevel()
{
	floors.clear();
	crystals.clear();

	guy.Reset();
	ReadFile( GetNextLevelName( curLevel++ ) );
}

void Campaign::ReadFile( const std::string& filename )
{
	using namespace std;

	const auto read_line = []( ifstream& file_stream )
	{
		string temp_str = "";
		for( char c = file_stream.get();
			c != '\n';
			c = file_stream.get() )
		{
			temp_str += c;
		}
		return( temp_str );
	};

	ifstream in{ filename };
	assert( in.good() );

	vector<vector<string>> tokens;
	string temp = "";
	tokens.emplace_back( vector<string>{} );

	const string levelName = read_line( in ); // Title.
	std::vector<int> weights;
	for( int i = 0; i < 5; ++i )
	{
		weights.emplace_back( stoi( read_line( in ) ) );
	}
	endLevelScreen.UpdateStarWeights( weights );

	for( char c = in.get(); in.good(); c = in.get() )
	{
		if( c == '\n' )
		{
			tokens.back().emplace_back( temp );
			tokens.emplace_back( vector<string>{} );
			temp = "";
		}
		else if( c == '|' )
		{
			tokens.back().emplace_back( temp );
			temp = "";
		}
		else
		{
			temp += c;
		}
	}
	tokens.back().emplace_back( temp );

	// Add objects to vectors!
	for( const vector<string>& list : tokens )
	{
		const auto& title = list[0];

		if( title == "Floor" )
		{
			floors.emplace_back( Floor{
				Vec2{ stof( list[1] ),stof( list[2] ) },
				chili::deg2rad( stof( list[3] ) ) } );
		}
		else if( title == "Crystal" )
		{
			crystals.emplace_back( Crystal{
				Vec2{ stof( list[1] ),stof( list[2] ) } } );
		}
		// else if( title == "" )
		// {
		// 
		// }
		else
		{
			assert( false );
		}
	}
}

std::string Campaign::GetNextLevelName( int curLevel ) const
{
	const auto path = "Levels/Level";
	const auto suffix = ".txt";
	return( path + std::to_string( curLevel ) + suffix );
}