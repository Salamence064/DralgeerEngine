#ifndef SCENE_H
#define SCENE_H

#include "component.h"

namespace Dralgeer {
    // todo probably refactor to use a struct that stores a void* and the enum type of the scene instead of this OOP solution
    // todo  but use the OOP solution for now

    enum SceneType {
        LEVEL_EDITOR_SCENE
    };

    class Scene {
        protected:
            // * ======================
            // * Protected Attributes
            // * ======================

            GameObject* gameObjects = nullptr; // todo maybe make a pointer of pointers
            int capacity = 8; // default capacity of 8 // todo probs will up in the future
            int numObjects = 0;

            bool running = 0;
            // todo add physics handler here.

            // * ==============================
            // * Protected abstract function
            // * ==============================

            virtual inline void loadResources() = 0;


            // * ====================
            // * Helper Functions
            // * ====================

            inline void addGO(GameObject const &go);

        public:
            // * ==============
            // * Attributes
            // * ==============

            SceneType type;
            Camera camera;


            // * ======================
            // * Abstract Functions
            // * ======================

            virtual void init() = 0;
            virtual void imGui() = 0;


            // * ====================
            // * Normal Functions
            // * ====================

            inline void start();
            inline void addGameObject(GameObject const &go);

            // Returns nullptr if no game object was found.
            inline GameObject* getGameObject(int id);
            void update(float dt);
            inline void render();
            inline void destroy();
    };

    class LevelEditorScene : public Scene {
        private:
            SpriteSheet sprites;
            GameObject components;
            bool imGuiSetup = 1; // ! DO NOT serialize

        protected:
            inline void loadResources() override;

        public:
            LevelEditorScene();


            // * ===================
            // * Rule of 5 Stuff
            // * ===================

            LevelEditorScene(LevelEditorScene const &scene);
            LevelEditorScene(LevelEditorScene &&scene);
            LevelEditorScene& operator = (LevelEditorScene const &scene);
            LevelEditorScene& operator = (LevelEditorScene &&scene);
            ~LevelEditorScene();


            // * ====================
            // * Normal Functions
            // * ====================

            void init() override;
            void imGui() override;
    };
}

#endif // !SCENE_H
