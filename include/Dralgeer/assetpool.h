#ifndef ASSET_POOL_H
#define ASSET_POOL_H

// todo not sure why this is littered in errors but we will run the program to see

#include "component.h"

namespace AssetPool {
        namespace {
            static std::unordered_map<std::string, Shader> shaders;
            static std::unordered_map<std::string, Texture> textures;
            static std::unordered_map<std::string, SpriteSheet> spriteSheets;
        }

        inline static Shader getShader(std::string const &filepath) {
            if (shaders.find(filepath) != shaders.end()) { return shaders[filepath]; }

            // add new shader if it is not included
            Shader shader;
            shader.readSource(filepath);
            shader.compile();
            shaders.insert({filepath, shader});
            return shader;
        };

        inline static Texture getTexture(std::string const &filepath) {
            if (textures.find(filepath) != textures.end()) { return textures[filepath]; }

            // add new texture if it is not included
            Texture texture;
            texture.init(filepath);
            textures.insert({filepath, texture});
            return texture;
        };


        inline static void addSpriteSheet(std::string const &filepath, SpriteSheet const &spr) {
            if (spriteSheets.find(filepath) == spriteSheets.end()) { spriteSheets.insert({filepath, spr}); }
        };

        inline static SpriteSheet getSpriteSheet(std::string const &filepath) {
            if (spriteSheets.find(filepath) != spriteSheets.end()) { return spriteSheets[filepath]; };
            // todo remove the error thrown in the future in favor of a log message + returning nullptr
            return SpriteSheet();
        };
    }

#endif // !ASSET_POOL_H
