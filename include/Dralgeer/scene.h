#pragma once

#include "framebuffer.h"
#include "gizmo.h"
#include "render.h"
#include "event.h"
#include <Zeta2D/physicshandler.h>

namespace Dralgeer {
    // todo this will only be added later after editor stuff is done since each will be custom made
    // todo root scenes
    // todo subscenes

    // todo basically the editor will be used to create the rooms then the rooms will be put into each of the root scenes as subscenes

    enum RootScene {
        FLOOR1,
        FLOOR2,
        FLOOR3,
        FLOOR4,
        FLOOR5,
        FLOOR6,
        FLOOR7,
        FLOOR8,
        FLOOR9,
        LEVEL_EDITOR_SCENE
    };

    class RootScenes {
        private:
            // * ==============
            // * Attributes
            // * ==============
            

        public:


    };

    // todo probably use a graph inside of the root scene to determine which subscene to switch to

    // todo probably move some of the inline stuff into functions in the .cpp files

    // todo update to be serialized sometime. Probs once I roll out my new serialization format
    // todo add an onNotify function when I need it

    // todo next steps:
    //  - Add root scenes
    //  - Add graphs inside the root scenes
    //  - Add the event system stuff to switch between certain root scenes

    // A scene contained within a root scene.
    // These will be used to represent different rooms or subareas.
    // The root scene should change subscenes when appropriate.
    class SubScene {
        private:
            Renderer renderer;
            Zeta::Handler physicsHandler;

            SpriteRenderer** sprites = nullptr;
            int numSprites = 0;
            int capacity;

        public:
            FrameBuffer frameBuffer;
            Camera camera;

            inline SubScene() {};

            // * Do not allow for construction of a SubScene from another SubScene
            inline SubScene(SubScene const &ss) { throw std::runtime_error("Cannot construct a SubScene object from another SubScene object."); };
            inline SubScene(SubScene &&ss) { throw std::runtime_error("Cannot construct a SubScene object from another SubScene object."); };

            // * Do not allow for reassignment of a SubScene
            inline SubScene& operator = (SubScene const &ss) { throw std::runtime_error("You cannot reassign a SubScene object."); };
            inline SubScene& operator = (SubScene &&ss) { throw std::runtime_error("You cannot reassign a SubScene object."); };

            inline ~SubScene() {
                for (int i = 0; i < numSprites; ++i) { delete sprites[i]; }
                delete[] sprites;
            };


            // * ===================
            // * Normal Functions
            // * ===================

            void init(int width, int height, int capacity, SpriteRenderer** spr, int size,
                        ZMath::Vec2D const &g = ZMath::Vec2D(0.0f), float timeStep = FPS_60);
            
            void update(float &dt);

            inline void render(Shader const &currShader) { renderer.render(currShader, camera); };

            // add a sprite renderer to the subscene
            inline void addSprite(SpriteRenderer* spr) {
                if (numSprites == capacity) {
                    capacity *= 2;
                    SpriteRenderer** temp = new SpriteRenderer*[capacity];

                    for (int i = 0; i < numSprites; ++i) { temp[i] = sprites[i]; }

                    delete[] sprites;
                    sprites = temp;
                }

                sprites[numSprites++] = spr;
            };

            // add multiple sprite renderers to the subscene
            inline void addSprites(SpriteRenderer** spr, int size) {
                if (numSprites - 1 + size >= capacity) {
                    capacity += size;
                    SpriteRenderer** temp = new SpriteRenderer*[capacity];

                    for (int i = 0; i < numSprites; ++i) { temp[i] = sprites[i]; }

                    delete[] sprites;
                    sprites = temp;
                }

                for (int i = 0; i < size; ++i) { sprites[numSprites++] = spr[i]; }
            };
    };

    struct Scene {
        void* scene;
        RootScene type;
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
            bool imGuiSetup = 1;

            EditorCamera editorCamera;
            GridLines gridLines;
            MouseControls mouseControls;
            GizmoSystem gizmoSystem;

            EditorRenderer renderer;
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

            inline LevelEditorScene() { gameObjects = new GameObject*[capacity]; };


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

            void onNotify(EventType event, GameObject* go);
            void exportScene();
            void importScene();
    };
}
