#pragma once

#define GLEW_STATIC

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <regex>
#include <unordered_map>
#include <STB/stb_image.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm/glm.hpp>

namespace Dralgeer {
    class Shader {
        private:
            char const* sources[2]; // sources for the vertex and fragment shaders (vertex at 0, fragment at 1)
            int sizes[2]; // sizes for the vertex and fragment shaders (vertex at 0, fragment at 1)
            std::string filepath;

            int shaderID;
            bool inUse = 0;

        public:
            Shader() {};

            // * parse the shader passed in
            Shader(std::string const &filepath) {
                this->filepath = filepath;
                
                try {
                    std::ifstream f(filepath);
                    if (!f.is_open()) { throw std::runtime_error("File '" + filepath + "' could not be opened."); }

                    std::stringstream buffer;
                    buffer << f.rdbuf();
                    std::string source = buffer.str();
                    std::string s = source;
                    std::string splitStr[4];

                    // determine the indices using RegEx
                    size_t indices[4];
                    size_t offset = 0;
                    std::smatch match;
                    
                    for (int i = 0; std::regex_search(s, match, std::regex("(#type)( )+([a-zA-Z]+)")); i+=2) {
                        indices[i] = match.position() + offset + 6;
                        indices[i + 1] = match.length() - 6;
                        s = match.suffix();
                        offset = source.length() - s.length();
                    }
                    
                    splitStr[0] = source.substr(indices[0], indices[1]); // type of the first part
                    splitStr[1] = source.substr(indices[1] + 1, indices[2]); // store the first part of the shader data 
                    splitStr[2] = source.substr(indices[2], indices[3]); // type of the second part
                    splitStr[3] = source.substr(indices[3] + 1); // store the second part of the shader data
                    
                    // first part
                    if (splitStr[0] == "vertex") { sources[0] = splitStr[1].c_str(); sizes[0] = splitStr[1].length(); }
                    else if (splitStr[0] == "fragment") { sources[1] = splitStr[1].c_str(); sizes[1] = splitStr[1].length(); }
                    else { throw std::runtime_error("Unexpected token '" + splitStr[0] + "'"); }

                    // second part
                    if (splitStr[2] == "vertex") { sources[0] = splitStr[3].c_str(); sizes[0] = splitStr[3].length(); }
                    else if (splitStr[2] == "fragment") { sources[1] = splitStr[3].c_str(); sizes[1] = splitStr[3].length(); }
                    else { throw std::runtime_error("Unexpected token '" + splitStr[2] + "'"); }

                } catch (std::runtime_error e) {
                    // todo: for future log the error
                    std::cout << e.what() << "\n";
                }
            };

            // * compile and link the vertex and fragment shaders
            void compile() {
                // Load and compile the vertex shader, then pass it to the GPU
                int id = glCreateShader(GL_VERTEX_SHADER);
                glShaderSource(id, 2, sources, sizes);
                glCompileShader(id);

                // check for compilation errors
                int success = 0;
                glGetShaderiv(id, GL_COMPILE_STATUS, &success);
                if (!success) {
                    int len = 0;
                    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &len);
                    std::cout << "ERROR: '" << filepath << "'\n\tShader compilation failed.\n";
                    
                    char* errorLog = nullptr;
                    glGetShaderInfoLog(id, len, &len, errorLog);

                    for (int i = 0; i < len; ++i) { std::cout << errorLog[i]; }
                    std::cout << "\n";

                    glDeleteShader(id);
                    if (errorLog) { delete[] errorLog; }
                    return;
                }

                // link shader
                shaderID = glCreateProgram();
                glAttachShader(shaderID, id);
                glLinkProgram(shaderID);

                // check for linking errors
                glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
                if(!success) {
                    int len = 0;
                    glGetProgramiv(shaderID, GL_INFO_LOG_LENGTH, &len);
                    std::cout << "ERROR: '" << filepath << "'\n\tShader linking failed.\n";

                    char* errorLog = nullptr;
                    glGetShaderInfoLog(shaderID, len, &len, errorLog);

                    for (int i = 0; i < len; ++i) { std::cout << errorLog[i]; }
                    std::cout << "\n";

                    glDeleteProgram(shaderID);
                    glDeleteShader(id);
                    if (errorLog) { delete[] errorLog; }
                }
            };

