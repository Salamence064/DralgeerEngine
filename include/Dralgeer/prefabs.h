#pragma once

#include "component.h"

namespace Dralgeer {
    namespace Prefabs {
        // todo possibly add a transform as a component in the GameObject
        // todo this is only if necessary

        static GameObject* generateSpriteObject(Sprite const &spr, float width, float height) {
            GameObject* go = new GameObject();
            go->name = "SpriteObjectGen";
            go->transform.scale.x = width;
            go->transform.scale.y = height;
            go->transform.pos.x = 0;
            go->transform.pos.y = 0;
            go->transform.zIndex = 1;

            SpriteRenderer* renderer = new SpriteRenderer();
            renderer->sprite.width = spr.width;
            renderer->sprite.height = spr.height;
            renderer->color = {1.0f, 1.0f, 1.0f, 1.0f};
            renderer->sprite.texture = new Texture();
            renderer->sprite.texture->init(spr.texture->filepath);
            renderer->gameObject = new GameObject();
            renderer->gameObject->transform.pos.x = 0.0f;
            renderer->gameObject->transform.pos.y = 0.0f;
            renderer->gameObject->transform.scale.x = width;
            renderer->gameObject->transform.scale.y = height;
            renderer->gameObject->transform.zIndex = 1;

            go->addComponent(renderer);

            return go;
        };
    }
}
