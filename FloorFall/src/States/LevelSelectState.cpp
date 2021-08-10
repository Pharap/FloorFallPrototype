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

void LevelSelectState::update(Game & game)
{
	// Get a reference to the arduboy object.
	auto & arduboy = game.getArduboy();

	// If the up button was pressed...
	if(arduboy.justPressed(UP_BUTTON))
	{
		// If the selected index is greater than the first index...
		if(this->selectedIndex > firstIndex)
			// Decrement the selected index.
			--this->selectedIndex;
	}

	// If the down button was pressed...
	if(arduboy.justPressed(DOWN_BUTTON))
	{
		// If the selected index is less than the last index...
		if(this->selectedIndex < lastIndex)
			// Increment the selected index.
			++this->selectedIndex;
	}

	// If the A button was pressed...
	if(arduboy.justPressed(A_BUTTON))
	{
		// Read a pointer from the level list.
		const auto pointer = pgm_read_ptr(&Levels::levels[this->selectedIndex]);

		// Convert it to a valid map pointer.
		const auto map = static_cast<const uint8_t *>(pointer);

		// Load the map.
		game.loadMap(map);

		// Change the state to gameplay mode.
		// (I.e. begin playing the selected level.)
		game.changeState(GameState::GameplayState);
	}
}

void LevelSelectState::render(Game & game)
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
				arduboy.print(F("> "));

			// Print the level number.
			arduboy.print(F("Level "));
			arduboy.print(index);
		}

		arduboy.println();
	}
}