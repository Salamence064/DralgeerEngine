// todo include the deserializer for gameobjects in here

#pragma once

#include <string>
#include <GLM/glm/glm.hpp>

namespace Dralgeer {
    struct Transform {
        glm::vec2 pos;
        glm::vec2 scale;

        float rotation = 0.0f;
        int zIndex;
    };

    namespace GameObject {
        int IDCounter = 0; // used to track the game object's ID // ! Will be updated when serialization is implemented based on that

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
