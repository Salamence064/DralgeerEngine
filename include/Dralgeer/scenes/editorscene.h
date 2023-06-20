#pragma once

#include "scene.h"
#include "../components/editorcamera.h"

namespace Dralgeer {
    class LevelEditorInitializer : public SceneInitializer {
        private:
            // todo add physics stuff here

            SpriteSheet sprites;
            GameObject components;
            bool imGuiSetup = 1; // ! DO NOT serialize

        public:
            LevelEditorInitializer() {};

            inline void init(Scene const &scene) override {
                // load the spritesheet
                sprites = AssetPool::getSpriteSheet("assets/images/spritesheets/decorationsAndBlocks.png");
                
                components.name = "LevelEditor";
                // todo maybe add transform as a component class for the GameObject if necessary
                EditorCamera* camera = new EditorCamera(); // defo refactor this stuff
                components.addComponent(camera);

                // todo call components.setNoSerialize() when I have serialization setup
                // todo add gizmo stuff after creating them
                // todo add MouseControls after creating that, too
            };

            inline void loadResources(Scene const &scene) override;

            inline void imGui() override;
    };
}
