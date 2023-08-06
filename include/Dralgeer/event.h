#pragma once

namespace Dralgeer {
    enum EventType {
        START_PLAY,
        STOP_PLAY,
        SAVE_LEVEL,
        LOAD_LEVEL,
        USER_EVENT
    };


    namespace EventSystem {
        // todo figure out a way to send the notifications to various parts of the code without making an observer class and having everything extend that

        inline void notify(EventType event);
    }
}
