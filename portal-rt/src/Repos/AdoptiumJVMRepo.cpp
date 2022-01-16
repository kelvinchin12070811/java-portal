/***********************************************************************************************************************
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 **********************************************************************************************************************/
#include <fmt/format.h>
#include <restclient-cpp/restclient.h>
#include <fmt/ostream.h>

#include <nlohmann/json.hpp>

#include "Repos/AdoptiumJVMRepo.hpp"

namespace portal::repos {
std::vector<std::string> AdoptiumJVMRepo::getAvailableJVMs()
{
    auto res = RestClient::get(
            fmt::format("{}/v3/info/release_versions?heap_size=normal&image_type=jdk&page=0"
                        "&page_size=10&project=jdk&release_type=ga&sort_method=DEFAULT&sort_order="
                        "DESC&vendor=eclipse",
                        adoptiumAPIDomain));

    if (res.code != 200) {
        throw std::runtime_error { fmt::format("Error, can't fetch resource, error code {}",
                                               res.code) };
    }

    auto document = nlohmann::json::parse(res.body);
    std::vector<std::string> versions;
    versions.reserve(document["versions"].size());

    for (const auto &version : document["versions"])
        versions.push_back(version["openjdk_version"]);
    
    return versions;
}
}