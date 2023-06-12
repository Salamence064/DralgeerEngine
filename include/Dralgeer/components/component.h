// ? This header stores bitfields for different flags and the counter for component ids

#pragma once

#define COMPONENT_FLAG 0x000001U
#define NON_PICKABLE 0x000002U

namespace Dralgeer {
    namespace Component {
        int idCounter = 0;

        // // todo store the current ComponentID in the class
        // // todo will possibly be a flag class
        // // todo maybe resort to void* instead though
        // // todo make this an abstract class with the needed functions
        // // todo maybe contain the flags in here
        // class Component {
        //     public:
        //         int uID;
        //         Component() {};
        // }; // // todo refactor to either get rid of this or actually make this part of it useful.
    }
}
