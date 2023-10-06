#include <Dralgeer/window.h>

namespace Dralgeer {
    namespace Window {
        WindowData data;
        GLFWwindow* window;
        Scene currScene;
        Stack<RootScene> sceneController(9);

        ImGuiLayer imGuiLayer;
        FrameBuffer frameBuffer;
        PickingTexture* pickingTexture;

        bool runtimePlaying = 0;
    }
}
