#define IMGUI_DISABLE_OBSOLETE_FUNCTIONS
#include <Dralgeer/scene.h>
#include <IMGUI/imgui.h>
#include <Dralgeer/prefabs.h>
#include <Dralgeer/assetpool.h>
#include <Dralgeer/gizmo.h>

namespace Dralgeer {
    // * ================================================
    // * Abstract Scene Class

    void Scene::update(float dt, bool wantCapture) {
        camera.adjustProjection();

        // std::cout << "\n========================================\n";
        // std::cout << "[GameObjects]\n";

        for (int i = numObjects - 1; i >= 0; --i) {
            gameObjects[i]->update(dt, camera, wantCapture);

            // SpriteRenderer* spr = (SpriteRenderer*) gameObjects[i]->getComponent(SPRITE_RENDERER);

            // if (spr) {
            //     std::cout << "\nGameObject: " <<  gameObjects[i]->name << " " << spr->gameObject->id << "\n";
            //     std::cout << "\tPos: " << spr->gameObject->transform.pos.x << ", " << spr->gameObject->transform.pos.y << "\n";
            //     std::cout << "\tScale: " << spr->gameObject->transform.scale.x << ", " << spr->gameObject->transform.scale.y << "\n";
            //     std::cout << "\tFilepath: " << spr->sprite.texture->filepath << "\n";
            //     std::cout << "\tzIndex: " << spr->gameObject->transform.zIndex << "\n";
            // }

            if (gameObjects[i]->dead) {
                Renderer::destroy((SpriteRenderer*) gameObjects[i]->getComponent(SPRITE_RENDERER));
                for (int j = i; j < numObjects - 1; ++j) { gameObjects[j] = gameObjects[j + 1]; }
                numObjects--;
            }
        }

        // std::cout << "\n========================================\n";
    };

    // * ================================================
    // * LevelEditorScene

    inline void LevelEditorScene::loadResources() {
        SpriteSheet* spr = new SpriteSheet();
        spr->init(AssetPool::getTexture("../../assets/images/spritesheets/decorationsAndBlocks.png"), 16, 16, 81, 0);
        AssetPool::addSpriteSheet("../../assets/images/spritesheets/decorationsAndBlocks.png", spr);

        SpriteSheet* gizmoSpr = new SpriteSheet();
        gizmoSpr->init(AssetPool::getTexture("../../assets/images/gizmos.png"), 24, 48, 3, 0);
        AssetPool::addSpriteSheet("../../assets/images/gizmos.png", gizmoSpr);

        // todo for testing purposes
        // SpriteRenderer* testSpr = new SpriteRenderer();
        // testSpr->sprite.texture = new Texture();
        // testSpr->sprite.texture->init("../../assets/images/wall.jpg");
        // testSpr->sprite.width = testSpr->sprite.texture->width;
        // testSpr->sprite.height = testSpr->sprite.texture->height;
        // testSpr->color = {0.8824f, 0.0039f, 0.0039f, 1.0f};
        // testSpr->gameObject = new GameObject();
        // testSpr->gameObject->transform.pos = {100.0f, 100.0f};
        // testSpr->gameObject->name = "ThisIsATest";
        // testSpr->gameObject->transform.scale = {300.0f, 300.0f};
        // testSpr->gameObject->transform.zIndex = 1;
        // testSpr->start();

        // Renderer::add(testSpr);

        // for (int i = 0; i < spr->numSprites; ++i) {
        //     SpriteRenderer* testSpr = new SpriteRenderer();
        //     testSpr->sprite.texture = spr->sprites[i].texture;
        //     testSpr->sprite.height = spr->sprites[i].height;
        //     testSpr->sprite.width = spr->sprites[i].width;
        //     testSpr->sprite.texCoords[0] = spr->sprites[i].texCoords[0];
        //     testSpr->sprite.texCoords[1] = spr->sprites[i].texCoords[1];
        //     testSpr->sprite.texCoords[2] = spr->sprites[i].texCoords[2];
        //     testSpr->sprite.texCoords[3] = spr->sprites[i].texCoords[3];
        //     testSpr->color = {1.0f, 1.0f, 1.0f, 1.0f};
        //     testSpr->gameObject = new GameObject();
        //     testSpr->gameObject->name = "Test";
        //     testSpr->gameObject->transform.pos = {16*i - 16*(i%16), 16*(i%16)};
        //     testSpr->gameObject->transform.scale = {16.0f, 16.0f};
        //     testSpr->gameObject->transform.zIndex = 0;
        //     testSpr->start();

        //     Renderer::add(testSpr);
        // }

        // todo ================================================================

        for (int i = 0; i < numObjects; ++i) {
            SpriteRenderer* spr = (SpriteRenderer*) gameObjects[i]->getComponent(SPRITE_RENDERER);
            if (spr && spr->sprite.texture) { AssetPool::addTexture(spr->sprite.texture->filepath, spr->sprite.texture); }
        }
    };

