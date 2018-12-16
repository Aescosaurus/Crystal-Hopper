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

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	mt( wnd.mouse ),
	guy( mt )
{
	floors.emplace_back( Floor{ { 150.0f,350.0f },
		{ 160.0f,60.0f },chili::deg2rad( 0.0f ) } );
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
	if( dt > 1.0f ) dt = 0.0f;
	else dt *= 60.0f;

	mt.Update();
	guy.Update( dt );

	float shortest = 9999.0f;
	const Line* closest = nullptr;
	for( const auto& plat : floors )
	{
		// if at least one point is on screen
		{
			for( const auto& curLine : plat.GetLines() )
			{
				auto curDist = -1.0f;
				if( guy.CheckColl( curLine,curDist ) )
				{
					if( curDist < shortest )
					{
						shortest = curDist;
						closest = &curLine;
					}
				}
			}
		}
	}
	if( closest != nullptr )
	{
		guy.CollideWith( *closest,dt );
	}
}

void Game::ComposeFrame()
{
	mt.Draw( gfx );
	guy.Draw( gfx );

	for( const auto& floor : floors )
	{
		floor.Draw( gfx );
	}
}
