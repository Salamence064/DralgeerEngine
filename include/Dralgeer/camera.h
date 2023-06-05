#pragma once

#include <GLM/glm/glm.hpp>
#include <GLM/glm/gtc/matrix_transform.hpp>

namespace Dralgeer {
    struct Camera {
        glm::vec2 pos;

        glm::mat4 proj, invProj;
        glm::mat4 view, invView;
        
        glm::vec2 projSize = {1024, 576}; // 32 * 32, 32 * 18
        float zoom = 1.0f;

        inline void adjustProjection() {
            proj = glm::mat4(1.0f);
            proj = glm::ortho(0.0f, projSize.x, 0.0f, projSize.y, 0.0f, 100.0f);
            invProj = glm::inverse(proj);
        };

        inline void adjustView() {
            view = glm::mat4(1.0f);
            view = glm::lookAt(
                glm::vec3(pos.x, pos.y, 20.0f),  // Set the camera a bit away from the screen's z so we can actually "see" the game
                glm::vec3(pos.x, pos.y, -1.0f),  
                glm::vec3(0.0f, 1.0f, 0.0f)      // Set the y-axis to be "up" because this is a 2D game engine
            );

            invView = glm::inverse(view);
        };
    };
}
