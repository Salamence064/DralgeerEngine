// ? Contain the definitions for components which need to access information about the current scene here.

#include <Zeta2D/zmath2D.h>
#include <utility>
#include <Dralgeer/dimgui.h>
#include <Dralgeer/editor.h>
#include <Dralgeer/listeners.h>
#include <Dralgeer/debugdraw.h>
#include <Dralgeer/prefabs.h>

namespace Dralgeer {
    // * =====================================================================
    // * ID Counters
    namespace IDCounter { int componentID = 0, gameObjectID = 0; }

    // * =====================================================================
    // * SpriteRenderer Stuff

    SpriteRenderer::SpriteRenderer() { type = ComponentType::SPRITE_RENDERER; id = IDCounter::componentID++; };

    // * ====================
    // * Rule of 5 Stuff
    // * ====================

    SpriteRenderer::SpriteRenderer(SpriteRenderer const &spr) : color(spr.color), lastTransform(spr.lastTransform) {
        type = spr.type;
        id = IDCounter::componentID++;

        imGuiSetup = 1;
        isDirty = 1;

        sprite.width = spr.sprite.width;
        sprite.height = spr.sprite.height;
        sprite.texCoords[0] = spr.sprite.texCoords[0];
        sprite.texCoords[1] = spr.sprite.texCoords[1];
        sprite.texCoords[2] = spr.sprite.texCoords[2];
        sprite.texCoords[3] = spr.sprite.texCoords[3];
        sprite.texture = spr.sprite.texture;

        if (spr.gameObject) {
            gameObject = new GameObject();
            gameObject->transform = spr.gameObject->transform;
            gameObject->name = spr.gameObject->name;
        }
    };

