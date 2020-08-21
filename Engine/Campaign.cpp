#include "Campaign.h"
#include "ChiliUtils.h"
#include <functional>
#include <string>
#include <fstream>
#include <cassert>
#include "Logger.h"
#include "SpriteEffect.h"

Campaign::Campaign( Keyboard& kbd,Mouse& mouse,Graphics& gfx,
	const OptionsMenu& optionsMenu )
	:
	kbd( kbd ),
	mouse( mouse ),
	gfx( gfx ),
	guy( mouse,particles,gravities[Level2Index()] ),
	pointCounter( startPoints ),
	optionsMenu( optionsMenu )
{
	UpdateSaveInfo( true );
	GotoNextLevel();
}

void Campaign::Update()
{
	const float origDt = time.Mark();
	// if( origDt > 1.0f / 15.0f ) dt = 0.0f;
	// else dt *= 60.0f;
	float dt = ( origDt > 1.0f / 15.0f )
		? 0.0f : origDt/* * 60.0f*/;
	if( mouse.LeftIsPressed() )
	{
		dt *= jumpSlowdown;
	}

	// if( origDt > 1.0f / 15.0f ) return;

	switch( gameState )
	{
	case State::Gameplay:
	{
		// Easily skip levels while testing.
// #if !NDEBUG
		// if( kbd.KeyIsPressed( VK_RETURN ) )
		// {
		// 	if( kbd.KeyIsPressed( VK_CONTROL ) || canSkip )
		// 	{
		// 		GotoNextLevel();
		// 	}
		// 	canSkip = false;
		// }
		// else canSkip = true;
// #endif

		// Restart level easily.
		if( /*kbd.KeyIsPressed( VK_CONTROL ) &&*/
			kbd.KeyIsPressed( 'R' ) )
		{
			if( canRestart ) RestartLevel();
			canRestart = false;
		}
		else canRestart = true;

		guy.Update( dt );

		// Limit number of jumps on some levels.
		if( guy.HasJumped() ) ++curJumps;
		if( curJumps >= jumpLimit && jumpLimit > -1 )
		{
			guy.DisableJumping();
		}

		// Remove points for jumping and hitting obstacles.
		points -= guy.GetPointLoss();
		guy.ResetLostPoints();

		// Remove points over time.
		pointSubtracter.Update( dt );
		if( pointSubtracter.IsDone() )
		{
			pointSubtracter.Reset();
			points -= timePointVal;
		}
		points = std::max( points,1 );

		// Platforms each deal with their own collision.
		FloorUpdateInfo flUpdateInfo{ particles,guy.GetCurGravity() };
		for( auto& plat : floors )
		{
			plat->Update( flUpdateInfo,dt );
			plat->HandleColl( guy,dt );
		}

		// Find out if you need to collect a crystal.
		for( auto& cry : crystals )
		{
			cry->Update( dt );

			float tempDist = -1.0f;
			if( guy.CheckColl( cry->GetCollider(),tempDist ) )
			{
				// TODO: Give points or something.
				cry->Collect();
				particles.emplace_back( std::make_unique<Explosion>(
					cry->GetPos(),cry->explType ) );
			}
		}

		// Find out if you are colliding with a spiky boi.
		for( auto& spB : spikyBois )
		{
			spB.Update( dt );
			const auto spikyColl = spB.GetCollider();

			float tempDist = -1.0f;
			if( guy.CheckColl( spikyColl,tempDist ) )
			{
				// TODO: Possibly destroy spiky boi after?
				guy.CollideWith( spikyColl,dt );
				if( !guy.IsInvincible() )
				{
					guy.ApplyInvul();
					points -= SpikyBoi::pointValue;
					particles.emplace_back( std::make_unique<Explosion>(
						guy.GetPos(),Explosion::Type::Confetti ) );
				}
			}
		}

		// Find out if you should collide with a comet.
		for( auto& comet : comets )
		{
			comet.Update( dt );
			const auto cometColl = comet.GetCollider();

			float tempDist = -1.0f;
			if( guy.CheckColl( cometColl,tempDist ) )
			{
				guy.AddVelocity( comet.GetVel(),dt );
				if( !guy.IsInvincible() )
				{
					guy.ApplyInvul();
					points -= Comet::pointValue;
					// comet.CreateDust();
					// comet.CreateDustAt( guy.GetPos() );
					particles.emplace_back( std::make_unique<Explosion>(
						guy.GetPos(),Explosion::Type::Confetti ) );
					comet.Destroy();
				}
			}
		}

		// Test collision with stalagmites (stalactites?).
		for( auto& spike : spikes )
		{
			if( spike.HandleColl( guy,dt ) )
			{
				if( !guy.IsInvincible() )
				{
					guy.ApplyInvul();
					points -= Stalagmite::pointValue;
					particles.emplace_back( std::make_unique<Explosion>(
						guy.GetPos(),Explosion::Type::Confetti ) );
				}
			}
		}

		// Update martians and test collision with player.
		for( auto& marv : martians )
		{
			marv.Update( dt );
			float temp = 0.0f;
			if( guy.CheckColl( marv.GetCollider(),temp ) )
			{
				if( !guy.IsInvincible() )
				{
					guy.AddVelocity( marv.GetVel(),dt );
					if( !guy.IsInvincible() )
					{
						guy.ApplyInvul();
						points -= Marvin::pointValue;
						particles.emplace_back( std::make_unique<Explosion>(
							guy.GetPos(),Explosion::Type::Confetti ) );
					}
				}
			}
		}

		// Update mars turrets.
		for( auto& marsTur : marsTurrets )
		{
			const auto marsTurColl = marsTur.GetColl();
			marsTur.Update( guy.GetPos(),dt );

			float temp = 0.0f;
			if( guy.CheckColl( marsTurColl,temp ) )
			{
				guy.CollideWith( marsTurColl,dt );
				marsTur.Destroy();
				particles.emplace_back( std::make_unique<Explosion>(
					marsTur.GetPos(),Explosion::Type::MarsTurretBoop ) );
			}
		}

		// Update mars turret bullets.
		for( auto& marsTurBull : marsTurretBullets )
		{
			const auto mTurBullColl = marsTurBull.GetCollider();
			marsTurBull.Update( dt );

			float temp = 0.0f;
			if( guy.CheckColl( mTurBullColl,temp ) )
			{
				guy.CollideWith( mTurBullColl,dt );
				if( !guy.IsInvincible() )
				{
					guy.ApplyInvul();
					marsTurBull.Destroy();
					points -= MarsTurret::Bullet::pointValue;
					particles.emplace_back( std::make_unique<Explosion>(
						guy.GetPos(),Explosion::Type::Confetti ) );
				}
			}

			if( !Graphics::GetScreenRect()
				.GetExpanded( -32 ).ContainsPoint(
				Vei2( marsTurBull.GetPos() ) ) )
			{
				marsTurBull.Destroy();
			}
		}

		// Update mars divers.
		for( auto& div : divers )
		{
			div.Update( guy.GetPos(),dt );

			float temp = 0.0f;
			if( guy.CheckColl( div.GetCollider(),temp ) )
			{
				// guy.CollideWith( div.GetCollider(),dt );
				if( !guy.IsInvincible() )
				{
					guy.ApplyInvul();
					guy.AddVelocity( div.GetVel(),dt );
					points -= MarsDiver::pointValue;
					particles.emplace_back( std::make_unique<Explosion>(
						guy.GetPos(),Explosion::Type::Confetti ) );
				}
			}
		}

		// Update gravity flippers.
		for( auto& gravFlipper : gravFlippers )
		{
			const auto& gflColl = gravFlipper.GetColl();
			float temp = 0.0f;
			if( guy.CheckColl( gflColl,temp ) )
			{
				guy.CollideWith( gflColl,dt );
				guy.FlipGravity();
			}
		}

		// Update gravity slow fields.
		for( auto& gravSlow : gravSlows )
		{
			float temp = 0.0f;
			if( guy.CheckColl( gravSlow.GetColl(),temp ) )
			{
				guy.FlipSlowPercent();
				guy.CollideWith( gravSlow.GetColl(),dt );
			}
		}

		// Update gravity rotators.
		for( auto& gravRotator : gravRotators )
		{
			float temp = 0.0f;
			const auto& rotatorColl = gravRotator.GetColl();
			if( guy.CheckColl( rotatorColl,temp ) )
			{
				guy.RotateGravity();
				guy.CollideWith( rotatorColl,dt );
			}
		}

		// Update level enders.
		for( auto& le : levelEnders )
		{
			le.Update( dt );

			float temp = 0.0f;
			const auto& leColl = le.GetColl();
			if( guy.CheckColl( leColl,temp ) )
			{
				crystals.clear();
				points = 0;
				endLevelScreen.Lose();
			}
		}

		// Update all particles.
		ExplosionUpdateInfo exUpdateInfo{ guy.GetCurGravity() };
		for( auto& part : particles )
		{
			part->Update( exUpdateInfo,dt );
		}

		// Remove crystals that have been collected.
		chili::remove_erase_if( crystals,
			std::mem_fn( &Crystal::WillRemove ) );

		// Remove finished explosions.
		chili::remove_erase_if( particles,
			std::mem_fn( &Explosion::Done ) );

		// Remove mars turrets that were stomped.
		chili::remove_erase_if( marsTurrets,
			std::mem_fn( &MarsTurret::IsDestroyed ) );

		// Remove destroyed mars turret bullets.
		chili::remove_erase_if( marsTurretBullets,
			std::mem_fn( &MarsTurret::Bullet::IsDestroyed ) );

		// Fade out title.
		titlePercent = std::max( 0.0f,titlePercent - titleFadeSpeed * dt );

		// Update points counter.
		pointCounter.Update( points,dt );

		// Bring up end level menu when we've collected
		//  all the crystals.
		if( crystals.size() == 0 )
		{
			endLevelTimer.Update( dt );

			if( endLevelTimer.IsDone() )
			{
				OpenEndLevelScreen();
			}
		}
		break;
	}
	case State::EndLevel: // End level menu.
	{
		endLevelScreen.Update( mouse );

		// Handle button/key presses.
		if( endLevelScreen.PressedContinue() ||
			kbd.KeyIsPressed( VK_RETURN ) )
		{
			GotoNextLevel();
			gameState = State::Gameplay;
		}
		else if( endLevelScreen.PressedRetry()/* ||
			kbd.KeyIsPressed( 'R' )*/ )
		{
			gameState = State::Gameplay;
			RestartLevel();
		}
		break;
	}
	}
}

