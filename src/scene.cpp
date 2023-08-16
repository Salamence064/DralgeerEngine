#define IMGUI_DISABLE_OBSOLETE_FUNCTIONS
#include <Dralgeer/scene.h>
#include <IMGUI/imgui.h>
#include <Dralgeer/prefabs.h>
#include <Dralgeer/assetpool.h>
#include <Dralgeer/gizmo.h>

// ! for testing
#include <Dralgeer/debugdraw.h>

namespace Dralgeer {
    // * ================================================
    // * Level Editor Class

    void LevelEditorScene::update(float &dt, bool wantCapture, bool physicsUpdate) {
        camera.adjustProjection();

        if (physicsUpdate) {
            physicsHandler.update(dt);

        } else {
            editorCamera.update(dt, wantCapture);
            gridLines.update(camera);
            mouseControls.update();
            gizmoSystem.update();
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

    LevelEditorScene::~LevelEditorScene() {
        for (int i = 0; i < numObjects; ++i) { delete gameObjects[i]; }
        delete[] gameObjects;
    };

    void LevelEditorScene::init() {
        renderer.start();

        camera.pos = glm::vec2(0.0f, 0.0f);
        camera.adjustProjection();
        camera.adjustView();

        loadResources();

        // load sprite sheet
        sprites = AssetPool::getSpriteSheet("../../assets/images/spritesheets/decorationsAndBlocks.png");

        editorCamera.init(camera);
        gizmoSystem.init(AssetPool::getSpriteSheet("../../assets/images/gizmos.png"));
        gizmoSystem.start();

        addGameObject(gizmoSystem.gizmos[TRANSLATE_GIZMO].xObject);
        addGameObject(gizmoSystem.gizmos[TRANSLATE_GIZMO].yObject);
        addGameObject(gizmoSystem.gizmos[SCALE_GIZMO].xObject);
        addGameObject(gizmoSystem.gizmos[SCALE_GIZMO].yObject);
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

    // * ================================================
}
