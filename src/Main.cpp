/***********************************************************************************************************************
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 **********************************************************************************************************************/
#include <string>

#include <boost/program_options.hpp>
#include <fmt/ostream.h>

#include "utils/WindowsConsoleInitialize.hpp"

constexpr std::string_view ADOPTIUM_API{ "https://api.adoptium.net" };

namespace po = boost::program_options;

int main(int argc, char** argv)
{
#ifdef WIN_ADDITIONAL_STEPS
    portal::utils::WindowsConsoleInitialize winConsoleInitialize;
#endif // WIN_ADDITIONAL_STEPS

    po::options_description desc{ "Switches" };
    po::positional_options_description positionalDesc;

    desc.add_options()
        ("test", po::value<int>(), "Test flag")
        ("command", po::value<std::string>(), "Command to execute");

    positionalDesc.add("command", 1);

    po::variables_map vm;
    po::store(po::command_line_parser{ argc, argv }
        .options(desc)
        .positional(positionalDesc)
        .allow_unregistered()
        .run(), vm);

    po::notify(vm);

    if (vm.count("command") > 0)
    {
        auto command = vm["command"].as<std::string>();
        if (command == "help")
        {
            fmt::print("{}\n", desc);
            return 1;
        }
    }

    return 0;
}
