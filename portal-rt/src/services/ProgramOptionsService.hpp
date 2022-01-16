/***********************************************************************************************************************
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 **********************************************************************************************************************/
#pragma once
#include <atomic>
#include <functional>
#include <map>
#include <tuple>
#include <vector>

#include <boost/program_options.hpp>

namespace portal::services {
/**
 * @brief Singleton object that process the arguments that passed into portal.
 */
class ProgramOptionsService
{
private:
    /**
     * @brief Determine the descriptions of the command for help message or documentations.
     */
    struct CommandDescription
    {
        /**
         * @brief Description of the command.
         */
        std::string description;
        /**
         * @brief Invoker function that invoke the corresponded worker function.
         */
        std::function<void()> invoker;
    };

public:
    /**
     * @brief Get the singleton instance of the ProgramOptionsServices.
     * @return Singleton instance of the ProgramOptionsServices.
     */
    static ProgramOptionsService &instance();

    /**
     * @brief Initialize the service.
     * @param argc argc value that passed from the main function.
     * @param argv argv value that passed from the main function.
     */
    void init(int argc, char **argv);

    ProgramOptionsService(const ProgramOptionsService &) = delete;
    ProgramOptionsService(ProgramOptionsService &&) = delete;

    ProgramOptionsService &operator=(const ProgramOptionsService &) = delete;
    ProgramOptionsService &operator=(ProgramOptionsService &&) = delete;

private:
    /**
     * @brief Description that describe all the available switches which portal accepted.
     */
    boost::program_options::options_description optionsDescription { "Switches available" };
    /**
     * @brief Description that describe all the available commands or positional args which portal
     * accepted.
     */
    boost::program_options::positional_options_description positionalOptionsDescription;
    /**
     * @brief map of variable that parsed from supplied argument list.
     */
    boost::program_options::variables_map variableMap;
    /**
     * @brief list of options/commands that will be mapped to it's corresponded caller function.
     */
    std::map<std::string, CommandDescription> commands;
    /**
     * @brief Determine if the application is in loading state and hence render loading animation.
     */
    std::atomic_bool isLoading { false };

private:
    /**
     * @brief Map and distribute different command to different functions.
     */
    void distributeCommandWorkers();
    /**
     * @brief Print help message to the screen.
     */
    void printHelpMessage();
    /**
     * @brief Fetch version of JVMs available online.
     */
    void fetchRemoteJVMVersion();
    /**
     * @brief Render the loading indication when a task is working in background.
     * @param status Status message that describe the current working task.
     *
     * @info This function should run asynchronously as a detached thread.
     */
    void renderLoadingIndicator(std::string_view status);
    /**
     * @brief Stop rendering the loading indicator as a task has done.
     */
    void stopRenderLoadingIndicator();

    ProgramOptionsService() = default;
    ~ProgramOptionsService() = default;
};
}