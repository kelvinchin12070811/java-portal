#pragma once
#ifdef WIN32
#define WIN_ADDITIONAL_STEPS

#include <bitset>

#include <Windows.h>

/**
 * @brief Additional steps to initialize console on Windows
 */
namespace portal::utils
{
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

	private:
		DWORD stderrMode;
		DWORD stdoutMode;
	};
}

#endif // WIN32
