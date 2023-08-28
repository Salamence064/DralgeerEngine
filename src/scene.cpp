#define IMGUI_DISABLE_OBSOLETE_FUNCTIONS
#include <Dralgeer/scene.h>
#include <IMGUI/imgui.h>
#include <Dralgeer/prefabs.h>
#include <Dralgeer/assetpool.h>
#include <Dralgeer/gizmo.h>
#include <fstream>
#include <Dralgeer/systemmessages.h>

namespace Dralgeer {
    // * ================================================
    // * Level Editor Class

    // todo need to update dt even when physicsUpdate isn't true
    void LevelEditorScene::update(float &dt, bool wantCapture, bool physicsUpdate) {
        camera.adjustProjection();

        if (physicsUpdate) {
            // physicsHandler.update(dt);

        } else {
            editorCamera.update(dt, wantCapture);
            gridLines.update(camera);
            mouseControls.update();
            gizmoSystem.update();

            for (int i = 0; i < numObjects; ++i) {
                if (gameObjects[i]->sprite && gameObjects[i]->sprite->rebufferZIndex) { renderer.updateZIndex(gameObjects[i]->sprite); }
            }
        }

        for (int i = numObjects - 1; i >= 0; --i) {
            gameObjects[i]->update();

            if (gameObjects[i]->dead) {
                renderer.destroy(gameObjects[i]->sprite);
                delete gameObjects[i];
                for (int j = i; j < numObjects - 1; ++j) { gameObjects[j] = gameObjects[j + 1]; }
                numObjects--;
            }
        }
    };

    inline void LevelEditorScene::loadResources() {
        SpriteSheet* spr = new SpriteSheet();
        spr->init(AssetPool::getTexture("../../assets/images/spritesheets/decorationsAndBlocks.png"), 16, 16, 81, 0);
        AssetPool::addSpriteSheet("../../assets/images/spritesheets/decorationsAndBlocks.png", spr);

        SpriteSheet* gizmoSpr = new SpriteSheet();
        gizmoSpr->init(AssetPool::getTexture("../../assets/images/gizmos.png"), 24, 48, 3, 0);
        AssetPool::addSpriteSheet("../../assets/images/gizmos.png", gizmoSpr);

        for (int i = 0; i < numObjects; ++i) {
            SpriteRenderer* spr = gameObjects[i]->sprite;
            if (spr && spr->sprite.texture) { AssetPool::addTexture(spr->sprite.texture->filepath, spr->sprite.texture); }
        }
    };

    LevelEditorScene::LevelEditorScene(LevelEditorScene const &scene) {
        camera = scene.camera;
        
        editorCamera = scene.editorCamera;
        gridLines = scene.gridLines;
        mouseControls = scene.mouseControls;
        gizmoSystem = scene.gizmoSystem;

        capacity = scene.capacity;
        numObjects = scene.numObjects;

        gameObjects = new GameObject*[capacity];
        for (int i = 0; i < numObjects; ++i) { gameObjects[i] = new GameObject(*(scene.gameObjects[i])); }

        if (scene.sprites && scene.sprites->sprites) {
            sprites = new SpriteSheet();
            sprites->numSprites = scene.sprites->numSprites;
            
            for (int i = 0; i < sprites->numSprites; ++i) {
                sprites->sprites[i].width = scene.sprites->sprites[i].width;
                sprites->sprites[i].height = scene.sprites->sprites[i].height;
                sprites->sprites[i].texture = scene.sprites->sprites[i].texture; // copying the texture pointer is fine
                sprites->sprites[i].texCoords[0] = scene.sprites->sprites[i].texCoords[0];
                sprites->sprites[i].texCoords[1] = scene.sprites->sprites[i].texCoords[1];
                sprites->sprites[i].texCoords[2] = scene.sprites->sprites[i].texCoords[2];
                sprites->sprites[i].texCoords[3] = scene.sprites->sprites[i].texCoords[3];
            }
        }
    };

    LevelEditorScene::LevelEditorScene(LevelEditorScene &&scene) {
        camera = std::move(scene.camera);
        editorCamera = std::move(scene.editorCamera);
        mouseControls = std::move(scene.mouseControls);
        gridLines = std::move(scene.gridLines);
        gizmoSystem = std::move(scene.gizmoSystem);

        sprites = scene.sprites;
        scene.sprites = NULL;

        capacity = scene.capacity;
        numObjects = scene.numObjects;
        gameObjects = scene.gameObjects;
        scene.gameObjects = NULL;
    };

