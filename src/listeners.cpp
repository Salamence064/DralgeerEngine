#include <Dralgeer/camera.h>
#include <Dralgeer/listeners.h>

namespace Dralgeer {
    namespace MouseListener {
        void updateWorldCoords(Camera const &cam) {
            mLastWorldX = mWorldX;
            mLastWorldY = mWorldY;

            mWorldX = ((cam.invView * cam.invProj) * glm::vec4(((mX - mGameViewPortX)/mGameViewPortWidth) * 2.0f - 1.0f, 0.0f, 0.0f, 1.0f)).x;
            mWorldY = ((cam.invView * cam.invProj) * glm::vec4(0.0f, -(((mY - mGameViewPortY)/mGameViewPortHeight) * 2.0f - 1.0f), 0.0f, 1.0f)).y;
        };
    }
}
