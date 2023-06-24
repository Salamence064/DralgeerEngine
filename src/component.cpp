// ? Contain the definitions for components which need to access information about the current scene here.

#include <Zeta2D/zmath2D.h>
#include <utility>
#include <IMGUI/imgui.h>
#include <Dralgeer/editor.h>
#include <Dralgeer/listeners.h>
#include <Dralgeer/window.h>

namespace Dralgeer {
    // * =====================================================================
    // * SpriteRenderer Stuff

    SpriteRenderer::SpriteRenderer() { type = ComponentType::SPRITE_RENDERER; id = idCounter++; };

    // * ====================
    // * Rule of 5 Stuff
    // * ====================

    SpriteRenderer::SpriteRenderer(SpriteRenderer const &spr) : color(spr.color), lastTransform(spr.lastTransform) {
        type = spr.type;
        id = idCounter++;

        imGuiSetup = 1;
        isDirty = 1;

        if (spr.sprite.texture) {
            sprite.width = spr.sprite.width;
            sprite.height = spr.sprite.height;
            sprite.texture = new Texture();
            sprite.texture->init(spr.sprite.texture->filepath);
        }

        if (spr.gameObject) {
            gameObject = new GameObject();
            gameObject->transform = spr.gameObject->transform;
            gameObject->name = spr.gameObject->name;
        }
    };

    SpriteRenderer::SpriteRenderer(SpriteRenderer &&spr) : color(std::move(spr.color)), lastTransform(std::move(spr.lastTransform)) {
        type = spr.type;
        id = idCounter++;

        imGuiSetup = 1;
        isDirty = 1;

        sprite.width = spr.sprite.width;
        sprite.height = spr.sprite.height;
        sprite.texture = spr.sprite.texture;
        spr.sprite.texture = NULL;

        gameObject = spr.gameObject;
        spr.gameObject = NULL;
    };

    SpriteRenderer& SpriteRenderer::operator = (SpriteRenderer const &spr) {
        if (this != &spr) {
            type = spr.type;
            color = spr.color;
            lastTransform = spr.lastTransform;
            imGuiSetup = 1;
            isDirty = 1;

            sprite.width = spr.sprite.width;
            sprite.height = spr.sprite.height;
            sprite.texture = new Texture();
            sprite.texture->init(spr.sprite.texture->filepath);

            if (gameObject) { delete gameObject; gameObject = nullptr; }
            if (spr.gameObject) {
                gameObject = new GameObject();
                gameObject->transform = spr.gameObject->transform;
                gameObject->name = spr.gameObject->name;
            }
        }

        return *this;
    };

    SpriteRenderer& SpriteRenderer::operator = (SpriteRenderer &&spr) {
        if (this != &spr) { // ensure it is not self assignment
            type = spr.type;
            color = std::move(spr.color);
            lastTransform = std::move(spr.lastTransform);
            imGuiSetup = 1;
            isDirty = 1;

            sprite.width = spr.sprite.width;
            sprite.height = spr.sprite.height;
            sprite.texture = spr.sprite.texture;
            spr.sprite.texture = NULL;

            gameObject = spr.gameObject;
            spr.gameObject = NULL;
        }

        return *this;
    };

    SpriteRenderer::~SpriteRenderer() {
        if (sprite.texture != nullptr) { delete sprite.texture; }
        if (gameObject) { delete gameObject; }
    };


    // * ====================
    // * Normal Functions
    // * ====================

    inline void SpriteRenderer::start() { lastTransform = gameObject->transform; };

    inline void SpriteRenderer::update(float dt) {
        if (lastTransform != gameObject->transform) {
            gameObject->transform = lastTransform;
            isDirty = 1;
        }
    };

    void SpriteRenderer::imGui() {
        if (imGuiSetup) {
            ImGui::SetWindowPos(ImVec2(IMGUI_COLOR_PICKER_X, IMGUI_COLOR_PCIKER_Y));
            ImGui::SetWindowSize(ImVec2(IMGUI_COLOR_PICKER_WIDTH, IMGUI_COLOR_PCIKER_HEIGHT));
            imGuiSetup = 0;
        }

        if (DImGui::colorPicker4("Color Picker", color)) { isDirty = 1; }
    };

    // * =====================================================================
    // * EditorCamera Stuff

    EditorCamera::EditorCamera(Camera const &cam) {
        type = ComponentType::EDITOR_CAMERA;
        id = idCounter++;
        camera = cam;
    };

    // * ====================
    // * Rule of 5 Stuff
    // * ====================

    EditorCamera::EditorCamera(EditorCamera const &cam) {
        id = idCounter++;
        type = cam.type;
        camera = cam.camera;

        if (cam.gameObject) {
            gameObject = new GameObject();
            gameObject->transform = cam.gameObject->transform;
            gameObject->name = cam.gameObject->name;
        }
    };

