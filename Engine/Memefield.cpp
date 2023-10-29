#include "Memefield.h"
#include <random>

void Memefield::SpawnMemes(const int nMemes)
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> xDist(0, width);
	std::uniform_int_distribution<int> yDist(0, height);

	for (int i; i < nMemes; i++)
	{
		AtTile({ xDist(rng), yDist(rng) }).MemePlanted();
	}
}

void Memefield::Tile::MemePlanted()
{
	hasMeme = true;
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
