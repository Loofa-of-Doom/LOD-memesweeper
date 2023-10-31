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
		void SetReveal();
		void SetFlag();
		bool HasFlag() const;
	private:
		State state = State::Hidden;
		bool hasMeme = false;
		bool hasFlag = false;
	};
public:
	Memefield(int in_nMemes);
	Tile& AtTile(Vei2 tileLocation);
	void SpawnMemes();
	void Draw(Graphics& gfx);
	Vei2 TileToPixLoc(Vei2 tileLoc);
	void Reveal(Vei2 mouseClick);
	void ClickFlag(Vei2 mouseClick);
	
private:
	bool finishedSpawning = false;
	static constexpr int width = 20;
	static constexpr int height = 15;
	int nMemes;
	Tile tiles[width * height];
	Color backgroundCol = Colors::LightGray;
	
};

