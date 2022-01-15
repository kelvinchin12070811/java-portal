/***********************************************************************************************************************
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 **********************************************************************************************************************/
#include <iostream>

#include <fmt/ostream.h>

#include "utils/WindowsConsoleInitialize.hpp"
#include "services/ProgramOptionsService.hpp"


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
