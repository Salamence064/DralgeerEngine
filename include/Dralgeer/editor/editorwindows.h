#pragma once

#include <stdexcept>
#include <IMGUI/imgui.h>

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

            // todo add a way to set the game viewport through the mouse listener

            ImGui::End();
        };

        inline bool getWantCaptureMouse() const; // todo add the functionality of this once we update the mouse listener to be able to hold this information

        inline ImVec2 getLargestSize() const;
        inline ImVec2 getCenteredPos(ImVec2 const &size) const;
    };
}
