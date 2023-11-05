#include "Memefield.h"
#include <random>
#include <assert.h>

void Memefield::SpawnMemes()
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> xDist(0, width - 1);
	std::uniform_int_distribution<int> yDist(0, height - 1);
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

void Memefield::RemoveMeme(Vei2 mouseClick)
{
	Vei2 clickedTileLoc = PixToTileLoc(mouseClick);
	AtTile(clickedTileLoc).DisarmMeme();
	nMemes--;
	CheckNeighbor(mouseClick);
	AtTile(PixToTileLoc(mouseClick)).SetReveal();
	
}

Vei2 Memefield::TileToPixLoc(Vei2 const tileLoc) const
{
	return Vei2(tileLoc.x * SpriteCodex::tileSize, tileLoc.y * SpriteCodex::tileSize);
}

Vei2 Memefield::PixToTileLoc(Vei2 const pixelLoc) const
{
	return Vei2(pixelLoc / SpriteCodex::tileSize);
}

void Memefield::ClickReveal(Vei2 mouseClick)
{
	Vei2 clickedTileLoc = PixToTileLoc(mouseClick);
	if (AtTile(clickedTileLoc).HasMeme())
	{
		blownUp = true;
		AtTile(PixToTileLoc(mouseClick)).SetReveal();
	}
	else
	{
		CheckNeighbor(mouseClick);
		AtTile(PixToTileLoc(mouseClick)).SetReveal();
	}
	

	
}

void Memefield::ClickFlag(Vei2 mouseClick)
{
	AtTile(PixToTileLoc(mouseClick)).SetFlag();
}


Memefield::Memefield(int in_nMemes)
	:
	nMemes(in_nMemes),
	background(0, width* SpriteCodex::tileSize, 0, height* SpriteCodex::tileSize)
{
	assert(nMemes < width * height);
}

Memefield::Tile& Memefield::AtTile(Vei2 tileLocation)
{
	return tiles[tileLocation.y * width + tileLocation.x];
}

void Memefield::Tile::MemePlanted()
{
	hasMeme = true;
}

void Memefield::Tile::DisarmMeme()
{
	hasMeme = false;
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
			switch (numBombsNear)
			{
			case 0:
				SpriteCodex::DrawTile0(pixelLoc, gfx);
				break;
			case 1:
				SpriteCodex::DrawTile1(pixelLoc, gfx);
				break;
			case 2:
				SpriteCodex::DrawTile2(pixelLoc, gfx);
				break;
			case 3:
				SpriteCodex::DrawTile3(pixelLoc, gfx);
				break;
			case 4:
				SpriteCodex::DrawTile4(pixelLoc, gfx);
				break;
			case 5:
				SpriteCodex::DrawTile5(pixelLoc, gfx);
				break;
			case 6:
				SpriteCodex::DrawTile6(pixelLoc, gfx);
				break;
			case 7:
				SpriteCodex::DrawTile7(pixelLoc, gfx);
				break;
			case 8:
				SpriteCodex::DrawTile8(pixelLoc, gfx);
				break;
			}
		}
		else
		{
			SpriteCodex::DrawTileBombRed(pixelLoc, gfx);
			//SpriteCodex::DrawTileBomb(pixelLoc, gfx);
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

void Memefield::Tile::SetNumber(int tileNum)
{
	numBombsNear = tileNum;
}

void Memefield::Tile::UpNum()
{
	numBombsNear++;
}

void Memefield::CheckNeighbor(Vei2 mouseClick)
{
	Vei2 tileLoc = PixToTileLoc(mouseClick);

	//the 3 tiles that are above the tile that was clicked
	Vei2 topRowStart = tileLoc + Vei2(-1, -1);
	Vei2 topRowEnd = tileLoc + Vei2(1, -1);

	for (topRowStart.x; topRowStart.x <= topRowEnd.x; topRowStart.x++)
	{
		if (IsTileInBounds(topRowStart))
		{
			if (AtTile(topRowStart).HasMeme())
			{
				AtTile(tileLoc).UpNum();
			}
		}
		
	}

	//Left and Right Tile
	Vei2 leftTile = tileLoc + Vei2(-1, 0);
	Vei2 rightTile = tileLoc + Vei2(1, 0);

	if (IsTileInBounds(leftTile))
	{
		if (AtTile(leftTile).HasMeme())
		{
			AtTile(tileLoc).UpNum();
		}
	}
	if (IsTileInBounds(rightTile))
	{
		if (AtTile(rightTile).HasMeme())
		{
			AtTile(tileLoc).UpNum();
		}
	}
	

	//the 3 tiles that are below the tile that was clicked
	Vei2 bottomRowStart = tileLoc + Vei2(-1, 1);
	Vei2 bottomRowEnd = tileLoc + Vei2(1, 1);

	for (bottomRowStart.x; bottomRowStart.x <= bottomRowEnd.x; bottomRowStart.x++)
	{
		if (IsTileInBounds(bottomRowStart))
		{
			if (AtTile(bottomRowStart).HasMeme())
			{
				AtTile(tileLoc).UpNum();
			}
		}
	}


}

void Memefield::ClickNoBomb(Vei2 mouseClick)
{
	Vei2 clickedTileLoc = PixToTileLoc(mouseClick);
	CheckNeighbor(mouseClick);
	AtTile(PixToTileLoc(mouseClick)).SetReveal();
}

bool Memefield::IsBlownUp()
{
	return blownUp;
}

bool Memefield::IsTileInBounds(Vei2 tileLoc) const
{
	return tileLoc.x >= 0 && tileLoc.x <= width - 1 &&
		tileLoc.y >= 0 && tileLoc.y <= height - 1;
}

