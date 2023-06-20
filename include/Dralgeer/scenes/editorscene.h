#pragma once

#include "scene.h"

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
                // sprites = AssetPool::get
            };

            inline void loadResources(Scene const &scene) override;

            inline void imGui() override;
    };
}