void Campaign::Draw()
{
#if NDEBUG
	// Draw background.
	gfx.DrawSpriteNormal( 0,0,*backgrounds[Level2Index()],
		SpriteEffect::Copy{} );
#endif

	// Draw all the entities.
	for( const auto& flr : floors ) flr->Draw( gfx );
	for( const auto& cry : crystals ) cry->Draw( gfx );
	for( const auto& spB : spikyBois ) spB.Draw( gfx );
	for( const auto& com : comets ) com.Draw( gfx );
	for( const auto& spike : spikes ) spike.Draw( gfx );
	for( const auto& marv : martians ) marv.Draw( gfx );
	for( const auto& mt : marsTurrets ) mt.Draw( gfx );
	for( const auto& mtb : marsTurretBullets ) mtb.Draw( gfx );
	for( const auto& d : divers ) d.Draw( gfx );
	for( const auto& gfl : gravFlippers ) gfl.Draw( gfx );
	for( const auto& gs : gravSlows ) gs.Draw( gfx );
	for( const auto& gr : gravRotators ) gr.Draw( gfx );
	for( const auto& le : levelEnders ) le.Draw( gfx );
	guy.Draw( gfx );

	// Draw level title.
	if( titlePercent > 0.0f )
	{
		const auto titleCol = curLevel < lunarStart ? Colors::Gray : Colors::White;

		luckyPixel->DrawTextCentered( levelName,
			Graphics::GetCenter() - Vei2{ 0,50 },titleCol,
			SpriteEffect::SubstituteFade{ Colors::White,
			titleCol,titlePercent },gfx );
	}

	// Draw points counter.
	// luckyPixel->DrawText( std::to_string( points ),
	// 	Vei2{ 5,10 },Colors::White,gfx );
	pointCounter.Draw( gfx );

	// Draw number of remaining jumps available.
	// if( jumpLimit != -1 )
	// {
	// 	luckyPixel->DrawText( std::to_string( jumpLimit - curJumps ),
	// 		Vei2{ 15,15 },Colors::White,gfx );
	// }

	// Draw end of level screen if level has been completed.
	if( gameState == State::EndLevel )
	{
		endLevelScreen.Draw( gfx );
	}
}

