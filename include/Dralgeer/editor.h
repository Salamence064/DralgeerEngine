#ifndef EDITOR_H
#define EDITOR_H

// todo move to its own .cpp file

#include "scene.h"
#include <string>
#include <GLM/glm/glm.hpp>

namespace Dralgeer {
    namespace DImGui {
        // * These functions draw the buttons used to control the values of the attributes of the objects in the editor.

        inline static void drawVec2Control(std::string const &label, glm::vec2 &values,
                float resetValue = 0.0f, float colWidth = DEFAULT_WIDGET_WIDTH);

        inline static void dragFloat(std::string const &label, float &value);
        inline static void dragInt(std::string const &label, int &value);
        inline static bool colorPicker4(std::string const &label, glm::vec4 &color);
    }

    class GameViewWindow {
        private:
            float leftX, rightX, topY, bottomY;
            // bool isPlaying = 0; // todo add in when I add in events

            inline ImVec2 getLargestSize() const;
            inline ImVec2 getCenteredPos(ImVec2 const &size) const;

        public:
            inline void imGui();
            inline bool getWantCaptureMouse() const;
    };

    class PropertiesWindow {
        private:
            PickingTexture pickingTexture;
            float debounce = 0.2f;

        public:
            GameObject* activeGameObject = nullptr;

            inline PropertiesWindow() {};
            inline void init(PickingTexture const &tex);
            inline void update(float dt, Scene* currScene, bool wantCapture);
            inline void imGui() const;
    };
}

#endif // !EDITOR_H
