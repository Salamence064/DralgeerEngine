#include <Dralgeer/gizmo.h>
#include <Dralgeer/prefabs.h>

namespace Dralgeer {
    GizmoSystem::GizmoSystem(GizmoSystem const &gs) {
        gizmoSprites = gs.gizmoSprites; // This is okay as the AssetPool is the one that does the job of storing and deleting these
        activeGizmo = gs.activeGizmo;
        gizmos[0] = gs.gizmos[0];
        gizmos[1] = gs.gizmos[1];
    };

    GizmoSystem::GizmoSystem(GizmoSystem && gs) {
        activeGizmo = gs.activeGizmo;
        gizmos[0] = std::move(gs.gizmos[0]);
        gizmos[1] = std::move(gs.gizmos[1]);
        gizmoSprites = gs.gizmoSprites;
        gs.gizmoSprites = nullptr;
    };

    GizmoSystem& GizmoSystem::operator = (GizmoSystem const &gs) {
        gizmoSprites = gs.gizmoSprites; // This is okay as the AssetPool is the one that does the job of storing and deleting these
        activeGizmo = gs.activeGizmo;
        gizmos[0] = gs.gizmos[0];
        gizmos[1] = gs.gizmos[1];

        return *this;
    };

    GizmoSystem& GizmoSystem::operator = (GizmoSystem &&gs) {
        if (this != &gs) {
            activeGizmo = gs.activeGizmo;
            gizmos[0] = std::move(gs.gizmos[0]);
            gizmos[1] = std::move(gs.gizmos[1]);
            gizmoSprites = gs.gizmoSprites;
            gs.gizmoSprites = nullptr;
        }

        return *this;
    };

    // Note: We do not need to have a destructor as the AssetPool's destructor will clean up the SpriteSheet

    // ! To expand the number of gizmos handled by this editor to more than just two, we can simply use a for loop that excludes the one active gizmo
    void GizmoSystem::update() {
        gizmos[activeGizmo].inUse = 1;
        gizmos[!activeGizmo].inUse = 0;
        gizmos[!activeGizmo].setInactive();

        // update the gizmos
        gizmos[TRANSLATE_GIZMO].update();
        gizmos[SCALE_GIZMO].update();

        // check for setting new gizmos active
        if (KeyListener::keyPressed[GLFW_KEY_E]) { activeGizmo = TRANSLATE_GIZMO; }
        else if (KeyListener::keyPressed[GLFW_KEY_R]) { activeGizmo = SCALE_GIZMO; }
    };

    // * ==================================================================

    // * ====================
    // * Rule of 5 Stuff
    // * ====================

    Gizmo::Gizmo(Gizmo const &gizmo) {
        gizmoType = gizmo.gizmoType;

        xObject = new GameObject(*gizmo.xObject);
        yObject = new GameObject(*gizmo.yObject);
        xSprite = new SpriteRenderer(*gizmo.xSprite);
        ySprite = new SpriteRenderer(*gizmo.ySprite);
    };

    Gizmo::Gizmo(Gizmo && gizmo) {
        gizmoType = gizmo.gizmoType;

        xObject = gizmo.xObject;
        yObject = gizmo.yObject;
        xSprite = gizmo.xSprite;
        ySprite = gizmo.ySprite;

        gizmo.xObject = nullptr;
        gizmo.yObject = nullptr;
        gizmo.xSprite = nullptr;
        gizmo.ySprite = nullptr;
    };

    Gizmo& Gizmo::operator = (Gizmo const &gizmo) {
        if (this != &gizmo) {
            gizmoType = gizmo.gizmoType;

            xObject = new GameObject(*gizmo.xObject);
            yObject = new GameObject(*gizmo.yObject);
            xSprite = new SpriteRenderer(*gizmo.xSprite);
            ySprite = new SpriteRenderer(*gizmo.ySprite);
        }

        return *this;
    };

    Gizmo& Gizmo::operator = (Gizmo &&gizmo) {
        if (this != &gizmo) {
            gizmoType = gizmo.gizmoType;

            xObject = gizmo.xObject;
            yObject = gizmo.yObject;
            xSprite = gizmo.xSprite;
            ySprite = gizmo.ySprite;

            gizmo.xObject = nullptr;
            gizmo.yObject = nullptr;
            gizmo.xSprite = nullptr;
            gizmo.ySprite = nullptr;
        }

        return *this;
    };

    Gizmo::~Gizmo() {
        delete xObject;
        delete yObject;
        delete xSprite;
        delete ySprite;
    };

    // * =====================
    // * Normal Functions
    // * =====================

    void Gizmo::init(Sprite spr, GizmoType gType) {
        gizmoType = gType;

        xObject = Prefabs::generateSpriteObject(spr, gizmoWidth, gizmoHeight);
        yObject = Prefabs::generateSpriteObject(spr, 16, 48);
        xSprite = xObject->sprite; // todo not handling it properly after prefabs could be a source of error later
        ySprite = yObject->sprite;

        xObject->pickable = 0;
        yObject->pickable = 0;
        xObject->serialize = 0;
        yObject->serialize = 0;
    };

    void Gizmo::update() {
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
