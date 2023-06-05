#pragma once

#include <GLM/glm/glm.hpp>

namespace Dralgeer {
    struct Camera {
        glm::mat4 projection, invProjection;
        glm::mat4 view, invView;
        glm::vec2 pos;
        glm::vec2 projectionSize = {1024, 576}; // 32 * 32, 32 * 18
        float zoom = 1.0f;

        // ! add adjustment functions
    };
}
