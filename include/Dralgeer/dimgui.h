#pragma once

#include "constants.h"
#include <string>
#include <GLM/glm/glm.h>
#include <IMGUI/imgui.h>

namespace Dralgeer {
    namespace DImGui {
        // * These functions draw the buttons used to control the values of the attributes of the objects in the editor.

        inline static void drawVec2Control(std::string const &label, glm::vec2 &values,
                float resetValue = 0.0f, float colWidth = DEFAULT_WIDGET_WIDTH)
        {
            ImGui::PushID(label.c_str());

            ImGui::Columns(2);
            ImGui::SetColumnWidth(0, colWidth);
            ImGui::Text(label.c_str());
            ImGui::NextColumn();

            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));

            float lineHeight = ImGui::GetFontSize() + ImGui::GetStyle().FramePadding.y * 2.0f;
            ImVec2 buttonSize(lineHeight + 3.0f, lineHeight);
            float widthEach = (ImGui::CalcItemWidth() * 0.5f) - buttonSize.x;

            ImGui::PushItemWidth(widthEach);
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.88235f, 0.00392f, 0.00392f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.88235f, 0.30392f, 0.30392f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.88235f, 0.00392f, 0.00392f, 1.0f));
            if (ImGui::Button("X", buttonSize)) { values.x = resetValue; }

            ImGui::PopStyleColor(3);

            ImGui::SameLine();
            ImGui::DragFloat("##x", &values.x, 0.1f);
            ImGui::PopItemWidth();

            ImGui::SameLine();

            ImGui::PushItemWidth(widthEach);
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.2f, 1.0f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.4f, 0.4f, 1.0f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0.2f, 0.2f, 1.0f, 1.0f));
            if (ImGui::Button("Y", buttonSize)) { values.y = resetValue; }

            ImGui::PopStyleColor(3);

            ImGui::SameLine();
            ImGui::DragFloat("##y", &values.y, 0.1f);
            ImGui::PopItemWidth();

            ImGui::NextColumn();
            
            ImGui::Columns(1);
            ImGui::PopStyleVar();
            ImGui::PopID();
        };

        inline static void dragFloat(std::string const &label, float &value) {
            ImGui::PushID(label.c_str());

            ImGui::Columns(2);
            ImGui::SetColumnWidth(0, DEFAULT_WIDGET_WIDTH);
            ImGui::Text(label.c_str());
            ImGui::NextColumn();

            ImGui::DragFloat("##dragFloat", &value, 0.1f);

            ImGui::Columns(1);
            ImGui::PopID();
        };

        inline static void dragInt(std::string const &label, int &value) {
            ImGui::PushID(label.c_str());

            ImGui::Columns(2);
            ImGui::SetColumnWidth(0, DEFAULT_WIDGET_WIDTH);
            ImGui::Text(label.c_str());
            ImGui::NextColumn();

            // todo may cause issues (consult java implementation if this does happen)
            ImGui::DragInt("##dragInt", &value, 0.1f);

            ImGui::Columns(1);
            ImGui::PopID();
        };

        inline static bool colorPicker4(std::string const &label, glm::vec4 &color) {
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
    }
}
