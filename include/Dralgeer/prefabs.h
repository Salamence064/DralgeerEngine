#pragma once

#include "component.h"

namespace Dralgeer {
    namespace Prefabs {
        static GameObject* generateSpriteObject(Sprite const &spr, float width, float height) {
            GameObject* go = new GameObject();
            go->name = "SpriteObjectGen";
            go->transform.scale.x = width;
            go->transform.scale.y = height;

            SpriteRenderer* renderer = new SpriteRenderer();
            renderer->sprite.width = spr.width;
            renderer->sprite.height = spr.height;
            renderer->sprite.texCoords[0] = spr.texCoords[0];
            renderer->sprite.texCoords[1] = spr.texCoords[1];
            renderer->sprite.texCoords[2] = spr.texCoords[2];
            renderer->sprite.texCoords[3] = spr.texCoords[3];
            renderer->sprite.texture = spr.texture; // because of how the asset pool will work

            renderer->gameObject = new GameObject();
            renderer->gameObject->transform.pos.x = -64.0f;
            renderer->gameObject->transform.scale.x = width;
            renderer->gameObject->transform.scale.y = height;

            go->addComponent(renderer);

            return go;
        };
    }
}
