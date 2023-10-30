#include "Memefield.h"
#include <random>

void Memefield::SpawnMemes()
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> xDist(0, width);
	std::uniform_int_distribution<int> yDist(0, height);

	int i = 0;
	Vei2 newLoc;

	do
	{
		newLoc = { xDist(rng), yDist(rng) };
		AtTile(newLoc).MemePlanted();
		i++;
	} while (i < nMemes);// && !AtTile(newLoc).HasMeme());
}

void Memefield::Draw(Graphics& gfx)
{
	background = { 0, width * SpriteCodex::tileSize, 0, height * SpriteCodex::tileSize };
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
		SpriteCodex::DrawTileFlag(pixelLoc, gfx);
		break;
	case State::Revealed:
		SpriteCodex::DrawTileBomb(pixelLoc, gfx);
		break;
	}
}

