#ifndef IMGUI_LAYER_H
#define IMGUI_LAYER_H

#include <GLFW/glfw3.h>
#include <IMGUI/imgui_impl_glfw.h>
#include <IMGUI/imgui_impl_opengl3.h>
#include "editor.h"
#include "listeners.h"

namespace Dralgeer {
    class ImGuiLayer {
        private:
            GLFWwindow* window;

        public:
            ImGuiLayer(GLFWwindow* window) {
                this->window = window;
            };

            void init() {
                // create the context
                ImGui::CreateContext();

                // set flags
                ImGuiIO& io = ImGui::GetIO();
                io.IniFilename = "config.ini"; // save a .ini for ease of use

                // todo google how to do docking and add the necessary flag for that, too
                io.ConfigFlags |= ImGuiConfigFlags_::ImGuiConfigFlags_NavEnableKeyboard;
                if (JoystickListener::jGamepad) { io.ConfigFlags |= ImGuiConfigFlags_::ImGuiConfigFlags_NavEnableGamepad; }

                io.BackendFlags |= ImGuiBackendFlags_::ImGuiBackendFlags_HasMouseCursors;
                io.BackendPlatformName = "imgui_impl_glfw";

                // initialize the ImGui attributes
                ImGui_ImplGlfw_InitForOpenGL(window, 1);
                ImGui_ImplOpenGL3_Init("#version 330");
            };

            
    };
}

#endif // !IMGUI_LAYER_H
