#pragma once

#include "texture.h"
#include "listeners.h"

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
                // todo
                // first: refactor the renderer to store gameobjects with SpriteRenderers
                // // second: don't store a gameobject inside of a component and refactor the program based around that (maybe)
                // third: ensure the proper id is getting passed from the renderer to the pickingShader

                glBindFramebuffer(GL_FRAMEBUFFER, fboID);
                glReadBuffer(GL_COLOR_ATTACHMENT0);

                // todo this doesn't properly read the entityID for all of the sprites
                // todo look through tutorials probably and see how it's supposed to be done
                int pixel;
                glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &pixel);

                std::cout << pixel << "\n";

                glBindFramebuffer(GL_FRAMEBUFFER, 0);
                return pixel;
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
