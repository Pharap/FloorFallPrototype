#include "SplashscreenState.h"

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

void SplashscreenState::update(Game & game)
{
	// Get a reference to the arduboy object.
	auto & arduboy = game.getArduboy();

	// If A or B is pressed...
	if (arduboy.justPressed(A_BUTTON) || arduboy.justPressed(B_BUTTON))
	{
		// Proceed to the titlescreen.
		game.changeState(GameState::TitlescreenState);
		return;
	}

	// TODO: fix this god-awful mess.

	// If blink delay is greater than zero...
	if (blinkDelay > 0)
	{
		// Every 1 second...
		if (arduboy.everyXFrames(60))
		{
			// Reduce the delay by 1.
			--this->blinkDelay;

			// If the delay reaches 0.
			if (blinkDelay == 0)
				// Prepare to blink.
				this->blinkInvert = !this->blinkInvert;
		}
	}
	else if (arduboy.everyXFrames(2))
	{
		// Eye opening.
		if (this->blinkInvert)
		{
			if (this->blinkTick > blinkTickMin)
				// Decrease tick counter.
				--this->blinkTick;
			else
				// Create a random delay before blinking again.
				this->blinkDelay = blinkDelayDefault + (rand() % (blinkDelayVariance + 1));
		}
		// Eye closing.
		else
		{
			if (this->blinkTick < blinkTickMax)
				// Increase tick counter.
				++this->blinkTick;
			else
				// Switch to eye opening.
				this->blinkInvert = !this->blinkInvert;
		}
	}
}

void SplashscreenState::render(Game & game)
{
	constexpr uint8_t logoX = ((Arduboy2::width() - Images::pharapLogoWidth) / 2);
	constexpr uint8_t logoY = ((Arduboy2::height() - Images::pharapLogoHeight) / 2);

	Sprites::drawOverwrite(logoX, logoY, Images::pharapLogo, 0);
	
	constexpr uint8_t topEyelidLeft = (logoX + 14);
	constexpr uint8_t topEyelidTop = (logoY + 15);
	
	constexpr uint8_t bottomEyelidLeft = (logoX + 14);
	constexpr uint8_t bottomEyelidBottom = (logoY + 27);
	
	constexpr uint8_t eyelidWidth = (34 - 14);

	// Get a reference to the arduboy object.
	auto & arduboy = game.getArduboy();

	arduboy.fillRect(topEyelidLeft, topEyelidTop, eyelidWidth, this->blinkTick);
	arduboy.fillRect(bottomEyelidLeft, bottomEyelidBottom - this->blinkTick, eyelidWidth, this->blinkTick);
}