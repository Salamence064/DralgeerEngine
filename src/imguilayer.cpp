#include <Dralgeer/window.h>
#include <Dralgeer/listeners.h>
#include <Dralgeer/imguilayer.h>

namespace Dralgeer {
    inline void ImGuiLayer::setupDockerSpace() const {
        uint32_t windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar |
                ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

        ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(Window::data.width, Window::data.height - 93.0f), ImGuiCond_Always);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

        ImGui::Begin("Dockspace Demo", NULL, windowFlags);
        ImGui::PopStyleVar(2);

        // Dockspace
        ImGui::DockSpace(ImGui::GetID("Dockspace"));
    };

    void ImGuiLayer::init(GLFWwindow* window, PickingTexture const &pickingTexture) {
        propertiesWindow.init(pickingTexture);
        this->window = window;

        // create the context
        ImGui::CreateContext();

        // set flags
        ImGuiIO& io = ImGui::GetIO();
        io.IniFilename = "config.ini"; // save a .ini for ease of use
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_DockingEnable;
        if (JoystickListener::jGamepad) { io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; }

        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendPlatformName = "imgui_impl_glfw";

        // initialize the ImGui attributes
        ImGui_ImplGlfw_InitForOpenGL(window, 1);
        ImGui_ImplOpenGL3_Init("#version 330");
    };

    void ImGuiLayer::update(float dt, Scene* currScene) {
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        setupDockerSpace();

        currScene->imGui();
        gameViewWindow.imGui();
        propertiesWindow.update(dt, currScene, gameViewWindow.getWantCaptureMouse());
        propertiesWindow.imGui();

        ImGui::End();
        ImGui::Render();

        // render to the current OpenGL context
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    };

    void ImGuiLayer::dispose() const {
        ImGui_ImplGlfw_Shutdown();
        ImGui_ImplOpenGL3_Shutdown();
        ImGui::DestroyContext();
    };
}
