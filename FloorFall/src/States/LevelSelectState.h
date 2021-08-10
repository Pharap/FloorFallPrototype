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

#include "../Levels.h"
#include "../Utils.h"

class Game;

class LevelSelectState
{
private:
	// The total number of options (levels).
	static constexpr uint8_t optionCount = Utils::getSize(Levels::levels);

	// The first index of all options.
	static constexpr uint8_t firstIndex = 0;

	// The last index of all options.
	static constexpr uint8_t lastIndex = (optionCount - 1);

private:
	// The index of the selected level.
	uint8_t selectedIndex;

public:
	void update(Game & game);
	void render(Game & game);
};