#pragma once
#include "Vector2.h"
#include "Graphics.h"
#include "Rectangle.h"
#include "SpriteCodex.h"

class TileBoard
{
	//STATICS
public:
	static constexpr int TILEWIDTH = 16;
	static constexpr int TILEDEPTH = 16;
	static constexpr int TILESWIDE = 8;
	static constexpr int TILESDEEP = 6;
	static constexpr int BOARDERBEZELSIZE = 10;
	//CLASSES
public:
	class Tile
	{
	public:
		enum class State {
			Revealed,
			Hidden,
			Flagged
		};

	public:
		Tile() = default;
		Tile(Vector2_Int& BoardPosition);

		State GetState()
		{
			return _TileState;
		}
		int GetCount() {
			return _TileCount;
		}
		void ChangeToRevealed();
		void ChangeToHidden();
		void ChangeToFlagged();
		void Count();
		void DrawTile(Graphics& gfx, Vector2_Int& off);
		Vector2_Int GetTileScreenPosition() const;
		bool _HasBomb = false;
	public:
		Vector2_Int _TileBoardPosition;
		State _TileState;
		Rectangle_Int _TileRectangle;
		int _TileCount = 0;
	};

	//FUNCTIONS
public:
	TileBoard(Vector2_Int& ScreenPosition);
	~TileBoard();
	void UpdateBoard(float dt);
	void DrawBoard(Graphics& gfx);

	//MEMBERS
public:
	Vector2_Int _Offset;								//Offset Board In Game Screen Space
	Rectangle_Int _BoardRectangle;
	Rectangle_Int _BoardRectangleBoarder;
	Tile TileGrid[TILESWIDE * TILESDEEP];		// Tile Array
private:
	
};

