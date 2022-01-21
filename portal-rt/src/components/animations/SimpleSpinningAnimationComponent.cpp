/***********************************************************************************************************************
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 **********************************************************************************************************************/
#include <chrono>
#include <iostream>

#include <fmt/color.h>
#include <fmt/ostream.h>

#include "components/animations/SimpleSpinningAnimationComponent.hpp"

namespace portal::components::animations {
SimpleSpinningAnimationComponent::SimpleSpinningAnimationComponent(std::string message)
    : message { std::move(message) }
{
}

void SimpleSpinningAnimationComponent::start()
{
    if (rendering) return;
    if (!rendering) rendering = true;

    renderWorker = std::thread { [this]() { render(); } };
}

void SimpleSpinningAnimationComponent::stop()
{
    if (rendering) rendering = false;
    if (renderWorker.joinable()) renderWorker.join();
}

SimpleSpinningAnimationComponent::~SimpleSpinningAnimationComponent()
{
    stop();
}

void SimpleSpinningAnimationComponent::render()
{
    fmt::print("\x1b[s");

    while (rendering) {
        using namespace std::chrono;

        fmt::print("\x1b[u");
        fmt::print(fmt::fg(fmt::color::gold), "{} {}", animationFrames[frameIndex++], message);
        std::cout.flush();
        if (frameIndex >= animationFrames.size()) frameIndex = 0;
        std::this_thread::sleep_for(duration_cast<nanoseconds>(1s) / 10);
    }

    fmt::print("\x1b[u\x1b[J");
}
}