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

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	mt( wnd.mouse ),
	guy( mt ),
	test{ Vec2{ 100.0f,100.0f },Vec2{ 400.0f,450.0f } }
{}

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
}

void Game::ComposeFrame()
{
	mt.Draw( gfx );
	guy.Draw( gfx );

	auto col = Colors::Red;
	const auto x0 = wnd.mouse.GetPosX();
	const auto y0 = wnd.mouse.GetPosY();
	const auto x1 = test.start.x;
	const auto y1 = test.start.y;
	const auto x2 = test.end.x;
	const auto y2 = test.end.y;
	const auto dist = abs( ( y2 - y1 ) * x0 -
		( x2 - x1 ) * y0 + x2 * y1 - y2 * x1 ) /
		sqrt( ( y2 - y1 ) * ( y2 - y1 ) +
		( x2 - x1 ) * ( x2 - x1 ) );
	if( dist < 10.0f ) col = Colors::Green;
	gfx.DrawLine( test.start,test.end,col );
}
