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
	static const int TILESWIDE = 30;
	static const int TILESDEEP = 20;
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
		void ChangeToRevealed();
		void ChangeToHidden();
		void ChangeToFlagged();
		void DrawTile(Graphics& gfx, Vector2_Int& off);
		Vector2_Int GetTileScreenPosition() const;
		bool _HasBomb = false;
	public:
		Vector2_Int _TileBoardPosition;
		State _TileState;
		Rectangle_Int _TileRectangle;
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
	Tile TileGrid[TILESWIDE * TILESDEEP];		// Tile Array
private:
	
};

