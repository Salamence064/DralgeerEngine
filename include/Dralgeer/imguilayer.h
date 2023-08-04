#pragma once

#include <IMGUI/imgui_impl_glfw.h>
#include <IMGUI/imgui_impl_opengl3.h>
#include "editor.h"
#include "framebuffer.h"

namespace Dralgeer {
    class ImGuiLayer {
        private:
            GLFWwindow* window; // We do not need to implement rule of 5 as this will be the same one in Window.
            inline void setupDockerSpace(int width, int height) const;

        public:
            PropertiesWindow propertiesWindow;
            GameViewWindow gameViewWindow;

            ImGuiLayer() {};
            void init(GLFWwindow* window, PickingTexture* pickingTexture);
            void update(float dt, Scene* currScene, unsigned int frameBufferTexID, int windowWidth, int windowHeight, GameViewWindow* window, unsigned int texID2, unsigned int fboID);
            void dispose() const;
    };
}
