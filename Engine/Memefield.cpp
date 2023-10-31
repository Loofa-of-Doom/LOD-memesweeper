#include "Memefield.h"
#include <random>

void Memefield::SpawnMemes()
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> xDist(0, width);
	std::uniform_int_distribution<int> yDist(0, height);
	Vei2 newLoc;
	if (!finishedSpawning)
	{
		int i = 0;
		do
		{
			newLoc = { xDist(rng), yDist(rng) };
			while (AtTile(newLoc).HasMeme())
			{
				newLoc = { xDist(rng), yDist(rng) };
			}
			AtTile(newLoc).MemePlanted();
			i++;

		} while (i < nMemes);

		finishedSpawning = true;

	}


}

void Memefield::Draw(Graphics& gfx)
{
	RectI background = { 0, width * SpriteCodex::tileSize, 0, height * SpriteCodex::tileSize };
	gfx.DrawRect(background, backgroundCol);

	int i = 0;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			
			Vei2 tileLocation = TileToPixLoc({x,y});
			tiles[i].Draw(gfx,tileLocation);
			i++;
		}
	}
}

Vei2 Memefield::TileToPixLoc(Vei2 tileLoc)
{
	return Vei2(tileLoc.x * SpriteCodex::tileSize, tileLoc.y * SpriteCodex::tileSize);
}

void Memefield::ClickReveal(Vei2 mouseClick)
{
	Vei2 pixelLoc;
	pixelLoc = mouseClick / SpriteCodex::tileSize;
	
	AtTile(pixelLoc).SetReveal();
}

void Memefield::ClickFlag(Vei2 mouseClick)
{
	Vei2 pixelLoc;
	pixelLoc = mouseClick / SpriteCodex::tileSize;

	AtTile(pixelLoc).SetFlag();
}




Memefield::Memefield(int in_nMemes)
	:
	nMemes(in_nMemes)
{
}

Memefield::Tile& Memefield::AtTile(Vei2 tileLocation)
{
	return tiles[tileLocation.y * width + tileLocation.x];
}

void Memefield::Tile::MemePlanted()
{
	hasMeme = true;
}

bool Memefield::Tile::HasMeme()
{
	return hasMeme;
}

void Memefield::Tile::Draw(Graphics& gfx, Vei2& pixelLoc) const
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
		if (!hasMeme)
		{
			SpriteCodex::DrawTile0(pixelLoc, gfx);
		}
		else
		{
			SpriteCodex::DrawTileBomb(pixelLoc, gfx);
		}
		break;
	}
}

void Memefield::Tile::SetReveal()
{
	state = State::Revealed;
}

void Memefield::Tile::SetFlag()
{
	if (!(state == State::Flagged))
	{
		state = State::Flagged;
	}
	else
	{
		state = State::Hidden;
	}
	
}

