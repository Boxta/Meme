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

using namespace std;

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	Board(Vector2_Int(170, 150))
{
	//Randomly Set Bombs On The Board
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> XPos(0, Board.TILESWIDE);
	uniform_int_distribution<int> YPos(0, Board.TILESDEEP);
	Vector2_Int BomLocation;
	for (int b = 0; b < BOMBCOUNT; ++b) {
		do
		{
			BomLocation = Vector2_Int(XPos(gen), YPos(gen));
		} while (Board.TileGrid[BomLocation.y * Board.TILESWIDE + BomLocation.x]._HasBomb);

		Board.TileGrid[BomLocation.y * Board.TILESWIDE + BomLocation.x]._HasBomb = true;
	}
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
	if (!_GameOver) {
		MouseInputUpdates();
	}
}

void Game::RevealTile(const Vector2_Int & startposition)
{
	//Store Clicked Tile Position
	Vector2_Int pos = Board.TileGrid[startposition.y * Board.TILESWIDE + startposition.x]._TileBoardPosition;
	
	//Change State To Revealed
	Board.TileGrid[startposition.y * Board.TILESWIDE + startposition.x].ChangeToRevealed();
	
	//Get Grid Positions Around This Tile
	const Vector2_Int left = Vector2_Int(pos.x - 1, pos.y);
	const Vector2_Int right = Vector2_Int(pos.x + 1, pos.y);
	const Vector2_Int up = Vector2_Int(pos.x, pos.y - 1);
	const Vector2_Int down = Vector2_Int(pos.x, pos.y + 1);
	const Vector2_Int leftup = Vector2_Int(pos.x - 1, pos.y - 1);
	const Vector2_Int leftdown = Vector2_Int(pos.x - 1, pos.y + 1);
	const Vector2_Int rightup = Vector2_Int(pos.x + 1, pos.y - 1);
	const Vector2_Int rightdown = Vector2_Int(pos.x + 1, pos.y + 1);

	//Create Array For Iteration
	const Vector2_Int BrdPosList[8] = { left, right, up, down, leftup, leftdown, rightup, rightdown };

	//Count Surrounding Bombs 
	for (int u = 0; u < 8; ++u)
	{
		//Ignore Out Of Bound Tile Board Positions AND Tiles That Are Revealed
		if (BrdPosList[u].x < 0 || BrdPosList[u].x > Board.TILESWIDE - 1 ||
			BrdPosList[u].y < 0 || BrdPosList[u].y > Board.TILESDEEP - 1 ||
			Board.TileGrid[BrdPosList[u].y * Board.TILESWIDE + BrdPosList[u].x].GetState() == TileBoard::Tile::State::Revealed)
		{
			continue;
		}
			
		//If Bomb Found Increment Sending Tile Count
		if (Board.TileGrid[BrdPosList[u].y * Board.TILESWIDE + BrdPosList[u].x]._HasBomb)
		{
			Board.TileGrid[startposition.y * Board.TILESWIDE + startposition.x].Count();
		}
	}

	//Reveal all Tiles around this Tile, No bombs found around This
	if (Board.TileGrid[startposition.y * Board.TILESWIDE + startposition.x].GetCount() == 0)
	{
		for (int u = 0; u < 8; ++u)
		{
			//Ignore Out Of Bound Tile Board Positions AND Tiles That Are Revealed
			if (BrdPosList[u].x < 0 || BrdPosList[u].x > Board.TILESWIDE - 1 ||
				BrdPosList[u].y < 0 || BrdPosList[u].y > Board.TILESDEEP - 1 ||
				Board.TileGrid[BrdPosList[u].y * Board.TILESWIDE + BrdPosList[u].x].GetState() == TileBoard::Tile::State::Revealed)
			{
				continue;
			}
			else
			{
				//Recursively call this function
				RevealTile(Board.TileGrid[BrdPosList[u].y * Board.TILESWIDE + BrdPosList[u].x]._TileBoardPosition);
			}
		}
	}
}

void Game::GameOver()
{
	_GameOver = true;
	for (int w = 0; w < Board.TILESWIDE; ++w)
	{
		for (int h = 0; h < Board.TILESDEEP; ++h)
		{
			if(Board.TileGrid[h * Board.TILESWIDE + w]._HasBomb)
			{
				//Explode Bombs
				Board.TileGrid[h * Board.TILESWIDE + w].ChangeToRevealed();
			}
		}
	}
}

void Game::MouseInputUpdates()
{
	//Check mouse is within the Board
	if (wnd.mouse.GetPosX() > Board._Offset.x &&
		wnd.mouse.GetPosX() < Board._Offset.x + (Board.TILESWIDE * Board.TILEWIDTH) &&
		wnd.mouse.GetPosY() > Board._Offset.y &&
		wnd.mouse.GetPosY() < Board._Offset.y + (Board.TILESDEEP * Board.TILEDEPTH))
	{
		//Left Click a Tile To Reveal It
		if (wnd.mouse.LeftIsPressed())
		{
			//Get Clicked Tile Board Position
			Vector2_Int ClickedTile = Vector2_Int((wnd.mouse.GetPos().x - Board._Offset.x) / Board.TILEWIDTH,
				(wnd.mouse.GetPos().y - Board._Offset.y) / Board.TILEDEPTH);

			//Stop Chillis Mouse Call From Firing Every Frame
			wnd.mouse.Clear();

			//If Tile at click location is Hidden
			if (Board.TileGrid[ClickedTile.y * Board.TILESWIDE + ClickedTile.x].GetState() == TileBoard::Tile::State::Hidden)
			{
				//If has no Bomb on Click
				if (!Board.TileGrid[ClickedTile.y * Board.TILESWIDE + ClickedTile.x]._HasBomb)
				{
					//Reveal Tile [Recursive]
					RevealTile(ClickedTile);
				}
				else
				{
					GameOver();
				}
			}
			else if (Board.TileGrid[ClickedTile.y * Board.TILESWIDE + ClickedTile.x].GetState() == TileBoard::Tile::State::Flagged)
			{
				//Flagged So Do Nothing
			}
			else if (Board.TileGrid[ClickedTile.y * Board.TILESWIDE + ClickedTile.x].GetState() == TileBoard::Tile::State::Revealed)
			{
				//Revealed So Do Nothing
			}
		}
		//Right Click a Tile To Flag It
		if (wnd.mouse.RightIsPressed())
		{
			Vector2_Int ClickedTile = Vector2_Int((wnd.mouse.GetPos().x - Board._Offset.x) / Board.TILEWIDTH,
				(wnd.mouse.GetPos().y - Board._Offset.y) / Board.TILEDEPTH);
			wnd.mouse.Clear();
			if (Board.TileGrid[ClickedTile.y * Board.TILESWIDE + ClickedTile.x].GetState() == TileBoard::Tile::State::Hidden)
			{
				Board.TileGrid[ClickedTile.y * Board.TILESWIDE + ClickedTile.x].ChangeToFlagged();
			}
			else if (Board.TileGrid[ClickedTile.y * Board.TILESWIDE + ClickedTile.x].GetState() == TileBoard::Tile::State::Flagged)
			{
				Board.TileGrid[ClickedTile.y * Board.TILESWIDE + ClickedTile.x].ChangeToHidden();
			}
			else if (Board.TileGrid[ClickedTile.y * Board.TILESWIDE + ClickedTile.x].GetState() == TileBoard::Tile::State::Revealed)
			{
				//Revealed So Do Nothing
			}
		}
	}
}

void Game::ComposeFrame()
{
	Board.DrawBoard(gfx);
}
