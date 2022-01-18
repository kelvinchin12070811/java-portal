/***********************************************************************************************************************
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 **********************************************************************************************************************/

namespace portal::components::animations {
/**
 * @brief Animation Component interface that handle the abstraction of animation components.
 */
struct IAnimationComponent
{
    /**
     * @brief Start the render of animation.
     */
    virtual void start() = 0;
    /**
     * @brief Stop the render of animation.
     */
    virtual void stop() = 0;
    virtual ~IAnimationComponent() = default;
};
}