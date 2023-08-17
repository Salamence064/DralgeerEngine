#pragma once

#include "gizmo.h"
#include "render.h"
#include <Zeta2D/physicshandler.h>

namespace Dralgeer {
    enum SceneType {
        LEVEL_EDITOR_SCENE
    };

    struct Scene {
        void* scene;
        SceneType type;
    };

    // todo add a removeGameObject function
    class LevelEditorScene {
        private:
            // * ==============
            // * Attributes
            // * ==============

            GameObject** gameObjects = nullptr;
            int capacity = 64; // default capacity of 64 // todo probs will adjust in the future
            int numObjects = 0;

            bool running = 0; // is the scene running (not physics related)

            SpriteSheet* sprites = nullptr;
            bool imGuiSetup = 1; // ! DO NOT serialize

            EditorCamera editorCamera;
            GridLines gridLines;
            MouseControls mouseControls;
            GizmoSystem gizmoSystem;

            Renderer renderer;
            Zeta::Handler physicsHandler;


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

            inline void loadResources();

        public:
            // * ==============
            // * Attributes
            // * ==============

            Camera camera;

            inline LevelEditorScene() { gameObjects = new GameObject*[capacity]; }; // todo maybe move this to the init function


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

            void init();
            void imGui();

            inline void start() {
                for (int i = 0; i < numObjects; ++i) {
                    gameObjects[i]->start();
                    renderer.add(gameObjects[i]->sprite);
                }

                running = 1;
            };

            inline void addGameObject(GameObject* go) {
                addGO(go);
                
                if (running) {
                    go->start();
                    renderer.add(go->sprite);
                }
            };

            // Returns nullptr if no game object was found.
            inline GameObject* getGameObject(int id) {
                for (int i = 0; i < numObjects; ++i) {
                    if (gameObjects[i]->id == id) { return gameObjects[i]; }
                }

                return nullptr;
            };

            void update(float &dt, bool wantCapture, bool physicsUpdate);
            inline void render(Shader const &currShader) { renderer.render(currShader, camera); };
            void exportScene();
            void importScene();
    };
}
