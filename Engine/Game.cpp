/******************************************************************************************
 *	Chili DirectX Framework Version 16.07.20											  *
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "ChiliUtils.h"
#include <functional>

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	mt( wnd.mouse ),
	guy( mt )
{
	// TODO: Find a way to do this by reading files.
	floors.emplace_back( Floor{ { 250.0f,350.0f },
		{ 160.0f,50.0f },chili::deg2rad( 35.0f ) } );
	floors.emplace_back( Floor{ { 650.0f,450.0f },
		{ 160.0f,50.0f },chili::deg2rad( -35.0f ) } );

	crystals.emplace_back( Crystal{ { 100.0f,450.0f } } );
	crystals.emplace_back( Crystal{ { 650.0f,150.0f } } );
}

void Game::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	float dt = time.Mark();
	if( dt > 1.0f / 15.0f ) dt = 0.0f;
	else dt *= 60.0f;

	mt.Update();
	guy.Update( dt );

	// Find which line or corner to collide with.
	float shortest = 9999.0f;
	const Line* closestLine = nullptr;
	const Circle* closestCorner = nullptr;
	for( const auto& plat : floors )
	{
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
	if( closestLine != nullptr )
	{
		guy.CollideWith( *closestLine,dt );
	}
	else if( closestCorner != nullptr ) // else if important.
	{
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
	// chili::remove_erase_if( crystals,
	// 	std::mem_fn( &Crystal::WillRemove ) );
}

void Game::ComposeFrame()
{
	for( const auto& flr : floors ) flr.Draw( gfx );

	for( const auto& cry : crystals ) cry.Draw( gfx );

	guy.Draw( gfx );
	mt.Draw( gfx );
}
