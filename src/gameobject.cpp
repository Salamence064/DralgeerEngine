// ? Provide definitions for the GameObject functions.

#include <Dralgeer/component.h>

namespace Dralgeer {
    // * ====================
    // * Rule of 5 Stuff
    // * ====================

    GameObject::GameObject() {
        components = new Component*[8];
        id = idCounter++;
    };

    GameObject::GameObject(GameObject const &go) : name(go.name), serialize(go.serialize), transform(go.transform) {
        id = idCounter++;
        dead = 0;

        capacity = go.capacity;
        numComponents = go.numComponents;
        components = new Component*[capacity];

        for (int i = 0; i < numComponents; ++i) {
            switch (go.components[i]->type) {
                case ComponentType::SPRITE_RENDERER: { components[i] = new SpriteRenderer(*((SpriteRenderer*) go.components[i])); }
                case ComponentType::EDITOR_CAMERA: { components[i] = new EditorCamera(*((EditorCamera*) go.components[i])); }
                // case ComponentType::GRID_LINES: { components[i] = new GridLines(*((GridLines*) go.components[i])); }
            }
        }
    };

    GameObject::GameObject(GameObject &&go) : name(std::move(go.name)), serialize(go.serialize), transform(std::move(go.transform)) {
        id = idCounter++;
        dead = 0;

        capacity = go.capacity;
        numComponents = go.numComponents;
        components = go.components;
        go.components = NULL;
    };

    GameObject& GameObject::operator = (GameObject const &go) {
        if (this != &go) {
            name = go.name;
            transform = go.transform;
            serialize = go.serialize;
            
            for (int i = 0; i < numComponents; ++i) { delete components[i]; }
            delete[] components;

            capacity = go.capacity;
            numComponents = go.numComponents;
            components = new Component*[capacity];

            for (int i = 0; i < numComponents; ++i) {
                switch (go.components[i]->type) {
                    case ComponentType::SPRITE_RENDERER: { components[i] = new SpriteRenderer(*((SpriteRenderer*) go.components[i])); }
                    case ComponentType::EDITOR_CAMERA: { components[i] = new EditorCamera(*((EditorCamera*) go.components[i])); }
                    // case ComponentType::GRID_LINES: { components[i] = new GridLines(*((GridLines*) go.components[i])); }
                }
            }
        }

        return *this;
    };

    GameObject& GameObject::operator = (GameObject &&go) {
        if (this != &go) { // ensure there is not self assignment
            name = std::move(go.name);
            transform = std::move(go.transform);
            serialize = go.serialize;

            capacity = go.capacity;
            numComponents = go.numComponents;
            components = go.components;
            go.components = NULL;
        }

        return *this;
    };

    GameObject::~GameObject() {
        for (int i = 0; i < numComponents; ++i) { delete components[i]; }
        delete[] components;
    };


    // * =====================
    // * Normal Functions
    // * =====================

    template <typename T> inline T* GameObject::getComponent(ComponentType type) {
        for (int i = 0; i < numComponents; ++i) {
            if (type == components[i]->type) { return (T*) components[i]; }
        }

        return nullptr;
    };

    inline void GameObject::removeComponent(ComponentType type) {
        for (int i = 0; i < numComponents; ++i) {
            if (type == components[i]->type) {
                delete components[i];
                numComponents--;
                for (int j = i; j < numComponents; ++j) { components[j] = components[j + 1]; }
                return;
            }
        }
    };

    inline void GameObject::addComponent(Component* c) {
        if (numComponents == capacity) {
            capacity *= 2;

            Component** temp = new Component*[capacity];
            for (int i = 0; i < numComponents; ++i) { temp[i] = components[i]; }
            
            delete[] components;
            components = temp;
        }

        components[numComponents++] = c;
    };

    inline void GameObject::start() { for (int i = 0; i < numComponents; ++i) { components[i]->start(); }};
    inline void GameObject::destory() { for (int i = 0; i < numComponents; ++i) { components[i]->destroy(); }};
    inline void GameObject::update(float dt) { for (int i = 0; i < numComponents; ++i) { components[i]->update(dt); }};
}
