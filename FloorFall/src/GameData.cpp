#include "GameData.h"

#include "Logic.h"
#include "Images.h"
#include "Utils.h"

// Include Arduboy2 for Sprites.
#include <Arduboy2.h>

// Include progmem reading funtions for map loading.
#include <avr/pgmspace.h>

void GameData::renderBoard() const
{
	// Forward to the offset version.
	this->renderBoard(0, 0);
}

void GameData::renderBoard(int16_t xOffset, int16_t yOffset) const
{
	// These checks are left in as a precaution.
	// I certainly have no intent of using such a large board,
	// but someone using this code in the future might attempt to,
	// so I think it's only fair to warn them that they'll need to rewrite this section.
	static_assert(Board::width < 256, "Board width must be less than 256 due to use of uint8_t for traversal");
	static_assert(Board::height < 256, "Board height must be less than 256 due to use of uint8_t for traversal");

	// Note that using int16_t for y and x would (quite rightly)
	// produce warnings about comparing signed and unsigned numbers,
	// because size_t (Board's size_type) will always be unsigned.

	for(uint8_t y = 0; y < this->board.getHeight(); ++y)
	{
		// Calculate the y position of the tile
		const int16_t drawY = (yOffset + (y * this->getTileHeight()));

		// Note that both y and tileHeight are automatically
		// promoted to int before the multiplication,
		// so the multiplication is 16-bit on Arduboy
		// and thus there's no need to worry about overflow.

		for(uint8_t x = 0; x < this->board.getWidth(); ++x)
		{
			// Calculte the x position of the tile
			const int16_t drawX = (xOffset + (x * this->getTileWidth()));

			// Get a readonly reference to the tile
			const auto & tile = this->board.getCell(x, y);

			// Draw the tile
			this->renderTile(tile, drawX, drawY);
		}
	}
}

void GameData::renderTile(Tile tile, int16_t x, int16_t y) const
{
	// Cache the type and the parameter.
	const auto type = tile.getType();
	const auto parameter = tile.getParameter();

	// Used to track the sprite to be drawn.
	const uint8_t * sprite = nullptr;

	// Select a sprite depending on the type of the tile.
	switch(type)
	{
		case TileType::Broken:
			sprite = Images::brokenTile;
			break;

		case TileType::Solid:
			sprite = Images::solidTile;
			break;

		case TileType::Button:
			sprite = Images::buttonTile;
			break;
	}

	// If sprite is no longer nullptr...
	// (I.e. if a suitable sprite was found for the tile.)
	if(sprite != nullptr)
		// Draw the sprite, using the tile's parameter as the frame index.
		Sprites::drawOverwrite(x, y, sprite, parameter);
}

void GameData::reloadLastMap()
{
	// Exactly what it says on the tin.
	this->loadMap(this->lastMap);
}

void GameData::loadMap(const uint8_t * map)
{
	// Read the map dimensions
	const uint8_t width = pgm_read_byte(&map[0]);
	const uint8_t height = pgm_read_byte(&map[1]);

	// Read the player position
	const uint8_t playerX = pgm_read_byte(&map[2]);
	const uint8_t playerY = pgm_read_byte(&map[3]);

	// If debugging is enabled, do some extra sanity checks...
	#if defined(DEBUG)
	// Ensure the player position is valid
	assert(playerX < width);
	assert(playerY < height);
	#endif

	// Set the player position
	this->playerX = playerX;
	this->playerY = playerY;

	// Get a pointer to the data area of the map
	const uint8_t * mapData = &map[4];

	// Prepare an empty tile to copy.
	// (Oddly enough, this does actually save memory.)
	constexpr auto emptyTile = Tile::makeEmptyTile();

	// Note:
	// I tried a handful of ways of doing this,
	// and although this probably isn't the fastest way,
	// it's cheaper (in terms of progmem) and simpler
	// than the other approaches I tried.
	// On Arduboy, especially for a game like this, space trumps time.

	// Calculate the size of a row as stored in the map.
	// The unusual cacluation is because the map stores two tiles per byte.
	const auto rowSize = ((width / 2) + (((width % 2) != 0) ? 1 : 0));

	// Loop through the board.
	for(uint8_t y = 0; y < board.getHeight(); ++y)
	{
		// Calculate the map offset of the row.
		// (The compiler is probably replacing the multiplication
		// with an addition to a variable outside the loop.)
		const size_t rowIndex = (y * rowSize);
		
		for(uint8_t x = 0; x < board.getWidth(); ++x)
		{
			// If the tile is outside the map...
			if((x >= width) || (y >= height))
			{
				// Clear the tile.
				board.getCell(x, y) = emptyTile;
				
				// Continue to the next iteration.
				continue;
			}

			// Calculate the index as an offset from the row index.
			const size_t index = (rowIndex + (x / 2));

			// Read the current byte of map data,
			// containing two tiles worth of information.
			const auto mapByte = pgm_read_byte(&mapData[index]);

			// Set the tile.
			board.getCell(x, y) =
				// If x is even, read the left tile. Otherwise, read the right tile.
				Utils::isEven(x) ? getLeftTile(mapByte) : getRightTile(mapByte);
		}
	}

	// Remember which map was loaded last
	// to allow the board to be properly reset.
	this->lastMap = map;
}