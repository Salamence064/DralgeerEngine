#include <Dralgeer/window.h>

namespace Dralgeer {
    namespace MouseListener {
        // todo these don't work as extern functions.
        // todo add separate functions in the MouseListener that will change the values of the worldX and worldY
        // todo but are not static and can be called by other parts of the program when it is needed

        // todo add in an updateWorldCoords function to the MouseListener that can be used outside of the callbacks

        // todo update to just take a camera as a parameter instead of doing this

        void updateWorldCoords() {
            if (!Window::currScene) { return; } // ensure there is an active scene for this to update

            mLastWorldX = mWorldX;
            mLastWorldY = mWorldY;

            mWorldX = ((Window::currScene->camera.invView * Window::currScene->camera.invProj) * 
                    glm::vec4(((mX - mGameViewPortX)/mGameViewPortWidth) * 2.0f - 1.0f, 0.0f, 0.0f, 1.0f)).x;

            mWorldY = ((Window::currScene->camera.invView * Window::currScene->camera.invProj) * 
                    glm::vec4(0.0f, -(((mY - mGameViewPortY)/mGameViewPortHeight) * 2.0f - 1.0f), 0.0f, 1.0f)).y;
        };

        // float calcOrthoX() {
        //     if (!Window::currScene) { return mWorldX; }

        //     glm::vec4 temp = {((mX - mGameViewPortX)/mGameViewPortWidth) * 2.0f - 1.0f, 0.0f, 0.0f, 1.0f};
        //     glm::mat4 t = Window::currScene->camera.invProj;
        //     glm::mat4 viewProj = Window::currScene->camera.invView * Window::currScene->camera.invProj;
        //     temp = viewProj * temp;
        //     return temp.x;
        // };

        // float calcOrthoY() {
        //     if (!Window::currScene) { return mWorldY; }

        //     return ((Window::currScene->camera.invView * Window::currScene->camera.invProj) * 
        //             glm::vec4(0.0f, -(((mY - mGameViewPortY)/mGameViewPortHeight) * 2.0f - 1.0f), 0.0f, 1.0f)).y;
        // };
    }
}
