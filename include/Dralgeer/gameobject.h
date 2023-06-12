// todo include the deserializer for gameobjects in here

#pragma once

#include <string>
#include <vector>
#include <stdexcept>
#include <GLM/glm/glm.hpp>
#include "components/component.h"

namespace Dralgeer {
    struct Transform {
        glm::vec2 pos;
        glm::vec2 scale;

        int zIndex;
        float rotation = 0.0f;

        inline bool operator == (Transform const &t) const { return pos == t.pos && scale == t.scale && zIndex == t.zIndex && rotation == t.rotation; };
        inline bool operator != (Transform const &t) const { return pos != t.pos || scale != t.scale || zIndex != t.zIndex || rotation != t.rotation; };
    };

    namespace GameObject {
        int idCounter = 0; // used to track the game object's ID // ! Will be updated when serialization is implemented based on that

        class GameObject {
            private:
                int id;
                void** components;
                int capacity = 8; // start with 8 slots for components // todo probs up this later
                int numComponents = 0;

            public:
                std::string name;
                Transform transform; // ! DO NOT serialize

                bool serialize = 1; // ! DO NOT serialize
                bool dead = 0; // ! DO NOT serialize
                
                GameObject() {
                    components = new void*[8];
                    id = idCounter++;
                };

                // don't allow for reassignment or constructruction from another game object
                GameObject(GameObject const &go) { throw std::runtime_error("GameObject objects CANNOT be created from another GameObject."); };
                GameObject operator = (GameObject const &go) { throw std::runtime_error("GameObject objects CANNOT be reassigned."); };

                // todo test to make sure templates can be used like this
                // todo if this doesnt work try it without casting components[i] to T* in the statement retrieving the flags
                template <typename T> T* getComponent(uint32_t const objectFlag) {
                    if (!(objectFlag & COMPONENT_FLAG)) { return nullptr; }

                    for (int i = 0; i < numComponents; ++i) {
                        if ((objectFlag ^ COMPONENT_FLAG) & ((T*) components[i])->flags) { return (T*) components[i]; }
                    }

                    return nullptr;
                };

                

                int getID() { return id; };

                ~GameObject() {
                    for (int i = 0; i < numComponents; ++i) { delete components[i]; }
                    delete[] components;
                };
        };
    }
}
