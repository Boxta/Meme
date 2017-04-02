#include "TileBoard.h"

TileBoard::TileBoard(Vector2_Int& ScreenPosition)
{
	_Offset = ScreenPosition;
	_BoardRectangle = Rectangle_Int(_Offset, TILEWIDTH * TILESWIDE, TILEDEPTH * TILESDEEP);
	_BoardRectangleBoarder = Rectangle_Int(Vector2_Int(_Offset.x - BOARDERBEZELSIZE, _Offset.y - BOARDERBEZELSIZE), (TILEWIDTH * TILESWIDE) + (2 * BOARDERBEZELSIZE), (TILEDEPTH * TILESDEEP) + (2 * BOARDERBEZELSIZE));
	for (int x = 0; x < TILESWIDE; ++x)
	{
		for (int y = 0; y < TILESDEEP; ++y)
		{
			TileGrid[y * TILESWIDE + x] = Tile(Vector2_Int(x, y));
		}
	}
}


TileBoard::~TileBoard()
{
}

void TileBoard::DrawBoard(Graphics & gfx)
{
	//Draw Bezel Rectangle
	gfx.DrawRect(_BoardRectangleBoarder, Color(100, 100, 100));

	//Draw Board Background Rectangle
	gfx.DrawRect(_BoardRectangle, Color(192, 192, 192));

	//Draw Each Tile
	for (int x = 0; x < TILESWIDE; ++x)
	{
		for (int y = 0; y < TILESDEEP; ++y)
		{
			TileGrid[y * TILESWIDE + x].DrawTile(gfx, _Offset);
		}
	}
}

TileBoard::Tile::Tile(Vector2_Int& BoardPosition)
{
	_TileState = State::Hidden;
	_TileBoardPosition = BoardPosition;
	_TileRectangle = Rectangle_Int(Vector2_Int(BoardPosition.x * TILEWIDTH, BoardPosition.y * TILEDEPTH), TILEWIDTH, TILEDEPTH);
}

void TileBoard::Tile::ChangeToFlagged()
{
	_TileState = State::Flagged;
}

void TileBoard::Tile::Count()
{
	++_TileCount;
}

void TileBoard::Tile::ChangeToRevealed()
{
	_TileState = State::Revealed;
}

void TileBoard::Tile::ChangeToHidden()
{
	_TileState = State::Hidden;
}

void TileBoard::Tile::DrawTile(Graphics& gfx, Vector2_Int& off)
{
	Vector2_Int newpos = off + GetTileScreenPosition();
	switch (_TileState)
	{
	case State::Hidden:
		SpriteCodex::DrawTileButton(newpos, gfx);
		break;
	case State::Flagged:
		SpriteCodex::DrawTileButton(newpos, gfx);
		SpriteCodex::DrawTileFlag(newpos, gfx);
		break;
	case State::Revealed:
		if (_HasBomb)
		{
			SpriteCodex::DrawTileBombRed(newpos, gfx);
			SpriteCodex::DrawTileBomb(newpos, gfx);
		}
		else
		{
			SpriteCodex::DrawTile0(newpos, gfx);
			switch (_TileCount)
			{
			case 0:
				return;
			case 1:
				SpriteCodex::DrawTile1(newpos, gfx);
				return;
			case 2:
				SpriteCodex::DrawTile2(newpos, gfx);
				return;
			case 3:
				SpriteCodex::DrawTile3(newpos, gfx);
				return;
			case 4:
				SpriteCodex::DrawTile4(newpos, gfx);
				return;
			case 5:
				SpriteCodex::DrawTile5(newpos, gfx);
				return;
			case 6:
				SpriteCodex::DrawTile6(newpos, gfx);
				return;
			case 7:
				SpriteCodex::DrawTile7(newpos, gfx);
				return;
			default:
				return;
			}
		}
		break;
	}
}

Vector2_Int TileBoard::Tile::GetTileScreenPosition() const
{
	return Vector2_Int(_TileBoardPosition.x * TILEWIDTH, _TileBoardPosition.y * TILEDEPTH);
}
