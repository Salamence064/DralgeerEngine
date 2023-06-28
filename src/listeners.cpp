#include <Dralgeer/window.h>

namespace Dralgeer {
    namespace MouseListener {
        float calcOrthoX() {
            if (!Window::currScene) { return mWorldX; }

            glm::vec4 temp = {((mX - mGameViewPortX)/mGameViewPortWidth) * 2.0f - 1.0f, 0.0f, 0.0f, 1.0f};
            glm::mat4 t = Window::currScene->camera.invProj;
            glm::mat4 viewProj = Window::currScene->camera.invView * Window::currScene->camera.invProj;
            temp = viewProj * temp;
            return temp.x;
        };

        float calcOrthoY() {
            if (!Window::currScene) { return mWorldY; }

            return ((Window::currScene->camera.invView * Window::currScene->camera.invProj) * 
                    glm::vec4(0.0f, -(((mY - mGameViewPortY)/mGameViewPortHeight) * 2.0f - 1.0f), 0.0f, 1.0f)).y;
        };
    }
}
