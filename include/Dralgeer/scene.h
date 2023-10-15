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

    // todo probably use a graph inside of the root scene to determine which subscene to switch to

    // todo probably move some of the inline stuff into functions in the .cpp files

    // A scene contained within a root scene.
    // These will be used to represent different rooms or subareas.
    // The root scene should change subscenes when appropriate.
    class SubScene {
        private:
            Renderer renderer;
            Zeta::Handler physicsHandler;

            SpriteRenderer** sprites = nullptr;
            int sCount = 0;
            int sCapacity;

            GameObject** gameObjects = nullptr;
            int gCount = 0;
            int gCapacity;
            
            SpriteArea* sa = nullptr;
            int saCount = 0;
            int saCapacity;

        public:
            FrameBuffer frameBuffer;
            Camera camera;

            inline SubScene(int width, int height, int sCapacity, int gCapacity, int saCapacity,
                    ZMath::Vec2D const &g = ZMath::Vec2D(0.0f), float timeStep = FPS_60)
            {
                frameBuffer.init(width, height);
                physicsHandler = Zeta::Handler(g, timeStep);

                this->sCapacity = sCapacity;
                this->gCapacity = gCapacity;
                this->saCapacity = saCapacity;
                sprites = new SpriteRenderer*[sCapacity];
                gameObjects = new GameObject*[gCapacity];
                sa = new SpriteArea[saCapacity];
            };

            // * Do not allow for construction of a SubScene from another SubScene
            inline SubScene(SubScene const &ss) { throw std::runtime_error("Cannot construct a SubScene object from another SubScene object."); };
            inline SubScene(SubScene &&ss) { throw std::runtime_error("Cannot construct a SubScene object from another SubScene object."); };

            // * Do not allow for reassignment of a SubScene
            inline SubScene& operator = (SubScene const &ss) { throw std::runtime_error("You cannot reassign a SubScene object."); };
            inline SubScene& operator = (SubScene &&ss) { throw std::runtime_error("You cannot reassign a SubScene object."); };

            inline ~SubScene() {
                for (int i = 0; i < sCount; ++i) { delete sprites[i]; }
                delete[] sprites;

                for (int i = 0; i < gCount; ++i) { delete gameObjects[i]; }
                delete[] gameObjects;
            };


            // * ===================
            // * Normal Functions
            // * ===================

            // add a sprite renderer to the subscene
            inline void addSprite(SpriteRenderer* spr) {
                if (sCount == sCapacity) {
                    sCapacity *= 2;
                    SpriteRenderer** temp = new SpriteRenderer*[sCapacity];

                    for (int i = 0; i < sCount; ++i) { temp[i] = sprites[i]; }

                    delete[] sprites;
                    sprites = temp;
                }

                sprites[sCount++] = spr;
            };

            // add a game object to the subscene
            inline void addGameObject(GameObject* go) {
                if (gCount == gCapacity) {
                    gCapacity *= 2;
                    GameObject** temp = new GameObject*[gCapacity];

                    for (int i = 0; i < gCount; ++i) { temp[i] = gameObjects[i]; }

                    delete[] gameObjects;
                    gameObjects = temp;
                }

                gameObjects[gCount++] = go;
            };

            // add multiple sprite renderers to the subscene
            inline void addSprites(SpriteRenderer** spr, int size) {
                if (sCount - 1 + size >= sCapacity) {
                    sCapacity += size;
                    SpriteRenderer** temp = new SpriteRenderer*[sCapacity];

                    for (int i = 0; i < sCount; ++i) { temp[i] = sprites[i]; }

                    delete[] sprites;
                    sprites = temp;
                }

                for (int i = 0; i < size; ++i) { sprites[sCount++] = spr[i]; }
            };

            // add multiple game objects to the subscene
            inline void addSprites(GameObject** go, int size) {
                if (gCount - 1 + size >= gCapacity) {
                    gCapacity += size;
                    GameObject** temp = new GameObject*[gCapacity];

                    for (int i = 0; i < gCount; ++i) { temp[i] = gameObjects[i]; }

                    delete[] gameObjects;
                    gameObjects = temp;
                }

                for (int i = 0; i < size; ++i) { gameObjects[gCount++] = go[i]; }
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
