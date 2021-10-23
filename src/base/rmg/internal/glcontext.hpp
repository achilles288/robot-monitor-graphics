/**
 * @file glcontext.hpp
 * @brief Types, constants, and pointers to OpenGL functions
 * 
 * The functions "live" in the graphics card driver, and they are used through
 * their pointers.
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#pragma once
#ifndef __RMG_GL_CONTEXT_H__
#define __RMG_GL_CONTEXT_H__ ///< Header guard

#ifndef RMG_API
#ifdef _WIN32
#ifdef RMG_EXPORT
#define RMG_API __declspec(dllexport) ///< RMG API
#else
#define RMG_API __declspec(dllimport) ///< RMG API
#endif
#else
#define RMG_API ///< RMG API
#endif
#endif


#include <cstddef>

#if defined(__gl_h_) || defined(__GL_H__) || defined(_GL_H) || defined(__X_GL_H)
#error gl.h included before glew.hpp
#endif

#include <GL/gl.h>


// Typedefs for functions for OpenGL > 1.1
typedef void (GLAPIENTRY* PFNGLACTIVETEXTUREPROC) (GLenum texture); ///< GL typedef
typedef void (GLAPIENTRY* PFNGLATTACHSHADERPROC) (GLuint program, GLuint shader); ///< GL typedef
typedef void (GLAPIENTRY* PFNGLBINDATTRIBLOCATIONPROC) (GLuint program, GLuint index, const GLchar *name); ///< GL typedef
typedef void (GLAPIENTRY* PFNGLBINDBUFFERPROC) (GLenum target, GLuint buffer); ///< GL typedef
typedef void (GLAPIENTRY* PFNGLBINDFRAMEBUFFERPROC) (GLenum target, GLuint framebuffer); ///< GL typedef
typedef void (GLAPIENTRY* PFNGLBINDVERTEXARRAYPROC) (GLuint array); ///< GL typedef
typedef void (GLAPIENTRY* PFNGLBUFFERDATAPROC) (GLenum target, GLsizeiptr size, const void *data, GLenum usage); ///< GL typedef
typedef void (GLAPIENTRY* PFNGLBUFFERSUBDATAPROC) (GLenum target, GLintptr offset, GLsizeiptr size, const void *data); ///< GL typedef
typedef void (GLAPIENTRY* PFNGLCOMPILESHADERPROC) (GLuint shader); ///< GL typedef
typedef GLuint (GLAPIENTRY* PFNGLCREATEPROGRAMPROC) (void); ///< GL typedef
typedef GLuint (GLAPIENTRY* PFNGLCREATESHADERPROC) (GLenum type); ///< GL typedef
typedef void (GLAPIENTRY* PFNGLDELETEBUFFERSPROC) (GLsizei n, const GLuint *buffers); ///< GL typedef
typedef void (GLAPIENTRY* PFNGLDELETEFRAMEBUFFERSPROC) (GLsizei n, const GLuint* framebuffers); ///< GL typedef
typedef void (GLAPIENTRY* PFNGLDELETEPROGRAMPROC) (GLuint program); ///< GL typedef
typedef void (GLAPIENTRY* PFNGLDELETESHADERPROC) (GLuint shader); ///< GL typedef
typedef void (GLAPIENTRY* PFNGLDELETEVERTEXARRAYSPROC) (GLsizei n, const GLuint *arrays); ///< GL typedef
typedef void (GLAPIENTRY* PFNGLDETACHSHADERPROC) (GLuint program, GLuint shader); ///< GL typedef
typedef void (GLAPIENTRY* PFNGLDISABLEVERTEXATTRIBARRAYPROC) (GLuint index); ///< GL typedef
typedef void (GLAPIENTRY* PFNGLENABLEVERTEXATTRIBARRAYPROC) (GLuint index); ///< GL typedef
typedef void (GLAPIENTRY* PFNGLFRAMEBUFFERTEXTURE2DPROC) (GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level); ///< GL typedef
typedef void (GLAPIENTRY* PFNGLGENBUFFERSPROC) (GLsizei n, GLuint *buffers); ///< GL typedef
typedef void (GLAPIENTRY* PFNGLGENERATEMIPMAPEXTPROC) (GLenum target); ///< GL typedef
typedef void (GLAPIENTRY* PFNGLGENFRAMEBUFFERSPROC) (GLsizei n, GLuint *framebuffers); ///< GL typedef
typedef void (GLAPIENTRY* PFNGLGENVERTEXARRAYSPROC) (GLsizei n, GLuint *arrays); ///< GL typedef
typedef void (GLAPIENTRY* PFNGLGETPROGRAMINFOLOGPROC) (GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog); ///< GL typedef
typedef void (GLAPIENTRY* PFNGLGETPROGRAMIVPROC) (GLuint program, GLenum pname, GLint *params); ///< GL typedef
typedef void (GLAPIENTRY* PFNGLGETSHADERIVPROC) (GLuint shader, GLenum pname, GLint *params); ///< GL typedef
typedef void (GLAPIENTRY* PFNGLGETSHADERINFOLOGPROC) (GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog); ///< GL typedef
typedef GLint (GLAPIENTRY* PFNGLGETUNIFORMLOCATIONPROC) (GLuint program, const GLchar *name); ///< GL typedef
typedef void (GLAPIENTRY* PFNGLLINKPROGRAMPROC) (GLuint program); ///< GL typedef
typedef void (GLAPIENTRY* PFNGLPROVOKINGVERTEXPROC) (GLenum mode); ///< GL typedef
typedef void (GLAPIENTRY* PFNGLSHADERSOURCEPROC) (GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length); ///< GL typedef
typedef void (GLAPIENTRY* PFNGLUNIFORM1FPROC) (GLint location, GLfloat v0); ///< GL typedef
typedef void (GLAPIENTRY* PFNGLUNIFORM1IPROC) (GLint location, GLint v0); ///< GL typedef
typedef void (GLAPIENTRY* PFNGLUNIFORM3FVPROC) (GLint location, GLsizei count, const GLfloat *value); ///< GL typedef
typedef void (GLAPIENTRY* PFNGLUNIFORM4FVPROC) (GLint location, GLsizei count, const GLfloat *value); ///< GL typedef
typedef void (GLAPIENTRY* PFNGLUNIFORMMATRIX3FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value); ///< GL typedef
typedef void (GLAPIENTRY* PFNGLUNIFORMMATRIX4FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value); ///< GL typedef
typedef void (GLAPIENTRY* PFNGLUSEPROGRAMPROC) (GLuint program); ///< GL typedef
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIBPOINTERPROC) (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer); ///< GL typedef


namespace rmg {
namespace internal {

extern PFNGLACTIVETEXTUREPROC glActiveTexture; ///< GL function
extern PFNGLATTACHSHADERPROC glAttachShader; ///< GL function
extern PFNGLBINDBUFFERPROC glBindBuffer; ///< GL function
extern PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer; ///< GL function
extern PFNGLBINDVERTEXARRAYPROC glBindVertexArray; ///< GL function
extern PFNGLBUFFERDATAPROC glBufferData; ///< GL function
extern PFNGLCOMPILESHADERPROC glCompileShader; ///< GL function
extern PFNGLCREATEPROGRAMPROC glCreateProgram; ///< GL function
extern PFNGLCREATESHADERPROC glCreateShader; ///< GL function
extern PFNGLDELETEBUFFERSPROC glDeleteBuffers; ///< GL function
extern PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers; ///< GL function
extern PFNGLDELETEPROGRAMPROC glDeleteProgram; ///< GL function
extern PFNGLDELETESHADERPROC glDeleteShader; ///< GL function
extern PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays; ///< GL function
extern PFNGLDETACHSHADERPROC glDetachShader; ///< GL function
extern PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray; ///< GL function
extern PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray; ///< GL function
extern PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D; ///< GL function
extern PFNGLGENBUFFERSPROC glGenBuffers; ///< GL function
extern PFNGLGENERATEMIPMAPEXTPROC glGenerateMipmap; ///< GL funtion
extern PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers; ///< GL function
extern PFNGLGENVERTEXARRAYSPROC glGenVertexArrays; ///< GL function
extern PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog; ///< GL function
extern PFNGLGETPROGRAMIVPROC glGetProgramiv; ///< GL function
extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog; ///< GL function
extern PFNGLGETSHADERIVPROC glGetShaderiv; ///< GL function
extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation; ///< GL function
extern PFNGLLINKPROGRAMPROC glLinkProgram; ///< GL function
extern PFNGLSHADERSOURCEPROC glShaderSource; ///< GL function
extern PFNGLUNIFORM1FPROC glUniform1f; ///< GL function
extern PFNGLUNIFORM1IPROC glUniform1i; ///< GL function
extern PFNGLUNIFORM3FVPROC glUniform3fv; ///< GL function
extern PFNGLUNIFORM4FVPROC glUniform4fv; ///< GL function
extern PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix3fv; ///< GL function
extern PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv; ///< GL function
extern PFNGLUSEPROGRAMPROC glUseProgram; ///< GL function
extern PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer; ///< GL function


/**
 * @brief GL functions for a specific GL context
 */
