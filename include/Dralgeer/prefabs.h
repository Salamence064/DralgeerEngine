#pragma once

#include "component.h"

namespace Dralgeer {
    namespace Prefabs {
        // todo possibly add a transform as a component in the GameObject
        // todo this is only if necessary

        static GameObject generateSpriteObject(Sprite const &spr, float width, float height) {
            GameObject go;
            go.name = "SpriteObjectGen";
            go.transform.scale.x = width;
            go.transform.scale.y = height;

            SpriteRenderer renderer = SpriteRenderer();
            go.addComponent(&renderer);

            return go;
        };
    }
}
