// todo put AssetPool

#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <regex>
#include <gl.h>
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
                        indices[i] = match.position() + offset;
                        indices[i + 1] = indices[i] + match.length();
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
}
