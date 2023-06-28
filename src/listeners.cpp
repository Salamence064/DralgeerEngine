#include <Dralgeer/window.h>

namespace Dralgeer {
    namespace MouseListener {
        float calcOrthoX() {
            return ((Window::currScene->camera.invView * Window::currScene->camera.invProj) * 
                    glm::vec4(((mX - mGameViewPortX)/mGameViewPortWidth) * 2.0f - 1.0f, 0.0f, 0.0f, 1.0f)).x;
        };

        float calcOrthoY() {
            return ((Window::currScene->camera.invView * Window::currScene->camera.invProj) * 
                    glm::vec4(0.0f, -(((mY - mGameViewPortY)/mGameViewPortHeight) * 2.0f - 1.0f), 0.0f, 1.0f)).y;
        };
    }
}
