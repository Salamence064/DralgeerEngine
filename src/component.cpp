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

    void EditorCamera::update(float dt, bool wantCapture) {
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

    void GridLines::update(Camera const &cam) {
        int firstX = ((int) (cam.pos.x * cam.zoom) - GRID_WIDTH);
        int firstY = ((int) (cam.pos.y * cam.zoom) - GRID_HEIGHT);
        int width = ((int) (cam.projSize.x * cam.zoom)) + 2 * GRID_WIDTH;
        int height = ((int) (cam.projSize.y * cam.zoom)) + 2 * GRID_HEIGHT;

        int vertLines = ((int) (cam.projSize.x * cam.zoom)/GRID_WIDTH) + 2;
        int horzLines = ((int) (cam.projSize.y * cam.zoom)/GRID_HEIGHT) + 2;

        int maxLines = MAX(vertLines, horzLines);
        // glm::vec3 color(0.8549f, 0.4392f, 0.8392f); // violet
        glm::vec3 color(0.8471f, 0.749f, 0.8471f); // thistle

        // todo consider changing how the lines are handled since this would be a decent chunk of data moving between the GPU and CPU
        // todo  every frame
        for (int i = 0; i < maxLines; ++i) {
            int x = firstX + i*GRID_WIDTH;
            int y = firstY + i*GRID_HEIGHT;

            if (i < vertLines) { DebugDraw::addLine2D(glm::vec2(x, firstX), glm::vec2(x, firstY + height), color, 1); }
            if (i < horzLines) { DebugDraw::addLine2D(glm::vec2(firstX, y), glm::vec2(firstX + width, y), color, 1); }
        }
    };

    // * =====================================================================
    // * MouseControls Stuff

    MouseControls::MouseControls() { id = IDCounter::componentID++; };

    // * ==========================
    // * Rule of 5 Stuff (Kinda)
    // * ==========================

    MouseControls& MouseControls::operator = (MouseControls const &mc) {
        if (this != &mc) {
            heldObject = nullptr; // since the object should be added to the scene this should not cause a memory leak
        }

        return *this;
    };

    MouseControls& MouseControls::operator = (MouseControls &&mc) {
        if (this != &mc) {
            heldObject = nullptr; // since the object should be added to the scene this should not cause a memory leak
        }

        return *this;
    };

    // Note, do not delete heldObject for the scene should handle that.

    // * =====================
    // * Normal Functions
    // * =====================

    void MouseControls::update() {
        if (heldObject) {
            heldObject->transform.pos.x = (int) (MouseListener::mWorldX/GRID_WIDTH) * GRID_WIDTH;
            heldObject->transform.pos.y = (int) (MouseListener::mWorldY/GRID_HEIGHT) * GRID_HEIGHT;

            heldObject->sprite->transform.pos = heldObject->transform.pos;
            
            // todo this currently adds an artifact sprite on the final placement (i.e. double places)
            // todo I will figure out how to eliminate this later
            // todo can place sprites over each other without overriding -- fix this (to override) in the future

            if (MouseListener::mButtonPressed[GLFW_MOUSE_BUTTON_LEFT]) {
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

    GameObject::GameObject(GameObject const &go) : name(go.name), serialize(go.serialize), transform(go.transform) {
        id = ++IDCounter::gameObjectID;
        sprite = new SpriteRenderer(*go.sprite);
    };

    GameObject::GameObject(GameObject &&go) : name(std::move(go.name)), serialize(go.serialize), transform(std::move(go.transform)) {
        id = ++IDCounter::gameObjectID;
        sprite = go.sprite;
        go.sprite = nullptr;
    };

    GameObject& GameObject::operator = (GameObject const &go) {
        if (this != &go) {
            name = go.name;
            transform = go.transform;
            serialize = go.serialize;
            sprite = new SpriteRenderer(*go.sprite);
        }

        return *this;
    };

    GameObject& GameObject::operator = (GameObject &&go) {
        if (this != &go) { // ensure there is not self assignment
            name = std::move(go.name);
            transform = std::move(go.transform);
            serialize = go.serialize;
            sprite = go.sprite;
            go.sprite = nullptr;
        }

        return *this;
    };

    // * =====================================================================
}
