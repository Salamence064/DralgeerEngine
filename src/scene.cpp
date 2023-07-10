// #define IMGUI_DISABLE_OBSOLETE_FUNCTIONS
#include <Dralgeer/scene.h>
#include <IMGUI/imgui.h>
#include <Dralgeer/prefabs.h>
#include <Dralgeer/assetpool.h>

namespace Dralgeer {
    // * ================================================
    // * Abstract Scene Class

    void Scene::update(float dt) {
        camera.adjustProjection();
        
        for (int i = numObjects - 1; i >= 0; --i) {
            gameObjects[i]->update(dt);

            if (gameObjects[i]->dead) {
                Renderer::destroy((SpriteRenderer*) gameObjects[i]->getComponent(SPRITE_RENDERER));
                for (int j = i; j < numObjects - 1; ++j) { gameObjects[j] = gameObjects[j + 1]; }
                numObjects--;
            }
        }
    };

    // * ================================================
    // * LevelEditorScene

    inline void LevelEditorScene::loadResources() {
        SpriteSheet* spr = new SpriteSheet();
        spr->init(AssetPool::getTexture("../../assets/images/spritesheets/decorationsAndBlocks.png"), 16, 16, 81, 0);

        AssetPool::addSpriteSheet("../../assets/images/spritesheets/decorationsAndBlocks.png", spr);

        // todo add gizmos

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
            if (spr && spr->sprite.texture) {
                Texture* temp = spr->sprite.texture;
                // todo if this doesn't work try playing around with making it a new Texture from dereferenced or just assigning it directly
                spr->sprite.texture = AssetPool::getTexture(temp->filepath);
                delete temp; // ! this is probably right
            }
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
        for (int i = 0; i < numObjects; ++i) { gameObjects[i] = scene.gameObjects[i]; }
    };

    LevelEditorScene::LevelEditorScene(LevelEditorScene &&scene) {
        type = scene.type;
        camera = std::move(scene.camera);
        sprites = std::move(scene.sprites);
        components = std::move(scene.components);

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

            capacity = scene.capacity;
            numObjects = scene.numObjects;

            gameObjects = new GameObject*[capacity];
            for (int i = 0; i < numObjects; ++i) { gameObjects[i] = scene.gameObjects[i]; }
        }

        return *this;
    };

    LevelEditorScene& LevelEditorScene::operator = (LevelEditorScene &&scene) {
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

    LevelEditorScene::~LevelEditorScene() { delete[] gameObjects; };

    void LevelEditorScene::init() {
        camera.pos = glm::vec2(0.0f, 0.0f);
        camera.adjustProjection();
        camera.adjustView();

        loadResources();

        // load sprite sheet
        // todo could try making the sprites thing a pointer just to see
        // todo sprites in the spritesheet never get added to the renderer (don't think that's the issue but could be worth trying)
        sprites = *(AssetPool::getSpriteSheet("../../assets/images/spritesheets/decorationsAndBlocks.png"));

        components.name = "LevelEditor";
        components.transform.zIndex = 0;
        components.transform.pos = {0.0f, 0.0f};
        components.transform.scale = {0.0f, 0.0f};
        components.serialize = 0;

        components.addComponent(new MouseControls());
        components.addComponent(new GridLines());
        components.addComponent(new EditorCamera(camera));

        addGameObject(&components);
    };

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
        
        for (int i = 0; i < sprites.numSprites; ++i) {
            // for readability
            Sprite sprite = sprites.sprites[i];

            // multiplying by an int is for scaling purposes
            float spriteWidth = sprite.width * 3;
            float spriteHeight = sprite.height * 3;

            // todo try displaying the sprites with the working renderer I have already to narrow down the issue
            ImGui::PushID(i);
            if (ImGui::ImageButton(&sprite.texture->texID, ImVec2(spriteWidth, spriteHeight),
                ImVec2(sprite.texCoords[2].x, sprite.texCoords[0].y), ImVec2(sprite.texCoords[0].x, sprite.texCoords[2].y)))
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

    // * ================================================
}
