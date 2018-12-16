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
	guy( mt ),
	test{ Vec2{ 100.0f,100.0f },Vec2{ 400.0f,450.0f } }
{
	floors.emplace_back( Floor{ { 350.0f,350.0f },
		{ 160.0f,60.0f },chili::deg2rad( 15.0f ) } );
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
	float dt = time.Mark() * 60.0f;

	mt.Update();
	guy.Update( dt );

	// float shortest = 9999.0f;
	// for each platform
		// if at least one point is on screen
			// auto curDist = -1.0f;
			// if( guy.CheckColl( curLine,curDist ) )
				// if( curDist < shortest ) shortest = curDist;
}

void Game::ComposeFrame()
{
	mt.Draw( gfx );
	guy.Draw( gfx );

	for( const auto& floor : floors )
	{
		floor.Draw( gfx );
	}

	auto col = Colors::Red;

	const auto& msPos = wnd.mouse.GetPos();
	auto dist = 0.0f;
	const float lenSq = test.GetDiff().GetLengthSq<float>();
	if( lenSq == 0.0f )
	{
		dist = ( msPos - test.start ).GetLength<float>();
	}
	else
	{
		const float t = std::max( 0.0f,std::min( 1.0f,
			Vec2::Dot( msPos - test.start,test.GetDiff() ) / lenSq ) );
		const Vec2 proj = test.start + ( test.GetDiff() ) * t;
		dist = ( proj - msPos ).GetLength<float>();
	}

	if( dist < 10.0f ) col = Colors::Green;
	gfx.DrawLine( test.start,test.end,col );
}
