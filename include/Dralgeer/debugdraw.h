#ifndef DEBUG_DRAW_H
#define DEBUG_DRAW_H

#include "assetpool.h"

namespace Dralgeer {
    namespace DebugDraw {
        struct Line2D {
            glm::vec2 start;
            glm::vec2 end;
            glm::vec3 color;
            int lifetime;

            inline int beginFrame() {
                lifetime--;
                return lifetime;
            };
        };


        // todo make into a dynamic pointer array
        static Line2D* lines = new Line2D[capacity];
        static int numLines = 0;
        static int capacity = 8;

        // 6 floats per vertex, 2 vertices per line
        static float vertexArray[DEBUG_VERTEX_ARR_SIZE];
        static Shader shader;

        static unsigned int vaoID, vboID;
        static bool started = 0;

        // ! fuck it, we are using a temporary camera for now -- replace when I finish scene.h
        Camera camera = {glm::vec2(0.0f)}; // ! could be the cause of some issues

        inline void start();
        inline void beginFrame();
        inline void draw();
        inline void destroy();
        inline void addLine2D(glm::vec2 const &start, glm::vec2 const &end, glm::vec3 const &color = glm::vec3(0.882f, 0.004f, 0.004f),
                int lifetime = 1);

        // TODO: add addBox2D funcs
        // TODO: add addCircle funcs
        // TODO: add constants for common colors
    }
}

#endif // !DEBUG_DRAW_H
