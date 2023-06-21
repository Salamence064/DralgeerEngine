#ifndef COMPONENT_H
#define COMPONENT_H

#include <Zeta2D/zmath2D.h>
#include <utility>
#include "sprite.h"
#include "listeners.h"
#include "camera.h"

namespace Dralgeer {
    // * ===========================
    // * Abstract Component Class
    // * ===========================

    enum ComponentType {
        SPRITE_RENDERER,
        EDITOR_CAMERA,
        GRID_LINES
    };

    // todo maybe find a way to do stuff with just a flag inside of this class
        // ! This would probably be ideal seeing as we have to store it like that already
        // ! The only hurdle left would be storing the unique data for the different subclasses as inside functions we can use a switch
    // * Implement rule of 5 for anything that extends this.
    class Component {
        protected:
            int idCounter = 0;

        public:
            ComponentType type;

            int id;
            GameObject* gameObject = nullptr; // Has to be a pointer due to forward declaration. // ! do not serialize

            // todo test if this use of virtual functions works
            virtual inline void start() {}; // by default doesn't do anything, but can be overriden.
            virtual inline void update(float dt) = 0; // every component needs to override update.
            virtual inline void destroy() {}; // by default doesn't do anything, but can be overriden.
    };


    // * ====================
    // * Game Object Stuff
    // * ====================

    struct Transform {
        glm::vec2 pos;
        glm::vec2 scale;

        int zIndex;
        float rotation = 0.0f;

        inline bool operator == (Transform const &t) const { return pos == t.pos && scale == t.scale && zIndex == t.zIndex && rotation == t.rotation; };
        inline bool operator != (Transform const &t) const { return pos != t.pos || scale != t.scale || zIndex != t.zIndex || rotation != t.rotation; };
    };

    class GameObject {
        private:
            int idCounter = 0; // used to track the game object's ID
            Component** components = nullptr;
            int capacity = 8; // start with 8 slots for components // todo probs up this later
            int numComponents = 0;

        public:
            // * ==============
            // * Attributes
            // * ==============

            int id;
            std::string name;
            Transform transform; // ! DO NOT serialize

            bool serialize = 1; // ! DO NOT serialize
            bool dead = 0; // ! DO NOT serialize
            
            // * ===============================================

            GameObject() {
                components = new Component*[8];
                id = idCounter++;
            };


            // * ====================
            // * Rule of 5 Stuff
            // * ====================

