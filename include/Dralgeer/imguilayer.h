#ifndef IMGUI_LAYER_H
#define IMGUI_LAYER_H

#include <GLFW/glfw3.h>
#include "editor.h"
#include "listeners.h"

namespace Dralgeer {
    class ImGuiLayer {
        private:
            GLFWwindow* window;

            // todo google which headers are needed for these
            // ImGuiImplGlfw imGuiGlfw;
            // ImGuiImplGl3 imGuiGl3;

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
                // io.BackendPlatformName = "imgui_"; // todo look up what is needed for c++

                std::string glslVersion = "#version 330";
                // todo initialize the imGui attribs
            };

            
    };
}

#endif // !IMGUI_LAYER_H
