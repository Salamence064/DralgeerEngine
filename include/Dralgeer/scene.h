#ifndef SCENE_H
#define SCENE_H

#include "prefabs.h"
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

            GameObject* gameObjects = nullptr;
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
                    Renderer::add(*((SpriteRenderer*) gameObjects[i].getComponent(ComponentType::SPRITE_RENDERER)));
                }

                running = 1;
            };

            inline void addGameObject(GameObject const &go) {
                addGO(go);
                
                if (running) {
                    int n = numObjects - 1;
                    gameObjects[n].start();
                    Renderer::add(*((SpriteRenderer*) gameObjects[n].getComponent(ComponentType::SPRITE_RENDERER)));
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
                        Renderer::destroy((SpriteRenderer*) gameObjects[i].getComponent(ComponentType::SPRITE_RENDERER));
                        for (int j = i; j < numObjects - 1; ++j) { gameObjects[j] = gameObjects[j + 1]; }
                        numObjects--;
                    }
                }
            };

            inline void render() { Renderer::render(); };
            inline void destroy() { for (int i = 0; i < numObjects; ++i) { gameObjects[i].destory(); }};
    };

    class LevelEditorScene : public Scene {
        private:
            SpriteSheet sprites;
            GameObject components;
            bool imGuiSetup = 1; // ! DO NOT serialize

        protected:
            inline void loadResources() override {
                AssetPool::getShader("assets/shaders/default.glsl");

                SpriteSheet spr;
                spr.init(AssetPool::getTexture("assets/images/spritesheets/decorationsAndBlocks.png"), 16, 16, 81, 0);
                AssetPool::addSpriteSheet("assets/images/spritesheets/decorationsAndBlocks.png", spr);

                // todo add gizmos

                for (int i = 0; i < numObjects; ++i) {
                    SpriteRenderer* spr = (SpriteRenderer*) gameObjects[i].getComponent(ComponentType::SPRITE_RENDERER);
                    if (spr && spr->sprite.texture) {
                        Texture* temp = spr->sprite.texture;
                        spr->sprite.texture = new Texture(AssetPool::getTexture(temp->filepath));
                        delete temp;
                    }
                }
            };

        public:
            LevelEditorScene() {
                type = SceneType::LEVEL_EDITOR_SCENE;
                gameObjects = new GameObject[capacity];
            };


            // * ===================
            // * Rule of 5 Stuff
            // * ===================

            LevelEditorScene(LevelEditorScene const &scene) {
                type = scene.type;
                camera = scene.camera;
                sprites = scene.sprites;
                components = scene.components;
                
                capacity = scene.capacity;
                numObjects = scene.numObjects;

                gameObjects = new GameObject[capacity];
                for (int i = 0; i < numObjects; ++i) { gameObjects[i] = scene.gameObjects[i]; }
            };

            LevelEditorScene(LevelEditorScene &&scene) {
                type = scene.type;
                camera = std::move(scene.camera);
                sprites = std::move(scene.sprites);
                components = std::move(scene.components);

                capacity = scene.capacity;
                numObjects = scene.numObjects;
                gameObjects = scene.gameObjects;
                scene.gameObjects = NULL;
            };

            LevelEditorScene& operator = (LevelEditorScene const &scene) {
                if (this != &scene) {
                    camera = scene.camera;
                    sprites = scene.sprites;
                    components = scene.components;

                    capacity = scene.capacity;
                    numObjects = scene.numObjects;

                    gameObjects = new GameObject[capacity];
                    for (int i = 0; i < numObjects; ++i) { gameObjects[i] = scene.gameObjects[i]; }
                }

                return *this;
            };

            LevelEditorScene& operator = (LevelEditorScene &&scene) {
                if (this != &scene) {
                    camera = std::move(scene.camera);
                    sprites = std::move(scene.sprites);
                    components = std::move(scene.components);

                    capacity = scene.capacity;
                    numObjects = scene.numObjects;
                    gameObjects = scene.gameObjects;
                    scene.gameObjects = NULL;
                }

                return *this;
            };

            ~LevelEditorScene() { delete[] gameObjects; };


            // * ====================
            // * Normal Functions
            // * ====================

            void init() override {
                camera.pos = glm::vec2(0.0f, 0.0f);
                loadResources();

                // load sprite sheet
                sprites = AssetPool::getSpriteSheet("assets/images/spritesheets/decorationsAndBlocks.png");

                components.name = "LevelEditor";
                components.transform.zIndex = 0;
                components.transform.pos = {0.0f, 0.0f};
                components.transform.scale = {0.0f, 0.0f};
                components.serialize = 0;

                // todo add other components once they are created
                components.addComponent(new GridLines());
                components.addComponent(new EditorCamera(camera));

                addGameObject(components);
            };

            void imGui() override {
                ImGui::Begin("Tiles");

                if (imGuiSetup) {
                    ImGui::SetWindowPos(ImVec2(0.0f, 0.0f));
                    ImGui::SetWindowSize(ImVec2(720.0f, 520.0f));
                    imGuiSetup = 0;
                }

                // get the window positioning, size, and item spacing
                ImVec2 windowPos = ImGui::GetWindowPos();
                ImVec2 windowSize = ImGui::GetWindowSize();
                ImVec2 itemSpacing = ImGui::GetStyle().ItemSpacing;
                float windowX2 = windowPos.x + windowSize.x;
                
                for (int i = 0; i < sprites.numSprites; ++i) {
                    // for readability
                    Sprite sprite = sprites.sprites[i];

                    // multiplying by an int is for scaling purposes
                    float spriteWidth = sprite.width * 3;
                    float spriteHeight = sprite.height * 3;

                    ImGui::PushID(i);
                    if (ImGui::ImageButton((int*) sprite.texture->texID, ImVec2(spriteWidth, spriteHeight),
                        ImVec2(sprite.texCords[2].x, sprite.texCords[0].y), ImVec2(sprite.texCords[0].x, sprite.texCords[2].y)))
                    {
                        GameObject go = Prefabs::generateSpriteObject(sprite, GRID_WIDTH, GRID_HEIGHT);
                        // todo attach it to the mouse cursor once we add in the mouse controls component
                    }

                    ImGui::PopID();

                    ImVec2 lastButtonPos = ImGui::GetItemRectMax();
                    if (i + 1 < sprites.numSprites && lastButtonPos.x + itemSpacing.x + spriteWidth < windowX2) { ImGui::SameLine(); }
                }

                ImGui::End();
            };
    };
}

#endif // !SCENE_H
