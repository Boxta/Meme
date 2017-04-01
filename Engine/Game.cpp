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
	//Check mouse is within the Board
	if (wnd.mouse.GetPosX() > Board._Offset.x &&
		wnd.mouse.GetPosX() < Board._Offset.x + (Board.TILESWIDE * Board.TILEWIDTH) &&
		wnd.mouse.GetPosY() > Board._Offset.y &&
		wnd.mouse.GetPosY() < Board._Offset.y + (Board.TILESDEEP * Board.TILEDEPTH))
	{
		//Left Click a Tile To Flag It
		if (wnd.mouse.LeftIsPressed())
		{
			Vector2_Int ClickedTile = Vector2_Int((wnd.mouse.GetPos().x - Board._Offset.x) / Board.TILEWIDTH,
				(wnd.mouse.GetPos().y - Board._Offset.y) / Board.TILEDEPTH);
			wnd.mouse.Flush();
			if (Board.TileGrid[ClickedTile.y * Board.TILESWIDE + ClickedTile.x].GetState() == TileBoard::Tile::State::Hidden )
			{
				Board.TileGrid[ClickedTile.y * Board.TILESWIDE + ClickedTile.x].ChangeToRevealed();
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
		//Right Click a Tile To Reveal It
		if (wnd.mouse.RightIsPressed())
		{
			Vector2_Int ClickedTile = Vector2_Int((wnd.mouse.GetPos().x - Board._Offset.x) / Board.TILEWIDTH,
				(wnd.mouse.GetPos().y - Board._Offset.y) / Board.TILEDEPTH);
			wnd.mouse.Flush();
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
