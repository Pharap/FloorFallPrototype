#include "Game.h"

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

#include "Levels.h"

void Game::setup()
{
	this->arduboy.begin();
	this->gameplayState.loadMap(Levels::level0);
}

void Game::loop()
{
	if(!this->arduboy.nextFrame())
		return;

	this->arduboy.pollButtons();

	this->arduboy.clear();

	this->update();

	this->arduboy.display();
}

void Game::update()
{
	switch(this->gameState)
	{
		case GameState::SplashscreenState:
			this->splashscreenState.update(*this);
			this->splashscreenState.render(*this);
			break;

		case GameState::TitlescreenState:
			this->titlescreenState.update(*this);
			this->titlescreenState.render(*this);
			break;

		case GameState::LevelSelectState:
			this->levelSelectState.update(*this);
			this->levelSelectState.render(*this);
			break;

		case GameState::GameplayState:
			this->gameplayState.update(*this);
			this->gameplayState.render(*this);
			break;
	}
}