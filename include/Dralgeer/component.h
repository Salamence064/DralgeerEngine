#pragma once

#include "sprite.h"
#include "camera.h"
#include "listeners.h"

namespace Dralgeer {
    class GameObject;

    // * ===========================
    // * Abstract Component Class
    // * ===========================

    enum ComponentType {
        SPRITE_RENDERER,
        EDITOR_CAMERA,
        GRID_LINES,
        MOUSE_CONTROLS,
        GIZMO
    };

    enum GizmoType {
        SCALE_GIZMO,
        TRANSLATE_GIZMO
    };

    // todo maybe find a way to do stuff with just a flag inside of this class
        // ! This would probably be ideal seeing as we have to store it like that already
        // ! The only hurdle left would be storing the unique data for the different subclasses as inside functions we can use a switch
    
    // todo when I implement the enum + void* system instead, I can remove the Camera const &cam from many update function signatures
    
    namespace IDCounter { extern int componentID, gameObjectID; }

    // * Implement rule of 5 for anything that extends this.
    class Component {
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
            unsigned int fbo; // ! for debugging purposes
            unsigned int realFbo; // ! for debugging purposes

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

    class Gizmo : public Component { // todo add rule of 5 later
        private:
            SpriteSheet* gizmoSprites; // ! Do NOT serialize
            GizmoType activeGizmo; // ! Do NOT serialize

            glm::vec4 xColor = glm::vec4(0.8824f, 0.3039f, 0.3039f, 1.0f);
            glm::vec4 xHoverColor = glm::vec4(0.8824f, 0.0039f, 0.0039f, 1.0f);
            glm::vec4 yColor = glm::vec4(0.3f, 0.3f, 1.0f, 1.0f);
            glm::vec4 yHoverColor = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

            GameObject* xObject; // ! Do NOT serialize
            GameObject* yObject; // ! Do NOT serialize
            GameObject* activeObject = nullptr; // ! Do NOT serialize
            SpriteRenderer* xSprite; // ! Do NOT serialize
            SpriteRenderer* ySprite; // ! Do NOT serialize

            glm::vec2 xOffset = glm::vec2(64, -5), yOffset = glm::vec2(16, 61);
            int gizmoWidth = 16, gizmoHeight = 48;

            bool xActive = 0, yActive = 0;

            // todo somehow add in the properties window to be manipulated (probably as a pointer parameter)


            // * ====================
            // * Helper Functions
            // * ====================

            inline void setActive() {
                xSprite->color = xColor;
                ySprite->color = yColor;
            };

            // Is the mouse hovered over the gizmo's xObject?
            inline bool xHoverState() {
                if (MouseListener::mWorldX <= xObject->transform.pos.x &&
                    MouseListener::mWorldX >= xObject->transform.pos.x - gizmoHeight &&
                    MouseListener::mWorldY >= yObject->transform.pos.y &&
                    MouseListener::mWorldY <= yObject->transform.pos.y + gizmoWidth)
                {
                    xSprite->color = xHoverColor;
                    return 1;
                }

                xSprite->color = xColor;
                return 0;
            };

            // Is the mouse hovered over the gizmo's yObject?
            inline bool yHoverState() {
                if (MouseListener::mWorldX <= yObject->transform.pos.x &&
                    MouseListener::mWorldX >= yObject->transform.pos.x - gizmoWidth &&
                    MouseListener::mWorldY <= yObject->transform.pos.y &&
                    MouseListener::mWorldY >= yObject->transform.pos.y - gizmoHeight)
                {
                    ySprite->color = yHoverColor;
                    return 1;
                }

                ySprite->color = yColor;
                return 0;
            };

        public:
            bool inUse = 0; // Remember to call setInactive after setting this to 0.

            // * ====================
            // * Helper Function
            // * ====================

            inline void setInactive() {
                gameObject = nullptr; // ! seems useless (probs remove)
                xSprite->color = glm::vec4(0.0f);
                ySprite->color = glm::vec4(0.0f);
            };


            // * ====================
            // * Constructors
            // * ====================

            Gizmo();

            // * Note, components attached to both of the GameObjects attached to mc will not be attached to the GameObjects contained in this.
            Gizmo(Gizmo const &gizmo);
            Gizmo(Gizmo &&gizmo);

            // * Note, components attached to both of the GameObjects attached to mc will not be attached to the GameObjects contained in this.
            Gizmo& operator = (Gizmo const &gizmo);
            Gizmo& operator = (Gizmo &&gizmo);

            ~Gizmo();


            // * ====================
            // * Normal Functions
            // * ====================

            void init(SpriteSheet* spr);

            inline void start() override {
                xObject->transform.rotation = 90.0f;
                yObject->transform.rotation = 180.0f;
                xObject->transform.zIndex = 1000;
                yObject->transform.zIndex = 1000;

                xObject->serialize = 0;
                yObject->serialize = 0;
            };

            void update(float dt, Camera const &cam, bool wantCapture) override;

    };
}
