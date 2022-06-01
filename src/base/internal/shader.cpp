/**
 * @file shader.cpp
 * @brief Shader program class taking main backend role in drawing
 * 
 * Compiles vertex and fragment shaders. Link the program. Run it using
 * loaded vertex buffer objects and make drawings.
 * 
 * @copyright Copyright (c) 2022 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#define RMG_EXPORT


#include "../rmg/internal/shader.hpp"

#include <cstdio>
#include <cstdlib>

#include "../rmg/assert.hpp"


namespace rmg {
namespace internal {

/**
 * @brief Destructor
 */
Shader::~Shader() {
    if(id)
        glDeleteProgram(id);
}

/**
 * @brief Compiles a shader from file (Vertex shader or fragment shader)
 * 
 * @param type Shader type (GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, .etc)
 * @param path Path to shader file
 * 
 * @return ID of the compiled shader used to retrive it
 */
uint32_t Shader::compileShader(uint32_t type, const char* path)
{
    if(type != GL_VERTEX_SHADER && type != GL_FRAGMENT_SHADER) {
        RMG_EXPECT(type == GL_VERTEX_SHADER || type == GL_FRAGMENT_SHADER);
        return 0;
    }
    
    uint32_t shaderID = glCreateShader(type);
    
    // Opens the file
    FILE *fp = fopen(path, "r");
    if(fp == nullptr) {
        #ifdef _WIN32
        printf("error: Shader file '%s' could not be opened\n", path);
        #else
        printf("\033[0;1;31merror:\033[0m "
               "Shader file '%s' could not be opened\n",
               path);
        #endif
        return 0;
    }
    
    // Reads the file
    char fileContent[65536];
    int i = 0;
    char ch = getc(fp);
    while(ch != EOF && i < 65535) {
        fileContent[i] = ch;
        ch = getc(fp);
        i++;
    }
    fileContent[i] = '\0';
    fclose(fp);
    
    // Compiles the shader
    GLint res = GL_FALSE;
    int infoLogLength;
    char const* ptr = fileContent;
    glShaderSource(shaderID, 1, &ptr, NULL);
    glCompileShader(shaderID);
    
    // Checks the shader
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &res);
    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if(infoLogLength > 0) {
        char *message = (char*) malloc(infoLogLength+1);
        glGetShaderInfoLog(shaderID, infoLogLength, NULL, message);
        printf("%s\n", message);
        return 0;
    }
    
    return shaderID;
}

/**
 * @brief Compiles and links a shader program
 * 
 * @param vert Vertex shader file
 * @param frag Fragment shader file
 * 
 * @return Shader program ID
 */
uint32_t Shader::compileShaderProgram(const char* vert, const char* frag)
{
    uint32_t vertexShaderID = compileShader(GL_VERTEX_SHADER, vert);
    uint32_t fragmentShaderID = compileShader(GL_FRAGMENT_SHADER, frag);
    if(vertexShaderID == 0 || fragmentShaderID == 0) {
        if(vertexShaderID != 0)
            glDeleteShader(vertexShaderID);
        if(fragmentShaderID != 0)
            glDeleteShader(fragmentShaderID);
        return 0;
    }
    
    // Link the program
    uint32_t programID = glCreateProgram();
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    glLinkProgram(programID);
    
    // Check the program
    GLint res = GL_FALSE;
    int infoLogLength;
    glGetProgramiv(programID, GL_LINK_STATUS, &res);
    glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
    if(infoLogLength > 0) {
        char *message = (char*) malloc(infoLogLength+1);
        glGetProgramInfoLog(programID, infoLogLength, NULL, message);
        printf("%s\n", message);
        return 0;
    }
    
    glDetachShader(programID, vertexShaderID);
    glDetachShader(programID, fragmentShaderID);
    glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    return programID;
}

}}
