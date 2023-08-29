#pragma once

#include "component.h"
#include "prefabs.h"

namespace Dralgeer {
    enum GizmoType {
        TRANSLATE_GIZMO = 0,
        SCALE_GIZMO
    };

    class Gizmo {
        private:
            GizmoType gizmoType;

            glm::vec4 xColor = glm::vec4(0.8824f, 0.3039f, 0.3039f, 1.0f);
            glm::vec4 xHoverColor = glm::vec4(0.8824f, 0.0039f, 0.0039f, 1.0f);
            glm::vec4 yColor = glm::vec4(0.3f, 0.3f, 1.0f, 1.0f);
            glm::vec4 yHoverColor = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

            // todo focus on getting a nice system for it later

            // ! unsure if these should just be handled by a mixture of the scene and renderer, but since atm this doesnt communicate with either, we will take care of it here for now
            // Note: activeObject is guarenteed to be contained in the scene. Therefore, we do not need to bother with memory management for it.
            GameObject* activeObject = nullptr;
            SpriteRenderer* xSprite = nullptr;
            SpriteRenderer* ySprite = nullptr;

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

                if (xSprite->transform.pos != activeObject->sprite->transform.pos) {
                    xSprite->transform.pos = activeObject->sprite->transform.pos + xOffset;
                    ySprite->transform.pos = activeObject->sprite->transform.pos + yOffset;

                    xSprite->isDirty = 1;
                    ySprite->isDirty = 1;
                }
            };

            // Is the mouse hovered over the gizmo's xObject?
            inline bool xHoverState() {
                if (MouseListener::mWorldX <= xObject->transform.pos.x &&
                    MouseListener::mWorldX >= xObject->transform.pos.x - gizmoHeight &&
                    MouseListener::mWorldY >= xObject->transform.pos.y &&
                    MouseListener::mWorldY <= xObject->transform.pos.y + gizmoWidth)
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
            // todo consider removing the GameObjects entirely and just doing the SpriteRenderer
            GameObject* xObject = nullptr;
            GameObject* yObject = nullptr;

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
                xObject->sprite->transform.rotation = 90.0f;
                yObject->sprite->transform.rotation = 180.0f;
                xObject->sprite->transform.zIndex = 1499;
                yObject->sprite->transform.zIndex = 1499;
            };

            void update();
    };

    class GizmoSystem {
        private:
            SpriteSheet* gizmoSprites;
            GizmoType activeGizmo;

        public:
            int id;
            Gizmo gizmos[2];

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
