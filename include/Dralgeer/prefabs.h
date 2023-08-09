#pragma once

#include "component.h"

namespace Dralgeer {
    namespace Prefabs {
        inline static GameObject* generateGameObject(std::string const &name) { // todo there might be more I should add to this
            GameObject* go = new GameObject();
            go->name = name;
            return go;
        };

        static GameObject* generateSpriteObject(Sprite const &spr, float width, float height) {
            GameObject* go = new GameObject();
            go->name = "SpriteObjectGen";
            go->transform.scale.x = width;
            go->transform.scale.y = height;

            go->sprite = new SpriteRenderer();
            go->sprite->sprite.width = spr.width;
            go->sprite->sprite.height = spr.height;

            go->sprite->sprite.texCoords[0] = spr.texCoords[0];
            go->sprite->sprite.texCoords[1] = spr.texCoords[1];
            go->sprite->sprite.texCoords[2] = spr.texCoords[2];
            go->sprite->sprite.texCoords[3] = spr.texCoords[3];
            go->sprite->sprite.texture = spr.texture; // because of how the asset pool will work

            go->sprite->transform.pos.x = -64.0f;
            go->sprite->transform.pos.y = -64.0f;
            go->sprite->transform.scale.x = width;
            go->sprite->transform.scale.y = height;
            go->sprite->transform.zIndex = 0;

            go->start();
            return go;
        };
    }
}
