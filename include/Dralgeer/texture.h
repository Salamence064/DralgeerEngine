#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <regex>
#include <unordered_map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm/glm.h>

namespace Dralgeer {
    class Shader {
        private:
            std::string vertexSource;
            std::string fragmentSource;
            
            std::string filepath;

            int shaderID;

        public:
            Shader() {};

            // * parse the shader passed in
            void readSource(std::string const &filepath);

            // * compile and link the vertex and fragment shaders
            void compile();

            // * Do not call if already in use.
            inline void use() const { glUseProgram(shaderID); };

            inline void detach() const { glUseProgram(0); };


            // ? Note: OpenGL expects matrices in column major order.

            // * Only call if already in use.
            inline void uploadMat4(char const* name, glm::mat4 const &mat) const {
                int loc = glGetUniformLocation(shaderID, name);
                glUniformMatrix4fv(loc, 1, 0, &mat[0][0]); // todo glm says to do 1, but the actual size is 16
            };
            
            // * Only call if already in use.
            inline void uploadMat3(char const* name, glm::mat3 const &mat) const {
                int loc = glGetUniformLocation(shaderID, name);
                glUniformMatrix3fv(loc, 1, 0, &mat[0][0]);
            };

            // * Only call if already in use.
            inline void uploadVec4(char const* name, glm::vec4 const &vec) const {
                int loc = glGetUniformLocation(shaderID, name);
                glUniform4f(loc, vec.x, vec.y, vec.z, vec.w);
            };

            // * Only call if already in use.
            inline void uploadVec3(char const* name, glm::vec3 const &vec) const {
                int loc = glGetUniformLocation(shaderID, name);
                glUniform3f(loc, vec.x, vec.y, vec.z);
            };

            // * Only call if already in use.
            inline void uploadVec2(char const* name, glm::vec2 const &vec) const {
                int loc = glGetUniformLocation(shaderID, name);
                glUniform2f(loc, vec.x, vec.y);
            };

            // * Only call if already in use.
            inline void uploadFloat(char const* name, float n) const {
                int loc = glGetUniformLocation(shaderID, name);
                glUniform1f(loc, n);
            };

            // * To upload a texture, use this with the proper slot put as the parameter n.
            // * Only call if already in use.
            inline void uploadInt(char const* name, int n) const {
                int loc = glGetUniformLocation(shaderID, name);
                glUniform1i(loc, n);
            };

            // * Only call if already in use.
            inline void uploadIntArr(char const* name, int nums[], int size) const {
                int loc = glGetUniformLocation(shaderID, name);
                glUniform1iv(loc, size, nums);
            };

            ~Shader() { glDeleteProgram(shaderID); };
    };


    class Texture {
        public:
            std::string filepath;
            int width, height;
            unsigned int texID; // ! DO NOT serialize

            Texture() {};

            void init(std::string const &filepath);
            void init(int width, int height);
            inline void bind() const { glBindTexture(GL_TEXTURE_2D, texID); };
            inline void unbind() const { glBindTexture(GL_TEXTURE_2D, 0); };

            ~Texture() { glDeleteTextures(1, &texID); };
    };
}
