#include "MemeField.h"
#include <assert.h>
#include <random>
#include "Vei2.h"
#include "SpriteCodex.h"
#include <algorithm>

void MemeField::Tile::SpawnMeme()
{
	assert(!hasMeme);
	hasMeme = true;
}

bool MemeField::Tile::HasMeme() const
{
	return hasMeme;
}

void MemeField::Tile::Draw(const Vei2& screenPos, bool fucked, Graphics& gfx) const
{
	if (!fucked)
	{
		switch (state)
		{
		case State::Hidden:
			SpriteCodex::DrawTileButton(screenPos, gfx);
			break;
		case State::Flagged:
			SpriteCodex::DrawTileButton(screenPos, gfx);
			SpriteCodex::DrawTileFlag(screenPos, gfx);
			break;
		case State::Revealed:
			if (!HasMeme())
			{
				SpriteCodex::DrawTileNumber(screenPos, nNeighborMemes, gfx);
			}
			else
			{
				SpriteCodex::DrawTileBomb(screenPos, gfx);
			}
			break;
		}
	}
	else // we are fucked
	{
		switch (state)
		{
		case State::Hidden:
			if (HasMeme())
			{
				SpriteCodex::DrawTileBomb(screenPos, gfx);
			}
			else
			{
				SpriteCodex::DrawTileButton(screenPos, gfx);
			}
			break;
		case State::Flagged:
			if (HasMeme())
			{
				SpriteCodex::DrawTileBomb(screenPos, gfx);
				SpriteCodex::DrawTileFlag(screenPos, gfx);
			}
			else
			{
				SpriteCodex::DrawTileBomb(screenPos, gfx);
				SpriteCodex::DrawTileCross(screenPos, gfx);
			}
			break;
		case State::Revealed:
			if (!HasMeme())
			{
				SpriteCodex::DrawTileNumber(screenPos, nNeighborMemes, gfx);
			}
			else
			{
				SpriteCodex::DrawTileBombRed(screenPos, gfx);
			}
			break;
		}
	}
}

void MemeField::Tile::Draw(bool fucked, Graphics& gfx) const
{
	if (!fucked)
	{
		switch (state)
		{
		case State::Hidden:
			SpriteCodex::DrawTileButton(pixelLoc, gfx);
			break;
		case State::Flagged:
			SpriteCodex::DrawTileButton(pixelLoc, gfx);
			SpriteCodex::DrawTileFlag(pixelLoc, gfx);
			break;
		case State::Revealed:
			if (!HasMeme())
			{
				SpriteCodex::DrawTileNumber(pixelLoc, nNeighborMemes, gfx);
			}
			else
			{
				SpriteCodex::DrawTileBomb(pixelLoc, gfx);
			}
			break;
		}
	}
	else // we are fucked
	{
		switch (state)
		{
		case State::Hidden:
			if (HasMeme())
			{
				SpriteCodex::DrawTileBomb(pixelLoc, gfx);
			}
			else
			{
				SpriteCodex::DrawTileButton(pixelLoc, gfx);
			}
			break;
		case State::Flagged:
			if (HasMeme())
			{
				SpriteCodex::DrawTileBomb(pixelLoc, gfx);
				SpriteCodex::DrawTileFlag(pixelLoc, gfx);
			}
			else
			{
				SpriteCodex::DrawTileBomb(pixelLoc, gfx);
				SpriteCodex::DrawTileCross(pixelLoc, gfx);
			}
			break;
		case State::Revealed:
			if (!HasMeme())
			{
				SpriteCodex::DrawTileNumber(pixelLoc, nNeighborMemes, gfx);
			}
			else
			{
				SpriteCodex::DrawTileBombRed(pixelLoc, gfx);
			}
			break;
		}
	}
}

void MemeField::Tile::Reveal()
{
	assert(state == State::Hidden);
	state = State::Revealed;
}

bool MemeField::Tile::IsRevealed() const
{
	return state == State::Revealed;
}

void MemeField::Tile::ToggleFlag()
{
	assert(!IsRevealed());
	if (state == State::Hidden)
	{
		state = State::Flagged;
	}
	else
	{
		state = State::Hidden;
	}
}

bool MemeField::Tile::IsFlagged() const
{
	return state == State::Flagged;
}

Vei2 MemeField::Tile::GetPixLoc() const
{
	return pixelLoc;
}

void MemeField::Tile::SetPixeLoc(Vei2 newPixelLoc)
{
	pixelLoc += newPixelLoc;
}

