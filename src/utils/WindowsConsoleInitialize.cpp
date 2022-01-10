/***********************************************************************************************************************
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 **********************************************************************************************************************/
#include <iostream>
#include <stdexcept>

#include <fmt/ostream.h>

#include "WindowsConsoleInitialize.hpp"

#ifdef WIN_ADDITIONAL_STEPS
namespace portal::utils
{
	WindowsConsoleInitialize::WindowsConsoleInitialize()
	{
		if (!IsValidCodePage(65001))
		{
			fmt::print(std::cerr,
				"Code page 65001 (UTF-8) not available, output formatting might not formated as expected");
		}
		else
		{
			SetConsoleCP(65001);
		}
		
		auto stdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		auto stderrHandle = GetStdHandle(STD_ERROR_HANDLE);

		GetConsoleMode(stdoutHandle, &stdoutMode);
		GetConsoleMode(stderrHandle, &stderrMode);

		if (~stdoutMode & ENABLE_VIRTUAL_TERMINAL_PROCESSING)
			SetConsoleMode(stdoutHandle, stdoutMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

		if (~stderrMode & ENABLE_VIRTUAL_TERMINAL_PROCESSING)
			SetConsoleMode(stderrHandle, stderrMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
	}

	WindowsConsoleInitialize::~WindowsConsoleInitialize()
	{
		auto stdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		auto stderrHandle = GetStdHandle(STD_ERROR_HANDLE);
		DWORD consoleMode{ 0 };

		GetConsoleMode(stdoutHandle, &consoleMode);
		if (consoleMode != stdoutMode)
			SetConsoleMode(stdoutHandle, stdoutMode);

		GetConsoleMode(stderrHandle, &consoleMode);
		if (consoleMode != stderrMode)
			SetConsoleMode(stderrHandle, stderrMode);
	}
}
#endif // WIN_ADDITIONAL_STEPS
