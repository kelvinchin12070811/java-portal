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

int main(int argc, char** argv)
{
    const std::array<std::string, 4> loadingIconState = { "[█  ]", "[ █ ]", "[  █]", "[ █ ]" };
    int loopState { 0 };

    while (true)
    {
        using namespace std::chrono_literals;
        fmt::print("{}\r", loadingIconState[loopState]);
        std::this_thread::sleep_for(100ms);
        loopState++;
        if (loopState >= loadingIconState.size()) loopState = 0;
    }

    return 0;
}
