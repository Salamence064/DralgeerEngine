#ifndef COMPONENT_H
#define COMPONENT_H

#include <Zeta2D/zmath2D.h>
#include "sprite.h"
#include "listeners.h"
#include "camera.h"

namespace Dralgeer {
    // Forward declaration to allow for use in Component.
    class GameObject;


    // * ===========================
    // * Abstract Component Class
    // * ===========================

    // todo maybe find a way to do stuff with just a flag inside of this class
        // ! This would probably be ideal seeing as we have to store it like that already
        // ! The only hurdle left would be storing the unique data for the different subclasses as inside functions we can use a switch
    class Component {
        protected:
            int idCounter = 0;

        public:
            uint32_t flags; // maybe serialize?

            int id;
            GameObject gameObject; // should this even be here?? // ! do not serialize

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

    class GameObject { // todo definitely change it so that it can do rule or 5 stuff -- add that in
        private:
            int idCounter = 0; // used to track the game object's ID
            int id; // todo make public again tbh
            Component** components;
            int capacity = 8; // start with 8 slots for components // todo probs up this later
            int numComponents = 0;

        public:
            std::string name;
            Transform transform; // ! DO NOT serialize

            bool serialize = 1; // ! DO NOT serialize
            bool dead = 0; // ! DO NOT serialize
            
            GameObject() {
                components = new Component*[8];
                id = idCounter++;
            };

            // todo allow for both
            // don't allow for reassignment or constructruction from another game object
            // GameObject(GameObject const &go) { throw std::runtime_error("GameObject objects CANNOT be created from another GameObject."); };
            // GameObject operator = (GameObject const &go) { throw std::runtime_error("GameObject objects CANNOT be reassigned."); };

            template <typename T> T* getComponent(uint32_t objectFlag) {
                for (int i = 0; i < numComponents; ++i) {
                    if (objectFlag & components[i]->flags) { return (T*) components[i]; }
                }

                return nullptr;
            };

            template <typename T> void removeComponent(uint32_t objectFlag) {
                for (int i = 0; i < numComponents; ++i) {
                    if (objectFlag & components[i]->flags) {
                        delete components[i];
                        numComponents--;
                        for (int j = i; j < numComponents; ++j) { components[j] = components[j + 1]; }
                        return;
                    }
                }
            };

            void addComponent(Component* c) {
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

            inline int getID() { return id; };

            ~GameObject() {
                for (int i = 0; i < numComponents; ++i) { delete components[i]; }
                delete[] components;
            };
    };


    // * ==================
    // * Components
    // * ==================

    // * Remember to set isDirty to true if you change either the sprite or the color.
    class SpriteRenderer : public Component {
        private:
            bool imGuiSetup = 1; // ! DO NOT serialize

        public: // todo add rule of 5 operators
            // const uint32_t flags = COMPONENT_FLAG | SPRITE_RENDERER_FLAG;

            glm::vec4 color = glm::vec4(1, 1, 1, 1); // for some reason it doesn't work unless I have the equals
            Sprite sprite;

            Transform lastTransform; // ! DO NOT serialize
            bool isDirty = 1; // ! DO NOT serialize

            // * ==========================================================

            SpriteRenderer() { flags = SPRITE_RENDERER_FLAG; id = idCounter++; }; // todo test if you need to do = SpriteRenderer(); or not for default
            SpriteRenderer(SpriteRenderer const &spr) : color(spr.color), lastTransform(spr.lastTransform) {
                gameObject = spr.gameObject;
                flags = SPRITE_RENDERER_FLAG;
                id = idCounter++;

                imGuiSetup = spr.imGuiSetup;
                isDirty = spr.isDirty;

                sprite.texture = new Texture();
                sprite.texture->init(spr.sprite.texture->filepath);
            };

            SpriteRenderer& operator = (SpriteRenderer const &spr) {
                gameObject = spr.gameObject; // todo this reassignment will fail meaning we need a better method of doing this than just failing reassignment
                color = spr.color;
                lastTransform = spr.lastTransform;
                imGuiSetup = spr.imGuiSetup;
                isDirty = spr.isDirty;

                sprite.texture = new Texture();
                sprite.texture->init(spr.sprite.texture->filepath);

                flags = spr.flags;
                id = idCounter++;

                return (*this);
            };

            inline void start() override { lastTransform = gameObject.transform; };

            // ! Not convinced we even need this function
            // inline void editorUpdate();

            inline void update(float dt) override {
                if (lastTransform != gameObject.transform) {
                    gameObject.transform = lastTransform;
                    isDirty = 1;
                }
            };

            ~SpriteRenderer() { if (sprite.texture != nullptr) { delete sprite.texture; }};
    };

    class EditorCamera : public Component {
        private:
            float dragDebounce = 0.032f;
            float lerpTime = 0.0f;
            bool reset = 0;

            Camera camera;
            glm::vec2 clickOrigin;

        public:
            EditorCamera() { flags = EDITOR_CAMERA_FLAG; id = idCounter++; };

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
            GridLines() { flags = GRID_LINES_FLAG; id = idCounter++; };

            inline void update(float dt) override; // todo make once we have access to the camera from the current scene in the window
    };
}

#endif // !COMPONENT_H
