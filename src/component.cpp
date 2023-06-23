// ? Contain the definitions for components which need to access information about the current scene here.

#include <Dralgeer/window.h>

namespace Dralgeer {
    inline void GridLines::update(float dt) {
        Camera cam = Window::currScene->camera; // make the code more readable

        int firstX = ((int) (cam.pos.x * cam.zoom) - GRID_WIDTH);
        int firstY = ((int) (cam.pos.y * cam.zoom) - GRID_HEIGHT);
        int width = ((int) (cam.projSize.x * cam.zoom)) + 2 * GRID_WIDTH;
        int height = ((int) (cam.projSize.y * cam.zoom)) + 2 * GRID_HEIGHT;

        int vertLines = ((int) (cam.projSize.x * cam.zoom)/GRID_WIDTH) + 2;
        int horzLines = ((int) (cam.projSize.y * cam.zoom)/GRID_HEIGHT) + 2;

        int maxLines = MAX(vertLines, horzLines);
        glm::vec3 color(0.2f, 0.2f, 0.2f);

        for (int i = 0; i < maxLines; ++i) {
            int x = firstX + i*GRID_WIDTH;
            int y = firstY + i*GRID_HEIGHT;

            if (i < vertLines) { DebugDraw::addLine2D(glm::vec2(x, firstX), glm::vec2(x, firstY + height), color); }
            if (i < horzLines) { DebugDraw::addLine2D(glm::vec2(firstX, y), glm::vec2(firstX + width, y), color); }
        }
    };
}