    SpriteRenderer::SpriteRenderer(SpriteRenderer &&spr) : color(std::move(spr.color)), lastTransform(std::move(spr.lastTransform)) {
        type = spr.type;
        id = IDCounter::componentID++;

        imGuiSetup = 1;
        isDirty = 1;

        sprite.width = spr.sprite.width;
        sprite.height = spr.sprite.height;
        sprite.texture = spr.sprite.texture;
        sprite.texCoords[0] = spr.sprite.texCoords[0];
        sprite.texCoords[1] = spr.sprite.texCoords[1];
        sprite.texCoords[2] = spr.sprite.texCoords[2];
        sprite.texCoords[3] = spr.sprite.texCoords[3];
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
            sprite.texture = spr.sprite.texture;
            sprite.texCoords[0] = spr.sprite.texCoords[0];
            sprite.texCoords[1] = spr.sprite.texCoords[1];
            sprite.texCoords[2] = spr.sprite.texCoords[2];
            sprite.texCoords[3] = spr.sprite.texCoords[3];

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
            sprite.texCoords[0] = spr.sprite.texCoords[0];
            sprite.texCoords[1] = spr.sprite.texCoords[1];
            sprite.texCoords[2] = spr.sprite.texCoords[2];
            sprite.texCoords[3] = spr.sprite.texCoords[3];
            spr.sprite.texture = NULL;

            if (gameObject) { delete gameObject; }
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
    
    void SpriteRenderer::update(float dt, Camera const &cam, bool wantCapture) {
        if (gameObject && lastTransform != gameObject->transform) { // todo I have no idea what this is doing but it doesn't work without it
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
        id = IDCounter::componentID++;
        camera = cam;
    };

    // * ====================
    // * Rule of 5 Stuff
    // * ====================

    EditorCamera::EditorCamera(EditorCamera const &cam) {
        id = IDCounter::componentID++;
        type = cam.type;
        camera = cam.camera;

        if (cam.gameObject) {
            gameObject = new GameObject();
            gameObject->transform = cam.gameObject->transform;
            gameObject->name = cam.gameObject->name;
        }
    };

    EditorCamera::EditorCamera(EditorCamera &&cam) {
        id = IDCounter::componentID++;
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
            if (gameObject) { delete gameObject; }
            gameObject = cam.gameObject;
            cam.gameObject = NULL;
        }

        return *this;
    };

    EditorCamera::~EditorCamera() { delete gameObject; };


    // * =====================
    // * Normal Functions
    // * =====================

    void EditorCamera::update(float dt, Camera const &cam, bool wantCapture) {
        // todo this is probably not gonna work
        // todo it's getting close to the point where I will refactor it to use void* instead of the abstract class
        // todo and pass in a bool for the getWantCaptureMouse
        if (!wantCapture) { return; }

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

    GridLines::GridLines() { type = ComponentType::GRID_LINES; id = IDCounter::componentID++; };

    // * ====================
    // * Rule of 5 Stuff
    // * ====================

    GridLines::GridLines(GridLines const &gl) {
        type = gl.type;
        id = IDCounter::componentID++;

        if (gl.gameObject) {
            gameObject = new GameObject();
            gameObject->transform = gl.gameObject->transform;
            gameObject->name = gl.gameObject->name;
        }
    };

    GridLines::GridLines(GridLines &&gl) {
        type = gl.type;
        id = IDCounter::componentID++;
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
        if (this != &gl) {
            if (gameObject) { delete gameObject; }
            gameObject = gl.gameObject;
            gl.gameObject = NULL;
        }

        return *this;
    };

    GridLines::~GridLines() { delete gameObject; };


    // * =====================
    // * Normal Functions
    // * =====================

    void GridLines::update(float dt, Camera const &cam, bool wantCapture) {
        int firstX = ((int) (cam.pos.x * cam.zoom) - GRID_WIDTH);
        int firstY = ((int) (cam.pos.y * cam.zoom) - GRID_HEIGHT);
        int width = ((int) (cam.projSize.x * cam.zoom)) + 2 * GRID_WIDTH;
        int height = ((int) (cam.projSize.y * cam.zoom)) + 2 * GRID_HEIGHT;

        int vertLines = ((int) (cam.projSize.x * cam.zoom)/GRID_WIDTH) + 2;
        int horzLines = ((int) (cam.projSize.y * cam.zoom)/GRID_HEIGHT) + 2;

        int maxLines = MAX(vertLines, horzLines);
        // glm::vec3 color(0.8549f, 0.4392f, 0.8392f); // violet
        glm::vec3 color(0.8471f, 0.749f, 0.8471f); // thistle

        for (int i = 0; i < maxLines; ++i) {
            int x = firstX + i*GRID_WIDTH;
            int y = firstY + i*GRID_HEIGHT;

            if (i < vertLines) { DebugDraw::addLine2D(glm::vec2(x, firstX), glm::vec2(x, firstY + height), color, 1); }
            if (i < horzLines) { DebugDraw::addLine2D(glm::vec2(firstX, y), glm::vec2(firstX + width, y), color, 1); }
        }
    };

    // * =====================================================================
    // * MouseControls Stuff

    MouseControls::MouseControls() { type = MOUSE_CONTROLS; id = IDCounter::componentID++; };

    // * ====================
    // * Rule of 5 Stuff
    // * ====================

    MouseControls::MouseControls(MouseControls const &mc) {
        type = mc.type;
        id = IDCounter::componentID++;

        if (mc.gameObject) {
            gameObject = new GameObject();
            gameObject->transform = mc.gameObject->transform;
            gameObject->name = mc.gameObject->name;
        }
    };

    MouseControls::MouseControls(MouseControls &&mc) {
        type = mc.type;
        id = IDCounter::componentID++;
        gameObject = mc.gameObject;
        mc.gameObject = NULL;
    };

    MouseControls& MouseControls::operator = (MouseControls const &mc) {
        if (this != &mc) {
            if (gameObject) { delete gameObject; }
            if (mc.gameObject) {
                gameObject = new GameObject();
                gameObject->transform = mc.gameObject->transform;
                gameObject->name = mc.gameObject->name;
            }

            heldObject = nullptr; // since the object should be added to the scene this should not cause a memory leak
        }

        return *this;
    };

    MouseControls& MouseControls::operator = (MouseControls &&mc) {
        if (this != &mc) {
            if (gameObject) { delete gameObject; }
            gameObject = mc.gameObject;
            mc.gameObject = NULL;
        }

        return *this;
    };

    // Note, do not delete heldObject for the scene should handle that.
    MouseControls::~MouseControls() { if (gameObject) { delete gameObject; }};

    // * =====================
    // * Normal Functions
    // * =====================

    void MouseControls::update(float dt, Camera const &cam, bool wantCapture) {
        if (heldObject) {
            // todo the precision when placing sucks -- fix it by changing the values for this a little

            heldObject->transform.pos.x = (int) (MouseListener::mWorldX/GRID_WIDTH) * GRID_WIDTH;
            heldObject->transform.pos.y = (int) (MouseListener::mWorldY/GRID_HEIGHT) * GRID_HEIGHT;

            ((SpriteRenderer*) heldObject->getComponent(SPRITE_RENDERER))->gameObject->transform.pos = heldObject->transform.pos;
            
            // todo this currently adds an artifact sprite on the final placement (i.e. double places)
            // todo I will figure out how to eliminate this later
            // todo can place sprites over each other without overriding -- fix this (to override) in the future

            if (MouseListener::mButtonPressed[GLFW_MOUSE_BUTTON_LEFT]) {
                ((SpriteRenderer*) heldObject->getComponent(SPRITE_RENDERER))->lastTransform.pos = heldObject->transform.pos;

                // ! debugging code -----------------------------

                // glBindFramebuffer(GL_FRAMEBUFFER, fbo);

                // Transform t = ((SpriteRenderer*) heldObject->getComponent(SPRITE_RENDERER))->gameObject->transform;

                // DebugDraw::addLine2D(t.pos, glm::vec2(t.pos.x + t.scale.x, t.pos.y), glm::vec3(0.5, 1, 0));
                // DebugDraw::addLine2D(t.pos, glm::vec2(t.pos.x, t.pos.y + t.scale.y));
                // DebugDraw::addLine2D(glm::vec2(t.pos.x, t.pos.y + t.scale.y), t.pos + t.scale);
                // DebugDraw::addLine2D(glm::vec2(t.pos.x + t.scale.x, t.pos.y), t.pos + t.scale);

                // glBindFramebuffer(GL_FRAMEBUFFER, realFbo);

                // ! --------------------------------------------

                // std::cout << t.scale.x << ", " << t.scale.y << "\n";
                heldObject = nullptr;

                // handle click and drag
                // pressedLastFrame = 1;

                // for (int i = 0; i < pCount; ++i) {
                //     if (ZMath::compare(placedTiles[i].x, heldObject->transform.pos.x) &&
                //         ZMath::compare(placedTiles[i].y, heldObject->transform.pos.y))
                //     {
                //         return;
                //     }
                // }

                // if (pCount >= pCapacity) {
                //     pCapacity *= 2;
                //     glm::vec2* temp = new glm::vec2[pCapacity];

                //     for (int i = 0; i < pCount; ++i) { temp[i] = placedTiles[i]; }

                //     delete[] placedTiles;
                //     placedTiles = temp;
                // }

                // placedTiles[pCount++] = heldObject->transform.pos;
                // addObject = 1;
            }
            // } else if (pressedLastFrame && !MouseListener::mButtonPressed[GLFW_MOUSE_BUTTON_LEFT]) {
            //     ((SpriteRenderer*) heldObject->getComponent(SPRITE_RENDERER))->lastTransform.pos = heldObject->transform.pos;
            //     heldObject = nullptr;

            //     // reset click and drag info
            //     delete[] placedTiles;
            //     pCapacity = 16;
            //     pCount = 0;
            //     placedTiles = new glm::vec2[pCapacity];
            //     addObject = 0;
            //     pressedLastFrame = 0;
            // }
        }
    };

    // * =====================================================================
    // * GameObject Stuff

    // * ====================
    // * Rule of 5 Stuff
    // * ====================

    // todo fix the current gameobject systems. They kinda suck
    // todo well, specifically the rule of 5 operators do

    GameObject::GameObject() {
        components = new Component*[8];
        id = ++IDCounter::gameObjectID;
    };

    GameObject::GameObject(GameObject const &go) : name(go.name), serialize(go.serialize), transform(go.transform) {
        id = ++IDCounter::gameObjectID;
        dead = 0;

        capacity = go.capacity;
        numComponents = go.numComponents;
        components = new Component*[capacity];

        for (int i = 0; i < numComponents; ++i) {
            switch (go.components[i]->type) {
                case SPRITE_RENDERER: { components[i] = new SpriteRenderer(*((SpriteRenderer*) go.components[i])); break; }
                case EDITOR_CAMERA: { components[i] = new EditorCamera(*((EditorCamera*) go.components[i])); break; }
                case GRID_LINES: { components[i] = new GridLines(*((GridLines*) go.components[i])); break; }
                case MOUSE_CONTROLS: { components[i] = new MouseControls(*((MouseControls*) go.components[i])); break; }
            }
        }
    };

    GameObject::GameObject(GameObject &&go) : name(std::move(go.name)), serialize(go.serialize), transform(std::move(go.transform)) {
        id = ++IDCounter::gameObjectID;
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
                    case SPRITE_RENDERER: { components[i] = new SpriteRenderer(*((SpriteRenderer*) go.components[i])); break; }
                    case EDITOR_CAMERA: { components[i] = new EditorCamera(*((EditorCamera*) go.components[i])); break; }
                    case GRID_LINES: { components[i] = new GridLines(*((GridLines*) go.components[i])); break; }
                    case MOUSE_CONTROLS: { components[i] = new MouseControls(*((MouseControls*) go.components[i])); break; }
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

            for (int i = 0; i < numComponents; ++i) { delete components[i]; }
            delete[] components;

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

    // * =====================================================================
}
