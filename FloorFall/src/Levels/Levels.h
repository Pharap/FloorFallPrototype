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

#include "Level0.h"
#include "Level1.h"
#include "Level2.h"
// #include "Level3.h"
// #include "Level4.h"
// #include "Level5.h"
// #include "Level6.h"
// #include "Level7.h"
// #include "Level8.h"
// #include "Level9.h"

// #include "Level10.h"
// #include "Level11.h"
// #include "Level12.h"
// #include "Level13.h"
// #include "Level14.h"
// #include "Level15.h"
// #include "Level16.h"
// #include "Level17.h"
// #include "Level18.h"
// #include "Level19.h"

namespace Levels
{
	constexpr const uint8_t * levels[] PROGMEM
	{
		level0,
		level1,
		level2,
		// level3,
		// level4,
		// level5,
		// level6,
		// level7,
		// level8,
		// level9,

		// level10,
		// level11,
		// level12,
		// level13,
		// level14,
		// level15,
		// level16,
		// level17,
		// level18,
		// level19,
	};
}