/***********************************************************************************************************************
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 **********************************************************************************************************************/
#include <fmt/format.h>
#include <restclient-cpp/restclient.h>
#include <fmt/ostream.h>

#include "Repos/AdoptiumJVMRepo.hpp"

namespace portal::repos {
std::vector<std::string> AdoptiumJVMRepo::getAvailableJVMs()
{
    auto res = RestClient::get(fmt::format("{}/v3/info/release_versions", adoptiumAPIDomain));

    if (res.code != 200) {
        throw std::runtime_error { fmt::format("Error, can't fetch resource, error code {}",
                                               res.code) };
    }

    fmt::print("{}\n", res.body);
    
    return std::vector<std::string>();
}
}