#pragma once

#include "texture.h"

namespace Dralgeer {
    class FrameBuffer {
        private:
            unsigned int fboID, rboID;
            Texture tex;

        public:
            FrameBuffer() {};
            void init(int width, int height);
            inline unsigned int getTextureID() const { return tex.texID; };

            inline void bind() const {
                glBindFramebuffer(GL_FRAMEBUFFER, fboID);
                tex.bind();
            };

            inline void unbind() const {
                glBindFramebuffer(GL_FRAMEBUFFER, 0);
                tex.unbind();
            };

            ~FrameBuffer() {
                glDeleteRenderbuffers(1, &rboID);
                glDeleteFramebuffers(1, &fboID);
            };
    };

    class PickingTexture {
        private:
            unsigned int fboID, pTexID, depthTexID;

        public:
            int width, height;

            inline PickingTexture() {};
            void init(int width, int height);

            inline int readPixel(int x, int y) const {
                glReadBuffer(GL_COLOR_ATTACHMENT0);

                float pixels[3]; // todo check if this needs to actually be 3 (due to RGB) or if I can just store it to a single value
                glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, pixels);

                std::cout << "Rias\n";

                return (int) pixels[0] - 1;
            };

            inline void enableWriting() const { glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fboID); };
            inline void disableWriting() const { glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); };

            inline ~PickingTexture() {
                glDeleteFramebuffers(1, &fboID);
                glDeleteTextures(1, &pTexID);
                glDeleteTextures(1, &depthTexID);
            };
    };  
}
