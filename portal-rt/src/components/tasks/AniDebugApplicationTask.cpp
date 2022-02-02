/***********************************************************************************************************************
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 **********************************************************************************************************************/
#include "components/tasks/AniDebugApplicationTask.hpp"

#include <memory>

#include "components/animations/SimpleSpinningAnimationComponent.hpp"

namespace portal::components::tasks {
void AniDebugApplicationTask::run()
{
    using namespace std::chrono_literals;

    auto controller =
            std::make_unique<animations::SimpleSpinningAnimationComponent>("Debugging...");
    controller->start();
    std::this_thread::sleep_for(10h);
}
}