#include <Dralgeer/framebuffer.h>

namespace Dralgeer {
    // * =======================================================
    // * FrameBuffer Stuff

    void FrameBuffer::init(int width, int height) {
        // generate the framebuffer
        glGenFramebuffers(1, &fboID);
        glBindFramebuffer(GL_FRAMEBUFFER, fboID);

        // create the texture to render the data to and attach it to our frame buffer
        tex.init(width, height);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex.texID, 0);
        tex.unbind();

        // create the render buffer to store depth data
        glGenRenderbuffers(1, &rboID);
        glBindRenderbuffer(GL_RENDERBUFFER, rboID);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rboID);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);

        // ensure the framebuffer is complete
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) { throw std::runtime_error("[ERROR] Framebuffer is not complete.\n"); }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    };

    // * =======================================================
    // * PickingTexture Stuff

    void PickingTexture::init(int width, int height) {
        this->width = width;
        this->height = height;

        // generate the framebuffer
        glGenFramebuffers(1, &fboID);
        glBindFramebuffer(GL_FRAMEBUFFER, fboID);

        // create the texture to render the data to and attach it to our frame buffer
        glGenTextures(1, &pTexID);
        glBindTexture(GL_TEXTURE_2D, pTexID);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, width, height, 0, GL_RGB, GL_FLOAT, 0);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pTexID, 0);

        // create the texture object for the depth buffer
        glEnable(GL_DEPTH_TEST);
        glGenTextures(1, &depthTexID);
        glBindTexture(GL_TEXTURE_2D, depthTexID);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexID, 0);
        glDisable(GL_DEPTH_TEST);

        // disable the reading
        glReadBuffer(GL_NONE);
        glDrawBuffer(GL_COLOR_ATTACHMENT0); // todo im unsure if the color attachment I'm drawing to could be causing the issue
        // todo I think I will have to watch the videos

        // ensure the frame buffer is complete
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
            throw std::runtime_error("[ERROR] Framebuffer was unable to be initialized.\n\tIt is not complete.\n");
        }

        // unbind the texture and framebuffer
        glBindTexture(GL_TEXTURE_2D, 0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    };

    // * =======================================================
}
