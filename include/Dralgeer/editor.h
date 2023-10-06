#pragma once

#include "scene.h"
#include "framebuffer.h"
#include "listeners.h"

namespace Dralgeer {
    class GameViewWindow {
        private:
            float leftX, rightX, topY, bottomY;
            bool imGuiSetup = 1;
            bool isPlaying = 0;

            inline ImVec2 getLargestSize() const;
            inline ImVec2 getCenteredPos(ImVec2 const &size) const;

        public:
            void imGui(unsigned int frameBufferTexID);
            inline bool getWantCaptureMouse() const {
                return MouseListener::mX >= leftX && MouseListener::mX <= rightX && MouseListener::mY >= bottomY && MouseListener::mY <= topY;
            };
    };

    class PropertiesWindow {
        private:
            PickingTexture* pickingTexture;
            float debounce = 0.2f;

        public:
            GameObject* activeGameObject = nullptr;

            PropertiesWindow() {};
            inline void init(PickingTexture* pickingTexture) { this->pickingTexture = pickingTexture; };
            void update(float dt, void* currScene, RootScene sceneType, bool wantCapture);
            void imGui() const;
    };
}
