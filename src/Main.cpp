/***********************************************************************************************************************
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 **********************************************************************************************************************/
#include <array>
#include <chrono>
#include <string>
#include <thread>

#include <fmt/ostream.h>

#include "utils/WindowsConsoleInitialize.hpp"

int main(int argc, char** argv)
{
#ifdef WIN_ADDITIONAL_STEPS
    portal::utils::WindowsConsoleInitialize winConsoleInitialize;
#endif // WIN_ADDITIONAL_STEPS


#ifdef DEBUG
#ifdef WIN32
    system("pause");
#endif // WIN32
#endif // DEBUG
    return 0;
}
