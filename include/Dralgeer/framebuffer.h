#pragma once

#include "texture.h"
#include "listeners.h" // todo i think this is just for debugging

namespace Dralgeer {
    class FrameBuffer {
        private:
            unsigned int rboID;
            Texture tex;

        public:
            unsigned int fboID; // ! debugging

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
            unsigned int depthTexID;

        public:
            unsigned int pTexID, fboID; // ! debugging

            int width, height;

            bool test = 1; // ! debugging

            inline PickingTexture() {};
            void init(int width, int height);

            inline int readPixel(int x, int y) const {
                glBindFramebuffer(GL_FRAMEBUFFER, fboID);
                glReadBuffer(GL_COLOR_ATTACHMENT0);

                float pixels[3];
                glReadPixels(2*x, 2*y, 1, 1, GL_RGB, GL_FLOAT, pixels); // ! there's some issue that makes me need to multiply by 2 for it, but I have no idea why

                glBindFramebuffer(GL_FRAMEBUFFER, 0);
                return pixels[0];
            };

            inline void enableWriting() const { glBindFramebuffer(GL_FRAMEBUFFER, fboID); };
            inline void disableWriting() const { glBindFramebuffer(GL_FRAMEBUFFER, 0); };

            inline ~PickingTexture() {
                glDeleteFramebuffers(1, &fboID);
                glDeleteTextures(1, &pTexID);
                glDeleteTextures(1, &depthTexID);
            };
    };  
}
