#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <regex>
#include <unordered_map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GLM/glm/glm.hpp>
#include <GLM/glm/gtc/type_ptr.hpp>

namespace Dralgeer {
    class Shader {
        private:
            std::string vertexSource;
            std::string fragmentSource;
            
            std::string filepath;

            int shaderID;
            bool inUse = 0;

        public:
            Shader() {};

            // * parse the shader passed in
            void readSource(std::string const &filepath) {
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
                    
                    size_t i1 = source.find("\n", indices[0]);
                    size_t i2 = source.find("\n", indices[2]);

                    splitStr[0] = source.substr(indices[0], indices[1]); // type of the first part
                    splitStr[1] = source.substr(i1 + 1, indices[2] - i1 - 7); // store the first part of the shader data 
                    splitStr[2] = source.substr(indices[2], indices[3]); // type of the second part
                    splitStr[3] = source.substr(i2 + 1); // store the second part of the shader data

                    // first part
                    if (splitStr[0] == "vertex") { vertexSource = splitStr[1]; }
                    else if (splitStr[0] == "fragment") { fragmentSource = splitStr[1]; }
                    else { throw std::runtime_error("Unexpected token '" + splitStr[0] + "'"); }

                    // second part
                    if (splitStr[2] == "vertex") { vertexSource = splitStr[3]; }
                    else if (splitStr[2] == "fragment") { fragmentSource = splitStr[3]; }
                    else { throw std::runtime_error("Unexpected token '" + splitStr[2] + "'"); }

                } catch (std::runtime_error e) {
                    // todo: for future log the error
                    std::cout << e.what() << "\n";
                }
            };

            // * compile and link the vertex and fragment shaders
            void compile() {
                char const* vSrc = vertexSource.c_str();
                char const* fSrc = fragmentSource.c_str();

                // Load and compile the vertex shader, then pass it to the GPU
                GLuint vertexID = glCreateShader(GL_VERTEX_SHADER);
                glShaderSource(vertexID, 1, &vSrc, NULL);
                glCompileShader(vertexID);

                // check for compilation errors
                int success = 0;
                glGetShaderiv(vertexID, GL_COMPILE_STATUS, &success);
                if (!success) {
                    int len = 0;
                    glGetShaderiv(vertexID, GL_INFO_LOG_LENGTH, &len);
                    std::cout << "ERROR: '" << filepath << "'\n\tVertex shader compilation failed.\n";
                    
                    char* errorLog = new char[len];
                    glGetShaderInfoLog(vertexID, len, &len, errorLog);

                    for (int i = 0; i < len; ++i) { std::cout << errorLog[i]; }
                    std::cout << "\n";

                    glDeleteShader(vertexID);
                    delete[] errorLog;
                    return;
                }

                // Load and compile the fragment shader, then pass it to the GPU
                GLuint fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
                glShaderSource(fragmentID, 1, &fSrc, NULL);
                glCompileShader(fragmentID);

                // check for compilation errors
                glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &success);
                if (!success) {
                    int len = 0;
                    glGetShaderiv(fragmentID, GL_INFO_LOG_LENGTH, &len);
                    std::cout << "ERROR: '" << filepath << "'\n\tFragment shader compilation failed.\n";
                    
                    char* errorLog = new char[len];
                    glGetShaderInfoLog(fragmentID, len, &len, errorLog);

                    for (int i = 0; i < len; ++i) { std::cout << errorLog[i]; }
                    std::cout << "\n";

                    glDeleteShader(vertexID);
                    glDeleteShader(fragmentID);
                    delete[] errorLog;
                    return;
                }

                // link shader
                shaderID = glCreateProgram();
                glAttachShader(shaderID, vertexID);
                glAttachShader(shaderID, fragmentID);
                glLinkProgram(shaderID);

                glDeleteShader(vertexID);
                glDeleteShader(fragmentID);

                // check for linking errors
                glGetProgramiv(shaderID, GL_LINK_STATUS, &success);
                if(!success) {
                    int len = 0;
                    glGetProgramiv(shaderID, GL_INFO_LOG_LENGTH, &len);
                    std::cout << "ERROR: '" << filepath << "'\n\tShader linking failed.\n";

                    char* errorLog = new char[len];
                    glGetShaderInfoLog(shaderID, len, &len, errorLog);

                    for (int i = 0; i < len; ++i) { std::cout << errorLog[i]; }
                    std::cout << "\n";

                    glDeleteProgram(shaderID);
                    delete[] errorLog;
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
                glUniformMatrix4fv(loc, 1, 0, &mat[0][0]); // todo glm says to do 1, but the actual size is 16
            };
            
            inline void uploadMat3(char const* name, glm::mat3 const &mat) {
                int loc = glGetUniformLocation(shaderID, name);
                use(); // ensure it is in use

                float buffer[9];
                for (int i = 0; i < 3; ++i) { for (int j = 0; j < 3; ++j) { buffer[3*i + j] = mat[j][i]; }}
                glUniformMatrix3fv(loc, 1, 0, &mat[0][0]);
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

#endif // ! TEXTURE_H
