#pragma once

// todo come back to this

#include <IMGUI/imgui.h>
#include "window.h"
#include "component.h"
#include "framebuffer.h"

namespace Dralgeer {
    struct GameViewWindow {
        float leftX, rightX, topY, bottomY;
        // bool isPlaying = 0; // todo add in when we add in events

        inline void imGui() {
            bool open;
            ImGui::Begin("Game Viewport", &open, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
            if (!open) { throw std::runtime_error("Gameview Window failed to open."); }

            ImVec2 windowSize = getLargestSize();
            ImVec2 windowPos = getCenteredPos(windowSize);
            ImGui::SetCursorPos(windowPos);

            ImVec2 bottomLeft = ImGui::GetCursorScreenPos();
            bottomLeft.x -= ImGui::GetScrollX();
            bottomLeft.y -= ImGui::GetScrollY();

            leftX = bottomLeft.x;
            bottomY = bottomLeft.y;
            rightX = leftX + windowSize.x;
            topY = bottomY + windowSize.y;

            // todo add a way to get the textureID from the framebuffer from the window

            MouseListener::mGameViewPortX = bottomLeft.x;
            MouseListener::mGameViewPortY = bottomLeft.y;
            MouseListener::mGameViewPortWidth = windowSize.x;
            MouseListener::mGameViewPortHeight = windowSize.y;

            ImGui::End();
        };

        inline bool getWantCaptureMouse() const {
            return MouseListener::mX >= leftX && MouseListener::mX <= rightX && MouseListener::mY >= bottomY && MouseListener::mY <= topY;
        };

        inline ImVec2 getLargestSize() const {
            ImVec2 windowSize = ImGui::GetContentRegionAvail();
            windowSize.x -= ImGui::GetScrollX();
            windowSize.y -= ImGui::GetScrollY();

            float aspectWidth = windowSize.x;
            float aspectHeight = aspectWidth/TARGET_ASPECT_RATIO;

            if (aspectHeight > aspectWidth) {
                // must switch to pillar box mode
                aspectHeight = windowSize.y;
                aspectWidth = aspectHeight/TARGET_ASPECT_RATIO;
            }

            return ImVec2(aspectWidth, aspectHeight);
        };

        inline ImVec2 getCenteredPos(ImVec2 const &size) const {
            ImVec2 windowSize = ImGui::GetContentRegionAvail();
            windowSize.x -= ImGui::GetScrollX();
            windowSize.y -= ImGui::GetScrollY();
            return ImVec2((0.5f*(windowSize.x - size.x)) + ImGui::GetCursorPosX(), (0.5f*(windowSize.y - size.y)) + ImGui::GetCursorPosY());
        };
    };

    class PropertiesWindow {
        private:
            PickingTexture pickingTexture;
            float debounce = 0.2f;

        public:
            GameObject activeGameObject;

            inline PropertiesWindow(PickingTexture const &tex) : pickingTexture(tex) {};

            // todo implement once we have the MouseListener stuff figured out, too
            inline void update(float dt); // todo update the function signature after adding scenes and stuff

            // todo add the other functions and stuff
    };
}
