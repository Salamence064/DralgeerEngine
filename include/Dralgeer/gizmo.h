#pragma once

#include "component.h"
#include "prefabs.h"

// todo we could forwardly declare the properties window class and then include the editor header in the .cpp file

namespace Dralgeer {
    enum GizmoType {
        TRANSLATE_GIZMO = 0,
        SCALE_GIZMO
    };

    // todo probably end up doing the editor update system (maybe)

    class Gizmo { // todo add rule of 5 later
        private:
            GizmoType gizmoType; // ! Do NOT serialize

            glm::vec4 xColor = glm::vec4(0.8824f, 0.3039f, 0.3039f, 1.0f);
            glm::vec4 xHoverColor = glm::vec4(0.8824f, 0.0039f, 0.0039f, 1.0f);
            glm::vec4 yColor = glm::vec4(0.3f, 0.3f, 1.0f, 1.0f);
            glm::vec4 yHoverColor = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

            // todo focus on getting a nice system for it later

            // ! unsure if these should just be handled by a mixture of the scene and renderer, but since atm this doesnt communicate with either, we will take care of it here for now
            // Note: activeObject is guarenteed to be contained in the scene. Therefore, we do not need to bother with memory management for it.
            GameObject* activeObject = nullptr; // ! Do NOT serialize
            SpriteRenderer* xSprite = nullptr; // ! Do NOT serialize
            SpriteRenderer* ySprite = nullptr; // ! Do NOT serialize

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
            GameObject* xObject = nullptr; // ! Do NOT serialize
            GameObject* yObject = nullptr; // ! Do NOT serialize

            // * ====================
            // * Helper Function
            // * ====================

            inline void setInactive() {
                xSprite->color = glm::vec4(0.0f);
                ySprite->color = glm::vec4(0.0f);
            };


            // * ====================
            // * Constructors
            // * ====================

            // todo current gizmo system is not ideal but fairly good. Will improve later
            Gizmo() {};

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

            void init(Sprite spr, GizmoType gType);

            inline void start() {
                xObject->transform.rotation = 90.0f;
                yObject->transform.rotation = 180.0f;
                xObject->transform.zIndex = 1000;
                yObject->transform.zIndex = 1000;
            };

            void update();
    };

    class GizmoSystem {
        private:
            SpriteSheet* gizmoSprites; // ! Do NOT serialize
            GizmoType activeGizmo; // ! Do NOT serialize

        public:
            int id;
            Gizmo gizmos[2]; // ! Do NOT serialize

            inline GizmoSystem() { id = IDCounter::componentID++; };

            GizmoSystem(GizmoSystem const &gs);
            GizmoSystem(GizmoSystem &&gs);

            GizmoSystem& operator = (GizmoSystem const &gs);
            GizmoSystem& operator = (GizmoSystem &&gs);

            inline void init(SpriteSheet* spr) { gizmoSprites = spr; };

            inline void start() {
                gizmos[TRANSLATE_GIZMO].init(gizmoSprites->sprites[1], TRANSLATE_GIZMO);
                gizmos[TRANSLATE_GIZMO].start();
                gizmos[SCALE_GIZMO].init(gizmoSprites->sprites[2], SCALE_GIZMO);
                gizmos[SCALE_GIZMO].start();

                activeGizmo = TRANSLATE_GIZMO;
            };

            void update();            
    };
}
