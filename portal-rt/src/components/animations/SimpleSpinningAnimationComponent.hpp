/***********************************************************************************************************************
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 **********************************************************************************************************************/
#pragma once
#include <array>
#include <atomic>
#include <string>
#include <string_view>
#include <thread>

#include "components/animations/IAnimationComponent.hpp"

namespace portal::components::animations {
/**
 * @brief Render the simple spinning icon that indicate a task is running in background.
 */
class SimpleSpinningAnimationComponent : public IAnimationComponent
{
private:
    constexpr static std::array<std::string_view, 7> animationFrames { { "▖", "▌", "▛", "█", "▜",
                                                                         "▐", "▗" } };

public:
    SimpleSpinningAnimationComponent(std::string message);
    void start() override;
    void stop() override;

    SimpleSpinningAnimationComponent(const SimpleSpinningAnimationComponent &) = default;
    SimpleSpinningAnimationComponent(SimpleSpinningAnimationComponent &&) = default;
    SimpleSpinningAnimationComponent &operator=(const SimpleSpinningAnimationComponent &) = default;
    SimpleSpinningAnimationComponent &operator=(SimpleSpinningAnimationComponent &&) = default;
    ~SimpleSpinningAnimationComponent();

private:
    /**
     * @brief Determine if the component should be rendered.
     */
    std::atomic_bool rendering { false };
    /**
     * @brief Determine
     */
    std::string message;
    /**
     * @brief Index of current frame.
     */
    int frameIndex { 0 };
    /**
     * @brief Worker thread that renderring the animation on to console.
     */
    std::thread renderWorker;

    /**
     * @brief Worker function that render animation.
     */
    void render();
};
}