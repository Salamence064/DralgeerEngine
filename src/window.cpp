#include <Dralgeer/window.h>

namespace Dralgeer {
    namespace Window {
        WindowData data;
        GLFWwindow* window;
        Scene currScene;

        ImGuiLayer imGuiLayer;
        FrameBuffer frameBuffer;
        PickingTexture* pickingTexture;

        bool runtimePlaying = 0;
    }
}
