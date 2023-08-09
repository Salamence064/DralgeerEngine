#pragma once

#include "sprite.h"
#include "camera.h"
#include "listeners.h"

namespace Dralgeer {
    namespace IDCounter { extern int componentID, gameObjectID; }

    struct Transform {
        glm::vec2 pos;
        glm::vec2 scale;

        int zIndex;
        float rotation = 0.0f;

        inline bool operator == (Transform const &t) const { return pos == t.pos && scale == t.scale && zIndex == t.zIndex && rotation == t.rotation; };
        inline bool operator != (Transform const &t) const { return pos != t.pos || scale != t.scale || zIndex != t.zIndex || rotation != t.rotation; };
    };


    // * =============================
    // * Sprite Related Component
    // * =============================

    // * Remember to set isDirty to true if you change either the sprite or the color.
    class SpriteRenderer {
        private:
            bool imGuiSetup = 1; // ! DO NOT serialize

        public:
            // * ==============
            // * Attributes
            // * ==============

            // This should be equivalent to the ID of the GameObject containing this.
            // If it's -1, it is not attached to a GameObject.
            int entityID = -1;

            glm::vec4 color = glm::vec4(1, 1, 1, 1); // for some reason it doesn't work unless I have the equals
            Sprite sprite;

            Transform transform, lastTransform; // ! DO NOT serialize
            bool isDirty = 1; // ! DO NOT serialize

            // * ==========================================================

            inline SpriteRenderer() {};

            // Create a color picker for the sprites.
            void imGui();
            inline void start() { lastTransform = transform; };

            inline void update() {
                if (lastTransform != transform) {
                    lastTransform = transform;
                    isDirty = 1;
                }
            };
    };


    // * ====================
    // * Game Object Stuff
    // * ====================

    class GameObject {
        public:
            // * ==============
            // * Attributes
            // * ==============

            int id;
            std::string name;
            SpriteRenderer* sprite = nullptr; // todo maybe could make a standard object and take references to it when passing it to the renderer
            Transform transform; // ! DO NOT serialize

            bool serialize = 1; // ! DO NOT serialize
            bool dead = 0; // ! DO NOT serialize
            bool pickable = 1;
            
            // * ===============================================

            inline GameObject() { id = ++IDCounter::gameObjectID; };


            // * ====================
            // * Rule of 5 Stuff
            // * ====================

            GameObject(GameObject const &go);
            GameObject(GameObject &&go);

            GameObject& operator = (GameObject const &go);
            GameObject& operator = (GameObject &&go);

            // Note: we don't need a destructor as the Renderer or Scene should handle the GameObject's sprite's destruction.


            // * ====================
            // * Normal Functions
            // * ====================

            inline void start() { sprite->start(); sprite->entityID = id; };
            inline void imGui() { sprite->imGui(); };
            inline void update() { sprite->update(); };
    };


    // * ==================
    // * Components
    // * ==================

    class EditorCamera {
        private:
            float dragDebounce = 0.032f;
            float lerpTime = 0.0f;
            bool reset = 0;

            Camera camera;
            glm::vec2 clickOrigin;

        public:
            int id;

            inline EditorCamera() { id = IDCounter::componentID++; };

            inline void init(Camera const &cam) { camera = cam; };
            void update(float dt, bool wantCapture);

            inline void imGui() {
                // todo find a way to emulate the Java thing I have setup using .class in c++
                // todo  (probs will not be in a similar way)
            };
    };

    class GridLines {
        public:
            int id;

            inline GridLines() { id = IDCounter::componentID++; };

            void update(Camera const &cam);

            inline void imGui() {
                // todo find a way to emulate the Java thing I have setup using .class in c++
                // todo  (probs will not be in a similar way)
            };
    };

    class MouseControls {
        private:
            bool pressedLastFrame = 0;
            glm::vec2* placedTiles = new glm::vec2[16];
            int pCapacity = 16;
            int pCount = 0;

        public:
            int id;

            GameObject* heldObject = nullptr; // only set this equal to an object getting picked up // ! (and don't serialize)
            bool addObject = 0;

            MouseControls();

            inline MouseControls(MouseControls const &mc) { throw std::runtime_error("MouseControls object CANNOT be constructed from another."); };

            MouseControls& operator = (MouseControls const &mc);
            MouseControls& operator = (MouseControls &&mc);

            void update();

            inline void imGui() {
                // todo find a way to emulate the Java thing I have setup using .class in c++
                // todo  (probs will not be in a similar way)
            };
    };
}
