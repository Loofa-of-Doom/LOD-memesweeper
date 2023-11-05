#pragma once

#include "Graphics.h"

class MemeField
{
private:
	class Tile
	{
	public:
		enum class State
		{
			Hidden,
			Flagged,
			Revealed
		};
	public:
		void SetPixeLoc(Vei2 newTileLoc);
		void SpawnMeme();
		bool HasMeme() const;
		void Draw(const Vei2& screenPos, bool fucked, Graphics& gfx) const;
		void Reveal();
		bool IsRevealed() const;
		void ToggleFlag();
		bool IsFlagged() const;
		Vei2 GetPixLoc() const;
		void SetNeighborMemeCount(int memeCount);
	private:
		State state = State::Hidden;
		bool hasMeme = false;
		int nNeighborMemes = -1;
		// Starts drawing tile at top left corner of tile
		Vei2 startingPixLoc = { 200, 200 };
	};
public:
	MemeField(int nMemes);
	void Draw(Graphics& gfx) const;
	RectI GetRect() const;
	void OnRevealClick(const Vei2& screenPos);
	void OnFlagClick(const Vei2& screenPos);
private:
	Tile& TileAt(const Vei2& gridPos);
	const Tile& TileAt(const Vei2& gridPos) const;
	Tile& TileAtPixLoc(const Vei2& pixLoc);

	Vei2 ScreenToGrid(const Vei2& screenPos);
	Vei2 GridToScreen(const Vei2& gridPos);
	int CountNeighborMemes(const Vei2& gridPos);
private:
	static constexpr int width = 20;
	static constexpr int height = 16;
	bool isFucked = false;
	Tile field[width * height];
};