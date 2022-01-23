/***********************************************************************************************************************
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 **********************************************************************************************************************/
#include "components/tasks/JVMVersionListApplicationTask.hpp"

#include <memory>

#include <fmt/color.h>
#include <fmt/ostream.h>

#include "components/animations/SimpleSpinningAnimationComponent.hpp"
#include "repos/AdoptiumJVMRepo.hpp"

namespace portal::tasks {
void JVMVersionListApplicationTask::run()
{
    using namespace portal::components::animations;

    std::unique_ptr<repos::IJVMRepo> jvmRepo = std::make_unique<repos::AdoptiumJVMRepo>();
    std::unique_ptr<IAnimationComponent> animator =
            std::make_unique<SimpleSpinningAnimationComponent>("Fetching...");

    animator->start();

    try {
        auto result = jvmRepo->getAvailableJVMs();
        animator->stop();

        fmt::print(fmt::emphasis::bold, "Available versions:\n\n");
        fmt::print(" * {}\n", fmt::join(result, "\n * "));
        fmt::print("\nUse ");
        fmt::print(fmt::emphasis::bold | fmt::emphasis::bold, "portal add <version>");
        fmt::print(" to install a JVM\n");
    } catch (const std::exception &e) {
        throw std::runtime_error { e.what() };
    }
}
}