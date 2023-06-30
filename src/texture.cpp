#define STB_IMAGE_IMPLEMENTATION
#include <Dralgeer/texture.h>
#include <STB/stb_image.h>
#include <iostream> // ! for debugging

namespace Dralgeer {
    Texture::Texture(int width, int height) : width(width), height(height) {
        filepath = "generated";

        // generate texture on the GPU
        glGenTextures(1, &texID);
        glBindTexture(GL_TEXTURE_2D, texID);

        // define the type of interpolation when stretching or shrinking the image (linear)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
    };

    void Texture::init(std::string const &filepath) { // todo issue may arrise from here
        this->filepath = filepath;

        // generate texture on the GPU
        glGenTextures(1, &texID);
        glBindTexture(GL_TEXTURE_2D, texID);

        // * set texture parameters
        // repeat the image in both directions
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // when stretching or shriking the image, pixelate
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        // * load the image
        int width, height, channels;
        stbi_set_flip_vertically_on_load(1);
        unsigned char* image = stbi_load(filepath.c_str(), &width, &height, &channels, 0);

        if (image) {
            this->width = width;
            this->height = height;

            // upload image to the GPU
            if (channels == 3) { // RGB
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

            } else if (channels == 4) { // RGBA
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

            } else {
                stbi_image_free(image);
                throw std::runtime_error("ERROR: (Texture) Unkown number of channels '" + std::to_string(channels) + "'\n");
            }

        } else {
            stbi_image_free(image);
            throw std::runtime_error("ERROR: (Texture) Could not load image '" + filepath + "'\n");
        }

        stbi_image_free(image);
        glBindTexture(GL_TEXTURE_2D, 0); // unbind the texture
    };
}
