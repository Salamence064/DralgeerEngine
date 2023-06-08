// todo include Sprite, SpriteRenderer, and SpriteSheet in here

#pragma once

#include "../render/texture.h"

namespace Dralgeer {
    struct Sprite {
        float width, height;
        Texture texture;
        glm::vec2 texCords[4] = {glm::vec2(1, 1), glm::vec2(1, 0), glm::vec2(0, 0), glm::vec2(0, 1)};
    };


}
