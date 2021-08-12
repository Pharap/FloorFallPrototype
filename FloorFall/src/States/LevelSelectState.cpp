#include "LevelSelectState.h"

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
#include "../Settings.h"
#include "../Flash.h"

void LevelSelectState::update(Game & game)
{
	// Get a reference to the arduboy object.
	auto & arduboy = game.getArduboy();

	// If the up button was pressed...
	if(arduboy.justPressed(UP_BUTTON))
	{
		// If the selected index is greater than the first index...
		if(this->selectedIndex > firstIndex)
		{
			// Decrement the selected index.
			--this->selectedIndex;

			// The selected level has changed,
			// so load the selected level.
			this->loadSelectedLevel(game);
		}
	}

	// If the down button was pressed...
	if(arduboy.justPressed(DOWN_BUTTON))
	{
		// If the selected index is less than the last index...
		if(this->selectedIndex < lastIndex)
		{
			// Increment the selected index.
			++this->selectedIndex;

			// The selected level has changed,
			// so load the selected level.
			this->loadSelectedLevel(game);
		}
	}

	// If the A button was pressed...
	if(arduboy.justPressed(A_BUTTON))
		// Begin playing the selected level.
		game.changeState(GameState::GameplayState);

	// If the B button was pressed...
	if(arduboy.justPressed(B_BUTTON))
		// Return the player to the titlescreen.
		game.changeState(GameState::TitlescreenState);
}

void LevelSelectState::render(Game & game)
{
	this->renderLevelList(game);
	this->renderSelectedLevel(game);
}

void LevelSelectState::loadSelectedLevel(Game & game)
{
	// Read a pointer from the level list.
	const auto pointer = pgm_read_ptr(&Levels::levels[this->selectedIndex]);

	// Convert it to a valid map pointer.
	const auto map = static_cast<const uint8_t *>(pointer);

	// Get a mutable reference to the game data.
	auto & gameData = game.getGameData();

	// Load the map.
	gameData.loadMap(map);
}

void LevelSelectState::renderLevelList(Game & game)
{
	// Get a reference to the arduboy object.
	auto & arduboy = game.getArduboy();

	// Rudimentary menu rendering.
	// Renders three levels before and three levels after the selected level.
	for(int16_t offset = -3; offset <= 3; ++offset)
	{
		const int16_t index = (this->selectedIndex + offset);

		// If the calculated index is a valid level index.
		if((index >= firstIndex) && (index <= lastIndex))
		{
			// If the offset is zero...
			// (I.e. if this option is the selected level.)
			if(offset == 0)
				// Use an arrow to indicate the selected level.
				arduboy.print(F("\x10 "));

			// Create a temporary type alias.
			using Strings = Settings::Strings;

			// Print the level number.
			arduboy.print(FlashString(Strings::level));
			arduboy.print(index);
		}

		arduboy.println();
	}
}

void LevelSelectState::renderSelectedLevel(Game & game)
{
	// Get a mutable reference to the game data.
	auto & gameData = game.getGameData();

	// Render a preview of the board.
	gameData.renderBoard(boardPreviewX, boardPreviewY);
}