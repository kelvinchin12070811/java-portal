/***********************************************************************************************************************
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 **********************************************************************************************************************/
#pragma once
#include <string_view>

#include "Repos/IJVMRepo.hpp"

namespace portal::repos {
class AdoptiumJVMRepo : public IJVMRepo
{
public:
    static constexpr std::string_view adoptiumAPIDomain { "https://api.adoptium.net" };

public:
    std::vector<std::string> getAvailableJVMs() override;
};
}