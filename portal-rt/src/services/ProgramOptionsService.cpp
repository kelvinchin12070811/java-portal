/***********************************************************************************************************************
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 **********************************************************************************************************************/
#include <algorithm>
#include <array>
#include <iostream>

#include <fmt/format.h>
#include <fmt/ostream.h>

#include "ProgramOptionsService.hpp"
#include "Constants/Versions.hpp"

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
                    "Print help message",
                    [this]() { this->printHelpMessage(); }
                }
            },
            {
                "list", {
                    "List all installed JVMs",
                    []() {}
                }
            }
        };

        optionsDescription.add_options()
            ("version", "Print the version number")
            ("hello-world", "Print hello world message to the screen")
            ("level", value<int>(), "Level of an integer where use to testing only")
            ("command", value<std::string>(), "Commands");

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
        if (variableMap.count("version"))
        {
            fmt::print("{}", constants::VERSION);
            return;
        }

        if (variableMap.count("hello-world")) fmt::print("Hello World!\n");
        
        if (variableMap.count("level")) fmt::print("Level is set to {}\n", variableMap["level"].as<int>());

        if (variableMap.count("command"))
        {
            const auto& command = variableMap["command"].as<std::string>();

            try
            {
                commands.at(command).invoker();
            }
            catch (const std::exception&)
            {
                throw std::runtime_error{
                    fmt::format("Unknown command \"{}\", use \"portal help\" to get usage info", command)
                };
            }
        }
        else
        {
            throw std::runtime_error{ fmt::format("No command to run, use \"portal help\" to get usage info") };
        }
    }
    
    void ProgramOptionsService::printHelpMessage()
    {
        constexpr int columnWidth{ 20 };
        constexpr std::array<std::string_view, 1> ignoredOptions{ {"--command"} };

        fmt::print("{}\n{}\n{}\n{}\n{}\n{:>35}\n{:>35}\n\n", R"( ____            _        _)", R"(|  _ \ ___  _ __| |_ __ _| |)",
            R"(| |_) / _ \| '__| __/ _` | |)", R"(|  __| (_) | |  | || (_| | |)", R"(|_|   \___/|_|   \__\__,_|_|)",
            "A version manager for Java", fmt::format("v{}", constants::VERSION));

        fmt::print("Usage: portal [command] <option>...\n\n");
        fmt::print("Commands:\n");

        for (const auto& command : commands)
        {
            const auto& [name, description] = command;
            fmt::print("    {1:<{0}} := {2:<30}\n", columnWidth, name, description.description);
        }

        fmt::print("\nOptions:\n");

        for (const auto& option : optionsDescription.options())
        {
            std::string optionName{ option->format_name() };

            if (std::ranges::any_of(ignoredOptions, [&](const auto& command) { return command == optionName; }))
                continue;

            std::string optionParams{ option->format_parameter() };

            if (!optionParams.empty())
                optionName = fmt::format("{} [{}]", optionName, optionParams);

            fmt::print("    {1:<{0}} := {2}\n", columnWidth, optionName, option->description());
        }

        fmt::print("\n");
    }
}