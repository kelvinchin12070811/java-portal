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
    std::array<char, 8> loadingIcon { { '|', '/', '-', '\\', '|', '/', '-', '\\' } };
    int index { 0 };
    int percent{ 0 };

    fmt::print("hello world\n\x1b[s");
    while (true)
    {
        using namespace std::chrono_literals;
        fmt::print("\x1b[u\x1b[2K{} - loading: {}%", loadingIcon[index], percent++);
        std::this_thread::sleep_for(100ms);
        index++;
        if (index >= loadingIcon.size()) index = 0;
        if (percent > 100) percent = 0;
    }

#ifdef DEBUG
#ifdef WIN32
    system("pause");
#endif // WIN32
#endif // DEBUG
    return 0;
}