    EditorCamera::EditorCamera(EditorCamera &&cam) {
        id = idCounter++;
        type = cam.type;
        camera = std::move(cam.camera);
        gameObject = cam.gameObject;
        cam.gameObject = NULL;
    };

    EditorCamera& EditorCamera::operator = (EditorCamera const &cam) {
        if (this != &cam) {
            clickOrigin = {0, 0};
            dragDebounce = 0.032f;
            lerpTime = 0.0f;
            reset = 0;
            camera = cam.camera;

            if (gameObject) { delete gameObject; gameObject = nullptr; }
            if (cam.gameObject) {
                gameObject = new GameObject();
                gameObject->transform = cam.gameObject->transform;
                gameObject->name = cam.gameObject->name;
            }
        }

        return *this;
    };

    EditorCamera& EditorCamera::operator = (EditorCamera &&cam) {
        if (this != &cam) {
            clickOrigin = {0, 0};
            dragDebounce = 0.032f;
            lerpTime = 0.0f;
            reset = 0;

            camera = std::move(cam.camera);
            gameObject = cam.gameObject;
            cam.gameObject = NULL;
        }

        return *this;
    };

    EditorCamera::~EditorCamera() { delete gameObject; };


    // * =====================
    // * Normal Functions
    // * =====================

    inline void EditorCamera::update(float dt) {
        if (!Window::imGuiLayer.gameViewWindow.getWantCaptureMouse()) { return; }

        if (MouseListener::mButtonPressed[GLFW_MOUSE_BUTTON_LEFT] && dragDebounce > 0.0f) {
            clickOrigin = {MouseListener::mWorldX, MouseListener::mWorldY};
            dragDebounce -= dt;
            return;
        }

        if (MouseListener::mButtonPressed[GLFW_MOUSE_BUTTON_LEFT]) {
            glm::vec2 mousePos(MouseListener::mWorldX, MouseListener::mWorldY);
            glm::vec2 delta = mousePos - clickOrigin;
            camera.pos -= delta * (dt * EDITOR_DRAG_SENSITIVITY);

            // interpolate
            clickOrigin.x += (mousePos.x - clickOrigin.x) * dt;
            clickOrigin.y += (mousePos.y - clickOrigin.y) * dt;

        } else if (dragDebounce <= 0.0f) {
            dragDebounce = 0.032f;
        }

        if (!ZMath::compare(MouseListener::mScrollY, 0.0f)) {
            float addValue = powf(std::fabs(MouseListener::mScrollY * EDITOR_SCROLL_SENSITIVITY), 1/camera.zoom);
            camera.zoom += addValue * -SIGNOF(MouseListener::mScrollY);
        }

        if (reset) {
            // interpolate
            camera.pos.x -= camera.pos.x * dt;
            camera.pos.y -= camera.pos.y * dt;

            camera.zoom += ((1.0f - camera.zoom) * lerpTime);
            lerpTime += 0.1f * dt;

            if (std::fabs(camera.pos.x) <= 5.0f && std::fabs(camera.pos.y) <= 5.0f) {
                camera.pos = {0, 0};
                camera.zoom = 1.0f;
                lerpTime = 0.0f;
                reset = 0;
            }

        } else if (KeyListener::keyPressed[GLFW_KEY_TAB]) {
            reset = 1;
        }
    };


    // * =====================================================================
    // * GridLines Stuff

    GridLines::GridLines() { type = ComponentType::GRID_LINES; id = idCounter++; };

    // * ====================
    // * Rule of 5 Stuff
    // * ====================

    GridLines::GridLines(GridLines const &gl) {
        type = gl.type;
        id = idCounter++;

        if (gl.gameObject) {
            gameObject = new GameObject();
            gameObject->transform = gl.gameObject->transform;
            gameObject->name = gl.gameObject->name;
        }
    };

    GridLines::GridLines(GridLines &&gl) {
        type = gl.type;
        id = idCounter++;
        gameObject = gl.gameObject;
        gl.gameObject = NULL;
    };

    GridLines& GridLines::operator = (GridLines const &gl) {
        if (this != &gl) {
            if (gameObject) { delete gameObject; }
            if (gl.gameObject) {
                gameObject = new GameObject();
                gameObject->transform = gl.gameObject->transform;
                gameObject->name = gl.gameObject->name;
            }
        }

        return *this;
    };

    GridLines& GridLines::operator = (GridLines &&gl) {
        gameObject = gl.gameObject;
        gl.gameObject = NULL;
        return *this;
    };

    GridLines::~GridLines() { delete gameObject; };


    // * =====================
    // * Normal Functions
    // * =====================

