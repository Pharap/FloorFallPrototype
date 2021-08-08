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

class Game;

class GameplayState
{
private:
	// The dimensions of the board
	static constexpr uint8_t boardWidth = 8;
	static constexpr uint8_t boardHeight = 8;

	// The farthest limits of the board
	static constexpr uint8_t boardLeft = 0;
	static constexpr uint8_t boardRight = (boardWidth - 1);
	static constexpr uint8_t boardTop = 0;
	static constexpr uint8_t boardBottom = (boardHeight - 1);

	// The dimensions of each tile
	static constexpr uint8_t tileWidth = 8;
	static constexpr uint8_t tileHeight = 8;

private:
	// The board, represented as a grid of tiles
	Tile board[boardHeight][boardWidth]
	{
		{ Tile(TileType::Solid, 0), Tile(TileType::Button, 0), Tile(TileType::Broken, 3), Tile(TileType::Solid, 0), Tile(TileType::Button, 0), Tile(TileType::Broken, 3), Tile(TileType::Solid, 0), },
		{ Tile(TileType::Solid, 0), Tile(TileType::Button, 0), Tile(TileType::Broken, 3), Tile(TileType::Solid, 0), Tile(TileType::Button, 0), Tile(TileType::Broken, 3), Tile(TileType::Solid, 0), },
		{ Tile(TileType::Solid, 0), Tile(TileType::Button, 0), Tile(TileType::Broken, 3), Tile(TileType::Solid, 0), Tile(TileType::Button, 0), Tile(TileType::Broken, 3), Tile(TileType::Solid, 0), },
		{ Tile(TileType::Solid, 0), Tile(TileType::Button, 0), Tile(TileType::Broken, 3), Tile(TileType::Solid, 0), Tile(TileType::Button, 0), Tile(TileType::Broken, 3), Tile(TileType::Solid, 0), },
		{ Tile(TileType::Solid, 0), Tile(TileType::Button, 0), Tile(TileType::Broken, 3), Tile(TileType::Solid, 0), Tile(TileType::Button, 0), Tile(TileType::Broken, 3), Tile(TileType::Solid, 0), },
		{ Tile(TileType::Solid, 0), Tile(TileType::Button, 0), Tile(TileType::Broken, 3), Tile(TileType::Solid, 0), Tile(TileType::Button, 0), Tile(TileType::Broken, 3), Tile(TileType::Solid, 0), },
		{ Tile(TileType::Solid, 0), Tile(TileType::Button, 0), Tile(TileType::Broken, 3), Tile(TileType::Solid, 0), Tile(TileType::Button, 0), Tile(TileType::Broken, 3), Tile(TileType::Solid, 0), },
		{ Tile(TileType::Solid, 0), Tile(TileType::Button, 0), Tile(TileType::Broken, 3), Tile(TileType::Solid, 0), Tile(TileType::Button, 0), Tile(TileType::Broken, 3), Tile(TileType::Solid, 0), },
	};

	// The player's position on the board
	uint8_t playerX;
	uint8_t playerY;

	// The number of moves the player has made
	uint8_t playerMoves;

public:
	// Updates the game logic
	void update(Game & game);

	// Renders the game
	void render(Game & game);

private:
	// Handles player input
	void updatePlayer(Game & game);

	// Handles stepping onto a tile
	void stepOn(Tile & tile);

	// Handles stepping off of a tile
	void stepOff(Tile & tile);

	// Render's the player's character
	void renderPlayer(Game & game);

	// Draws the board
	void renderBoard(Game & game);

	// Draws a tile
	void drawTile(Game & game, Tile tile, int16_t x, int16_t y);
};