    LevelEditorScene& LevelEditorScene::operator = (LevelEditorScene const &scene) {
        if (this != &scene) {
            camera = scene.camera;
            
            editorCamera = scene.editorCamera;
            gridLines = scene.gridLines;
            mouseControls = scene.mouseControls;
            gizmoSystem = scene.gizmoSystem;

            // -----------------------------------------------------------

            if (gameObjects) {
                for (int i = 0; i < numObjects; ++i) { delete gameObjects[i]; }
                delete[] gameObjects;
            }

            capacity = scene.capacity;
            numObjects = scene.numObjects;

            gameObjects = new GameObject*[capacity];
            for (int i = 0; i < numObjects; ++i) { gameObjects[i] = new GameObject(*(scene.gameObjects[i])); }

            // -----------------------------------------------------------

            if (sprites) { delete sprites; sprites = nullptr; }

            if (scene.sprites && scene.sprites->sprites) {
                sprites = new SpriteSheet();
                sprites->numSprites = scene.sprites->numSprites;
                
                for (int i = 0; i < sprites->numSprites; ++i) {
                    sprites->sprites[i].width = scene.sprites->sprites[i].width;
                    sprites->sprites[i].height = scene.sprites->sprites[i].height;
                    sprites->sprites[i].texture = scene.sprites->sprites[i].texture; // copying the texture pointer is fine
                    sprites->sprites[i].texCoords[0] = scene.sprites->sprites[i].texCoords[0];
                    sprites->sprites[i].texCoords[1] = scene.sprites->sprites[i].texCoords[1];
                    sprites->sprites[i].texCoords[2] = scene.sprites->sprites[i].texCoords[2];
                    sprites->sprites[i].texCoords[3] = scene.sprites->sprites[i].texCoords[3];
                }
            }
        }

        return *this;
    };

    LevelEditorScene& LevelEditorScene::operator = (LevelEditorScene &&scene) {
        if (this != &scene) {
            camera = std::move(scene.camera);
            editorCamera = std::move(scene.editorCamera);
            mouseControls = std::move(scene.mouseControls);
            gridLines = std::move(scene.gridLines);
            gizmoSystem = std::move(scene.gizmoSystem);

            sprites = scene.sprites;
            scene.sprites = NULL;

            capacity = scene.capacity;
            numObjects = scene.numObjects;
            gameObjects = scene.gameObjects;
            scene.gameObjects = NULL;
        }

        return *this;
    };

    // todo the Zeta::Handler and adding gizmos to the GizmoBatch both cause crashing when calling the LevelEditorScene's destructor
    
    // todo when there are sprites added to the scene, it causes a crash on destruction
    // todo in other words, when there are sprites for a RenderBatch or GizmoBatch to handle, it causes a crash
    LevelEditorScene::~LevelEditorScene() {
        for (int i = 0; i < numObjects; ++i) { delete gameObjects[i]; }
        delete[] gameObjects;
    };

    void LevelEditorScene::init() {
        camera.pos = glm::vec2(0.0f, 0.0f);
        camera.adjustProjection();
        camera.adjustView();

        loadResources();

        // load sprite sheet
        sprites = AssetPool::getSpriteSheet("../../assets/images/spritesheets/decorationsAndBlocks.png");

        editorCamera.init(camera);
        gizmoSystem.init(AssetPool::getSpriteSheet("../../assets/images/gizmos.png"));
        gizmoSystem.start();

        // renderer.add(gizmoSystem.gizmos[TRANSLATE_GIZMO].xObject->sprite);
        // renderer.add(gizmoSystem.gizmos[TRANSLATE_GIZMO].yObject->sprite);
        // renderer.add(gizmoSystem.gizmos[SCALE_GIZMO].xObject->sprite);
        // renderer.add(gizmoSystem.gizmos[SCALE_GIZMO].yObject->sprite);
    };


    // disable pointer cast warnings for this function as it will warn of a void* cast unnecessarily
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wint-to-pointer-cast"

