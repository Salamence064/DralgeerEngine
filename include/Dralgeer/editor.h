#pragma once

#include "scene.h"
#include "framebuffer.h"
#include "listeners.h"

namespace Dralgeer {
    class GameViewWindow {
        private:
            float leftX, rightX, topY, bottomY;
            bool imGuiSetup = 1;
            // bool isPlaying = 0; // todo add in when I add in events

            inline ImVec2 getLargestSize() const;
            inline ImVec2 getCenteredPos(ImVec2 const &size) const;

        public:
            void imGui(unsigned int frameBufferTexID);
            inline bool getWantCaptureMouse() const {
                std::cout << "MousePos: " << MouseListener::mX << ", " << MouseListener::mY << "\n";
                std::cout << "Game Viewport positions: " << leftX << ", " << bottomY << "; " << rightX << ", " << topY << "\n";

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
            void update(float dt, Scene* currScene, bool wantCapture);
            void imGui() const;
    };
}
