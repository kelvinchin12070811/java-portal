/***********************************************************************************************************************
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 **********************************************************************************************************************/
#include "components/tasks/ApplicationTaskFactory.hpp"

#include <boost/assert.hpp>
#include <fmt/format.h>

#include "components/tasks/JVMVersionListApplicationTask.hpp"

namespace portal::tasks {
ApplicationTaskFactory &ApplicationTaskFactory::instance()
{
    static ApplicationTaskFactory instance_;
    return instance_;
}

std::unique_ptr<IApplicationTask>
ApplicationTaskFactory::getApplicationTaskFromName(std::string_view name)
{
    try {
        auto task = taskList.at(name).creator();
        BOOST_ASSERT_MSG(task, "Error, called message did not implemented or registred!");
        return task;
    } catch (const std::out_of_range &e) {
        throw std::out_of_range { fmt::format("Cannot find command \"{}\"", name) };
    }
}

ApplicationTaskFactory::ApplicationTaskFactory()
{
    taskList = decltype(taskList) {
        // clang-format off
        {
            "help",
            {
                "Print help message",
                [this]() { return nullptr; }
            }
        },
        {
            "list",
            {
                "List all installed JVMs",
                []() { return nullptr; }
            }
        },
        {
            "installable",
            {
                "List available versions of JVM online",
                []() { return std::make_unique<JVMVersionListApplicationTask>(); }
            }
        },
        {
            "ani-debug",
            {
                "use to debug animation",
                []() { return nullptr; }
            }
        }
        // clang-format on
    };
}
}