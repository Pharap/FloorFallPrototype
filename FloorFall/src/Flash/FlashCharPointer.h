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

// For size_t, ptrdiff_t
#include <stddef.h>

// For pgm_read_byte
#include <avr/pgmspace.h>

// Include FlashStringHelper
#include "FlashStringHelper.h"

class FlashCharPointer
{
public:
	// Provide C++ standard library style type aliases.
	using value_type = char;
	using size_type = size_t;
	using pointer = const value_type *;
	using const_pointer = const value_type *;

private:
	const_pointer address;

public:
	// For constructing via a bare pointer.
	constexpr FlashCharPointer(const_pointer value) :
		address { value }
	{
	}

	// For constructing via an array.
	// (As if by array decay.)
	template<size_t size>
	constexpr FlashCharPointer(const value_type (&string)[size]) :
		address { &string[0] }
	{
	}

	// For capturing the result of an F macro.
	explicit FlashCharPointer(FlashStringHelper flashStringHelper) :
		address { reinterpret_cast<const char *>(flashStringHelper) }
	{
	}

	// Dereference operator. (Read only.)
	char operator *() const
	{
		return pgm_read_byte(this->address);
	}

	// Indexing operator. (Read only.)
	// Equivalent to '*(pointer + index)'.
	char operator[](size_type index) const
	{
		return pgm_read_byte(&this->address[index]);
	}

	// Prefix increment operator.
	FlashCharPointer & operator ++()
	{
		++this->address;
		return *this;
	}

	// Postfix increment operator.
	FlashCharPointer operator ++(int)
	{
		const auto result = *this;
		this->operator++();
		return result;
	}

	// Prefix decrement operator.
	FlashCharPointer & operator --()
	{
		--this->address;
		return *this;
	}

	// Postfix decrement operator.
	FlashCharPointer operator --(int)
	{
		const auto result = *this;
		this->operator--();
		return result;
	}

	// Explicit conversion to const_pointer.
	// Explicit because the knowledge that this is a
	// pointer stored in flash is being discarded.
	constexpr explicit operator const_pointer() const
	{
		return this->address;
	}

	// Implicit conversion to FlashStringHelper.
	// Cannot be constexpr due to reinterpret_cast.
	operator FlashStringHelper() const
	{
		return reinterpret_cast<FlashStringHelper>(this->address);
	}
};

//
// Comparison Operators
//

constexpr bool operator ==(FlashCharPointer left, FlashCharPointer right)
{
	return (static_cast<const char *>(left) == static_cast<const char *>(right));
}

constexpr bool operator !=(FlashCharPointer left, FlashCharPointer right)
{
	return (static_cast<const char *>(left) != static_cast<const char *>(right));
}

constexpr bool operator <(FlashCharPointer left, FlashCharPointer right)
{
	return (static_cast<const char *>(left) < static_cast<const char *>(right));
}

constexpr bool operator <=(FlashCharPointer left, FlashCharPointer right)
{
	return (static_cast<const char *>(left) <= static_cast<const char *>(right));
}

constexpr bool operator >(FlashCharPointer left, FlashCharPointer right)
{
	return (static_cast<const char *>(left) > static_cast<const char *>(right));
}

constexpr bool operator >=(FlashCharPointer left, FlashCharPointer right)
{
	return (static_cast<const char *>(left) >= static_cast<const char *>(right));
}

//
// Arithmetic Operators
//

template<typename Right>
constexpr FlashCharPointer operator +(FlashCharPointer left, Right right)
{
	return FlashCharPointer(static_cast<const char *>(left) + right);
}

template<typename Left>
constexpr FlashCharPointer operator +(Left left, FlashCharPointer right)
{
	return FlashCharPointer(left + static_cast<const char *>(right));
}

template<typename Right>
constexpr FlashCharPointer operator -(FlashCharPointer left, Right right)
{
	return FlashCharPointer(static_cast<const char *>(left) - right);
}

constexpr auto operator -(FlashCharPointer left, FlashCharPointer right) ->
	decltype(static_cast<const char *>(left) - static_cast<const char *>(right))
{
	return (static_cast<const char *>(left) - static_cast<const char *>(right));
}