    void LevelEditorScene::imGui() {
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

        for (int i = 0; i < sprites->numSprites; ++i) {
            // for readability
            Sprite sprite = sprites->sprites[i];

            // multiplying by an int is for scaling purposes
            float spriteWidth = sprite.width * 3;
            float spriteHeight = sprite.height * 3;
            
            ImGui::PushID(i);
            if (ImGui::ImageButton("SpriteSelection", (void*) sprite.texture->texID, ImVec2(spriteWidth, spriteHeight),
                ImVec2(sprite.texCoords[2].x, sprite.texCoords[0].y), ImVec2(sprite.texCoords[0].x, sprite.texCoords[2].y)))
            {
                // todo the moving object rebuffers too frequently (even when no movement has been made)
                // todo additionally, it seems like the original object gets rebuffered a random amount of times after it gets placed
                // todo a side-effect of the stacking bug is that it will have another object that gets buffered in (I suppose that's obvious)

                // todo remove any blocks that are stacked on top of each other. This can be done when the held object is placed and before its lastTransform is set
                GameObject* go = Prefabs::generateSpriteObject(sprite, GRID_WIDTH, GRID_HEIGHT);
                addGameObject(go);
                mouseControls.heldObject = go;
            }

            ImGui::PopID();

            ImVec2 lastButtonPos = ImGui::GetItemRectMax();
            if (i + 1 < sprites->numSprites && lastButtonPos.x + itemSpacing.x + spriteWidth < windowX2) { ImGui::SameLine(); }
        }

        ImGui::End();

        // handle click and drag (maybe should move where in the code this occurs)
        if (mouseControls.addObject) {
            GameObject* go = Prefabs::generateSpriteObject(mouseControls.heldObject->sprite->sprite, GRID_WIDTH, GRID_HEIGHT);
            go->sprite->transform.pos = mouseControls.heldObject->transform.pos;
            go->sprite->lastTransform.pos = go->sprite->transform.pos;

            addGameObject(go);
            mouseControls.addObject = 0;
        }
    };

    #pragma GCC diagnostic pop

    // void LevelEditorScene::onNotify(EventType event, GameObject* go) {
    //     switch(event) {
    //         case Z_INDEX_UPDATE: { renderer.updateZIndex(go->sprite); break; }
    //     }
    // };

    void LevelEditorScene::exportScene() {
        int objects = 0;

        // count the number of serializable GameObjects
        for (int i = 0; i < numObjects; ++i) { if (gameObjects[i]->serialize) { ++objects; }}

        std::ofstream f("../scenes/levelEditor.scene");
        f << "serializedObjects: " << objects << ";\n\n";
        f.close();

        for (int i = 0; i < numObjects; ++i) {
            if (gameObjects[i]->serialize) { gameObjects[i]->exportGameObject("../scenes/levelEditor.scene"); }
        }
    };

