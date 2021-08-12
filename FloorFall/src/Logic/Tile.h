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

#include "TileType.h"

class Tile
{
private:
	static constexpr uint8_t typeMask = 0x0F;
	static constexpr uint8_t typeShift = 4;

	static constexpr uint8_t parameterMask = 0x0F;
	static constexpr uint8_t parameterShift = 0;

private:
	uint8_t value = 0;

public:
	constexpr Tile() = default;

	explicit constexpr Tile(uint8_t value) :
		value { value }
	{
	}

	constexpr Tile(TileType type) :
		value { combine(type, 0) }
	{
	}

	constexpr Tile(TileType type, uint8_t parameter) :
		value { combine(type, parameter) }
	{
	}

	constexpr TileType getType() const
	{
		return getType(this->value);
	}

	constexpr uint8_t getParameter() const
	{
		return getParameter(this->value);
	}

	void setParameter(uint8_t parameter)
	{
		// Clear the old parameter and set the new parameter
		this->value = (clearParameter(this->value) | toParameter(parameter));
	}

	// These have to be functions because the 'Tile' type is not
	// a complete type at this point in the code.

	static constexpr Tile makeSolidTile()
	{
		return Tile(TileType::Solid);
	}

	static constexpr Tile makeEmptyTile()
	{
		return Tile(TileType::Broken, 0);
	}

	static constexpr Tile makeBrokenTile(uint8_t steps)
	{
		return Tile(TileType::Broken, steps);
	}

	static constexpr Tile makeOnButton()
	{
		return Tile(TileType::Button, 1);
	}

	static constexpr Tile makeOffButton()
	{
		return Tile(TileType::Button, 0);
	}

private:
	static constexpr uint8_t combine(TileType type, uint8_t parameter)
	{
		return static_cast<uint8_t>(toType(type) | toParameter(parameter));
	}

	static constexpr uint8_t toType(TileType value)
	{
		return ((static_cast<uint8_t>(value) & typeMask) << typeShift);
	}

	static constexpr TileType getType(uint8_t value)
	{
		return static_cast<TileType>((value >> typeShift) & typeMask);
	}

	static constexpr uint8_t toParameter(uint8_t value)
	{
		return ((value & parameterMask) << parameterShift);
	}

	static constexpr uint8_t getParameter(uint8_t value)
	{
		return ((value >> parameterShift) & parameterMask);
	}

	static constexpr uint8_t clearParameter(uint8_t value)
	{
		return (value & ~(parameterMask << parameterShift));
	}
};

constexpr uint8_t toTileByte(Tile leftTile, Tile rightTile)
{
	return
		(
			((static_cast<uint8_t>(leftTile.getType()) & 0x3) << 0) |
			((static_cast<uint8_t>(leftTile.getParameter()) & 0x3) << 2) |
			((static_cast<uint8_t>(rightTile.getType()) & 0x3) << 4) |
			((static_cast<uint8_t>(rightTile.getParameter()) & 0x3) << 6)
		);
}

constexpr Tile getLeftTile(uint8_t tileByte)
{
	// Construct a tile from the lower nibble
	return Tile(static_cast<TileType>((tileByte >> 0) & 0x03), ((tileByte >> 2) & 0x03));
}

constexpr Tile getRightTile(uint8_t tileByte)
{
	// Construct a tile from the higher nibble
	return Tile(static_cast<TileType>((tileByte >> 4) & 0x03), ((tileByte >> 6) & 0x03));
}