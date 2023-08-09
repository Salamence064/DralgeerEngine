#pragma once

#include "sprite.h"
#include "camera.h"
#include "listeners.h"

namespace Dralgeer {
    // * ======================================
    // * Component Struct with void* + enum
    // * ======================================

    enum ComponentType {
        SPRITE_RENDERER,
        EDITOR_CAMERA,
        GRID_LINES,
        MOUSE_CONTROLS,
        GIZMO_SYSTEM
    };

    struct Component {
        void* component;
        ComponentType type;
    };

    // todo maybe find a way to do stuff with just a flag inside of this class
        // ! This would probably be ideal seeing as we have to store it like that already
        // ! The only hurdle left would be storing the unique data for the different subclasses as inside functions we can use a switch
    
    // todo when I implement the enum + void* system instead, I can remove the Camera const &cam from many update function signatures
    
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
        private:
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
            bool pickable = 1;
            
            // * ===============================================

            GameObject();


            // * ====================
            // * Rule of 5 Stuff
            // * ====================

            GameObject(GameObject const &go);
            GameObject(GameObject &&go);

            GameObject& operator = (GameObject const &go);
            GameObject& operator = (GameObject &&go);

            ~GameObject();


            // * ====================
            // * Normal Functions
            // * ====================

            inline void* getComponent(ComponentType type) const {
                for (int i = 0; i < numComponents; ++i) {
                    if (type == components[i]->type) { return components[i]; }
                }

                return nullptr;
            };

            inline void removeComponent(ComponentType type) {
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
            inline void imGui() { for (int i = 0; i < numComponents; ++i) { components[i]->imGui(); }};
            inline void update(float dt, Camera const &cam, bool wantCapture) { for (int i = 0; i < numComponents; ++i) { components[i]->update(dt, cam, wantCapture); }};
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

            MouseControls& operator = (MouseControls const &mc);
            MouseControls& operator = (MouseControls &&mc);

            void update();

            inline void imGui() {
                // todo find a way to emulate the Java thing I have setup using .class in c++
                // todo  (probs will not be in a similar way)
            };
    };
}
