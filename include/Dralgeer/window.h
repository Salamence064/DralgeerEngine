#ifndef WINDOW_H
#define WINDOW_H

// todo go through and make sure all memory allocated on the GPU is properly disposed of (with destructors and other stuff)
// todo go through and make certain constructors inline

#include "imguilayer.h"

namespace Dralgeer {
    struct WindowData {
        uint16_t width, height;
        std::string title;
    };

    // Model a window
    namespace Window {
        static WindowData data;
        static GLFWwindow* window;
        static Scene* currScene = nullptr;

        static ImGuiLayer imGuiLayer;
        static FrameBuffer frameBuffer;
        static PickingTexture pickingTexture;

        // static bool initGamepadState = 1;
        // static GLFWgamepadstate gamepadState;

        inline static void changeScene(SceneType scene);
        static void init(uint16_t width, uint16_t height, std::string const &title);
        static void run();
        static void destroy();
    }
}

#endif // ! WINDOW_H
