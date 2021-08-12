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

#include "FlashCharPointer.h"
#include "FlashStringHelper.h"

class FlashString
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
	const_pointer string;

public:
	// For constructing via a bare pointer.
	constexpr explicit FlashString(const_pointer string) :
		string { string }
	{
	}

	// For constructing via an array.
	template<size_t size>
	constexpr explicit FlashString(const value_type (&string)[size]) :
		string { &string[0] }
	{
	}

	// For capturing the result of an F macro.
	FlashString(FlashStringHelper flashStringHelper) :
		string { reinterpret_cast<const char *>(flashStringHelper) }
	{
	}

	// Match C++ standard library convention.
	size_type size() const
	{
		return strlen_P(this->string);
	}

	constexpr const_iterator begin() const
	{
		return const_iterator(&this->string[0]);
	}

	constexpr const_iterator cbegin() const
	{
		return const_iterator(&this->string[0]);
	}

	const_iterator end() const
	{
		return const_iterator(&this->string[this->size()]);
	}

	const_iterator cend() const
	{
		return const_iterator(&this->string[this->size()]);
	}

	char operator[](size_type index) const
	{
		return pgm_read_byte(&this->string[index]);
	}

	// Explicit conversion to raw pointer.
	// Explicit because the knowledge that this is a
	// pointer stored in flash is being discarded.
	constexpr explicit operator const_pointer() const
	{
		return this->string;
	}

	// Explicit conversion to FlashCharPointer.
	// Explicit because the knowledge that this
	// represents a string is being discarded.
	constexpr explicit operator FlashCharPointer() const
	{
		return FlashCharPointer(this->string);
	}

	// Implicit conversion to FlashStringHelper.
	// Cannot be constexpr due to reinterpret_cast.
	operator FlashStringHelper() const
	{
		return reinterpret_cast<FlashStringHelper>(this->string);
	}
};