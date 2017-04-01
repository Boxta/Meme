#pragma once
#include "Vei2.h"
#include "Graphics.h"
#include "RectI.h"
#include "SpriteCodex.h"

class TileBoard
{
	//STATICS
public:
	static constexpr int TILEWIDTH = 16;
	static constexpr int TILEDEPTH = 16;
	static const int TILESWIDE = 10;
	static const int TILESDEEP = 10;
	//CLASSES
public:
	class Tile
	{
		enum class State {
			Revealed,
			Hidden,
			Flagged
		};

	public:
		Tile() = default;
		Tile(Vei2& BoardPosition);
		void ChangeToFlagged();
		void DrawTile(Graphics& gfx, Vei2& off);
		Vei2 GetTileScreenPosition() const;
	public:
		Vei2 _TileBoardPosition;
		State _TileState;
		RectI _TileRectangle;
	};

	//FUNCTIONS
public:
	TileBoard(Vei2& ScreenPosition);
	~TileBoard();
	void UpdateBoard(float dt);
	void DrawBoard(Graphics& gfx);

	//MEMBERS
public:
	Vei2 _Offset;								//Offset Board In Game Screen Space
	RectI _BoardRectangle;
private:
	Tile TileGrid[TILESWIDE * TILESDEEP];		// Tile Array
};

