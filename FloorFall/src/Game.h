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

#include <Arduboy2.h>

#include "Strings.h"
#include "States.h"
#include "GameData.h"

class Game
{
private:
	Arduboy2 arduboy {};

	GameState gameState { GameState::SplashscreenState };

	SplashscreenState splashscreenState {};
	TitlescreenState titlescreenState {};
	LevelSelectState levelSelectState {};
	GameplayState gameplayState {};

	GameData gameData {};

public:
	void changeState(GameState gameState)
	{
		this->gameState = gameState;
	}

	Arduboy2 & getArduboy()
	{
		return this->arduboy;
	}

	const Arduboy2 & getArduboy() const
	{
		return this->arduboy;
	}

	GameData & getGameData()
	{
		return this->gameData;
	}

	const GameData & getGameData() const
	{
		return this->gameData;
	}

public:
	void setup();

	void loop();

private:
	void update();
};