void Campaign::RestartLevel()
{
	win = false;
	--curLevel; // Lets us reload the same level.
	GotoNextLevel();
}

void Campaign::UpdateOptions()
{
	guy.SetInvertControls( optionsMenu.DoInvertControls() );
	guy.SetClickMovement( optionsMenu.DoClickMovement() );
}

void Campaign::LoadLevel( int levelToLoad )
{
	curLevel = levelToLoad;
	GotoNextLevel();
}

bool Campaign::BackToMenu()
{
	if( endLevelScreen.PressedMenu() )
	{
		endLevelScreen.Reset();
		return( true );
	}
	return( false );
}

bool Campaign::Win() const
{
	return( win );
}

void Campaign::GotoNextLevel()
{
	// Destroy existing entities leftover from last level.
	floors.clear();
	crystals.clear();
	spikyBois.clear();
	comets.clear();
	spikes.clear();
	martians.clear();
	marsTurrets.clear();
	marsTurretBullets.clear();
	divers.clear();
	gravFlippers.clear();
	gravSlows.clear();
	gravRotators.clear();
	levelEnders.clear();

	particles.clear();

	gameState = State::Gameplay;

	endLevelTimer.Reset();
	pointSubtracter.Reset();

	// UpdateSaveInfo();

	// Reset title fade, jumps and points.
	titlePercent = 1.0f;
	curJumps = 0;
	points = startPoints;

	endLevelScreen.UnLose();
	endLevelScreen.Reset();

	ReadFile( GetNextLevelName( curLevel++ ) );

	// Reset player to center of screen.
	guy.Reset( particles,gravities[Level2Index()] );

	UpdateOptions();

	// Reset delta time.
	time.Mark();
}

