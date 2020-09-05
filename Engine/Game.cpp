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
#include "SpriteEffect.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	mainGame( wnd.kbd,wnd.mouse,gfx,options ),
	editor( wnd.kbd,wnd.mouse,gfx ),
	selector( wnd.mouse,wnd.kbd,gfx )
{}

Game::~Game()
{
	// Need to include these for some reason.
	SoundCodex::Purge();
	MusicCodex::Purge();
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
	// Fullscreen control stuff.
	if( wnd.kbd.KeyIsPressed( VK_CONTROL ) &&
		wnd.kbd.KeyIsPressed( 'W' ) )
	{
		wnd.Kill();
	}
	// if( wnd.kbd.KeyIsPressed( VK_CONTROL ) &&
	// 	wnd.kbd.KeyIsPressed( 'F' ) )
	// {
	// 	wnd.Maximize();
	// }
	// if( wnd.kbd.KeyIsPressed( VK_ESCAPE ) )
	// {
	// 	wnd.Minimize();
	// }

	if( gameState == State::Campaign || gameState == State::LevelEditor )
	{
		menu.Update( wnd.kbd,wnd.mouse );
		if( menu.WillExit() || mainGame.BackToMenu() )
		{
			mainGame.RestartLevel();
			mainGame.StopMusic();
			menu.Close();
			gameState = State::LevelSelect;
		}
	}
	if( gameState != State::Campaign && !playingMusic )
	{
		menuMusic->Play( Campaign::musicVol );
		playingMusic = true;
	}
	// Don't update if menu is open.
	if( menu.IsOpen() && !menu.WillRestart() ) return;

	switch( gameState )
	{
	case State::MainMenu:
	{
		const auto msPos = wnd.mouse.GetPos();
		const auto msDown = wnd.mouse.LeftIsPressed();
		// if( startCampaign.Update( msPos,msDown ) )
		// {
		// 	gameState = State::Campaign;
		// }
		if( levelSelect.Update( msPos,msDown ) )
		{
			gameState = State::LevelSelect;
			selector.Reset();
		}
		// if( startLevelEditor.Update( msPos,msDown ) )
		// {
		// 	gameState = State::LevelEditor;
		// }
		if( optionsButton.Update( msPos,msDown ) )
		{
			gameState = State::Options;
			options.Load();
		}
		if( quitButton.Update( msPos,msDown ) )
		{
			wnd.Kill();
		}
	}
	break;
	case State::LevelSelect:
	{
		selector.Update();
		const auto level = selector.GotoLevel();
		if( level >= 0 )
		{
			mainGame.LoadLevel( level );
			gameState = State::Campaign;
		}
		else if( selector.BackToMenu() )
		{
			gameState = State::MainMenu;
		}
	}
	break;
	case State::Campaign:
		if( playingMusic )
		{
			menuMusic->StopAll();
			playingMusic = false;
		}
		if( menu.WillRestart() )
		{
			menu.Close();
			mainGame.RestartLevel();
			return;
		}
		mainGame.Update();
		if( mainGame.Win() )
		{
			mainGame.RestartLevel();
			mainGame.StopMusic();
			gameState = State::Win;
		}
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
	case State::Options:
		options.Update( wnd.mouse );
		if( options.BackToMenu() )
		{
			options.Save();
			mainGame.UpdateOptions();
			gameState = State::MainMenu;
		}
		break;
	case State::Win:
		if( menuButton.Update( wnd.mouse.GetPos(),wnd.mouse.LeftIsPressed() ) )
		{
			gameState = State::MainMenu;
		}
		break;
	}
}

void Game::ComposeFrame()
{
	switch( gameState )
	{
	case State::MainMenu:
#if NDEBUG
		gfx.DrawSpriteNormal( 0,0,*titleBG,
			SpriteEffect::Copy{} );
#endif
		// startCampaign.Draw( gfx );
		levelSelect.Draw( gfx );
		// startLevelEditor.Draw( gfx );
		optionsButton.Draw( gfx );
		quitButton.Draw( gfx );
		break;
	case State::LevelSelect:
		selector.Draw();
		break;
	case State::Campaign:
		mainGame.Draw();
		menu.Draw( gfx );
		break;
	case State::LevelEditor:
		editor.Draw();
		menu.Draw( gfx );
		break;
	case State::Options:
		options.Draw( gfx );
		break;
	case State::Win:
		gfx.DrawSpriteNormal( 0,0,*winBG,
			SpriteEffect::Copy{} );
		menuButton.Draw( gfx );
	}

	gfx.DrawCircleSafe( wnd.mouse.GetPos(),6,Colors::Red2 );
	gfx.DrawCircleSafe( oldMouse3,4,Colors::Red2 );

	oldMouse3 = oldMouse2;
	oldMouse2 = oldMousePos;
	oldMousePos = wnd.mouse.GetPos();
}