#pragma once

#include "component.h"
#include "prefabs.h"

// todo we could forwardly declare the properties window class and then include the editor header in the .cpp file

namespace Dralgeer {
    // todo probably end up doing the editor update system (maybe)

    class Gizmo : public Component { // todo add rule of 5 later
        private:
            GizmoType gizmoType; // ! Do NOT serialize

            glm::vec4 xColor = glm::vec4(0.8824f, 0.3039f, 0.3039f, 1.0f);
            glm::vec4 xHoverColor = glm::vec4(0.8824f, 0.0039f, 0.0039f, 1.0f);
            glm::vec4 yColor = glm::vec4(0.3f, 0.3f, 1.0f, 1.0f);
            glm::vec4 yHoverColor = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);

            // todo focus on getting a nice system for it later

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

            // todo current gizmo system sucks and will be improved later -- for now it's just to have something
            Gizmo(Sprite spr, GizmoType gType, ComponentType cType);

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

            inline void start() override {
                xObject->transform.rotation = 90.0f;
                yObject->transform.rotation = 180.0f;
                xObject->transform.zIndex = 1000;
                yObject->transform.zIndex = 1000;
            };

            void update(float dt, Camera const &cam, bool wantCapture) override;
    };

    class GizmoSystem : public Component { // todo find a better replacement later on -- probs could do so with an enum + switch system (primary problem is storing the unique objects)
        private: // todo add rule of 5 shit later
            SpriteSheet* gizmoSprites; // ! Do NOT serialize
            GizmoType activeGizmo; // ! Do NOT serialize
            GameObject* gizmo; // ! Do NOT serialize

        public:
            GizmoSystem(SpriteSheet* spr) {
                gizmoSprites = spr;
                type = GIZMO_SYSTEM;
                id = IDCounter::componentID++;
            };

            inline void start() override {
                gizmo = Prefabs::generateGameObject("Gizmos");

                gizmo->addComponent(new Gizmo(gizmoSprites->sprites[1], TRANSLATE_GIZMO, TRANSLATE_GIZMO_COMPONENT));
                gizmo->addComponent(new Gizmo(gizmoSprites->sprites[2], SCALE_GIZMO, SCALE_GIZMO_COMPONENT));
                gizmo->serialize = 0;

                activeGizmo = TRANSLATE_GIZMO;
                gizmo->start();
            };

            void update(float dt, Camera const &cam, bool wantCapture) override;            
    };
}
