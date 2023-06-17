// ? This header stores bitfields for different flags and the counter for component ids

#pragma once

#include "gameobject.h"

#define NON_PICKABLE_FLAG 0x000001U
#define SPRITE_RENDERER_FLAG 0x000004U

namespace Dralgeer {
    // todo maybe find a way to do stuff with just a flag inside of this class
        // ! This would probably be ideal seeing as we have to store it like that already
        // ! The only hurdle left would be storing the unique data for the different subclasses as inside functions we can use a switch
    class Component {
        protected:
            int idCounter = 0;

        public:
            uint32_t flags;

            int id;
            GameObject::GameObject gameObject; // should this even be here??

            virtual inline void start() = 0;
            virtual inline void update(float dt) = 0;
            virtual inline void destroy() {}; // by default doesn't do anything, but can be overriden.
    };
}
