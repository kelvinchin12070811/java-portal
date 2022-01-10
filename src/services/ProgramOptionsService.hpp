/***********************************************************************************************************************
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 **********************************************************************************************************************/
#pragma once
#include <tuple>
#include <vector>

#include <boost/program_options.hpp>

namespace portal::services
{
    /**
     * @brief Singleton object that process the arguments that passed into portal.
     */
    class ProgramOptionsService
    {
    public:
        /**
         * @brief Get the singleton instance of the ProgramOptionsServices.
         * @return Singleton instance of the ProgramOptionsServices.
         */
        static ProgramOptionsService& instance();

        /**
         * @brief Initialize the service.
         * @param argc argc value that passed from the main function.
         * @param argv argv value that passed from the main function.
         */
        void init(int argc, char** argv);

        ProgramOptionsService(const ProgramOptionsService&) = delete;
        ProgramOptionsService(ProgramOptionsService&&) = delete;
        
        ProgramOptionsService& operator=(const ProgramOptionsService&) = delete;
        ProgramOptionsService& operator=(ProgramOptionsService&&) = delete;

    private:
        /**
         * @brief Description that describe all the available switches which portal accepted.
         */
        boost::program_options::options_description optionsDescription{ "Switches available" };
        /**
         * @brief Description that describe all the available commands or positional args which portal accepted.
         * 
         * @sa portal::services::ProgramOptionsService::positionalOptionsList
         */
        boost::program_options::positional_options_description positionalOptionsDescription;
        /**
         * @brief map of variable that parsed from supplied argument list.
         */
        boost::program_options::variables_map variableMap;

    private:
        /**
         * @brief Map and distribute different command to different functions.
         */
        void distributeCommandWorkers();
        /**
         * @brief Print help message to the screen.
         */
        void printHelpMessage();

        ProgramOptionsService() = default;
        ~ProgramOptionsService() = default;
    };
}