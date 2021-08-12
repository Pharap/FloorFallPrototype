#pragma once

//
//  Copyright (C) 2021 Pharap (@Pharap)
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//

#include <stdint.h>
#include <stddef.h>

#include "Logic.h"

// This data needs to be shared between multiple states.
class GameData
{
private:
	// The dimensions of the board.
	static constexpr uint8_t boardWidth = 8;
	static constexpr uint8_t boardHeight = 8;

	// The dimensions of each tile.
	static constexpr uint8_t tileWidth = 8;
	static constexpr uint8_t tileHeight = 8;

public:
	// A type alias for the type of the board.
	using Board = Grid<Tile, boardWidth, boardHeight>;

private:
	// The board, represented as a grid of tiles.
	Board board {};

	// The player's position on the board.
	uint8_t playerX;
	uint8_t playerY;

	// Keeps track of the last map loaded.
	// Necessary for resetting the board.
	const uint8_t * lastMap { nullptr };

public:
	// Returns a mutable reference to the player's X position.
	uint8_t & getPlayerX()
	{
		return this->playerX;
	}

	// Returns a read-only reference to the player's X position.
	constexpr const uint8_t & getPlayerX() const
	{
		return this->playerX;
	}

	// Returns a mutable reference to the player's Y position.
	uint8_t & getPlayerY()
	{
		return this->playerY;
	}

	// Returns a read-only reference to the player's Y position.
	constexpr const uint8_t & getPlayerY() const
	{
		return this->playerY;
	}

	// Returns a mutable reference to the game board.
	Board & getBoard()
	{
		return this->board;
	}

	// Returns a read-only reference to the game board.
	constexpr const Board & getBoard() const
	{
		return this->board;
	}

	constexpr uint8_t getTileWidth() const
	{
		return tileWidth;
	}

	constexpr uint8_t getTileHeight() const
	{
		return tileHeight;
	}

	// Draws the board.
	void renderBoard() const;

	// Draws the board at an offset.
	void renderBoard(int16_t x, int16_t y) const;

	// Draws a tile.
	void renderTile(Tile tile, int16_t x, int16_t y) const;

	// Reloads the last map loaded.
	void reloadLastMap();

	// A helper function for map loading.
	template<size_t mapSize>
	void loadMap(const uint8_t (& map)[mapSize]);

	// Loads a map.
	void loadMap(const uint8_t * map);
};

// Define the loadMap function template
template<size_t mapSize>
void GameData::loadMap(const uint8_t (& map)[mapSize])
{
	// Ensure the map has at least the required 4 byte header
	static_assert(mapSize > 4, "A map must be at least 4 bytes large");

	// If debugging is enabled, do some extra sanity checks...
	#if defined(DEBUG)
	// Read the map dimensions
	const uint8_t width = pgm_read_byte(&map[0]);
	const uint8_t height = pgm_read_byte(&map[1]);

	// Ensure that the map is a suitable size
	assert(width > 0);
	assert(height > 0);
	assert(width <= 8);
	assert(height <= 8);

	// Round the dimensions up to the next nearest multiple of two.
	const uint8_t evenWidth = (width + (width & 1));
	const uint8_t evenHeight = (height + (height & 1));
	
	// Calculate the expected size of the map
	const size_t dataSize = ((evenWidth * evenHeight) / (8 / 4));
	const size_t expectedSize = (4 + dataSize);

	// Ensure that the map is the expected size
	assert(mapSize == expectedSize);
	#endif

	// Defer to the actual map loading function
	this->loadMap(&map[0]);
}