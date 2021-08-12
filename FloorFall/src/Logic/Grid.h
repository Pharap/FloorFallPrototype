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

// For size_t
#include <stddef.h>

// Predeclare in the hopes that editor tools will use the names declared here.
template<typename Type, size_t width, size_t height>
class Grid;

// The benefit of using 'Grid' over a normal 2D array
// is that it's much easier to get the dimensions of a 'Grid'.
// Getting the dimensions of a 2D array requires some template voodoo
// that would scare most people who aren't used to dealing with templates.
// Such voodoo is provided by the C++ standard library,
// but we don't have those luxuries here in Arduino-land.
template<typename Type, size_t widthValue, size_t heightValue>
class Grid
{
public:
	// Declare names that follow the C++ standard library conventions.
	using value_type = Type;
	using reference = value_type &;
	using const_reference = const value_type &;
	using pointer = value_type *;
	using const_pointer = const value_type *;
	using size_type = size_t;

public:
	static constexpr size_type width = widthValue;
	static constexpr size_type height = heightValue;
	static constexpr size_type cellCount = (width * height);

private:
	value_type cells[height][width] {};

public:
	// 'getWidth', 'getHeight' and 'getCellCount'
	// aren't strictly necessary,
	// this is just me thinking ahead again.
	constexpr size_type getWidth() const
	{
		return width;
	}

	constexpr size_type getHeight() const
	{
		return height;
	}

	constexpr size_type getCellCount() const
	{
		return cellCount;
	}

	// Note:
	// Strictly speaking it would be possible to override the [] operator
	// in such a way that it could be doubled up (i.e. grid[x][y] or grid[y][x])
	// but that's probably going to lead to more confusion than just
	// having a 'getCell' function that accepts two arguments.

	// Returns a mutable reference.
	reference getCell(size_t x, size_t y)
	{
		return this->cells[y][x];
	}

	// Returns a read-only reference.
	constexpr const_reference getCell(size_t x, size_t y) const
	{
		return this->cells[y][x];
	}

	constexpr size_type getLeftEdge() const
	{
		return 0;
	}

	constexpr size_type getTopEdge() const
	{
		return 0;
	}

	constexpr size_type getRightEdge() const
	{
		return (this->getWidth() - 1);
	}

	constexpr size_type getBottomEdge() const
	{
		return (this->getHeight() - 1);
	}
};