#pragma once

#include "texture.h"
#include "listeners.h" // todo i think this is just for debugging

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
            unsigned int fboID, depthTexID;

        public:
            unsigned int pTexID;

            int width, height;

            bool test = 1;

            inline PickingTexture() {};
            void init(int width, int height);

            // todo the goal of this coding session will be:
            // get readPixel to correctly read the pixel
            // could potentially look into what's being passed to the shader through the vbo and see if the attribute for it is getting enabled

            inline int readPixel(int x, int y) const {
                if (test) { return 0; }

                // todo
                // first: refactor the renderer to store gameobjects with SpriteRenderers
                // // second: don't store a gameobject inside of a component and refactor the program based around that (maybe)
                // third: ensure the proper id is getting passed from the renderer to the pickingShader

                // todo seems to only ever read some of it while mouse is held down

                // todo I wonder if part of the issue is caused by the artifacts caused from drag clicking
                // todo try temporarily removing drag clicking and see if that is in fact the issue
                // todo I think I will do this when I come back to it

                std::cout << "[DEBUG] x, y: " << x << ", " << y << "\n";
                // std::cout << "[DEBUG] Mouse x, y: " << MouseListener::mWorldX << ", " << MouseListener::mWorldY << "\n";

                glBindFramebuffer(GL_FRAMEBUFFER, fboID);
                glReadBuffer(GL_COLOR_ATTACHMENT0);

                // todo this doesn't properly read the entityID for all of the sprites
                // todo look through tutorials probably and see how it's supposed to be done
                float pixels[3];
                glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, pixels);

                std::cout << pixels[0] << ", " << pixels[1] << ", " << pixels[2] << "\n";

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
