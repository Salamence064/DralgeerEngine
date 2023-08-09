#pragma once

#include "sprite.h"
#include "camera.h"
#include "listeners.h"

namespace Dralgeer {
    namespace IDCounter { extern int componentID, gameObjectID; }

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

            inline void start() { sprite->start(); };
            inline void imGui() { sprite->imGui(); };
            inline void update() { sprite->update(); };
    };


    // * ==================
    // * Components
    // * ==================

    // * Remember to set isDirty to true if you change either the sprite or the color.
    class SpriteRenderer { // todo could refactor to not store a gameobject but instead just a transform -- transform wouldn't need to be a pointer either
        private:
            bool imGuiSetup = 1; // ! DO NOT serialize

        public:
            // * ==============
            // * Attributes
            // * ==============

            int id;
            GameObject* gameObject = nullptr; // Has to be a pointer due to forward declaration. // ! do not serialize

            glm::vec4 color = glm::vec4(1, 1, 1, 1); // for some reason it doesn't work unless I have the equals
            Sprite sprite;

            Transform lastTransform; // ! DO NOT serialize
            bool isDirty = 1; // ! DO NOT serialize

            // * ==========================================================

            // todo test if you need to do = SpriteRenderer(); or not for default
            SpriteRenderer();
            
            // * Note, components attached to spr's GameObject will not be attached to the GameObject contained in this.
            SpriteRenderer(SpriteRenderer const &spr);
            SpriteRenderer(SpriteRenderer &&spr);

            // * Note, components attached to spr's GameObject will not be attached to the GameObject contained in this.
            SpriteRenderer& operator = (SpriteRenderer const &spr);
            SpriteRenderer& operator = (SpriteRenderer &&spr);

            ~SpriteRenderer();

            inline void start() { lastTransform = gameObject->transform; };
            void update();

            // Create a color picker for the sprites.
            void imGui();
    };

    class EditorCamera {
        private:
            float dragDebounce = 0.032f;
            float lerpTime = 0.0f;
            bool reset = 0;

            Camera camera;
            glm::vec2 clickOrigin;

        public:
            int id;

            EditorCamera(Camera const &cam);
            inline void update(float dt, bool wantCapture);

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

            unsigned int fbo; // ! for debugging purposes
            unsigned int realFbo; // ! for debugging purposes

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
