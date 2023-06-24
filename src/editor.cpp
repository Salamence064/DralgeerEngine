// ? Provide definitions for functions in editor.h

#include <Dralgeer/framebuffer.h>
#include <Dralgeer/listeners.h>
#include <Dralgeer/window.h>

namespace Dralgeer {
    // * ======================================================
    // * DImGui Stuff

    inline static void DImGui::drawVec2Control(std::string const &label, glm::vec2 &values,
            float resetValue = 0.0f, float colWidth = DEFAULT_WIDGET_WIDTH)
    {
        ImGui::PushID(label.c_str());

        ImGui::Columns(2);
        ImGui::SetColumnWidth(0, colWidth);
        ImGui::Text(label.c_str());
        ImGui::NextColumn();

        ImGui::PushStyleVar(ImGuiStyleVar_::ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));

        float lineHeight = ImGui::GetFontSize() + ImGui::GetStyle().FramePadding.y * 2.0f;
        ImVec2 buttonSize(lineHeight + 3.0f, lineHeight);
        float widthEach = (ImGui::CalcItemWidth() * 0.5f) - buttonSize.x;

        ImGui::PushItemWidth(widthEach);
        ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Button, ImVec4(0.88235f, 0.00392f, 0.00392f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_ButtonHovered, ImVec4(0.88235f, 0.30392f, 0.30392f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_ButtonActive, ImVec4(0.88235f, 0.00392f, 0.00392f, 1.0f));
        if (ImGui::Button("X", buttonSize)) { values.x = resetValue; }

        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        ImGui::DragFloat("%.2fx", &values.x, 0.1f);
        ImGui::PopItemWidth();

        ImGui::SameLine();

        ImGui::PushItemWidth(widthEach);
        ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Button, ImVec4(0.2f, 0.2f, 1.0f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_ButtonHovered, ImVec4(0.4f, 0.4f, 1.0f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_ButtonActive, ImVec4(0.2f, 0.2f, 1.0f, 1.0f));
        if (ImGui::Button("Y", buttonSize)) { values.y = resetValue; }

        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        ImGui::DragFloat("%.2fy", &values.y, 0.1f);
        ImGui::PopItemWidth();

        ImGui::NextColumn();
        
        ImGui::Columns(1);
        ImGui::PopStyleVar();
        ImGui::PopID();
    };

    inline static void DImGui::dragFloat(std::string const &label, float &value) {
        ImGui::PushID(label.c_str());

        ImGui::Columns(2);
        ImGui::SetColumnWidth(0, DEFAULT_WIDGET_WIDTH);
        ImGui::Text(label.c_str());
        ImGui::NextColumn();

        ImGui::DragFloat("%.2fdragFloat", &value, 0.1f);

        ImGui::Columns(1);
        ImGui::PopID();
    };

    inline static void DImGui::dragInt(std::string const &label, int &value) {
        ImGui::PushID(label.c_str());

        ImGui::Columns(2);
        ImGui::SetColumnWidth(0, DEFAULT_WIDGET_WIDTH);
        ImGui::Text(label.c_str());
        ImGui::NextColumn();

        // todo may cause issues (consult java implementation if this does happen)
        ImGui::DragInt("dragInt", &value, 0.1f);

        ImGui::Columns(1);
        ImGui::PopID();
    };

    inline static bool DImGui::colorPicker4(std::string const &label, glm::vec4 &color) {
        bool res = 0;
        ImGui::PushID(label.c_str());

        ImGui::Columns(2);
        ImGui::SetColumnWidth(0, DEFAULT_WIDGET_WIDTH);
        ImGui::Text(label.c_str());
        ImGui::NextColumn();

        float c[4] = {color.x, color.y, color.z, color.w};
        if (ImGui::ColorEdit4("##ColorPicker", c)) {
            color.x = c[0]; color.y = c[1]; color.z = c[2]; color.w = c[3];
            res = 1;
        }

        ImGui::Columns(1);
        ImGui::PopID();

        return res;
    };

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

    inline void GameViewWindow::imGui() {
        ImGui::Begin("Game Viewport", NULL, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

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

        ImGui::Image((int*) Window::frameBuffer.getTextureID(), windowSize, ImVec2(0, 1), ImVec2(1, 0));

        MouseListener::mGameViewPortX = bottomLeft.x;
        MouseListener::mGameViewPortY = bottomLeft.y;
        MouseListener::mGameViewPortWidth = windowSize.x;
        MouseListener::mGameViewPortHeight = windowSize.y;

        ImGui::End();
    };

    inline bool GameViewWindow::getWantCaptureMouse() const {
        return MouseListener::mX >= leftX && MouseListener::mX <= rightX && MouseListener::mY >= bottomY && MouseListener::mY <= topY;
    };

    // * ======================================================
    // * PropertiesWindow Stuff

    inline void PropertiesWindow::init(PickingTexture const &tex) { pickingTexture.init(tex.width, tex.height); };

    inline void PropertiesWindow::update(float dt, Scene* currScene, bool wantCapture) {
        if (!wantCapture) { return; }

        debounce -= dt;

        if (MouseListener::mButtonPressed[GLFW_MOUSE_BUTTON_LEFT] && debounce < 0.0f) {
            int x = (int) MouseListener::mX;
            int y = (int) MouseListener::mY;

            int id = pickingTexture.readPixel(x, y);
            GameObject* go = currScene->getGameObject(id);

            if (go && go->pickable) { activeGameObject = go; }
            else if (!go && !MouseListener::mIsDragging) { activeGameObject = nullptr; }

            debounce = 0.2f;
        }
    };

    inline void PropertiesWindow::imGui() const {
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
