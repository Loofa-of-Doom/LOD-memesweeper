#pragma once
#include "Vei2.h"
#include "Graphics.h"
#include "RectI.h"
#include "SpriteCodex.h"

class Memefield
{
public:
	enum class State
	{
		Hidden,
		Flagged,
		Revealed
	};
private:
	class Tile
	{
	public:
		void MemePlanted();
		void DisarmMeme();
		bool HasMeme();
		void Draw(Graphics& gfx, Vei2& pixeLoc) const;
		void SetReveal();
		void SetFlag();
		void SetNumber(int tileNum);
		void UpNum();
		bool HasFlag() const;
	private:
		State state = State::Hidden;
		bool hasMeme = false;
		bool hasFlag = false;
		int numBombsNear = 0;
	};
public:
	Memefield(int in_nMemes);

	//AtTile returns one of the arrays tiles specified at tile location thats passed through the paramaters 
	Tile& AtTile(Vei2 tileLocation);
	void SpawnMemes();
	void Draw(Graphics& gfx);
	void RemoveMeme(Vei2 mouseClick);

	//Tile locaction is a Vect like (3,1) , and different from the array index location which is a one value int
	Vei2 TileToPixLoc(Vei2 const tileLoc) const;
	Vei2 PixToTileLoc(Vei2 const pixelLoc) const;
	void ClickReveal(Vei2 mouseClick);
	void ClickFlag(Vei2 mouseClick);
	void CheckNeighbor(Vei2 mouseClick);
	void ClickNoBomb(Vei2 mouseClick);
	bool IsBlownUp();
	bool IsTileInBounds(Vei2 pixelLoc) const;

private:
	int nMemes;
	bool firstClickMade;
	bool blownUp = false;
	bool finishedSpawning = false;
	static constexpr int width = 3;
	static constexpr int height = 3;
	
	Tile tiles[width * height];
	Color backgroundCol = Colors::LightGray;
	RectI background;
	
};

