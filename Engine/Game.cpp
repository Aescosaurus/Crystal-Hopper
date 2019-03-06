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
	mainGame( wnd.kbd,wnd.mouse,gfx ),
	editor( wnd.kbd,wnd.mouse,gfx )
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
	// Fullscreen control stuff.
	if( wnd.kbd.KeyIsPressed( VK_CONTROL ) &&
		wnd.kbd.KeyIsPressed( 'W' ) )
	{
		wnd.Kill();
	}
	if( wnd.kbd.KeyIsPressed( VK_CONTROL ) &&
		wnd.kbd.KeyIsPressed( 'F' ) )
	{
		wnd.Maximize();
	}
	if( wnd.kbd.KeyIsPressed( VK_ESCAPE ) )
	{
		wnd.Minimize();
	}

	menu.Update( wnd.kbd,wnd.mouse );
	if( menu.WillExit() )
	{
		mainGame.RestartLevel();
		menu.Close();
		gameState = State::MainMenu;
	}
	// Don't update if menu is open.
	if( menu.IsOpen() && !menu.WillRestart() ) return;

	switch( gameState )
	{
	case State::MainMenu:
	{
		const auto msPos = wnd.mouse.GetPos();
		const auto msDown = wnd.mouse.LeftIsPressed();
		if( startCampaign.Update( msPos,msDown ) )
		{
			gameState = State::Campaign;
		}
		if( startLevelEditor.Update( msPos,msDown ) )
		{
			gameState = State::LevelEditor;
		}
		if( quitButton.Update( msPos,msDown ) )
		{
			wnd.Kill();
		}
	}
	break;
	case State::Campaign:
		if( menu.WillRestart() )
		{
			menu.Close();
			mainGame.RestartLevel();
			return;
		}
		mainGame.Update();
		break;
	case State::LevelEditor:
		if( menu.WillRestart() )
		{
			menu.Close();
			editor.Reset();
			return;
		}
		editor.Update();
		break;
	}
}

void Game::ComposeFrame()
{
	switch( gameState )
	{
	case State::MainMenu:
		startCampaign.Draw( gfx );
		startLevelEditor.Draw( gfx );
		quitButton.Draw( gfx );
		break;
	case State::Campaign:
		mainGame.Draw();
		menu.Draw( gfx );
		break;
	case State::LevelEditor:
		editor.Draw();
		menu.Draw( gfx );
		break;
	}

	gfx.DrawCircleSafe( wnd.mouse.GetPos(),6,Colors::Red2 );
	gfx.DrawCircleSafe( oldMouse3,4,Colors::Red2 );

	oldMouse3 = oldMouse2;
	oldMouse2 = oldMousePos;
	oldMousePos = wnd.mouse.GetPos();
}