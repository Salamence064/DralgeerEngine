#pragma once

#include "component.h"

namespace Dralgeer {
    enum EventType {
        START_PLAY,
        STOP_PLAY,
        SAVE_LEVEL,
        LOAD_LEVEL,
        ADD_GAMEOBJECT_TO_SCENE,
        Z_INDEX_UPDATE,
        // REMOVE_GAMEOBJECT_FROM_SCENE,
        USER_EVENT
    };

    namespace EventSystem {
        // todo in the future have this go through different observers and update that.
        // todo the observers will be custom objects placed down when the user places a custom event
        extern void notify(EventType event, GameObject* go = nullptr);
    }
}
