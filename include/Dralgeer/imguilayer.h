#ifndef IMGUI_LAYER_H
#define IMGUI_LAYER_H

#include <IMGUI/imgui_impl_glfw.h>
#include <IMGUI/imgui_impl_opengl3.h>
#include "editor.h"
#include "framebuffer.h"

namespace Dralgeer {
    class ImGuiLayer {
        private:
            GLFWwindow* window; // We do not need to implement rule of 5 as this will be the same one in Window.

            // todo factor in the top of the window and the task bar without hardcoding it in
            inline void setupDockerSpace(int width, int height) const;

        public:
            PropertiesWindow propertiesWindow;
            GameViewWindow gameViewWindow;

            ImGuiLayer() {};
            void init(GLFWwindow* window, PickingTexture const &pickingTexture);
            void update(float dt, Scene* currScene, int windowWidth, int windowHeight);
            void dispose() const;
    };
}

#endif // !IMGUI_LAYER_H
