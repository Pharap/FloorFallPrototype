#include "GameplayState.h"

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

#include "../Game.h"

void GameplayState::update(Game & game)
{
	this->updatePlayer(game);
}

void GameplayState::render(Game & game)
{
	this->renderBoard(game);
	this->renderPlayer(game);
}

void GameplayState::updatePlayer(Game & game)
{
	// Get a reference to the arduboy object
	auto & arduboy = game.getArduboy();

	// Track the player's old position
	const auto oldPlayerX = this->playerX;
	const auto oldPlayerY = this->playerY;

	// If the player has pressed the left button
	if(arduboy.justPressed(LEFT_BUTTON))
	{
		// If the player is not on the furthest left tile
		if(this->playerX > boardLeft)
		{
			// Move the player left
			--this->playerX;
		}
	}

	// If the player has pressed the right button
	if(arduboy.justPressed(RIGHT_BUTTON))
	{
		// If the player is not on the furthest right tile
		if(this->playerX < boardRight)
		{
			// Move the player right
			++this->playerX;
		}
	}

	// If the player has pressed the up button
	if(arduboy.justPressed(UP_BUTTON))
	{
		// If the player is not on the top tile
		if(this->playerY > boardTop)
		{
			// Move the player up
			--this->playerY;
		}
	}

	// If the player has pressed the down button
	if(arduboy.justPressed(DOWN_BUTTON))
	{
		// If the player is not on the bottom tile
		if(this->playerY < boardBottom)
		{
			// Move the player down
			++this->playerY;
		}
	}

	// Figure out if the player has moved
	const bool playerMoved = ((this->playerX != oldPlayerX) || (this->playerY != oldPlayerY));

	// If the player has moved
	if(playerMoved)
	{
		this->stepOff(board[oldPlayerY][oldPlayerX]);
		this->stepOn(board[this->playerY][this->playerX]);
	}
}

void GameplayState::stepOn(Tile & tile)
{
	// Cache the type and the parameter
	const auto type = tile.getType();
	const auto parameter = tile.getParameter();

	switch(type)
	{
		// If the tile is solid
		case TileType::Solid:
			// Do nothing
			break;

		// If the tile is a button
		case TileType::Button:
			switch(parameter)
			{
				// If the button is off
				case 0:
					// Turn it on
					tile.setParameter(1);
					break;

				// If the button is on
				case 1:
					// Turn it off
					tile.setParameter(0);
					break;
			}
			break;

		// If the tile is broken
		case TileType::Broken:
			{
				// If the tile is fully broken
				if(parameter == 0)
				{
					// Game over
				}
			}
			break;
	}
}

void GameplayState::stepOff(Tile & tile)
{
	// Cache the type and the parameter
	const auto type = tile.getType();
	const auto parameter = tile.getParameter();

	switch(type)
	{
		// If the tile is solid
		case TileType::Solid:
			// Do nothing
			break;

		// If the tile is a button
		case TileType::Button:
			// Do nothing
			break;

		// If the tile is broken
		case TileType::Broken:
			{
				// If the tile can still be stepped on
				if(parameter > 0)
				{
					// Decrease the number of remaining steps
					tile.setParameter(parameter - 1);

					// TODO:
					// Consider implementing a falling animation when (parameter == 0)
				}
			}
			break;
	}
}

void GameplayState::renderPlayer(Game & game)
{
	// Get a reference to the arduboy object
	auto & arduboy = game.getArduboy();

	// Calculate the y position of the player
	const uint8_t yOffset = (this->playerY * tileHeight);

	// Calculte the x position of the player
	const uint8_t xOffset = (this->playerX * tileWidth);

	// Draw the player as a filled rectangle
	arduboy.fillRect(xOffset, yOffset, tileWidth, tileHeight);
}

void GameplayState::renderBoard(Game & game)
{
	for(int16_t y = 0; y < boardHeight; ++y)
	{
		// Calculate the y position of the tile
		const int16_t yOffset = (y * tileHeight);

		for(int16_t x = 0; x < boardWidth; ++x)
		{
			// Calculte the x position of the tile
			const int16_t xOffset = (x * tileWidth);

			// Get a readonly reference to the tile
			const auto tile = board[y][x];

			// Draw the tile
			this->drawTile(game, tile, xOffset, yOffset);
		}
	}
}

void GameplayState::drawTile(Game & game, Tile tile, int16_t x, int16_t y)
{
	// Get a reference to the arduboy object
	auto & arduboy = game.getArduboy();

	// Cache the type and the parameter
	const auto type = tile.getType();
	const auto parameter = tile.getParameter();

	switch(type)
	{
		case TileType::Solid:
			arduboy.drawRect(x, y, tileWidth, tileHeight);
			break;

		case TileType::Button:
			{
				arduboy.setCursor(x, y);
				switch(parameter)
				{
					case 0:
						arduboy.print('-');
						break;

					case 1:
						arduboy.print('+');
						break;

					default:
						arduboy.print('?');
						break;
				}
			}
			break;

		case TileType::Broken:
			if(parameter > 0)
			{
				arduboy.setCursor(x, y);
				arduboy.print(static_cast<char>('0' + parameter));
			}
			break;
	}
}