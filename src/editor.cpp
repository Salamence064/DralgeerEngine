// ? Provide definitions for functions in editor.h

#include <Dralgeer/framebuffer.h>
#include <Dralgeer/window.h>

namespace Dralgeer {
    // * ======================================================
    // * GameViewWindow Stuff

    inline ImVec2 GameViewWindow::getLargestSize() const {
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

    inline ImVec2 GameViewWindow::getCenteredPos(ImVec2 const &size) const {
        ImVec2 windowSize = ImGui::GetContentRegionAvail();
        windowSize.x -= ImGui::GetScrollX();
        windowSize.y -= ImGui::GetScrollY();
        return ImVec2((0.5f*(windowSize.x - size.x)) + ImGui::GetCursorPosX(), (0.5f*(windowSize.y - size.y)) + ImGui::GetCursorPosY());
    };

    // disable pointer cast warnings for this function as it will warn of a void* cast unnecessarily
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wint-to-pointer-cast"

    void GameViewWindow::imGui(unsigned int frameBufferTexID) {
        ImGui::Begin("Game Viewport", NULL, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_MenuBar);

        if (imGuiSetup) {
            ImGui::SetWindowPos(ImVec2(800.0f, 500.0f));
            ImGui::SetWindowSize(ImVec2(720.0f, 520.0f));
            imGuiSetup = 0;
        }

        ImGui::BeginMenuBar();

        if (ImGui::MenuItem("Play", "", isPlaying, !isPlaying)) {
            isPlaying = 1;
            EventSystem::notify(START_PLAY);
        }

        if (ImGui::MenuItem("Stop", "", !isPlaying, isPlaying)) {
            isPlaying = 1;
            EventSystem::notify(STOP_PLAY);
        }

        ImGui::EndMenuBar();

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

        ImGui::Image((void*) frameBufferTexID, windowSize, ImVec2(0, 1), ImVec2(1, 0));

        MouseListener::mGameViewPortX = bottomLeft.x;
        MouseListener::mGameViewPortY = bottomLeft.y;
        MouseListener::mGameViewPortWidth = windowSize.x;
        MouseListener::mGameViewPortHeight = windowSize.y;

        ImGui::End();
    };

    #pragma GCC diagnostic pop


    // * ======================================================
    // * PropertiesWindow Stuff

    void PropertiesWindow::update(float dt, void* currScene, SceneType sceneType, bool wantCapture) {
        if (!wantCapture) { return; }

        debounce -= dt;

        // todo add a check for mouse dragging to ensure it doesnt select from that
        if (MouseListener::mButtonPressed[GLFW_MOUSE_BUTTON_LEFT] && debounce < 0.0f) {
            int x = (int) MouseListener::mWorldX;
            int y = (int) MouseListener::mWorldY;

            int id = pickingTexture->readPixel(x, y);
            GameObject* go = nullptr;

            switch(sceneType) {
                case LEVEL_EDITOR_SCENE: { go = ((LevelEditorScene*) currScene)->getGameObject(id); break; }
            }

            if (go && go->pickable) { activeGameObject = go; }
            else if (!go && !MouseListener::mIsDragging) { activeGameObject = nullptr; }

            debounce = 0.2f;
        }
    };

    void PropertiesWindow::imGui() const {
        if (activeGameObject) {
            ImGui::Begin("Properties");

            // todo implement once we implement the physics stuff
            if (ImGui::BeginPopupContextWindow("ComponentAdder")) {
                // if (ImGui::MenuItem("Add Rigidbody")) {
                //     if (!activeGameObject->getComponent()) {
                //         activeGameObject.addComponent(new RigidBody2D());
                //     }
                // }

                // if (ImGui.menuItem("Add Box Collider")) {
                //     if (activeGameObject.getComponent(Box2DCollider.class) == null &&
                //             (activeGameObject.getComponent(CircleCollider.class) == null)) {
                //         activeGameObject.addComponent(new Box2DCollider());
                //     }
                // }

                // if (ImGui.menuItem("Add Circle Collider")) {
                //     if (activeGameObject.getComponent(CircleCollider.class) == null &&
                //             (activeGameObject.getComponent(Box2DCollider.class) == null)) {
                //         activeGameObject.addComponent(new CircleCollider());
                //     }
                // }

                ImGui::EndPopup();
            }

            activeGameObject->imGui();
            ImGui::End();
        }
    };

    // * ======================================================
}
