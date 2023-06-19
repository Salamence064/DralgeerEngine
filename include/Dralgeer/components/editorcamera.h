#pragma once

#include <GLFW/glfw3.h>
#include <Zeta2D/zmath2D.h>
#include "component.h"
#include "../camera.h"
#include "../listeners.h"

// Editor camera constants
#define EDITOR_DRAG_SENSITIVITY 30.0f
#define EDITOR_SCROLL_SENSITIVITY 0.1f

namespace Dralgeer {
    class EditorCamera : public Component {
        private:
            float dragDebounce = 0.032f;
            float lerpTime = 0.0f;
            bool reset = 0;

            Camera camera;
            glm::vec2 clickOrigin;

        public:
            inline void update(float dt) override {
                // todo check if the ImGui layer in the window wants to be updated (will have to add the thing to the window first though)

                if (MouseListener::mButtonPressed[GLFW_MOUSE_BUTTON_LEFT] && dragDebounce > 0.0f) {
                    clickOrigin = {MouseListener::mWorldX, MouseListener::mWorldY};
                    dragDebounce -= dt;
                    return;
                }

                if (MouseListener::mButtonPressed[GLFW_MOUSE_BUTTON_LEFT]) {
                    glm::vec2 mousePos(MouseListener::mWorldX, MouseListener::mWorldY);
                    glm::vec2 delta = mousePos - clickOrigin;
                    camera.pos -= delta * (dt * EDITOR_DRAG_SENSITIVITY);
                    clickOrigin = glm::mix<glm::vec2, float>(clickOrigin, mousePos, dt);

                } else if (dragDebounce <= 0.0f) {
                    dragDebounce = 0.032f;
                }

                if (!ZMath::compare(MouseListener::mScrollY, 0.0f)) {
                    float addValue = powf(std::fabs(MouseListener::mScrollY * EDITOR_SCROLL_SENSITIVITY), 1/camera.zoom);
                    camera.zoom += addValue * -SIGNOF(MouseListener::mScrollY);
                }

                if (reset) {
                    camera.pos = glm::mix<glm::vec2, float>(camera.pos, glm::vec2(0, 0), lerpTime);
                    camera.zoom += ((1.0f - camera.zoom) * lerpTime);
                    lerpTime += 0.1f * dt; // ! maybe move this to the front of all of this if I experience issues

                    if (std::fabs(camera.pos.x) <= 5.0f && std::fabs(camera.pos.y) <= 5.0f) {
                        camera.pos = {0, 0};
                        camera.zoom = 1.0f;
                        lerpTime = 0.0f;
                        reset = 0;
                    }

                } else if (KeyListener::keyPressed[GLFW_KEY_TAB]) {
                    reset = 1;
                }
            };
    };
}