class RMG_API GLContext {
  private:
    PFNGLACTIVETEXTUREPROC func_glActiveTexture = NULL;
    PFNGLATTACHSHADERPROC func_glAttachShader = NULL;
    PFNGLBINDBUFFERPROC func_glBindBuffer = NULL;
    PFNGLBINDFRAMEBUFFERPROC func_glBindFramebuffer = NULL;
    PFNGLBINDVERTEXARRAYPROC func_glBindVertexArray = NULL;
    PFNGLBUFFERDATAPROC func_glBufferData = NULL;
    PFNGLCOMPILESHADERPROC func_glCompileShader = NULL;
    PFNGLCREATEPROGRAMPROC func_glCreateProgram = NULL;
    PFNGLCREATESHADERPROC func_glCreateShader = NULL;
    PFNGLDELETEBUFFERSPROC func_glDeleteBuffers = NULL;
    PFNGLDELETEFRAMEBUFFERSPROC func_glDeleteFramebuffers = NULL;
    PFNGLDELETEPROGRAMPROC func_glDeleteProgram = NULL;
    PFNGLDELETESHADERPROC func_glDeleteShader = NULL;
    PFNGLDELETEVERTEXARRAYSPROC func_glDeleteVertexArrays = NULL;
    PFNGLDETACHSHADERPROC func_glDetachShader = NULL;
    PFNGLDISABLEVERTEXATTRIBARRAYPROC func_glDisableVertexAttribArray = NULL;
    PFNGLENABLEVERTEXATTRIBARRAYPROC func_glEnableVertexAttribArray = NULL;
    PFNGLFRAMEBUFFERTEXTURE2DPROC func_glFramebufferTexture2D = NULL;
    PFNGLGENBUFFERSPROC func_glGenBuffers = NULL;
    PFNGLGENERATEMIPMAPEXTPROC func_glGenerateMipmap = NULL;
    PFNGLGENFRAMEBUFFERSPROC func_glGenFramebuffers = NULL;
    PFNGLGENVERTEXARRAYSPROC func_glGenVertexArrays = NULL;
    PFNGLGETPROGRAMINFOLOGPROC func_glGetProgramInfoLog = NULL;
    PFNGLGETPROGRAMIVPROC func_glGetProgramiv = NULL;
    PFNGLGETSHADERINFOLOGPROC func_glGetShaderInfoLog = NULL;
    PFNGLGETSHADERIVPROC func_glGetShaderiv = NULL;
    PFNGLGETUNIFORMLOCATIONPROC func_glGetUniformLocation = NULL;
    PFNGLLINKPROGRAMPROC func_glLinkProgram = NULL;
    PFNGLSHADERSOURCEPROC func_glShaderSource = NULL;
    PFNGLUNIFORM1FPROC func_glUniform1f = NULL;
    PFNGLUNIFORM1IPROC func_glUniform1i = NULL;
    PFNGLUNIFORM3FVPROC func_glUniform3fv = NULL;
    PFNGLUNIFORM4FVPROC func_glUniform4fv = NULL;
    PFNGLUNIFORMMATRIX3FVPROC func_glUniformMatrix3fv = NULL;
    PFNGLUNIFORMMATRIX4FVPROC func_glUniformMatrix4fv = NULL;
    PFNGLUSEPROGRAMPROC func_glUseProgram = NULL;
    PFNGLVERTEXATTRIBPOINTERPROC func_glVertexAttribPointer = NULL;
    
  public:
    /**
     * @brief Default constructor
     */
    GLContext() = default;
    
    /**
     * @brief Initialize the GL pointers
     * 
     * @return Error code
     */
    int init();
    
    /**
     * @brief Sets the current GL context
     * 
     * This function is to be called when switching between multiple GL
     * contexts.
     */
    void setCurrent();
};

}}


#endif
