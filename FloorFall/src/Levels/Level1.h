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
#include <avr/pgmspace.h>

#include "../Logic/Tile.h"

namespace Levels
{
	constexpr uint8_t level1[] PROGMEM
	{
		// Width, Height
		5, 1,

		// Player X, Player Y
		0, 0,

		toTileByte(Tile::makeSolidTile(), Tile::makeBrokenTile(1)),
		toTileByte(Tile::makeOffButton(), Tile::makeBrokenTile(1)),
		toTileByte(Tile::makeOffButton(), Tile::makeEmptyTile()),
	};
}