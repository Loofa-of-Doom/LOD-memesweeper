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
		bool HasMeme();
		void Draw(Graphics& gfx, Vei2& pixeLoc) const;
	private:
		State state = State::Hidden;
		bool hasMeme = false;
		Vei2 pixelLoc;
	};
public:
	Memefield(int in_nMemes);
	Tile& AtTile(Vei2 tileLocation);
	void SpawnMemes();
	void Draw(Graphics& gfx);
private:
	static constexpr int width = 20;
	static constexpr int height = 15;
	int nMemes;
	Tile tiles[width * height];
	Vei2 TileToPixLoc(Vei2 tileLoc);
	//RectI background;
	
};

