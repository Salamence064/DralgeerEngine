#ifndef SCENE_H
#define SCENE_H

#include "component.h"
#include "render.h"

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

            GameObject** gameObjects = nullptr;
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

            inline void addGO(GameObject* go) {
                if (numObjects == capacity) {
                    capacity *= 2;
                    GameObject** temp = new GameObject*[capacity];

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
                    gameObjects[i]->start();
                    Renderer::add((SpriteRenderer*) gameObjects[i]->getComponent(SPRITE_RENDERER));
                }

                running = 1;
            };

            inline void addGameObject(GameObject* go) {
                addGO(go);
                
                if (running) {
                    int n = numObjects - 1;
                    gameObjects[n]->start();
                    Renderer::add((SpriteRenderer*) gameObjects[n]->getComponent(SPRITE_RENDERER));
                }
            };

            // Returns nullptr if no game object was found.
            inline GameObject* getGameObject(int id) {
                for (int i = 0; i < numObjects; ++i) {
                    if (gameObjects[i]->id == id) { return gameObjects[i]; }
                }

                return nullptr;
            };

            void update(float dt);
            inline void render() { Renderer::render(camera); };
            inline void destroy() { for (int i = 0; i < numObjects; ++i) { gameObjects[i]->destory(); }};
    };

    class LevelEditorScene : public Scene {
        private:
            SpriteSheet* sprites = nullptr;
            GameObject components;
            bool imGuiSetup = 1; // ! DO NOT serialize

        protected:
            inline void loadResources() override;

        public:
            LevelEditorScene();


            // * ===================
            // * Rule of 5 Stuff
            // * ===================

            LevelEditorScene(LevelEditorScene const &scene);
            LevelEditorScene(LevelEditorScene &&scene);
            LevelEditorScene& operator = (LevelEditorScene const &scene);
            LevelEditorScene& operator = (LevelEditorScene &&scene);
            ~LevelEditorScene();


            // * ====================
            // * Normal Functions
            // * ====================

            void init() override;
            void imGui() override;
    };
}

#endif // !SCENE_H
