/***********************************************************************************************************************
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 **********************************************************************************************************************/
#include <iostream>
#include <string>

#include <boost/program_options.hpp>
#include <fmt/ostream.h>

#include "utils/WindowsConsoleInitialize.hpp"
#include "services/ProgramOptionsService.hpp"

constexpr std::string_view ADOPTIUM_API{ "https://api.adoptium.net" };

namespace po = boost::program_options;

int main(int argc, char** argv)
{
#ifdef WIN_ADDITIONAL_STEPS
    portal::utils::WindowsConsoleInitialize winConsoleInitialize;
#endif // WIN_ADDITIONAL_STEPS

    try
    {
        portal::services::ProgramOptionsService::instance().init(argc, argv);
    }
    catch (const std::exception& e)
    {
        fmt::print(std::cerr, "{}\n", e.what());
        return 1;
    }

    return 0;
}