            inline void use() {
                if (!inUse) {
                    // bind the shader program
                    glUseProgram(shaderID);
                    inUse = 1;
                }
            };

            inline void detach() {
                glUseProgram(0);
                inUse = 0;
            };


            // ? Note: OpenGL expects matrices in column major order.

            inline void uploadMat4(char const* name, glm::mat4 const &mat) {
                int loc = glGetUniformLocation(shaderID, name);
                use(); // make sure it is in use

                float buffer[16];
                for (int i = 0; i < 4; ++i) { for (int j = 0; j < 4; ++j) { buffer[4*i + j] = mat[j][i]; }}
                glUniformMatrix4fv(loc, 16, 0, buffer);
            };
            
            inline void uploadMat3(char const* name, glm::mat3 const &mat) {
                int loc = glGetUniformLocation(shaderID, name);
                use(); // ensure it is in use

                float buffer[9];
                for (int i = 0; i < 3; ++i) { for (int j = 0; j < 3; ++j) { buffer[3*i + j] = mat[j][i]; }}
                glUniformMatrix3fv(loc, 9, 0, buffer);
            };

            inline void uploadVec4(char const* name, glm::vec4 const &vec) {
                int loc = glGetUniformLocation(shaderID, name);
                use(); // ensure it is in use
                glUniform4f(loc, vec.x, vec.y, vec.z, vec.w);
            };

            inline void uploadVec3(char const* name, glm::vec3 const &vec) {
                int loc = glGetUniformLocation(shaderID, name);
                use(); // ensure it is in use
                glUniform3f(loc, vec.x, vec.y, vec.z);
            };

            inline void uploadVec2(char const* name, glm::vec2 const &vec) {
                int loc = glGetUniformLocation(shaderID, name);
                use(); // ensure it is in use
                glUniform2f(loc, vec.x, vec.y);
            };

            inline void uploadFloat(char const* name, float n) {
                int loc = glGetUniformLocation(shaderID, name);
                use(); // ensure it is in use
                glUniform1f(loc, n);
            };

            // * To upload a texture, use this with the proper slot put as the parameter n.
            inline void uploadInt(char const* name, int n) {
                int loc = glGetUniformLocation(shaderID, name);
                use(); // ensure it is in use
                glUniform1i(loc, n);
            };

            inline void uploadIntArr(char const* name, int nums[], int size) {
                int loc = glGetUniformLocation(shaderID, name);
                use(); // ensure it is in use
                glUniform1iv(loc, size, nums);
            };
    };


    class Texture {
        public:
            std::string filepath;
            int width, height;
            unsigned int texID; // ! DO NOT serialize

            Texture() {};

            // ! Not sure if we need this constructor
            Texture(int width, int height) : width(width), height(height) {
                filepath = "generated";

                // generate texture on the GPU
                glGenTextures(1, &texID);
                glBindTexture(GL_TEXTURE_2D, texID);

                // define the type of interpolation when stretching or shrinking the image (linear)
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
            };

            void init(std::string const &filepath) {
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
            };

            bool operator == (Texture const &tex) const { return tex.width == width && tex.height == height && tex.texID == texID && tex.filepath == filepath; };

            inline void bind() const { glBindTexture(GL_TEXTURE_2D, texID); };
            inline void unbind() const { glBindTexture(GL_TEXTURE_2D, 0); };
    };


    namespace AssetPool {
        namespace {
            static std::unordered_map<std::string, Shader> shaders;
            static std::unordered_map<std::string, Texture> textures;
            // static std::unordered_map<std::string, SpriteSheet> spriteSheets; // todo add when I create sprites and sprite sheets
        }

        inline Shader getShader(std::string const &filepath) {
            if (shaders.find(filepath) != shaders.end()) { return shaders[filepath]; }

            // add new shader if it is not included
            Shader shader(filepath);
            shader.compile();
            shaders.insert({filepath, shader});
            return shader;
        };

        inline Texture getTexture(std::string const &filepath) {
            if (textures.find(filepath) != textures.end()) { return textures[filepath]; }

            // add new texture if it is not included
            Texture texture;
            texture.init(filepath);
            textures.insert({filepath, texture});
            return texture;
        };
    }
}
