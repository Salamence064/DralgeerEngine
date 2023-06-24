#ifndef COMPONENT_H
#define COMPONENT_H

#include <Zeta2D/zmath2D.h>
#include <utility>
#include "sprite.h"
#include "editor.h"
#include "listeners.h"
#include "camera.h"
#include <IMGUI/imgui.h>

namespace Dralgeer {
    class GameObject;

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

            virtual inline void start() {}; // by default doesn't do anything, but can be overriden.
            virtual inline void update(float dt) = 0; // every component needs to override update.
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

            inline void* getComponent(ComponentType type);
            inline void removeComponent(ComponentType type);
            inline void addComponent(Component* c);

            inline void start();
            inline void destory();
            inline void imGui();
            inline void update(float dt);
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

            inline void start() override;
            inline void update(float dt) override;

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

            inline void update(float dt) override;
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

            inline void update(float dt) override;
    };
}

#endif // !COMPONENT_H
