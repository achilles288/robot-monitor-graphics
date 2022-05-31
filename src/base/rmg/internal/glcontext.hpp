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


#include "GL/gl.h"

#include <cstddef>


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
typedef void (GLAPIENTRY* PFNGLUNIFORM2FPROC) (GLint location, GLfloat v0, GLfloat v1); ///< GL typedef
typedef void (GLAPIENTRY* PFNGLUNIFORM3FVPROC) (GLint location, GLsizei count, const GLfloat *value); ///< GL typedef
typedef void (GLAPIENTRY* PFNGLUNIFORM4FVPROC) (GLint location, GLsizei count, const GLfloat *value); ///< GL typedef
typedef void (GLAPIENTRY* PFNGLUNIFORMMATRIX3FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value); ///< GL typedef
typedef void (GLAPIENTRY* PFNGLUNIFORMMATRIX4FVPROC) (GLint location, GLsizei count, GLboolean transpose, const GLfloat *value); ///< GL typedef
typedef void (GLAPIENTRY* PFNGLUSEPROGRAMPROC) (GLuint program); ///< GL typedef
typedef void (GLAPIENTRY* PFNGLVERTEXATTRIBPOINTERPROC) (GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer); ///< GL typedef


namespace rmg {
namespace internal {

RMG_API extern PFNGLACTIVETEXTUREPROC glActiveTexture; ///< GL function
RMG_API extern PFNGLATTACHSHADERPROC glAttachShader; ///< GL function
RMG_API extern PFNGLBINDBUFFERPROC glBindBuffer; ///< GL function
RMG_API extern PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer; ///< GL function
RMG_API extern PFNGLBINDVERTEXARRAYPROC glBindVertexArray; ///< GL function
RMG_API extern PFNGLBUFFERDATAPROC glBufferData; ///< GL function
RMG_API extern PFNGLCOMPILESHADERPROC glCompileShader; ///< GL function
RMG_API extern PFNGLCREATEPROGRAMPROC glCreateProgram; ///< GL function
RMG_API extern PFNGLCREATESHADERPROC glCreateShader; ///< GL function
RMG_API extern PFNGLDELETEBUFFERSPROC glDeleteBuffers; ///< GL function
RMG_API extern PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers; ///< GL function
RMG_API extern PFNGLDELETEPROGRAMPROC glDeleteProgram; ///< GL function
RMG_API extern PFNGLDELETESHADERPROC glDeleteShader; ///< GL function
RMG_API extern PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays; ///< GL function
RMG_API extern PFNGLDETACHSHADERPROC glDetachShader; ///< GL function
RMG_API extern PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray; ///< GL function
RMG_API extern PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray; ///< GL function
RMG_API extern PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D; ///< GL function
RMG_API extern PFNGLGENBUFFERSPROC glGenBuffers; ///< GL function
RMG_API extern PFNGLGENERATEMIPMAPEXTPROC glGenerateMipmap; ///< GL funtion
RMG_API extern PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers; ///< GL function
RMG_API extern PFNGLGENVERTEXARRAYSPROC glGenVertexArrays; ///< GL function
RMG_API extern PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog; ///< GL function
RMG_API extern PFNGLGETPROGRAMIVPROC glGetProgramiv; ///< GL function
RMG_API extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog; ///< GL function
RMG_API extern PFNGLGETSHADERIVPROC glGetShaderiv; ///< GL function
RMG_API extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation; ///< GL function
RMG_API extern PFNGLLINKPROGRAMPROC glLinkProgram; ///< GL function
RMG_API extern PFNGLSHADERSOURCEPROC glShaderSource; ///< GL function
RMG_API extern PFNGLUNIFORM1FPROC glUniform1f; ///< GL function
RMG_API extern PFNGLUNIFORM1IPROC glUniform1i; ///< GL function
RMG_API extern PFNGLUNIFORM2FPROC glUniform2f; ///< GL function
RMG_API extern PFNGLUNIFORM3FVPROC glUniform3fv; ///< GL function
RMG_API extern PFNGLUNIFORM4FVPROC glUniform4fv; ///< GL function
RMG_API extern PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix3fv; ///< GL function
RMG_API extern PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv; ///< GL function
RMG_API extern PFNGLUSEPROGRAMPROC glUseProgram; ///< GL function
RMG_API extern PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer; ///< GL function


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
    PFNGLUNIFORM2FPROC func_glUniform2f = NULL;
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
