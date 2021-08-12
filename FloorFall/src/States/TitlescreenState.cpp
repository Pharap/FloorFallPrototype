#include "TitlescreenState.h"

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
#include "../Settings.h"
#include "../Flash.h"

void TitlescreenState::update(Game & game)
{
	// Get a reference to the arduboy object.
	auto & arduboy = game.getArduboy();

	// If the A button was pressed...
	if(arduboy.justPressed(A_BUTTON))
		// Go to the level select menu.
		game.changeState(GameState::LevelSelectState);
}

void TitlescreenState::render(Game & game)
{
	// Calculate the position of the titlescreen banner. (At compile time.)
	constexpr uint8_t titlescreenX = ((Arduboy2::width() - Images::titlescreenWidth) / 2);
	constexpr uint8_t titleScreenY = 0;

	// Draw the titlescreen banner.
	Sprites::drawOverwrite(titlescreenX, titleScreenY, Images::titlescreen, 0);

	// Get a reference to the arduboy object.
	auto & arduboy = game.getArduboy();

	// Use arbitrary values for now.
	arduboy.setCursor(48, 48);

	// Create a temporary type alias.
	using Strings = Settings::Strings;

	// Print a 'press A' style message.
	arduboy.println(FlashString(Strings::pressA));
}