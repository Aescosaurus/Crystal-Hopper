/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
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
#pragma once

#include "Campaign.h"
#include "Button.h"
#include "LevelEditor.h"
#include "OverlayMenu.h"
#include "OptionsMenu.h"
#include "LevelSelector.h"

class Game
{
private:
	enum class State
	{
		MainMenu,
		LevelSelect,
		Campaign,
		LevelEditor,
		Options
	};
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	OptionsMenu options; // Options need to be initialized first.
	Campaign mainGame;
	LevelEditor editor;
	OverlayMenu menu;
	LevelSelector selector;
	State gameState = State::MainMenu;

	Button startCampaign = Button{ Graphics::GetCenter() - Vei2{ 0,180 },"Start New Game" };
	Button levelSelect = Button{ Graphics::GetCenter() - Vei2{ 0,0 },"Play" };
	Button startLevelEditor = Button{ Graphics::GetCenter() + Vei2{ 0,0 },"Level Editor" };
	Button optionsButton = Button{ Graphics::GetCenter() + Vei2{ 0,80 },"Options" };
	Button quitButton = Button{ Graphics::GetCenter() + Vei2{ 0,170 },"Quit" };

	Vei2 oldMousePos;
	Vei2 oldMouse2;
	Vei2 oldMouse3;
	/********************************/
};