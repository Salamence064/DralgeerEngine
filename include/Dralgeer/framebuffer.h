#ifndef FRAME_BUFFER_H
#define FRAME_BUFFER_H

#include "texture.h"

namespace Dralgeer {
    class FrameBuffer {
        private:
            unsigned int fboID;
            Texture tex;

        public: // todo google the thing needed to make sure the fbo and texture get deleted after this gets deleted
            // todo if needed make this a default constructor and make an init function
            FrameBuffer (int width, int height);
            inline void bind() const;
            inline void unbind() const;
            inline int getTextureID() const;
    };

    class PickingTexture {
        private:
            unsigned int fboID;

        public:
            int width, height;

            inline PickingTexture() {};
            inline void init(int width, int height);
            inline int readPixel(int x, int y) const;
            inline void enableWriting() const;
            inline void disableWriting() const;
    };  
}

#endif // !FRAME_BUFFER_H
