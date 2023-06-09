// todo include Sprite, SpriteRenderer, and SpriteSheet in here

#pragma once

#include "../render/texture.h"
#include "../gameobject.h"
#include "component.h"

// ! will use when adding ImGui
#define IMGUI_COLOR_PICKER_X 1370
#define IMGUI_COLOR_PCIKER_Y 35
#define IMGUI_COLOR_PICKER_WIDTH 550
#define IMGUI_COLOR_PCIKER_HEIGHT 450

namespace Dralgeer {
    struct Sprite {
        float width, height;
        Texture* texture = nullptr;
        glm::vec2 texCords[4] = {glm::vec2(1, 1), glm::vec2(1, 0), glm::vec2(0, 0), glm::vec2(0, 1)};
    };

    // * Remember to set isDirty to true if you change either the sprite or the color.
    class SpriteRenderer {
        private:
            bool imGuiSetup = 1; // ! DO NOT serialize

        public: // todo make rule of 3 operators with throw exceptions for copy constructor and copy assignment
            uint32_t flags = COMPONENT_FLAG;
            GameObject::GameObject gameObject;

            glm::vec4 color = glm::vec4(1, 1, 1, 1); // for some reason it doesn't work unless I have the equals
            Sprite sprite;

            Transform lastTransform; // ! DO NOT serialize
            bool isDirty = 1; // ! DO NOT serialize

            // * ==========================================================

            SpriteRenderer() {};

            inline void start() { lastTransform = gameObject.transform; };

            // ! Not convinced we even need this function
            inline void editorUpdate();

            inline void update() {
                if (lastTransform != gameObject.transform) {
                    gameObject.transform = lastTransform;
                    isDirty = 1;
                }
            };

            ~SpriteRenderer() { if (sprite.texture != nullptr) { delete sprite.texture; }};
    };
}
