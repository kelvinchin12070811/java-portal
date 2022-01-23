/***********************************************************************************************************************
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 **********************************************************************************************************************/
#pragma once
#ifdef WIN32
// clang-format off
#define WIN_ADDITIONAL_STEPS

#include <bitset>

#include <Windows.h>
// clang-format on

/**
 * @brief Additional steps to initialize console on Windows, this object is unmoveable and
 * uncopyable.
 */
namespace portal::utils {
class WindowsConsoleInitialize
{
public:
    /**
     * @brief Construct initialize object to initialize required action on Windows.
     */
    WindowsConsoleInitialize();
    /**
     * @brief Clean up Windows console for initialized objects.
     */
    ~WindowsConsoleInitialize();

    WindowsConsoleInitialize(const WindowsConsoleInitialize &) = delete;
    WindowsConsoleInitialize(WindowsConsoleInitialize &&) = delete;

    WindowsConsoleInitialize &operator=(const WindowsConsoleInitialize &) = delete;
    WindowsConsoleInitialize &operator=(WindowsConsoleInitialize &&) = delete;

private:
    DWORD stderrMode;
    DWORD stdoutMode;
};
}

#endif // WIN32
