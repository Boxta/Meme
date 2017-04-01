#include "TileBoard.h"



TileBoard::TileBoard(Vei2& ScreenPosition)
{
	_Offset = ScreenPosition;
	_BoardRectangle = RectI(_Offset, TILEWIDTH * TILESWIDE, TILEDEPTH * TILESDEEP);

	for (int x = 0; x < TILESWIDE; ++x)
	{
		for (int y = 0; y < TILESDEEP; ++y)
		{
			TileGrid[y * TILESWIDE + x] = Tile(Vei2(x, y));
			if (y == 4)
				TileGrid[y * TILESWIDE + x].ChangeToFlagged();
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

TileBoard::Tile::Tile(Vei2& BoardPosition)
{
	_TileState = State::Hidden;
	_TileBoardPosition = BoardPosition;
	_TileRectangle = RectI(Vei2(BoardPosition.x * TILEWIDTH, BoardPosition.y * TILEDEPTH), TILEWIDTH, TILEDEPTH);
}

void TileBoard::Tile::ChangeToFlagged()
{
	_TileState = State::Flagged;
}

void TileBoard::Tile::DrawTile(Graphics& gfx, Vei2& off)
{
	Vei2 newpos = off + GetTileScreenPosition();
	switch (_TileState)
	{
	case State::Hidden:
		SpriteCodex::DrawTile0(newpos, gfx);
		//SpriteCodex::DrawTile8(GetTileScreenPosition(), gfx);
		break;
	case State::Flagged:
		SpriteCodex::DrawTile0(newpos, gfx);
		SpriteCodex::DrawTileFlag(newpos, gfx);
		break;
	case State::Revealed:
		SpriteCodex::DrawTileFlag(newpos, gfx);
		break;
	}
}

Vei2 TileBoard::Tile::GetTileScreenPosition() const
{
	return Vei2(_TileBoardPosition.x * TILEWIDTH, _TileBoardPosition.y * TILEDEPTH);
}
