// todo include the deserializer for gameobjects in here

#pragma once

#include <string>
#include <vector>
#include <stdexcept>
#include <GLM/glm/glm.hpp>
#include "components/component.h"

// todo also look up the entity component system and model it how it should be for C++

namespace Dralgeer {
    struct Transform {
        glm::vec2 pos;
        glm::vec2 scale;

        int zIndex;
        float rotation = 0.0f;

        inline bool operator == (Transform const &t) const { return pos == t.pos && scale == t.scale && zIndex == t.zIndex && rotation == t.rotation; };
        inline bool operator != (Transform const &t) const { return pos != t.pos || scale != t.scale || zIndex != t.zIndex || rotation != t.rotation; };
    };

    class GameObject { // todo definitely change it so that it can do rule or 5 stuff -- add that in
        private:
            int idCounter = 0; // used to track the game object's ID
            int id; // todo make public again tbh
            Component** components;
            int capacity = 8; // start with 8 slots for components // todo probs up this later
            int numComponents = 0;

        public:
            std::string name;
            Transform transform; // ! DO NOT serialize

            bool serialize = 1; // ! DO NOT serialize
            bool dead = 0; // ! DO NOT serialize
            
            GameObject() {
                components = new Component*[8];
                id = idCounter++;
            };

            // don't allow for reassignment or constructruction from another game object
            GameObject(GameObject const &go) { throw std::runtime_error("GameObject objects CANNOT be created from another GameObject."); };
            GameObject operator = (GameObject const &go) { throw std::runtime_error("GameObject objects CANNOT be reassigned."); };

            template <typename T> T* getComponent(uint32_t objectFlag) {
                for (int i = 0; i < numComponents; ++i) {
                    if (objectFlag & components[i]->flags) { return (T*) components[i]; }
                }

                return nullptr;
            };

            template <typename T> void removeComponent(uint32_t objectFlag) {
                for (int i = 0; i < numComponents; ++i) {
                    if (objectFlag & components[i]->flags) {
                        delete components[i];
                        numComponents--;
                        for (int j = i; j < numComponents; ++j) { components[j] = components[j + 1]; }
                        return;
                    }
                }
            };

            void addComponent(Component* c) {
                if (numComponents == capacity) {
                    capacity *= 2;

                    Component** temp = new Component*[capacity];
                    for (int i = 0; i < numComponents; ++i) { temp[i] = components[i]; }
                    
                    delete[] components;
                    components = temp;
                }

                components[numComponents++] = c;
            };

            inline void start() { for (int i = 0; i < numComponents; ++i) { components[i]->start(); }};
            inline void destory() { for (int i = 0; i < numComponents; ++i) { components[i]->destroy(); }};
            inline void update(float dt) { for (int i = 0; i < numComponents; ++i) { components[i]->update(dt); }};

            inline int getID() { return id; };

            ~GameObject() {
                for (int i = 0; i < numComponents; ++i) { delete components[i]; }
                delete[] components;
            };
    };
}
