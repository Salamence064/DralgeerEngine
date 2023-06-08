// todo include the deserializer for gameobjects in here

#pragma once

#include <string>
#include <GLM/glm/glm.hpp>

namespace Dralgeer {
    struct Transform {
        glm::vec2 pos;
        glm::vec2 scale;

        int zIndex;
        float rotation = 0.0f;

        bool operator != (Transform const &t) { return pos != t.pos || scale != t.scale || zIndex != t.zIndex || rotation != t.rotation; };
    };

    namespace GameObject {
        int idCounter = 0; // used to track the game object's ID // ! Will be updated when serialization is implemented based on that

        class GameObject {
            public:
                int uID;
                std::string name;
                Transform transform; // ! DO NOT serialize
                // ! add list of components attached to the object (probs use templates for that though or void*)

                bool serialize = 1; // ! DO NOT serialize
                bool dead = 0; // ! DO NOT serialize
                
                GameObject(std::string const &str) : name(str) {};

                
        };
    }
}