    LevelEditorScene::LevelEditorScene() {
        type = LEVEL_EDITOR_SCENE;
        gameObjects = new GameObject*[capacity];
    };

    LevelEditorScene::LevelEditorScene(LevelEditorScene const &scene) {
        type = scene.type;
        camera = scene.camera;
        sprites = scene.sprites;
        components = scene.components;
        
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
        type = scene.type;
        camera = std::move(scene.camera);
        components = std::move(scene.components);
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
            sprites = scene.sprites;
            components = scene.components;

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

            if (sprites) { delete sprites; }

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
            components = std::move(scene.components);
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
        camera.pos = glm::vec2(0.0f, 0.0f);
        camera.adjustProjection();
        camera.adjustView();

        loadResources();

        // load sprite sheet
        sprites = AssetPool::getSpriteSheet("../../assets/images/spritesheets/decorationsAndBlocks.png");

        components.name = "LevelEditor";
        components.transform.zIndex = 0;
        components.transform.pos = {0.0f, 0.0f};
        components.transform.scale = {0.0f, 0.0f};
        components.serialize = 0;

        components.addComponent(new MouseControls());
        components.addComponent(new GridLines());
        components.addComponent(new EditorCamera(camera));
        components.addComponent(new GizmoSystem(AssetPool::getSpriteSheet("../../assets/images/gizmos.png")));

        addGameObject(&components);
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

                // SpriteRenderer* s = (SpriteRenderer*) go->getComponent(SPRITE_RENDERER);
                // std::cout << s->gameObject->transform.scale.x << ", " << s->gameObject->transform.scale.y << "\n";

                ((MouseControls*) components.getComponent(MOUSE_CONTROLS))->heldObject = go;
            }

            ImGui::PopID();

            ImVec2 lastButtonPos = ImGui::GetItemRectMax();
            if (i + 1 < sprites->numSprites && lastButtonPos.x + itemSpacing.x + spriteWidth < windowX2) { ImGui::SameLine(); }
        }

        ImGui::End();

        // handle click and drag (maybe should move where in the code this occurs)
        // MouseControls* mc = (MouseControls*) components.getComponent(MOUSE_CONTROLS);
        // if (mc->addObject) {
        //     Sprite sprite = ((SpriteRenderer*) (mc->heldObject->getComponent(SPRITE_RENDERER)))->sprite;

        //     GameObject* go = Prefabs::generateSpriteObject(sprite, GRID_WIDTH, GRID_HEIGHT);
        //     SpriteRenderer* spr = (SpriteRenderer*) go->getComponent(SPRITE_RENDERER);
        //     spr->gameObject->transform.pos = mc->heldObject->transform.pos;
        //     spr->lastTransform.pos = spr->gameObject->transform.pos;

        //     addGameObject(go);
        //     mc->addObject = 0;
        // }
    };

    #pragma GCC diagnostic pop

    // * ================================================
}
