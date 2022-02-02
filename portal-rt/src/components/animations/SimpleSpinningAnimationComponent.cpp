/***********************************************************************************************************************
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 **********************************************************************************************************************/
#include "SimpleSpinningAnimationComponent.hpp"

#include <chrono>
#include <iostream>

#include <fmt/color.h>
#include <fmt/ostream.h>

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
    while (rendering) {
        using namespace std::chrono;
        fmt::print(fmt::fg(fmt::terminal_color::bright_yellow), "\r{} {}", animationFrames[frameIndex++], message);
        std::cout.flush();
        if (frameIndex >= animationFrames.size()) frameIndex = 0;
        std::this_thread::sleep_for(duration_cast<nanoseconds>(1s) / 10);
    }

    fmt::print("\r\x1b[0J");
}
}