            GameObject(GameObject const &go) : name(go.name), serialize(go.serialize), transform(go.transform) {
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

            GameObject(GameObject &&go) : name(std::move(go.name)), serialize(go.serialize), transform(std::move(go.transform)) {
                id = idCounter++;
                dead = 0;

                capacity = go.capacity;
                numComponents = go.numComponents;
                components = go.components;
                go.components = NULL;
            };

            GameObject& operator = (GameObject const &go) {
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

            GameObject& operator = (GameObject &&go) {
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

            ~GameObject() {
                for (int i = 0; i < numComponents; ++i) { delete components[i]; }
                delete[] components;
            };


            // * ====================
            // * Normal Functions
            // * ====================

            template <typename T> inline T* getComponent(ComponentType type) {
                for (int i = 0; i < numComponents; ++i) {
                    if (type == components[i]->type) { return (T*) components[i]; }
                }

                return nullptr;
            };

            template <typename T> inline void removeComponent(ComponentType type) {
                for (int i = 0; i < numComponents; ++i) {
                    if (type == components[i]->type) {
                        delete components[i];
                        numComponents--;
                        for (int j = i; j < numComponents; ++j) { components[j] = components[j + 1]; }
                        return;
                    }
                }
            };

            inline void addComponent(Component* c) {
                if (numComponents == capacity) {
                    capacity *= 2;

                    Component** temp = new Component*[capacity];
                    for (int i = 0; i < numComponents; ++i) { temp[i] = components[i]; }
                    
                    delete[] components;
                    components = temp;
                }

                components[numComponents++] = c;
            };

            inline void start() { for (int i = 0; i < numComponents; ++i) { components[i]->start(); }};
            inline void destory() { for (int i = 0; i < numComponents; ++i) { components[i]->destroy(); }};
            inline void update(float dt) { for (int i = 0; i < numComponents; ++i) { components[i]->update(dt); }};
    };


    // * ==================
    // * Components
    // * ==================

    // * Remember to set isDirty to true if you change either the sprite or the color.
    class SpriteRenderer : public Component {
        private:
            bool imGuiSetup = 1; // ! DO NOT serialize

        public:
            // * ==============
            // * Attributes
            // * ==============

            glm::vec4 color = glm::vec4(1, 1, 1, 1); // for some reason it doesn't work unless I have the equals
            Sprite sprite;

            Transform lastTransform; // ! DO NOT serialize
            bool isDirty = 1; // ! DO NOT serialize

            // * ==========================================================

            SpriteRenderer() { type = ComponentType::SPRITE_RENDERER; id = idCounter++; }; // todo test if you need to do = SpriteRenderer(); or not for default
            
            
            // * =====================
            // * Rule of 5 stuff
            // * =====================
            
            // * Note, components attached to spr's GameObject will not be attached to the GameObject contained in this.
            SpriteRenderer(SpriteRenderer const &spr) : color(spr.color), lastTransform(spr.lastTransform) {
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

            SpriteRenderer(SpriteRenderer &&spr) : color(std::move(spr.color)), lastTransform(std::move(spr.lastTransform)) {
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

            // * Note, components attached to spr's GameObject will not be attached to the GameObject contained in this.
            SpriteRenderer& operator = (SpriteRenderer const &spr) {
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

            SpriteRenderer& operator = (SpriteRenderer &&spr) {
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

            ~SpriteRenderer() {
                if (sprite.texture != nullptr) { delete sprite.texture; }
                if (gameObject) { delete gameObject; }
            };


            // * ====================
            // * Normal Functions
            // * ====================

            inline void start() override { lastTransform = gameObject->transform; };

            inline void update(float dt) override {
                if (lastTransform != gameObject->transform) {
                    gameObject->transform = lastTransform;
                    isDirty = 1;
                }
            };
    };

    class EditorCamera : public Component {
        private:
            float dragDebounce = 0.032f;
            float lerpTime = 0.0f;
            bool reset = 0;

            Camera camera;
            glm::vec2 clickOrigin;

        public:
            EditorCamera() { type = ComponentType::EDITOR_CAMERA; id = idCounter++; };

            // * ===================
            // * Rule of 5 Stuff
            // * ===================

            // * Note, components attached to cam's GameObject will not be attached to the GameObject contained in this.
            EditorCamera(EditorCamera const &cam) {
                id = idCounter++;
                type = cam.type;
                camera = cam.camera;

                if (cam.gameObject) {
                    gameObject = new GameObject();
                    gameObject->transform = cam.gameObject->transform;
                    gameObject->name = cam.gameObject->name;
                }
            };

            EditorCamera(EditorCamera &&cam) {
                id = idCounter++;
                type = cam.type;
                camera = std::move(cam.camera);
                gameObject = cam.gameObject;
                cam.gameObject = NULL;
            };

            // * Note, components attached to cam's GameObject will not be attached to the GameObject contained in this.
            EditorCamera& operator = (EditorCamera const &cam) {
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

            EditorCamera& operator = (EditorCamera &&cam) {
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

            ~EditorCamera() { delete gameObject; };


            // * ===================
            // * Normal Functions
            // * ===================

            inline void update(float dt) override {
                // todo check if the ImGui layer in the window wants to be updated (will have to add the thing to the window first though)

                if (MouseListener::mButtonPressed[GLFW_MOUSE_BUTTON_LEFT] && dragDebounce > 0.0f) {
                    clickOrigin = {MouseListener::mWorldX, MouseListener::mWorldY};
                    dragDebounce -= dt;
                    return;
                }

                if (MouseListener::mButtonPressed[GLFW_MOUSE_BUTTON_LEFT]) {
                    glm::vec2 mousePos(MouseListener::mWorldX, MouseListener::mWorldY);
                    glm::vec2 delta = mousePos - clickOrigin;
                    camera.pos -= delta * (dt * EDITOR_DRAG_SENSITIVITY);
                    clickOrigin = glm::mix<glm::vec2, float>(clickOrigin, mousePos, dt);

                } else if (dragDebounce <= 0.0f) {
                    dragDebounce = 0.032f;
                }

                if (!ZMath::compare(MouseListener::mScrollY, 0.0f)) {
                    float addValue = powf(std::fabs(MouseListener::mScrollY * EDITOR_SCROLL_SENSITIVITY), 1/camera.zoom);
                    camera.zoom += addValue * -SIGNOF(MouseListener::mScrollY);
                }

                if (reset) {
                    camera.pos = glm::mix<glm::vec2, float>(camera.pos, glm::vec2(0, 0), lerpTime);
                    camera.zoom += ((1.0f - camera.zoom) * lerpTime);
                    lerpTime += 0.1f * dt; // ! maybe move this to the front of all of this if I experience issues

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
    };

    class GridLines : public Component {
        public:
            GridLines() { type = ComponentType::GRID_LINES; id = idCounter++; };

            // * ====================
            // * Rule of 5 Stuff
            // * ====================

            // * Note, components attached to gl's GameObject will not be attached to the GameObject contained in this.
            GridLines(GridLines const &gl) {
                type = gl.type;
                id = idCounter++;

                if (gl.gameObject) {
                    gameObject = new GameObject();
                    gameObject->transform = gl.gameObject->transform;
                    gameObject->name = gl.gameObject->name;
                }
            };

            GridLines(GridLines &&gl) {
                type = gl.type;
                id = idCounter++;
                gameObject = gl.gameObject;
                gl.gameObject = NULL;
            };

            // * Note, components attached to gl's GameObject will not be attached to the GameObject contained in this.
            GridLines& operator = (GridLines const &gl) {
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

            GridLines& operator = (GridLines &&gl) {
                gameObject = gl.gameObject;
                gl.gameObject = NULL;
            };

            ~GridLines() { delete gameObject; };


            // * ====================
            // * Normal Functions
            // * ====================

            inline void update(float dt) override; // todo make once we have access to the camera from the current scene in the window
    };
}

#endif // !COMPONENT_H