void MemeField::Tile::SetNeighborMemeCount(int memeCount)
{
	assert(nNeighborMemes == -1);
	nNeighborMemes = memeCount;
}

MemeField::MemeField(int nMemes)
{
	assert(nMemes > 0 && nMemes < width * height);
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> xDist(0, width - 1);
	std::uniform_int_distribution<int> yDist(0, height - 1);

	for (int nSpawned = 0; nSpawned < nMemes; ++nSpawned)
	{
		Vei2 spawnPos;
		do
		{
			spawnPos = { xDist(rng),yDist(rng) };
		} while (TileAt(spawnPos).HasMeme());

		TileAt(spawnPos).SpawnMeme();
	}

	for (Vei2 gridPos = { 0,0 }; gridPos.y < height; gridPos.y++)
	{
		for (gridPos.x = 0; gridPos.x < width; gridPos.x++)
		{
			TileAt(gridPos).SetNeighborMemeCount(CountNeighborMemes(gridPos));
		}
	}
}

void MemeField::Draw(Graphics& gfx)  //*****************************************
{
	gfx.DrawRect(GetRect(), SpriteCodex::baseColor);
	Tile nextTile;
	for (Vei2 gridPos = { 0,0 }; gridPos.y < height; gridPos.y++)
	{
		for (gridPos.x = 0; gridPos.x < width; gridPos.x++)
		{
			nextTile = TileAt(gridPos);
			nextTile.SetPixeLoc(GridToScreen(gridPos));
			nextTile.Draw(isFucked, gfx);
		}
	}
}

RectI MemeField::GetRect() const
{
	return RectI(0, width * SpriteCodex::tileSize, 0, height * SpriteCodex::tileSize);
}

void MemeField::OnRevealClick(const Vei2& screenPos)
{
	if (!isFucked)
	{
		const Vei2 gridPos = ScreenToGrid(screenPos);
		assert(gridPos.x >= 0 && gridPos.x < width && gridPos.y >= 0 && gridPos.y < height);
		Tile& tile = TileAt(gridPos);
		if (!tile.IsRevealed() && !tile.IsFlagged())
		{
			tile.Reveal();
			if (tile.HasMeme())
			{
				isFucked = true;
			}
		}
	}
}

void MemeField::OnFlagClick(const Vei2& screenPos)
{
	if (!isFucked)
	{
		const Vei2 gridPos = ScreenToGrid(screenPos);
		assert(gridPos.x >= 0 && gridPos.x < width && gridPos.y >= 0 && gridPos.y < height);
		Tile& tile = TileAt(gridPos);
		if (!tile.IsRevealed())
		{
			tile.ToggleFlag();
		}
	}
}

MemeField::Tile& MemeField::TileAt(const Vei2& gridPos)
{
	return field[gridPos.y * width + gridPos.x];
}

MemeField::Tile& MemeField::TileAtPixLoc(const Vei2& pixLoc)
{
	Vei2 gridPos = ScreenToGrid(pixLoc);
	return field[gridPos.y * width + gridPos.x];
}

//void MemeField::InitPixLoc(Vei2 gridLocation)
//{
//	for (int i = 0; i < width * height; i++)
//	{
//		Vei2 
//		field[i].SetPixeLoc()
//	}
//}


const MemeField::Tile& MemeField::TileAt(const Vei2& gridPos) const
{
	return field[gridPos.y * width + gridPos.x];
}

Vei2 MemeField::ScreenToGrid(const Vei2& screenPos)
{
	return screenPos / SpriteCodex::tileSize;
}

Vei2 MemeField::GridToScreen(const Vei2& gridPos)
{
	return gridPos * SpriteCodex::tileSize;
}

int MemeField::CountNeighborMemes(const Vei2& gridPos)
{
	const int xStart = std::max(0, gridPos.x - 1);
	const int yStart = std::max(0, gridPos.y - 1);
	const int xEnd = std::min(width - 1, gridPos.x + 1);
	const int yEnd = std::min(height - 1, gridPos.y + 1);

	int count = 0;
	for (Vei2 gridPos = { xStart,yStart }; gridPos.y <= yEnd; gridPos.y++)
	{
		for (gridPos.x = xStart; gridPos.x <= xEnd; gridPos.x++)
		{
			if (TileAt(gridPos).HasMeme())
			{
				count++;
			}
		}
	}

	return count;
}

//Tile& MemeField::GetTile()
//{
//	// TODO: insert return statement here
//}
