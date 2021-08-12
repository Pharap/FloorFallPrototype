#pragma once

//
// MIT License
// 
// Copyright (c) 2020-2021 Pharap (@Pharap)
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

// Include __FlashStringHelper
#include <WString.h>

//
// FlashStringHelper
//

using FlashStringHelper = const __FlashStringHelper *;

//
// asFlashStringHelper
//

inline FlashStringHelper asFlashStringHelper(const char * flashString) noexcept
{
	return reinterpret_cast<FlashStringHelper>(flashString);
}

inline FlashStringHelper asFlashStringHelper(const unsigned char * flashString) noexcept
{
	return reinterpret_cast<FlashStringHelper>(flashString);
}

inline FlashStringHelper asFlashStringHelper(const signed char * flashString) noexcept
{
	return reinterpret_cast<FlashStringHelper>(flashString);
}

// Include pgm_read_ptr
#include <avr/pgmspace.h>

//
// readFlashString
//

inline FlashStringHelper readFlashStringPointer(const char * const * flashString) noexcept
{
	return static_cast<FlashStringHelper>(pgm_read_ptr(flashString));
}

inline FlashStringHelper readFlashStringPointer(const unsigned char * const * flashString) noexcept
{
	return static_cast<FlashStringHelper>(pgm_read_ptr(flashString));
}

inline FlashStringHelper readFlashStringPointer(const signed char * const * flashString) noexcept
{
	return static_cast<FlashStringHelper>(pgm_read_ptr(flashString));
}