void Campaign::OpenEndLevelScreen()
{
	if( curLevel > 58 && !endLevelScreen.HasLost() )
	{
		win = true;
	}

	endLevelTimer.Reset();

	const auto percent = float( points ) / startPoints;
	UpdateSaveInfo();
	// #if !NDEBUG
	Logger::Write( "Level" + std::to_string( curLevel - 1 ) +
		": " + std::to_string( points ) + "pts | " +
		std::to_string( int( percent * 100.0f ) ) + "%" +
		" | " + std::to_string( endLevelScreen
			.Points2Stars( percent ) ) + " stars" );
	// #endif
	endLevelScreen.UpdatePoints( percent,points );
	points = startPoints;

	gameState = State::EndLevel;
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

	levelName = read_line( in ); // Title.
	jumpLimit = std::stoi( read_line( in ) ); // Jump limit.

	std::vector<int> weights;
	for( int i = 0; i < 5; ++i )
	{
		weights.emplace_back( stoi( read_line( in ) ) );
	}
	endLevelScreen.UpdateStarWeights( weights );
	pointCounter.UpdatePointWeights( endLevelScreen.GetStarWeights() );

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
			floors.emplace_back( std::make_unique<Floor>(
				Vec2{ stof( list[1] ),stof( list[2] ) },
				/*chili::deg2rad*/( stof( list[3] ) ) ) );
		}
		else if( title == "MoonFloor" )
		{
			floors.emplace_back( std::make_unique<LunarFloor>(
				Vec2{ stof( list[1] ),stof( list[2] ) },
				stof( list[3] ) ) );
		}
		else if( title == "MarsFloor" )
		{
			floors.emplace_back( std::make_unique<MartianFloor>(
				Vec2{ stof( list[1] ),stof( list[2] ) },
				stof( list[3] ) ) );
		}
		else if( title == "JupiterFloor" )
		{
			floors.emplace_back( std::make_unique<JupiterFloor>(
				Vec2{ stof( list[1] ),stof( list[2] ) },
				stof( list[3] ) ) );
		}
		else if( title == "Crystal" )
		{
			crystals.emplace_back( std::make_unique<Crystal>(
				Vec2{ stof( list[1] ),stof( list[2] ) } ) );
		}
		else if( title == "MoonCrystal" )
		{
			crystals.emplace_back( std::make_unique<LunarCrystal>(
				Vec2{ stof( list[1] ),stof( list[2] ) } ) );
		}
		else if( title == "MarsCrystal" )
		{
			crystals.emplace_back( std::make_unique<MartianCrystal>(
				Vec2{ stof( list[1] ),stof( list[2] ) } ) );
		}
		else if( title == "JupiterCrystal" )
		{
			crystals.emplace_back( std::make_unique<JupiterCrystal>(
				Vec2{ stof( list[1] ),stof( list[2] ) } ) );
		}
		else if( title == "SpikyBoi" )
		{
			spikyBois.emplace_back( SpikyBoi{
				Vec2{ stof( list[1] ),stof( list[2] ) } } );
		}
		else if( title == "MovingFloor" )
		{
			floors.emplace_back( std::make_unique<MovingFloor>(
				Vec2{ stof( list[1] ),stof( list[2] ) }, // pos
				stof( list[3] ), // angle
				stoi( list[4] ),stoi( list[5] ), // dists
				stof( list[6] ) ) ); // speed
		}
		else if( title == "Comet" )
		{
			comets.emplace_back( Comet{ Vec2{
				stof( list[1] ),stof( list[2] ) },
				stof( list[3] ) } );
		}
		else if( title == "FallingFloor" )
		{
			floors.emplace_back( std::make_unique<FallingFloor>(
				Vec2{ stof( list[1] ),stof( list[2] ) },
				stof( list[3] ),gravities[Level2Index()] ) );
		}
		else if( title == "Spike" )
		{
			spikes.emplace_back( Stalagmite{ Vec2{
				stof( list[1] ),stof( list[2] ) },
				stof( list[3] ) } );
		}
		else if( title == "Marvin" )
		{
			martians.emplace_back( Marvin{ Vec2{
				stof( list[1] ),stof( list[2] ) },
				stof( list[3] ) } );
		}
		else if( title == "MarsTurret" )
		{
			marsTurrets.emplace_back( MarsTurret{ Vec2{
				stof( list[1] ),stof( list[2] ) },
				stof( list[3] ),marsTurretBullets } );
		}
		else if( title == "MarsDiver" )
		{
			divers.emplace_back( MarsDiver{ Vec2{
				stof( list[1] ),stof( list[2] ) } } );
		}
		else if( title == "GravityFlipper" )
		{
			gravFlippers.emplace_back( GravityFlipper{
				Vec2{ stof( list[1] ),stof( list[2] ) } } );
		}
		else if( title == "GravitySlower" )
		{
			gravSlows.emplace_back( GravSlowField{
				Vec2{ stof( list[1] ),stof( list[2] ) } } );
		}
		else if( title == "GravityRotator" )
		{
			gravRotators.emplace_back( GravRotator{
				Vec2{ stof( list[1] ),stof( list[2] ) } } );
		}
		else if( title == "LevelEnder" )
		{
			levelEnders.emplace_back( LevelEnder{
				Vec2{ stof( list[1] ),stof( list[2] ) },
				particles } );
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

void Campaign::UpdateSaveInfo( bool initSave )
{
	using namespace std;

	const auto read_line = []( ifstream& file_stream )
	{
		string temp_str = "0";
		for( char c = file_stream.get();
			c != '\n' && file_stream.good();
			c = file_stream.get() )
		{
			temp_str += c;
		}
		return( temp_str );
	};

	const int expectedLines = nPlanets * 15;
	vector<int> lines;

	{
		ifstream in{ "Misc/Save.txt" };
		assert( in.good() );

		while( in.good() )
		{
			lines.emplace_back( std::stoi( read_line( in ) ) );
		}

		while( lines.size() < expectedLines ) lines.emplace_back( 0 );
		while( lines.size() > expectedLines ) lines.pop_back();
	}

	const auto actualLevel = max( curLevel - 1,0 );
	lines[actualLevel] = initSave ? lines[actualLevel] :
		max( endLevelScreen.Points2Stars(
		float( points ) / startPoints ),lines[actualLevel] );

	{
		ofstream out{ "Misc/Save.txt" };
		assert( out.good() );

		for( auto line : lines )
		{
			out << std::to_string( line ) << '\n';
		}
	}
}

std::string Campaign::GetNextLevelName( int curLevel ) const
{
	const auto path = "Levels/Level";
	const auto suffix = ".txt";

	// Reload last level if there are no more.
	int i = -1;
	// Heck this is gross.
	while( !std::ifstream{ path + std::to_string(
		curLevel - ++i ) + suffix }.good() );

	return( path + std::to_string( curLevel - i ) + suffix );
}

int Campaign::Level2Index() const
{
	if( curLevel <= lunarStart )
	{
		return( 0 );
	}
	else if( curLevel <= marsStart )
	{
		return( 1 );
	}
	else if( curLevel <= jupiterStart )
	{
		return( 2 );
	}
	else // if curLevel <= saturnStart )
	{
		return( 3 );
	}
	assert( false );
	return( -1 );
}

/*
turn options into an overlay menu
ability to bring up options menu from upper right menu
mouse sensitivity slider
reset save option

tutorial
*/