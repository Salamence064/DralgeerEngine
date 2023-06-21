#ifndef SCENE_H
#define SCENE_H

#include "render.h"
#include "assetpool.h"

namespace Dralgeer {
    // todo probably refactor to use a struct that stores a void* and the enum type of the scene instead of this OOP solution
    // todo  but use the OOP solution for now

    enum SceneType {
        LEVEL_EDITOR_SCENE
    };

    class Scene {
        protected:
            // * ======================
            // * Protected Attributes
            // * ======================

            GameObject* gameObjects;
            int capacity = 8; // default capacity of 8 // todo probs will up in the future
            int numObjects = 0;

            bool running = 0;
            // todo add physics handler here.

            // * ==============================
            // * Protected abstract function
            // * ==============================

            virtual inline void loadResources() = 0;


            // * ====================
            // * Helper Functions
            // * ====================

            inline void addGO(GameObject const &go) {
                if (numObjects == capacity) {
                    capacity *= 2;
                    GameObject* temp = new GameObject[capacity];

                    for (int i = 0; i < numObjects; ++i) { temp[i] = gameObjects[i]; }

                    delete[] gameObjects;
                    gameObjects = temp;
                }

                gameObjects[numObjects++] = go;
            };

        public:
            // * ==============
            // * Attributes
            // * ==============

            SceneType type;
            Camera camera;


            // * ======================
            // * Abstract Functions
            // * ======================

            virtual void init() = 0;
            virtual void imGui() = 0;


            // * ====================
            // * Normal Functions
            // * ====================

            inline void start() {
                for (int i = 0; i < numObjects; ++i) {
                    gameObjects[i].start();
                    Renderer::add(*(gameObjects[i].getComponent<SpriteRenderer>(ComponentType::SPRITE_RENDERER)));
                }

                running = 1;
            };

            inline void addGameObject(GameObject const &go) {
                addGO(go);
                
                if (running) {
                    int n = numObjects - 1;
                    gameObjects[n].start();
                    Renderer::add(*(gameObjects[n].getComponent<SpriteRenderer>(ComponentType::SPRITE_RENDERER)));
                }
            };

            inline GameObject getGameObject(int id) {
                for (int i = 0; i < numObjects; ++i) {
                    if (gameObjects[i].id == id) { return gameObjects[i]; }
                }
            };

            void update(float dt) {
                camera.adjustProjection();
                
                for (int i = numObjects - 1; i >= 0; --i) {
                    gameObjects[i].update(dt);

                    if (gameObjects[i].dead) {
                        Renderer::destroy(gameObjects[i].getComponent<SpriteRenderer>(ComponentType::SPRITE_RENDERER));
                        for (int j = i; j < numObjects - 1; ++j) { gameObjects[j] = gameObjects[j + 1]; }
                        numObjects--;
                    }
                }
            };

            inline void render() { Renderer::render(); };
            inline void destroy() { for (int i = 0; i < numObjects; ++i) { gameObjects[i].destory(); }};
    };

    class LevelEditorScene : public Scene { // todo add rule of 5 stuff
        protected:
            inline void loadResources() override;

        public:
            LevelEditorScene() {
                type = SceneType::LEVEL_EDITOR_SCENE;
                gameObjects = new GameObject[capacity];
            };

            void init() override {
                camera.pos = glm::vec2(0.0f, 0.0f);
            };

            void imGui() override;
    };
}

#endif // !SCENE_H
