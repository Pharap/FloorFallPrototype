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

// For pgm_read_byte
#include <avr/pgmspace.h>

#include "FlashString.h"
#include "FlashCharPointer.h"
#include "FlashStringHelper.h"

// This exists solely as a simple way of caching the
// size of a flash string after computing it.
class KnownSizeFlashString
{
public:
	// Provide C++ standard library style type aliases.
	using value_type = char;
	using size_type = size_t;
	using pointer = const value_type *;
	using const_pointer = const value_type *;
	using iterator = FlashCharPointer;
	using const_iterator = FlashCharPointer;

private:
	pointer string;
	size_type stringSize;

public:
	// For constructing via an array.
	template<size_t size>
	constexpr explicit KnownSizeFlashString(const value_type (&string)[size]) :
		string { &string[0] },
		stringSize { size }
	{
	}

	// For constructing via a bare pointer and size.
	constexpr explicit KnownSizeFlashString(const_pointer string, size_type size) :
		string { string },
		stringSize { size }
	{
	}

	// For constructing from a FlashString.
	KnownSizeFlashString(FlashString flashString) :
		string { static_cast<const char *>(flashString) },
		stringSize { strlen_P(static_cast<const char *>(flashString)) }
	{
	}

	// For capturing the result of an F macro.
	KnownSizeFlashString(FlashStringHelper flashStringHelper) :
		string { reinterpret_cast<const char *>(flashStringHelper) },
		stringSize { strlen_P(reinterpret_cast<const char *>(flashStringHelper)) }
	{
	}

	// Match C++ standard library convention.
	constexpr size_type size() const
	{
		return this->stringSize;
	}

	constexpr const_iterator begin() const
	{
		return const_iterator(&this->string[0]);
	}

	constexpr const_iterator cbegin() const
	{
		return const_iterator(&this->string[0]);
	}

	constexpr const_iterator end() const
	{
		return const_iterator(&this->string[this->size()]);
	}

	constexpr const_iterator cend() const
	{
		return const_iterator(&this->string[this->size()]);
	}

	// Implicit conversion to FlashStringHelper.
	// Although information is being discarded, this is still Implicit
	// because it should really only be called when it's being passed to
	// an overload of 'print' on an object inheriting 'Print'.
	operator FlashStringHelper() const
	{
		return reinterpret_cast<FlashStringHelper>(this->string);
	}

	// Explicit conversion to FlashStringHelper.
	// This is explicit because expensive information is being discarded.
	explicit operator FlashString() const
	{
		return FlashString(this->string);
	}

	// Read from the string via indexing.
	char operator[](size_type index) const
	{
		return pgm_read_byte(&string[index]);
	}
};