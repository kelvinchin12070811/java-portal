/***********************************************************************************************************************
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 **********************************************************************************************************************/
#include <iostream>

#include <fmt/format.h>
#include <fmt/ostream.h>

#include "ProgramOptionsService.hpp"
#include "src/Constants/Versions.hpp"

namespace portal::services
{
    ProgramOptionsService& ProgramOptionsService::instance()
    {
        static ProgramOptionsService _instance;
        return _instance;
    }

    void ProgramOptionsService::init(int argc, char** argv)
    {
        using namespace boost::program_options;

        commands = decltype(commands){
            {
                "help", {
                    "help",
                    "Print help message",
                    [this]() { this->printHelpMessage(); }
                }
            }
        };

        optionsDescription.add_options()
            ("hello-world", "Print hello world message to the screen")
            ("level", value<int>(), "Level of an integer where use to testing only")
            ("command", value<std::string>()->required(), "Commands");

        positionalOptionsDescription
            .add("command", 1);

        store(
            command_line_parser{ argc, argv }
            .options(optionsDescription)
            .positional(positionalOptionsDescription)
            .allow_unregistered()
            .run(),
            variableMap
        );
        notify(variableMap);
        distributeCommandWorkers();
    }
    
    void ProgramOptionsService::distributeCommandWorkers()
    {
        if (variableMap.count("hello-world") > 0) fmt::print("Hello World!\n");
        
        if (variableMap.count("level") > 0) fmt::print("Level is setted to {}\n", variableMap["level"].as<int>());

        if (variableMap.count("command") > 0)
        {
            const auto& command = variableMap["command"].as<std::string>();

            try
            {
                commands.at(command).invoker();
            }
            catch (const std::exception&)
            {
                throw std::runtime_error{ fmt::format("Invalid command \"{}\"", command) };
            }
        }
    }
    
    void ProgramOptionsService::printHelpMessage()
    {
        fmt::print("{}\n{}\n{}\n{}\n{} v{}\n\n", R"( ____            _        _)", R"(|  _ \ ___  _ __| |_ __ _| |)",
            R"(| |_) / _ \| '__| __/ _` | |)", R"(|  __| (_) | |  | || (_| | |)", R"(|_|   \___/|_|   \__\__,_|_|)",
            constants::VERSION);
        fmt::print("Options:\n");
    }
}