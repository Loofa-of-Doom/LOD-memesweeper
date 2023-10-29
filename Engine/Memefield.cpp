#include "Memefield.h"
#include <random>

void Memefield::SpawnMemes(const int nMemes)
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
	} while (i < nMemes && AtTile(newLoc).HasMeme());
}




Memefield::Memefield(int in_nMemes)
	:
	nMemes(in_nMemes),
	background(0, width * SpriteCodex::tileSize, 0, height * SpriteCodex::tileSize)
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
