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
		void SpawnMemes();
	private:
		State state = State::Hidden;
		bool hasMeme = false;
	};
public:
	Memefield(int in_nMemes);
	Tile& AtTile(Vei2& tileLocation);
private:
	static constexpr int width = 20;
	static constexpr int height = 15;
	int nMemes;
	Tile tiles[width * height];
	RectI background;
	
};

