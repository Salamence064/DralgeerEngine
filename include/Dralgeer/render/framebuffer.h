// todo should include pickingtexture (maybe)

#pragma once

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
}
