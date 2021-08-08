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

#include <avr/pgmspace.h>

#include "Tile.h"

constexpr uint8_t boardWidth = 8;
constexpr uint8_t boardHeight = 8;

constexpr size_t mapSize = ((boardWidth * boardHeight) / (8 / 4));

inline void loadMap(Tile (& board)[boardHeight][boardWidth], const uint8_t (& map)[mapSize])
{
	for(uint8_t y = 0; y < boardHeight; ++y)
	{
		const size_t rowOffset = (y * boardWidth);

		for(uint8_t x = 0; x < boardWidth; x += 2)
		{
			const size_t index = (rowOffset + (x / 2));
			const uint8_t mapByte = pgm_read_byte(&map[index]);

			const TileType type0 = static_cast<TileType>((mapByte >> 0) & 0x03);
			const uint8_t parameter0 = ((mapByte >> 2) & 0x03);

			board[y][x + 0] = Tile(type0, parameter0);

			const TileType type1 = static_cast<TileType>((mapByte >> 4) & 0x03);
			const uint8_t parameter1 = ((mapByte >> 6) & 0x03);

			board[y][x + 1] = Tile(type1, parameter1);
		}
	}
}