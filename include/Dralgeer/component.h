#pragma once

#include "sprite.h"
#include "camera.h"

namespace Dralgeer {
    class GameObject;

    // * ===========================
    // * Abstract Component Class
    // * ===========================

    enum ComponentType {
        SPRITE_RENDERER,
        EDITOR_CAMERA,
        GRID_LINES,
        MOUSE_CONTROLS
    };

    // todo maybe find a way to do stuff with just a flag inside of this class
        // ! This would probably be ideal seeing as we have to store it like that already
        // ! The only hurdle left would be storing the unique data for the different subclasses as inside functions we can use a switch
    
    // todo when I implement the enum + void* system instead, I can remove the Camera const &cam from many update function signatures
    
    // * Implement rule of 5 for anything that extends this.
    class Component {
        protected:
            int idCounter = 0;

        public:
            ComponentType type;

            int id;
            GameObject* gameObject = nullptr; // Has to be a pointer due to forward declaration. // ! do not serialize

            virtual inline void start() {}; // by default doesn't do anything, but can be overriden.
            virtual void update(float dt, Camera const &cam, bool wantCapture) = 0; // every component needs to override update.
            virtual inline void destroy() {}; // by default doesn't do anything, but can be overriden.
            
            virtual void imGui() {
                // todo find a way to emulate the Java thing I have setup using .class in c++
                // todo  (probs will not be in a similar way)
            };
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

            // todo test if you need to do = SpriteRenderer(); or not for default
            SpriteRenderer();
            
            // * Note, components attached to spr's GameObject will not be attached to the GameObject contained in this.
            SpriteRenderer(SpriteRenderer const &spr);
            SpriteRenderer(SpriteRenderer &&spr);

            // * Note, components attached to spr's GameObject will not be attached to the GameObject contained in this.
            SpriteRenderer& operator = (SpriteRenderer const &spr);
            SpriteRenderer& operator = (SpriteRenderer &&spr);

            ~SpriteRenderer();

            inline void start() override { lastTransform = gameObject->transform; };
            void update(float dt, Camera const &cam, bool wantCapture) override;

            // Create a color picker for the sprites.
            void imGui() override;
    };

    class EditorCamera : public Component {
        private:
            float dragDebounce = 0.032f;
            float lerpTime = 0.0f;
            bool reset = 0;

            Camera camera;
            glm::vec2 clickOrigin;

        public:
            EditorCamera(Camera const &cam);

            // * Note, components attached to cam's GameObject will not be attached to the GameObject contained in this.
            EditorCamera(EditorCamera const &cam);
            EditorCamera(EditorCamera &&cam);

            // * Note, components attached to cam's GameObject will not be attached to the GameObject contained in this.
            EditorCamera& operator = (EditorCamera const &cam);
            EditorCamera& operator = (EditorCamera &&cam);

            ~EditorCamera();

            inline void update(float dt, Camera const &cam, bool wantCapture) override;
    };

    class GridLines : public Component {
        public:
            GridLines();

            // * Note, components attached to gl's GameObject will not be attached to the GameObject contained in this.
            GridLines(GridLines const &gl);
            GridLines(GridLines &&gl);

            // * Note, components attached to gl's GameObject will not be attached to the GameObject contained in this.
            GridLines& operator = (GridLines const &gl);
            GridLines& operator = (GridLines &&gl);

            ~GridLines();

            void update(float dt, Camera const &cam, bool wantCapture) override;
    };

    class MouseControls : public Component {
        private:
            bool pressedLastFrame = 0;
            glm::vec2* placedTiles = new glm::vec2[16];
            int pCapacity = 16;
            int pCount = 0;

        public:
            GameObject* heldObject = nullptr; // only set this equal to an object getting picked up
            bool addObject = 0;

            MouseControls();

            // * Note, components attached to both of the GameObjects attached to mc will not be attached to the GameObjects contained in this.
            MouseControls(MouseControls const &mc);
            MouseControls(MouseControls &&mc);

            // * Note, components attached to both of the GameObjects attached to mc will not be attached to the GameObjects contained in this.
            MouseControls& operator = (MouseControls const &mc);
            MouseControls& operator = (MouseControls &&mc);

            ~MouseControls();

            void update(float dt, Camera const &cam, bool wantCapture) override;
    };
}
