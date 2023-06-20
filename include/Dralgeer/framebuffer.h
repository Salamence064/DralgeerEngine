// todo should include pickingtexture

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
            FrameBuffer (int width, int height) {
                // generate the framebuffer
                glGenFramebuffers(1, &fboID);
                glBindFramebuffer(GL_FRAMEBUFFER, fboID);

                // create the texture to render the data to and attach it to our frame buffer
                tex = Texture(width, height);
                glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex.texID, 0);

                // create the render buffer to store depth data
                unsigned int rboID;
                glGenRenderbuffers(1, &rboID);
                glBindRenderbuffer(GL_RENDERBUFFER, rboID);
                glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32, width, height);
                glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboID);

                // ensure the framebuffer is complete
                if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE) {
                    glBindFramebuffer(GL_FRAMEBUFFER, 0);
                    return;
                }

                throw std::runtime_error("[ERROR] Framebuffer is not complete.\n");
            };

            inline void bind() const { glBindFramebuffer(GL_FRAMEBUFFER, fboID); };
            inline void unbind() const { glBindFramebuffer(GL_FRAMEBUFFER, 0); };
            inline int getTextureID() const { return tex.texID; };
    };

    class PickingTexture {
        private:
            unsigned int fboID;

        public:
            inline PickingTexture(int width, int height) { init(width, height); };

            inline void init(int width, int height) {
                // generate the framebuffer
                glGenFramebuffers(1, &fboID);
                glBindFramebuffer(GL_FRAMEBUFFER, fboID);

                // create the texture to render the data to and attach it to our frame buffer
                unsigned int pTexID = 0;
                glGenTextures(1, &pTexID);
                glBindTexture(GL_TEXTURE_2D, pTexID);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, width, height, 0, GL_RGB, GL_FLOAT, 0);
                glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pTexID, 0);

                // create the texture object for the depth buffer
                unsigned int depthTexID = 0;
                glEnable(GL_DEPTH_TEST);
                glGenTextures(1, &depthTexID);
                glBindTexture(GL_TEXTURE_2D, depthTexID);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
                glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexID, 0);
                glDisable(GL_DEPTH_TEST);

                // disable the reading
                glReadBuffer(GL_NONE);
                glDrawBuffer(GL_COLOR_ATTACHMENT0);

                // ensure the frame buffer is complete
                if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
                    throw std::runtime_error("[ERROR] Framebuffer was unable to be initialized.\n\tIt is not complete.\n");
                }

                // unbind the texture and framebuffer
                glBindTexture(GL_TEXTURE_2D, 0);
                glBindFramebuffer(GL_FRAMEBUFFER, 0);
            };

            inline int readPixel(int x, int y) const {
                glBindFramebuffer(GL_READ_FRAMEBUFFER, fboID);
                glReadBuffer(GL_COLOR_ATTACHMENT0);

                float pixels[3]; // todo check if this needs to actually be 3 (due to RGB) or if I can just store it to a single value
                glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, pixels);

                // todo see if the reading needs to be unbound

                return (int) pixels[0] - 1;
            };

            inline void enableWriting() const { glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fboID); };
            inline void disableWriting() const { glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); };
    };  
}

#endif // !FRAME_BUFFER_H
