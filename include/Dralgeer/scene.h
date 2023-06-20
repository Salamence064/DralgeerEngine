#ifndef SCENE_H
#define SCENE_H

#include "render.h"
#include "assetpool.h"

namespace Dralgeer {
    // todo for now will do this the OOP way just to get things up and runnings
    // todo  will refactor in the future
    // todo Consider refactoring this using void* (in window.h) and an enum

    // Forward declaration to allow for use in SceneInitializer.
    class Scene;


    // * ===================
    // * SceneInitializer
    // * ===================

    class SceneInitializer {
        public:
            inline virtual void init(Scene const &scene) = 0;
            inline virtual void loadResources(Scene const &scene) = 0;
            inline virtual void imGui() = 0;
    };


    // * ================
    // * Scene Stuff
    // * ================

    class Scene { // todo add the OOP stuff for now
        private:
            bool isRunning = 0;

        public:
            std::vector<GameObject*> gameObjects; // todo use a resizeable dynamic array instead of a vector probably
            Camera camera;

            Scene() : gameObjects({}) { camera.pos = glm::vec2(0, 0); };

            // ??? Are these even necessary??? (probs not)
            inline void start() {
                for (int i = 0; i < gameObjects.size(); ++i) { gameObjects[i]->start(); }
                isRunning = 1;
            };

            inline void addGameObject(GameObject* go) {
                gameObjects.push_back(go);
                if (isRunning) { go->start(); }
            };

            inline void destroy() { for (int i = 0; i < gameObjects.size(); ++i) { gameObjects[i]->destory(); }};

            // ! not sure if this is really needed either
            inline GameObject* getGameObject(int id) const {
                for (int i = 0; i < gameObjects.size(); ++i) { if (gameObjects[i]->id == id) { return gameObjects[i]; }}
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

            // todo refactor around the initializer approach for now
            // todo will later refactor around void*
    };


    // * ======================
    // * Scene Initializers
    // * ======================

    class LevelEditorInitializer : public SceneInitializer {
        private:
            // todo add physics stuff here

            SpriteSheet sprites;
            GameObject components;
            bool imGuiSetup = 1; // ! DO NOT serialize

        public:
            LevelEditorInitializer() {};

            inline void init(Scene const &scene) override {
                // load the spritesheet
                sprites = AssetPool::getSpriteSheet("assets/images/spritesheets/decorationsAndBlocks.png");
                
                components.name = "LevelEditor";
                // todo maybe add transform as a component class for the GameObject if necessary
                EditorCamera* camera = new EditorCamera(); // defo refactor this stuff
                components.addComponent(camera);

                // todo call components.setNoSerialize() when I have serialization setup
                // todo add gizmo stuff after creating them
                // todo add MouseControls after creating that, too
            };

            inline void loadResources(Scene const &scene) override;

            inline void imGui() override;
    };
}

#endif // !SCENE_H
