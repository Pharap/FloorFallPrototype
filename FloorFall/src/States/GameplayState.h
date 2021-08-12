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

#if defined(DEBUG)
#include <assert.h>
#endif

#include "../Logic.h"
#include "../GameData.h"

#include "GameplayPhase.h"

class Game;

class GameplayState
{
private:
	// Create a private type alias to the game board.
	using Board = GameData::Board;

private:
	// The phase/state of the game.
	GameplayPhase phase { GameplayPhase::Playing };

public:
	// Updates the game logic.
	void update(Game & game);

	// Renders the game.
	void render(Game & game);

private:
	void updatePlayingPhase(Game & game);

	void renderPlayingPhase(Game & game) const;

	void updateSuccessPhase(Game & game);

	void renderSuccessPhase(Game & game) const;

	void updateFailurePhase(Game & game);

	void renderFailurePhase(Game & game) const;

	// Handles player input.
	void updatePlayer(Game & game);

	// Render's the player's character.
	void renderPlayer(Game & game) const;

	// Draws the board and the player.
	void renderBoardAndPlayer(Game & game) const;

	// Handles stepping onto a tile.
	void stepOn(Tile & tile);

	// Handles stepping off of a tile.
	void stepOff(Tile & tile);

	// Determines if all buttons are on.
	bool areAllButtonsOn(const Board & board);

	// Resets the level.
	void resetLevel(Game & game);
};