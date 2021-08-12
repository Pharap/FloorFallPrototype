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

// For uint8_t
#include <stdint.h>

// For PROGMEM
#include <avr/pgmspace.h>

namespace Images
{
	constexpr uint8_t brokenTileWidth = 8;
	constexpr uint8_t brokenTileHeight = 8;

	constexpr uint8_t brokenTile[] PROGMEM
	{
		// Dimensions
		brokenTileWidth, brokenTileHeight,

		// Frame 0 - Broken Tile 0
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,

		// Frame 1 - Broken Tile 1
		0x7E, 0xFF, 0xFF, 0xBB, 0x81, 0xBF, 0xFF, 0x7E,

		// Frame 2 - Broken Tile 2
		0x7E, 0xFF, 0xBB, 0x9D, 0xAD, 0xB3, 0xFF, 0x7E,

		// Frame 3 - Broken Tile 3
		0x7E, 0xFF, 0xDB, 0xBD, 0xB5, 0xB5, 0xCB, 0x7E,

		// // Frame 4 - Broken Tile 4
		// 0x7E, 0xFF, 0xCF, 0xD7, 0xDB, 0x83, 0xDF, 0x7E,

		// // Frame 5 - Broken Tile 5
		// 0x7E, 0xFF, 0xD1, 0xB5, 0xB5, 0xCD, 0xFF, 0x7E,

		// // Frame 6 - Broken Tile 6
		// 0x7E, 0xFF, 0xC3, 0xAD, 0xAD, 0xDB, 0xFF, 0x7E,

		// // Frame 7 - Broken Tile 7
		// 0x7E, 0xFF, 0xFD, 0x9D, 0xE5, 0xF9, 0xFF, 0x7E,

		// // Frame 8 - Broken Tile 8
		// 0x7E, 0xFF, 0xCB, 0xB5, 0xB5, 0xCB, 0xFF, 0x7E,

		// // Frame 9 - Broken Tile 9
		// 0x7E, 0xFF, 0xF3, 0xAD, 0xAD, 0xC3, 0xFF, 0x7E,
	};
}