#include "TileBoard.h"

TileBoard::TileBoard(Vector2_Int& ScreenPosition)
{
	_Offset = ScreenPosition;
	_BoardRectangle = RectI(_Offset, TILEWIDTH * TILESWIDE, TILEDEPTH * TILESDEEP);

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
	gfx.DrawRect(_BoardRectangle, Color(192, 192, 192));
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
	_TileRectangle = RectI(Vector2_Int(BoardPosition.x * TILEWIDTH, BoardPosition.y * TILEDEPTH), TILEWIDTH, TILEDEPTH);
}

void TileBoard::Tile::ChangeToFlagged()
{
	_TileState = State::Flagged;
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
			SpriteCodex::DrawTile0(newpos, gfx);
			SpriteCodex::DrawTileBomb(newpos, gfx);
		}
		else
		{
			SpriteCodex::DrawTile0(newpos, gfx);
		}
		break;
	}
}

Vector2_Int TileBoard::Tile::GetTileScreenPosition() const
{
	return Vector2_Int(_TileBoardPosition.x * TILEWIDTH, _TileBoardPosition.y * TILEDEPTH);
}
