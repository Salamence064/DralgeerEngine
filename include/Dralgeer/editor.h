#ifndef EDITOR_H
#define EDITOR_H

#include "scene.h"
#include "framebuffer.h"

namespace Dralgeer {
    class GameViewWindow {
        private:
            float leftX, rightX, topY, bottomY;
            // bool isPlaying = 0; // todo add in when I add in events

            inline ImVec2 getLargestSize() const;
            inline ImVec2 getCenteredPos(ImVec2 const &size) const;

        public:
            inline void imGui();
            inline bool getWantCaptureMouse() const;
    };

    class PropertiesWindow {
        private:
            PickingTexture pickingTexture;
            float debounce = 0.2f;

        public:
            GameObject* activeGameObject = nullptr;

            inline PropertiesWindow() {};
            inline void init(PickingTexture const &tex);
            inline void update(float dt, Scene* currScene, bool wantCapture);
            inline void imGui() const;
    };
}

#endif // !EDITOR_H