    inline void GridLines::update(float dt) {
        Camera cam = Window::currScene->camera; // make the code more readable

        int firstX = ((int) (cam.pos.x * cam.zoom) - GRID_WIDTH);
        int firstY = ((int) (cam.pos.y * cam.zoom) - GRID_HEIGHT);
        int width = ((int) (cam.projSize.x * cam.zoom)) + 2 * GRID_WIDTH;
        int height = ((int) (cam.projSize.y * cam.zoom)) + 2 * GRID_HEIGHT;

        int vertLines = ((int) (cam.projSize.x * cam.zoom)/GRID_WIDTH) + 2;
        int horzLines = ((int) (cam.projSize.y * cam.zoom)/GRID_HEIGHT) + 2;

        int maxLines = MAX(vertLines, horzLines);
        glm::vec3 color(0.2f, 0.2f, 0.2f);

        for (int i = 0; i < maxLines; ++i) {
            int x = firstX + i*GRID_WIDTH;
            int y = firstY + i*GRID_HEIGHT;

            if (i < vertLines) { DebugDraw::addLine2D(glm::vec2(x, firstX), glm::vec2(x, firstY + height), color); }
            if (i < horzLines) { DebugDraw::addLine2D(glm::vec2(firstX, y), glm::vec2(firstX + width, y), color); }
        }
    };

    // * =====================================================================
    // * GameObject Stuff

    // * ====================
    // * Rule of 5 Stuff
    // * ====================

    GameObject::GameObject() {
        components = new Component*[8];
        id = idCounter++;
    };

    GameObject::GameObject(GameObject const &go) : name(go.name), serialize(go.serialize), transform(go.transform) {
        id = idCounter++;
        dead = 0;

        capacity = go.capacity;
        numComponents = go.numComponents;
        components = new Component*[capacity];

        for (int i = 0; i < numComponents; ++i) {
            switch (go.components[i]->type) {
                case ComponentType::SPRITE_RENDERER: { components[i] = new SpriteRenderer(*((SpriteRenderer*) go.components[i])); }
                case ComponentType::EDITOR_CAMERA: { components[i] = new EditorCamera(*((EditorCamera*) go.components[i])); }
                case ComponentType::GRID_LINES: { components[i] = new GridLines(*((GridLines*) go.components[i])); }
            }
        }
    };

    GameObject::GameObject(GameObject &&go) : name(std::move(go.name)), serialize(go.serialize), transform(std::move(go.transform)) {
        id = idCounter++;
        dead = 0;

        capacity = go.capacity;
        numComponents = go.numComponents;
        components = go.components;
        go.components = NULL;
    };

    GameObject& GameObject::operator = (GameObject const &go) {
        if (this != &go) {
            name = go.name;
            transform = go.transform;
            serialize = go.serialize;
            
            for (int i = 0; i < numComponents; ++i) { delete components[i]; }
            delete[] components;

            capacity = go.capacity;
            numComponents = go.numComponents;
            components = new Component*[capacity];

            for (int i = 0; i < numComponents; ++i) {
                switch (go.components[i]->type) {
                    case ComponentType::SPRITE_RENDERER: { components[i] = new SpriteRenderer(*((SpriteRenderer*) go.components[i])); }
                    case ComponentType::EDITOR_CAMERA: { components[i] = new EditorCamera(*((EditorCamera*) go.components[i])); }
                    case ComponentType::GRID_LINES: { components[i] = new GridLines(*((GridLines*) go.components[i])); }
                }
            }
        }

        return *this;
    };

    GameObject& GameObject::operator = (GameObject &&go) {
        if (this != &go) { // ensure there is not self assignment
            name = std::move(go.name);
            transform = std::move(go.transform);
            serialize = go.serialize;

            capacity = go.capacity;
            numComponents = go.numComponents;
            components = go.components;
            go.components = NULL;
        }

        return *this;
    };

    GameObject::~GameObject() {
        for (int i = 0; i < numComponents; ++i) { delete components[i]; }
        delete[] components;
    };


    // * =====================
    // * Normal Functions
    // * =====================

    inline void* GameObject::getComponent(ComponentType type) {
        for (int i = 0; i < numComponents; ++i) {
            if (type == components[i]->type) { return components[i]; }
        }

        return nullptr;
    };

    inline void GameObject::removeComponent(ComponentType type) {
        for (int i = 0; i < numComponents; ++i) {
            if (type == components[i]->type) {
                delete components[i];
                numComponents--;
                for (int j = i; j < numComponents; ++j) { components[j] = components[j + 1]; }
                return;
            }
        }
    };

    inline void GameObject::addComponent(Component* c) {
        if (numComponents == capacity) {
            capacity *= 2;

            Component** temp = new Component*[capacity];
            for (int i = 0; i < numComponents; ++i) { temp[i] = components[i]; }
            
            delete[] components;
            components = temp;
        }

        components[numComponents++] = c;
    };

    inline void GameObject::start() { for (int i = 0; i < numComponents; ++i) { components[i]->start(); }};
    inline void GameObject::destory() { for (int i = 0; i < numComponents; ++i) { components[i]->destroy(); }};
    inline void GameObject::imGui() { for (int i = 0; i < numComponents; ++i) { components[i]->imGui(); }};
    inline void GameObject::update(float dt) { for (int i = 0; i < numComponents; ++i) { components[i]->update(dt); }};

    // * =====================================================================
}
