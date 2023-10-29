#include "Memefield.h"
#include <random>

void Memefield::Tile::SpawnMemes()
{
}

Memefield::Memefield(int in_nMemes)
	:
	nMemes(in_nMemes),
	background(0, width * SpriteCodex::tileSize, 0, height * SpriteCodex::tileSize)
{
}

Memefield::Tile& Memefield::AtTile(Vei2& tileLocation)
{
	return tiles[tileLocation.y * width + tileLocation.x];
}
