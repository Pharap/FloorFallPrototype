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
#include "../Images.h"

// Include progmem reading funtions for map loading
#include <avr/pgmspace.h>

void GameplayState::update(Game & game)
{
	switch (this->phase)
	{
	case GameplayPhase::Playing:
		this->updatePlayingPhase(game);
		break;

	case GameplayPhase::Success:
		this->updateSuccessPhase(game);
		break;

	case GameplayPhase::Failure:
		this->updateFailurePhase(game);
		break;
	}
}

void GameplayState::render(Game & game)
{
	switch (this->phase)
	{
	case GameplayPhase::Playing:
		this->renderPlayingPhase(game);
		break;

	case GameplayPhase::Success:
		this->renderSuccessPhase(game);
		break;

	case GameplayPhase::Failure:
		this->renderFailurePhase(game);
		break;
	}
}

void GameplayState::updatePlayingPhase(Game & game)
{
	// Update the player.
	this->updatePlayer(game);

	// If all button tiles are on...
	if(this->areAllButtonsOn())
	{
		// Change the phase to success.
		this->phase = GameplayPhase::Success;
	}
}

void GameplayState::renderPlayingPhase(Game & game)
{
	this->renderBoard(game);
	this->renderPlayer(game);
}

void GameplayState::updateSuccessPhase(Game & game)
{
	// Get a reference to the arduboy object.
	auto & arduboy = game.getArduboy();

	// If the A button was pressed...
	if(arduboy.justPressed(A_BUTTON))
	{
		// Reset the phase to playing.
		this->phase = GameplayPhase::Playing;

		// Return the player to the level select menu.
		game.changeState(GameState::LevelSelectState);
	}
}

void GameplayState::renderSuccessPhase(Game & game)
{
	this->renderBoard(game);
	this->renderPlayer(game);

	// Get a reference to the arduboy object.
	auto & arduboy = game.getArduboy();

	arduboy.setCursor(0, 0);
	arduboy.println(F("SUCCESS"));
}

void GameplayState::updateFailurePhase(Game & game)
{
	// Get a reference to the arduboy object.
	auto & arduboy = game.getArduboy();

	// If the A button was pressed...
	if(arduboy.justPressed(A_BUTTON))
	{
		// Reset the level.
		this->resetLevel();

		// Change the phase back to playing.
		this->phase = GameplayPhase::Playing;
	}
}

void GameplayState::renderFailurePhase(Game & game)
{
	this->renderBoard(game);
	this->renderPlayer(game);

	// Get a reference to the arduboy object.
	auto & arduboy = game.getArduboy();

	arduboy.setCursor(0, 0);
	arduboy.println(F("FAILURE"));
}

void GameplayState::updatePlayer(Game & game)
{
	// Get a reference to the arduboy object.
	auto & arduboy = game.getArduboy();

	// Track the player's old position.
	const auto oldPlayerX = this->playerX;
	const auto oldPlayerY = this->playerY;

	// If the player has pressed the left button...
	if(arduboy.justPressed(LEFT_BUTTON))
	{
		// If the player is not on the furthest left tile...
		if(this->playerX > boardLeft)
		{
			// Move the player left.
			--this->playerX;
		}
	}

	// If the player has pressed the right button...
	if(arduboy.justPressed(RIGHT_BUTTON))
	{
		// If the player is not on the furthest right tile...
		if(this->playerX < boardRight)
		{
			// Move the player right
			++this->playerX;
		}
	}

	// If the player has pressed the up button...
	if(arduboy.justPressed(UP_BUTTON))
	{
		// If the player is not on the top tile...
		if(this->playerY > boardTop)
		{
			// Move the player up
			--this->playerY;
		}
	}

	// If the player has pressed the down button...
	if(arduboy.justPressed(DOWN_BUTTON))
	{
		// If the player is not on the bottom tile...
		if(this->playerY < boardBottom)
		{
			// Move the player down.
			++this->playerY;
		}
	}

	// Figure out if the player has moved.
	const bool playerMoved = ((this->playerX != oldPlayerX) || (this->playerY != oldPlayerY));

	// If the player has moved...
	if(playerMoved)
	{
		// Step off the old tile.
		this->stepOff(board[oldPlayerY][oldPlayerX]);

		// Step onto the new tile.
		this->stepOn(board[this->playerY][this->playerX]);
	}
}

void GameplayState::renderPlayer(Game & game)
{
	// Suppress "unused parameter" warnings.
	static_cast<void>(game);

	// Calculate the y position of the player.
	const uint8_t yOffset = (this->playerY * tileHeight);

	// Calculte the x position of the player.
	const uint8_t xOffset = (this->playerX * tileWidth);

	// Draw the player.
	Sprites::drawSelfMasked(xOffset, yOffset, Images::player, 0);
}

void GameplayState::renderBoard(Game & game)
{
	// Suppress "unused parameter" warnings.
	static_cast<void>(game);

	for(int16_t y = 0; y < boardHeight; ++y)
	{
		// Calculate the y position of the tile
		const int16_t yOffset = (y * tileHeight);

		for(int16_t x = 0; x < boardWidth; ++x)
		{
			// Calculte the x position of the tile
			const int16_t xOffset = (x * tileWidth);

			// Get a readonly reference to the tile
			const auto & tile = board[y][x];

			// Draw the tile
			this->renderTile(tile, xOffset, yOffset);
		}
	}
}

void GameplayState::renderTile(Tile tile, int16_t x, int16_t y)
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

void GameplayState::stepOn(Tile & tile)
{
	// Cache the type and the parameter
	const auto type = tile.getType();
	const auto parameter = tile.getParameter();

	switch(type)
	{
		// If the tile is solid...
		case TileType::Solid:
			// Do nothing.
			break;

		// If the tile is a button...
		case TileType::Button:
			switch(parameter)
			{
				// If the button is off...
				case 0:
					// Turn it on.
					tile.setParameter(1);
					break;

				// If the button is on...
				case 1:
					// Turn it off.
					tile.setParameter(0);
					break;
			}
			break;

		// If the tile is broken...
		case TileType::Broken:
			{
				// If the tile is fully broken...
				if(parameter == 0)
				{
					// Change the phase to failure.
					this->phase = GameplayPhase::Failure;
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

bool GameplayState::areAllButtonsOn()
{
	for(int16_t y = 0; y < boardHeight; ++y)
		for(int16_t x = 0; x < boardWidth; ++x)
		{
			// Get a readonly reference to the tile
			const auto & tile = board[y][x];

			// If the tile is a button
			if(tile.getType() == TileType::Button)
				// If the button is off
				if(tile.getParameter() == 0)
					// Return false because a button is off
					return false;
		}

	// If the end of the loop was reached
	// without encountering an off button
	// then assume all buttons are on.
	return true;
}

void GameplayState::resetLevel()
{
	// Resetting the level is the same as reloading the last map.
	this->loadMap(this->lastMap);
}

void GameplayState::loadMap(const uint8_t * map)
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

	// The index of the current byte of the map.
	size_t index = 0;

	// Loop through the map data
	for(uint8_t y = 0; y < height; ++y)
		for(uint8_t x = 0; x < width; x += 2)
		{
			// Read the current byte of map data,
			// containing two tiles worth of information.
			const uint8_t mapByte = pgm_read_byte(&mapData[index]);

			// Read the left tile
			board[y][x + 0] = getLeftTile(mapByte);

			// Read the right tile
			board[y][x + 1] = getRightTile(mapByte);

			// Move to the next byte
			++index;
		}

	// Remember which map was loaded last
	// to allow the board to be properly reset.
	this->lastMap = map;
}