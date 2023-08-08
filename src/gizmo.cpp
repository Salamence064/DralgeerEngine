#include <Dralgeer/gizmo.h>
#include <Dralgeer/prefabs.h>

namespace Dralgeer {
    void GizmoSystem::update(float dt, Camera const &cam, bool wantCapture) {
        if (activeGizmo == TRANSLATE_GIZMO) {
            ((Gizmo*) gizmo->getComponent(TRANSLATE_GIZMO_COMPONENT))->inUse = 1;
            Gizmo* scale = (Gizmo*) gizmo->getComponent(SCALE_GIZMO_COMPONENT);
            scale->inUse = 0;
            scale->setInactive();

        } else if (activeGizmo == SCALE_GIZMO) {
            ((Gizmo*) gizmo->getComponent(SCALE_GIZMO_COMPONENT))->inUse = 1;
            Gizmo* scale = (Gizmo*) gizmo->getComponent(TRANSLATE_GIZMO_COMPONENT);
            scale->inUse = 0;
            scale->setInactive();
        }

        gizmo->update(dt, cam, wantCapture); // update the gizmos

        if (KeyListener::keyPressed[GLFW_KEY_E]) { activeGizmo = TRANSLATE_GIZMO; }
        else if (KeyListener::keyPressed[GLFW_KEY_R]) { activeGizmo = SCALE_GIZMO; }
    };

    // * ==================================================================

    // * ====================
    // * Rule of 5 Stuff
    // * ====================

    Gizmo::Gizmo(Sprite spr, GizmoType gType, ComponentType cType) {
        // component stuff
        type = cType;
        id = IDCounter::componentID++;

        // gizmo stuff
        gizmoType = gType;

        xObject = Prefabs::generateSpriteObject(spr, gizmoWidth, gizmoHeight);
        yObject = Prefabs::generateSpriteObject(spr, 16, 48);
        xSprite = (SpriteRenderer*) xObject->getComponent(SPRITE_RENDERER); // todo not handling it properly after prefabs could be a source of error later
        ySprite = (SpriteRenderer*) yObject->getComponent(SPRITE_RENDERER);

        xObject->pickable = 0;
        yObject->pickable = 0;
        xObject->serialize = 0;
        yObject->serialize = 0;
    };

    Gizmo::Gizmo(Gizmo const &gizmo) {}; // ! temp just to get it to compile

    // * =====================
    // * Normal Functions
    // * =====================

    void Gizmo::update(float dt, Camera const &cam, bool wantCapture) {
        if (!inUse) { return; }

        if (activeObject) {
            switch (gizmoType) {
                case SCALE_GIZMO: { // todo can probs remove the !yActive part of the check
                    if (xActive && !yActive) { activeObject->transform.scale.x -= MouseListener::mLastWorldX - MouseListener::mWorldX; }
                    else if (yActive) { activeObject->transform.scale.y -= MouseListener::mLastWorldY - MouseListener::mWorldY; }
                    break;
                }

                case TRANSLATE_GIZMO: {
                    if (xActive && !yActive) { activeObject->transform.pos.x -= MouseListener::mLastWorldX - MouseListener::mWorldX; }
                    else if (yActive) { activeObject->transform.pos.y -= MouseListener::mLastWorldY - MouseListener::mWorldY; }
                    break;
                }
            }
        }

        // todo retrieve the active gameObject from the properties window

        if (!activeObject) { setInactive(); return; }
        setActive();

        bool xHot = xHoverState();
        bool yHot = yHoverState();

        if ((xHot || xActive) && MouseListener::mIsDragging && MouseListener::mButtonPressed[GLFW_MOUSE_BUTTON_LEFT]) {
            xActive = 1;
            yActive = 0;

        } else if ((yHot || yActive) && MouseListener::mIsDragging && MouseListener::mButtonPressed[GLFW_MOUSE_BUTTON_LEFT]) {
            xActive = 0;
            yActive = 1;

        } else {
            xActive = 0;
            yActive = 0;
        }

        xObject->transform.pos += xOffset;
        yObject->transform.pos += yOffset;
    };
}
