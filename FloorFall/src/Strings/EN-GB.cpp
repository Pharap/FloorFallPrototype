#include "EN-GB.h"

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

// Unfortunately it's necessary to 'define' these here
// despite this not actually providing the compiler with
// any information that it didn't have before.

// It's due to an unfortunate side effect of the
// header-source split model that C++ inherited from C.
// C++17 fixed this annoying discrepency by introducing 'inline' variables.
// But Arduino-land only supports C++11, not C++17.

constexpr char LanguageStrings<Language::EN_GB>::pressA[];
constexpr char LanguageStrings<Language::EN_GB>::level[];