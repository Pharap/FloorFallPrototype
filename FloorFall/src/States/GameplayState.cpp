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

	// Get a read-only reference to the shared game data.
	const auto & gameData = game.getGameData();

	// If all button tiles are on...
	if(this->areAllButtonsOn(gameData.getBoard()))
	{
		// Change the phase to success.
		this->phase = GameplayPhase::Success;
	}
}

void GameplayState::renderPlayingPhase(Game & game) const
{
	// Render the board with the player on top.
	this->renderBoardAndPlayer(game);
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

	// If the B button was pressed...
	if(arduboy.justPressed(B_BUTTON))
	{
		// Reset the phase to playing.
		this->phase = GameplayPhase::Playing;

		// Return the player to the level select menu.
		game.changeState(GameState::LevelSelectState);
	}
}

void GameplayState::renderSuccessPhase(Game & game) const
{
	// Render the board with the player on top.
	this->renderBoardAndPlayer(game);

	// Get a reference to the arduboy object.
	auto & arduboy = game.getArduboy();

	// For now just print in the top left corner.
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
		this->resetLevel(game);

		// Change the phase back to playing.
		this->phase = GameplayPhase::Playing;
	}

	// If the B button was pressed...
	if(arduboy.justPressed(B_BUTTON))
	{
		// Reset the phase to playing.
		this->phase = GameplayPhase::Playing;

		// Return the player to the level select menu.
		game.changeState(GameState::LevelSelectState);
	}
}

void GameplayState::renderFailurePhase(Game & game) const
{
	// Render the board with the player on top.
	this->renderBoardAndPlayer(game);

	// Get a reference to the arduboy object.
	auto & arduboy = game.getArduboy();

	// For now just print in the top left corner.
	arduboy.setCursor(0, 0);
	arduboy.println(F("FAILURE"));
}

void GameplayState::updatePlayer(Game & game)
{
	// Get a mutable reference to the arduboy object.
	auto & arduboy = game.getArduboy();

	// Get a mutable reference to the game data.
	auto & gameData = game.getGameData();

	// Get a mutable reference to the game board.
	auto & board = gameData.getBoard();

	// Get a mutable reference to the player's position.
	auto & playerX = gameData.getPlayerX();
	auto & playerY = gameData.getPlayerY();

	// Cache a copy of the player's old position.
	const auto oldPlayerX = playerX;
	const auto oldPlayerY = playerY;

	// If the player has pressed the left button...
	if(arduboy.justPressed(LEFT_BUTTON))
	{
		// If the player is not on the furthest left tile...
		if(playerX > board.getLeftEdge())
		{
			// Move the player left.
			--playerX;
		}
	}

	// If the player has pressed the right button...
	if(arduboy.justPressed(RIGHT_BUTTON))
	{
		// If the player is not on the furthest right tile...
		if(playerX < board.getRightEdge())
		{
			// Move the player right
			++playerX;
		}
	}

	// If the player has pressed the up button...
	if(arduboy.justPressed(UP_BUTTON))
	{
		// If the player is not on the top tile...
		if(playerY > board.getTopEdge())
		{
			// Move the player up
			--playerY;
		}
	}

	// If the player has pressed the down button...
	if(arduboy.justPressed(DOWN_BUTTON))
	{
		// If the player is not on the bottom tile...
		if(playerY < board.getBottomEdge())
		{
			// Move the player down.
			++playerY;
		}
	}

	// Figure out if the player has moved.
	const bool playerMoved = ((playerX != oldPlayerX) || (playerY != oldPlayerY));

	// If the player has moved...
	if(playerMoved)
	{
		// Step off the old tile.
		this->stepOff(board.getCell(oldPlayerX, oldPlayerY));

		// Step onto the new tile.
		this->stepOn(board.getCell(playerX, playerY));
	}
}

void GameplayState::renderPlayer(Game & game) const
{
	// Get a read-only reference to the game data.
	const auto & gameData = game.getGameData();

	// Calculate the y position of the player.
	const uint8_t yOffset = (gameData.getPlayerY() * gameData.getTileHeight());

	// Calculte the x position of the player.
	const uint8_t xOffset = (gameData.getPlayerX() * gameData.getTileWidth());

	// Draw the player.
	Sprites::drawSelfMasked(xOffset, yOffset, Images::player, 0);
}

void GameplayState::renderBoardAndPlayer(Game & game) const
{
	// This function exists primarily because
	// several different functions will want to
	// perform this same sequence of actions.

	// Get a mutable reference to the game data.
	auto & gameData = game.getGameData();

	// Draw the game board first.
	gameData.renderBoard();

	// Then draw the player on top of it.
	this->renderPlayer(game);
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

bool GameplayState::areAllButtonsOn(const Board & board)
{
	// Create an alias for the board's size type.
	using size_type = Board::size_type;

	// Strictly speaking, for the Arduboy Version
	// I could get away with just using uint8_t.
	// But if it doesn't cost much,
	// there's no harm in a bit of future-proofing.

	for(size_type y = 0; y < board.getHeight(); ++y)
		for(size_type x = 0; x < board.getWidth(); ++x)
		{
			// Get a read-only reference to the tile
			const auto & tile = board.getCell(x, y);

			// If the tile is a button
			if(tile.getType() == TileType::Button)
				// If the button is off
				if(tile.getParameter() == 0)
					// Return false because a button is off
					return false;
		}

	// If the end of the loop was reached
	// (without encountering an off button)
	// then assume all buttons are on.
	return true;
}

void GameplayState::resetLevel(Game & game)
{
	// Get a mutable reference to the game data.
	auto & gameData = game.getGameData();

	// Reload the last map.
	gameData.reloadLastMap();
}
