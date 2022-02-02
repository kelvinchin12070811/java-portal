/***********************************************************************************************************************
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 **********************************************************************************************************************/
#pragma once
#include <functional>
#include <map>
#include <memory>
#include <string_view>
#include <string>

#include "components/tasks/IApplicationTask.hpp"

namespace portal::components::tasks {
class ApplicationTaskFactory
{
public:
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
         * @brief Creator function that create the corresponded IApplicationTask object.
         */
        std::function<std::unique_ptr<IApplicationTask>()> creator;
    };

    static ApplicationTaskFactory &instance();

    std::unique_ptr<IApplicationTask> getApplicationTaskFromName(std::string_view name);

    ApplicationTaskFactory(const ApplicationTaskFactory &) = delete;
    ApplicationTaskFactory(ApplicationTaskFactory &&) = delete;
    ApplicationTaskFactory &operator=(const ApplicationTaskFactory &) = delete;
    ApplicationTaskFactory &operator=(ApplicationTaskFactory &&) = delete;

    ~ApplicationTaskFactory() = default;

private:
    ApplicationTaskFactory();

    std::map<std::string_view, CommandDescription> taskList;
};
}