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

namespace Images
{
	constexpr uint8_t buttonTileWidth = 8;
	constexpr uint8_t buttonTileHeight = 8;

	constexpr uint8_t buttonTile[] PROGMEM
	{
		// Dimensions
		buttonTileWidth, buttonTileHeight,

		// Frame 0 - Off
		0x7E, 0xC3, 0x99, 0xA5, 0xA5, 0x99, 0xC3, 0x7E,

		// Frame 1 - On
		0x7E, 0xC3, 0x99, 0xBD, 0xBD, 0x99, 0xC3, 0x7E,
	};
}