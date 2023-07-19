#include <Dralgeer/debugdraw.h>

namespace Dralgeer {
    namespace DebugDraw {
        Line2D* lines = new Line2D[64];
        int numLines = 0;
        int capacity = 64;

        float vertices[DEBUG_VERTEX_ARR_SIZE];
        Shader shader;

        unsigned int vaoID, vboID;
        bool started = 0;
    }
}
