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
        AssetPool::getShader("../../assets/shaders/default.glsl");

        SpriteSheet spr;
        spr.init(AssetPool::getTexture("../../assets/images/spritesheets/decorationsAndBlocks.png"), 16, 16, 81, 0);
        AssetPool::addSpriteSheet("../../assets/images/spritesheets/decorationsAndBlocks.png", spr);

        // todo add gizmos

        for (int i = 0; i < numObjects; ++i) {
            SpriteRenderer* spr = (SpriteRenderer*) gameObjects[i]->getComponent(SPRITE_RENDERER);
            if (spr && spr->sprite.texture) {
                Texture* temp = spr->sprite.texture;
                spr->sprite.texture = new Texture(AssetPool::getTexture(temp->filepath));
                delete temp;
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
        camera.adjustView();
        camera.adjustProjection();
        loadResources();

        // load sprite sheet
        sprites = AssetPool::getSpriteSheet("../../assets/images/spritesheets/decorationsAndBlocks.png");

        components.name = "LevelEditor";
        components.transform.zIndex = 0;
        components.transform.pos = {0.0f, 0.0f};
        components.transform.scale = {0.0f, 0.0f};
        components.serialize = 0;

        // todo add other components once they are created
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

            ImGui::PushID(i);
            // todo potentially use the more recent version of this function
            // todo the images are not being read properly from this function
            if (ImGui::ImageButton(&sprite.texture->texID, ImVec2(spriteWidth, spriteHeight),
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

    // * ================================================
}
