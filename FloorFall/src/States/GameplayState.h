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

#include "../Logic.h"

#include <stdint.h>
#include <stddef.h>

#if defined(DEBUG)
#include <assert.h>
#endif

#include "GameplayPhase.h"

class Game;

class GameplayState
{
private:
	// The dimensions of the board.
	static constexpr uint8_t boardWidth = 8;
	static constexpr uint8_t boardHeight = 8;

	// The furthest limits of the board.
	static constexpr uint8_t boardLeft = 0;
	static constexpr uint8_t boardRight = (boardWidth - 1);
	static constexpr uint8_t boardTop = 0;
	static constexpr uint8_t boardBottom = (boardHeight - 1);

	// The dimensions of each tile.
	static constexpr uint8_t tileWidth = 8;
	static constexpr uint8_t tileHeight = 8;

private:
	// The board, represented as a grid of tiles.
	Tile board[boardHeight][boardWidth] {};

	// The player's position on the board.
	uint8_t playerX;
	uint8_t playerY;

	// The number of moves the player has made.
	uint8_t playerMoves;

	// The phase/state of the game.
	GameplayPhase phase { GameplayPhase::Playing };

	// Keeps track of the last map loaded.
	// Necessary for resetting the board.
	const uint8_t * lastMap { nullptr };

public:
	// Updates the game logic.
	void update(Game & game);

	// Renders the game.
	void render(Game & game);

	// A helper function for map loading.
	template<size_t mapSize>
	void loadMap(const uint8_t (& map)[mapSize]);

	// Loads a map.
	void loadMap(const uint8_t * map);

private:
	void updatePlayingPhase(Game & game);

	void renderPlayingPhase(Game & game);

	void updateSuccessPhase(Game & game);

	void renderSuccessPhase(Game & game);

	void updateFailurePhase(Game & game);

	void renderFailurePhase(Game & game);

	// Handles player input.
	void updatePlayer(Game & game);

	// Render's the player's character.
	void renderPlayer(Game & game);

	// Draws the board.
	void renderBoard(Game & game);

	// Draws a tile.
	void renderTile(Tile tile, int16_t x, int16_t y);

	// Handles stepping onto a tile.
	void stepOn(Tile & tile);

	// Handles stepping off of a tile.
	void stepOff(Tile & tile);

	// Determines if all buttons are on.
	bool areAllButtonsOn();

	// Resets the level.
	void resetLevel();
};

// Define the loadMap function template
template<size_t mapSize>
void GameplayState::loadMap(const uint8_t (& map)[mapSize])
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