    void LevelEditorScene::importScene() {
        std::fstream f("../scenes/levelEditor.scene");
        if (!f.is_open()) { return; } // todo when I get it to work, add an info message here

        try {
            std::string line;
            bool addToSrc = 0;
            int addedObjects = 0, compAdded = 0;

            // determine the number of serialized objects
            std::getline(f, line);
            int k = line.find(" ") + 1;
            int serializedObjects = std::stoi(line.substr(k, line.find(";") - k));
            int objects = serializedObjects + numObjects;

            // determine the capacity of gameObjects
            if (objects > capacity) {
                do { capacity *= 2; } while (objects > capacity);

                GameObject** temp = new GameObject*[capacity];
                for (int j = 0; j < numObjects; ++j) { temp[j] = gameObjects[j]; }
                delete[] gameObjects;

                gameObjects = temp;
            }

            // add each serialized gameObject
            while(addedObjects < serializedObjects && std::getline(f, line)) {
                if (addToSrc) { // parse the GameObject
                    switch(compAdded) {
                        case 0: { // name
                            int i = line.find("name:");
                            if (i != std::string::npos) {
                                int index = i + 6;
                                gameObjects[numObjects] = new GameObject();
                                gameObjects[numObjects]->name = line.substr(index, line.find(",") - index);
                                ++compAdded;
                                continue;
                            }

                            break;
                        }

                        // ----- SpriteRenderer stuff -----
                        case 1: { // color
                            // color
                            int i = line.find("color:");
                            if (i != std::string::npos) {
                                int index = i + 7;
                                int c1 = line.find(","), c11 = c1 + 2;
                                int c2 = line.find(",", c11), c22 = c2 + 2;
                                int c3 = line.find(",", c22), c33 = c3 + 2;

                                gameObjects[numObjects]->sprite = new SpriteRenderer();
                                gameObjects[numObjects]->sprite->color.x = std::stof(line.substr(index, c1 - index));
                                gameObjects[numObjects]->sprite->color.y = std::stof(line.substr(c11, c2 - c11));
                                gameObjects[numObjects]->sprite->color.z = std::stof(line.substr(c22, c3 - c22));
                                gameObjects[numObjects]->sprite->color.w = std::stof(line.substr(c33, line.find(",", c33) - c33));

                                ++compAdded;
                                continue;
                            }

                            break;
                        }

                        // ----- Sprite stuff -----
                        case 2: { // width
                            int i = line.find("width:");
                            if (i != std::string::npos) {
                                int index = i + 7;
                                gameObjects[numObjects]->sprite->sprite.width = std::stof(line.substr(index, line.find(",") - index));
                                ++compAdded;
                                continue;
                            }

                            break;
                        }

                        case 3: { // height
                            int i = line.find("height:");
                            if (i != std::string::npos) {
                                int index = i + 8;
                                gameObjects[numObjects]->sprite->sprite.height = std::stof(line.substr(index, line.find(",") - index));
                                ++compAdded;
                                continue;
                            }

                            break;
                        }

                        // ----- Texture stuff -----

                        case 4: { // filepath
                            int i = line.find("filepath:");
                            if (i != std::string::npos) {
                                int index = i + 10;
                                gameObjects[numObjects]->sprite->sprite.texture = AssetPool::getTexture(line.substr(index, line.find(",") - index));
                                ++compAdded;
                                continue;
                            }

                            break;
                        }

                        // -------------------------

                        case 5: { // texCoords
                            int i = line.find("texCoords:");
                            if (i != std::string::npos) {
                                int index = i + 11;
                                int c1 = line.find(",", index), sc1 = line.find(";", c1), c11 = c1 + 2, sc11 = sc1 + 2;
                                int c2 = line.find(",", sc11), sc2 = line.find(";", c2), c22 = c2 + 2, sc22 = sc2 + 2;
                                int c3 = line.find(",", sc22), sc3 = line.find(";", c3), c33 = c3 + 2, sc33 = sc3 + 2;
                                int c4 = line.find(",", sc33), c44 = c4 + 2;

                                gameObjects[numObjects]->sprite->sprite.texCoords[0].x = std::stof(line.substr(index, c1 - index));
                                gameObjects[numObjects]->sprite->sprite.texCoords[0].y = std::stof(line.substr(c11, sc1 - c11));
                                gameObjects[numObjects]->sprite->sprite.texCoords[1].x = std::stof(line.substr(sc11, c2 - sc11));
                                gameObjects[numObjects]->sprite->sprite.texCoords[1].y = std::stof(line.substr(c22, sc2 - c22));
                                gameObjects[numObjects]->sprite->sprite.texCoords[2].x = std::stof(line.substr(sc22, c3 - sc22));
                                gameObjects[numObjects]->sprite->sprite.texCoords[2].y = std::stof(line.substr(c33, sc3 - c33));
                                gameObjects[numObjects]->sprite->sprite.texCoords[3].x = std::stof(line.substr(sc33, c4 - sc33));
                                gameObjects[numObjects]->sprite->sprite.texCoords[3].y = std::stof(line.substr(c44, line.find(",", c44) - c44));

                                ++compAdded;
                                continue;
                            }

                            break;
                        }

                        // ------------------------
                        // --------------------------------

                        // ----- Transform Stuff -----

                        case 6: { // pos
                            int i = line.find("pos:");
                            if (i != std::string::npos) {
                                int index = i + 5, c1 = line.find(",", index), c11 = c1 + 2;

                                gameObjects[numObjects]->sprite->transform.pos.x = std::stof(line.substr(index, c1 - index));
                                gameObjects[numObjects]->sprite->transform.pos.y = std::stof(line.substr(c11, line.find(",", c11) - c11));

                                ++compAdded;
                                continue;
                            }

                            break;
                        }

                        case 7: { // scale
                            int i = line.find("scale:");
                            if (i != std::string::npos) {
                                int index = i + 7, c1 = line.find(",", index), c11 = c1 + 2;

                                gameObjects[numObjects]->sprite->transform.scale.x = std::stof(line.substr(index, c1 - index));
                                gameObjects[numObjects]->sprite->transform.scale.y = std::stof(line.substr(c11, line.find(",", c11) - c11));

                                ++compAdded;
                                continue;
                            }

                            break;
                        }

                        case 8: { // zIndex
                            int i = line.find("zIndex:");
                            if (i != std::string::npos) {
                                int index = i + 8;
                                gameObjects[numObjects]->sprite->transform.zIndex = std::stoi(line.substr(index, line.find(",") - index));
                                ++compAdded;
                                continue;
                            }

                            break;
                        }

                        case 9: { // rotation
                            int i = line.find("rotation:");
                            if (i != std::string::npos) {
                                int index = i + 10;
                                gameObjects[numObjects]->sprite->transform.rotation = std::stof(line.substr(index, line.find(",") - index));
                                ++compAdded;
                                continue;
                            }

                            break;
                        }

                        // ---------------------------

                        case 10: { // End of GameObject
                            addToSrc = 0;
                            compAdded = 0;
                            ++addedObjects;
                            ++numObjects;
                        }
                    }

                } else if (line.find("GameObject:") != std::string::npos) {
                    addToSrc = 1;
                }
            }

        } catch (...) {
            std::cout << "Fun error\n"; // todo add error message from systemmessages.h
        }
    };

    // * ================================================
}
