/***********************************************************************************************************************
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 **********************************************************************************************************************/
/**
 * This file is a patch file for unsupported compiler to support certain C++ 20 features.
 */
#pragma once
#include <algorithm>

#ifdef __clang__
namespace std::ranges {
auto any_of(const auto &range, const auto &predicate)
{
    return std::any_of(range.begin(), range.end(), predicate);
}
}
#endif
