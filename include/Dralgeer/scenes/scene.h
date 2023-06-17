#pragma once

#include "../camera.h"
#include "../gameobject.h"
#include "../render/render.h"

namespace Dralgeer {
    class Scene {
        private:
            bool isRunning = 0;

        public:
            std::vector<GameObject::GameObject*> gameObjects; // todo use a resizeable dynamic array instead of a vector probably
            Camera camera;

            Scene() : gameObjects({}) { camera.pos = glm::vec2(0, 0); };

            // ??? Are these even necessary??? (probs not)
            inline void start() {
                for (int i = 0; i < gameObjects.size(); ++i) { gameObjects[i]->start(); }
                isRunning = 1;
            };

            inline void addGameObject(GameObject::GameObject* go) {
                gameObjects.push_back(go);
                if (isRunning) { go->start(); }
            };

            inline void destroy() { for (int i = 0; i < gameObjects.size(); ++i) { gameObjects[i]->destory(); }};

            // ! not sure if this is really needed either
            inline GameObject::GameObject* getGameObject(int id) const {
                for (int i = 0; i < gameObjects.size(); ++i) { if (gameObjects[i]->getID() == id) { return gameObjects[i]; }}
                return nullptr;
            };

            void update(float dt) {
                camera.adjustProjection();

                for (int i = gameObjects.size() - 1; i >= 0; --i) {
                    gameObjects[i]->update(dt);

                    if (gameObjects[i]->dead) {
                        Renderer::destroy(gameObjects[i]->getComponent<SpriteRenderer>(SPRITE_RENDERER_FLAG));
                        delete gameObjects[i];
                        gameObjects.erase(std::next(gameObjects.begin(), i)); // todo should be able to erase at 0 (test to be sure)
                    }
                }
            };

            inline void render() { Renderer::render(); };

            
    };
}
