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

Game::Game(MainWindow& wnd)
	:
	timer(),
	wnd( wnd ),
	gfx( wnd ),
	field(9)
{
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
	//Timer and buffers
	{
		frameTime = timer.Mark();
		nanoSecConv = frameTime * 0.000000001f;
		flagBuffer += nanoSecConv;
		revealBuffer += nanoSecConv;
	}
	
	field.SpawnMemes();
	if (!(state == GameState::GameOver))
	{
		
		if (wnd.mouse.LeftIsPressed() && revealBuffer > 0.25f && isFirstClick == true)
		{
			field.RemoveMeme(wnd.mouse.GetPos());
			isFirstClick = false;
			revealBuffer = 0.0f;
		}
		else if (wnd.mouse.LeftIsPressed() && revealBuffer > 0.25f)
		{
			field.ClickReveal(wnd.mouse.GetPos());
				revealBuffer = 0.0f;
		}
		if (wnd.mouse.RightIsPressed() && flagBuffer > 0.5f)
		{
			field.ClickFlag(wnd.mouse.GetPos());
				flagBuffer = 0.0f;
		}
	}
	
}

void Game::ComposeFrame()
{
	if (field.IsBlownUp())
	{
		state = GameState::GameOver;
		SpriteCodex::DrawGameOver(Vei2{ 400,300 }, gfx);
	}
	field.Draw(gfx);
}
