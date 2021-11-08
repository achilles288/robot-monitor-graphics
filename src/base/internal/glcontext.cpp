/**
 * @file glcontext.cpp
 * @brief Types, constants, and pointers to OpenGL functions
 * 
 * The functions "live" in the graphics card driver, and they are used through
 * their pointers.
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#define RMG_EXPORT


#include "../rmg/internal/glcontext.hpp"


#ifdef _WIN32
#define getProcAddress(name) wglGetProcAddress((LPCSTR) name)

#else
extern "C" {
    extern void (*glXGetProcAddressARB(const GLubyte *procName))();
}
#define getProcAddress(name) (*glXGetProcAddressARB)((const GLubyte*) name)
#endif


static void *getGLFuncAddress(const char* fname) {
    void *pret = (void*) getProcAddress(fname);
    // Some drivers return -apart from 0-, -1, 1, 2 or 3
    if(pret == (void*)-1 || pret == (void*)1 || pret == (void*)2 || pret == (void*)3)
        pret = (void*)0;
    return pret;
}


namespace rmg {
namespace internal {

RMG_API PFNGLACTIVETEXTUREPROC glActiveTexture = NULL;
RMG_API PFNGLATTACHSHADERPROC glAttachShader = NULL;
RMG_API PFNGLBINDBUFFERPROC glBindBuffer = NULL;
RMG_API PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer = NULL;
RMG_API PFNGLBINDVERTEXARRAYPROC glBindVertexArray = NULL;
RMG_API PFNGLBUFFERDATAPROC glBufferData = NULL;
RMG_API PFNGLCOMPILESHADERPROC glCompileShader = NULL;
RMG_API PFNGLCREATEPROGRAMPROC glCreateProgram = NULL;
RMG_API PFNGLCREATESHADERPROC glCreateShader = NULL;
RMG_API PFNGLDELETEBUFFERSPROC glDeleteBuffers = NULL;
RMG_API PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers = NULL;
RMG_API PFNGLDELETEPROGRAMPROC glDeleteProgram = NULL;
RMG_API PFNGLDELETESHADERPROC glDeleteShader = NULL;
RMG_API PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays = NULL;
RMG_API PFNGLDETACHSHADERPROC glDetachShader = NULL;
RMG_API PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray = NULL;
RMG_API PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray = NULL;
RMG_API PFNGLGENERATEMIPMAPEXTPROC glGenerateMipmap = NULL;
RMG_API PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D = NULL;
RMG_API PFNGLGENBUFFERSPROC glGenBuffers = NULL;
RMG_API PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers = NULL;
RMG_API PFNGLGENVERTEXARRAYSPROC glGenVertexArrays = NULL;
RMG_API PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = NULL;
RMG_API PFNGLGETPROGRAMIVPROC glGetProgramiv = NULL;
RMG_API PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = NULL;
RMG_API PFNGLGETSHADERIVPROC glGetShaderiv = NULL;
RMG_API PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = NULL;
RMG_API PFNGLLINKPROGRAMPROC glLinkProgram = NULL;
RMG_API PFNGLSHADERSOURCEPROC glShaderSource = NULL;
RMG_API PFNGLUNIFORM1FPROC glUniform1f = NULL;
RMG_API PFNGLUNIFORM1IPROC glUniform1i = NULL;
RMG_API PFNGLUNIFORM3FVPROC glUniform3fv = NULL;
RMG_API PFNGLUNIFORM4FVPROC glUniform4fv = NULL;
RMG_API PFNGLUNIFORMMATRIX3FVPROC glUniformMatrix3fv = NULL;
RMG_API PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv = NULL;
RMG_API PFNGLUSEPROGRAMPROC glUseProgram = NULL;
RMG_API PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer = NULL;


#define GETANDTEST(type, name) \
    func_ ## name = (type) getGLFuncAddress(#name); \
    if(func_ ## name == 0) \
        return 1;


/**
 * @brief Initialize the GL pointers
 * 
 * @return Error code
 */
int GLContext::init() {
    GETANDTEST(PFNGLACTIVETEXTUREPROC, glActiveTexture)
    GETANDTEST(PFNGLATTACHSHADERPROC, glAttachShader)
    GETANDTEST(PFNGLBINDBUFFERPROC, glBindBuffer)
    GETANDTEST(PFNGLBINDFRAMEBUFFERPROC, glBindFramebuffer)
    GETANDTEST(PFNGLBINDVERTEXARRAYPROC, glBindVertexArray)
    GETANDTEST(PFNGLBUFFERDATAPROC, glBufferData)
    GETANDTEST(PFNGLCOMPILESHADERPROC, glCompileShader)
    GETANDTEST(PFNGLCREATEPROGRAMPROC, glCreateProgram)
    GETANDTEST(PFNGLCREATESHADERPROC, glCreateShader)
    GETANDTEST(PFNGLDELETEBUFFERSPROC, glDeleteBuffers)
    GETANDTEST(PFNGLDELETEFRAMEBUFFERSPROC, glDeleteFramebuffers)
    GETANDTEST(PFNGLDELETEPROGRAMPROC, glDeleteProgram)
    GETANDTEST(PFNGLDELETESHADERPROC, glDeleteShader)
    GETANDTEST(PFNGLDELETEVERTEXARRAYSPROC, glDeleteVertexArrays)
    GETANDTEST(PFNGLDETACHSHADERPROC, glDetachShader)
    GETANDTEST(PFNGLDISABLEVERTEXATTRIBARRAYPROC, glDisableVertexAttribArray)
    GETANDTEST(PFNGLENABLEVERTEXATTRIBARRAYPROC, glEnableVertexAttribArray)
    GETANDTEST(PFNGLFRAMEBUFFERTEXTURE2DPROC, glFramebufferTexture2D)
    GETANDTEST(PFNGLGENBUFFERSPROC, glGenBuffers)
    GETANDTEST(PFNGLGENERATEMIPMAPEXTPROC, glGenerateMipmap)
    GETANDTEST(PFNGLGENFRAMEBUFFERSPROC, glGenFramebuffers)
    GETANDTEST(PFNGLGENVERTEXARRAYSPROC, glGenVertexArrays)
    GETANDTEST(PFNGLGETPROGRAMINFOLOGPROC, glGetProgramInfoLog)
    GETANDTEST(PFNGLGETPROGRAMIVPROC, glGetProgramiv)
    GETANDTEST(PFNGLGETSHADERINFOLOGPROC, glGetShaderInfoLog)
    GETANDTEST(PFNGLGETSHADERIVPROC, glGetShaderiv)
    GETANDTEST(PFNGLGETUNIFORMLOCATIONPROC, glGetUniformLocation)
    GETANDTEST(PFNGLLINKPROGRAMPROC, glLinkProgram)
    GETANDTEST(PFNGLSHADERSOURCEPROC, glShaderSource)
    GETANDTEST(PFNGLUNIFORM1FPROC, glUniform1f)
    GETANDTEST(PFNGLUNIFORM1IPROC, glUniform1i)
    GETANDTEST(PFNGLUNIFORM3FVPROC, glUniform3fv)
    GETANDTEST(PFNGLUNIFORM4FVPROC, glUniform4fv)
    GETANDTEST(PFNGLUNIFORMMATRIX4FVPROC, glUniformMatrix3fv)
    GETANDTEST(PFNGLUNIFORMMATRIX4FVPROC, glUniformMatrix4fv)
    GETANDTEST(PFNGLUSEPROGRAMPROC, glUseProgram)
    GETANDTEST(PFNGLVERTEXATTRIBPOINTERPROC, glVertexAttribPointer)
    setCurrent();
    return 0;
}

/**
 * @brief Sets the current GL context
 * 
 * This function is to be called when switching between multiple GL
 * contexts.
 */
void GLContext::setCurrent() {
    glActiveTexture = func_glActiveTexture;
    glAttachShader = func_glAttachShader;
    glBindBuffer = func_glBindBuffer;
    glBindFramebuffer = func_glBindFramebuffer;
    glBindVertexArray = func_glBindVertexArray;
    glBufferData = func_glBufferData;
    glCompileShader = func_glCompileShader;
    glCreateProgram = func_glCreateProgram;
    glCreateShader = func_glCreateShader;
    glDeleteBuffers = func_glDeleteBuffers;
    glDeleteFramebuffers = func_glDeleteFramebuffers;
    glDeleteProgram = func_glDeleteProgram;
    glDeleteShader = func_glDeleteShader;
    glDeleteVertexArrays = func_glDeleteVertexArrays;
    glDetachShader = func_glDetachShader;
    glDisableVertexAttribArray = func_glDisableVertexAttribArray;
    glEnableVertexAttribArray = func_glEnableVertexAttribArray;
    glFramebufferTexture2D = func_glFramebufferTexture2D;
    glGenBuffers = func_glGenBuffers;
    glGenerateMipmap = func_glGenerateMipmap;
    glGenFramebuffers = func_glGenFramebuffers;
    glGenVertexArrays = func_glGenVertexArrays;
    glGetProgramInfoLog = func_glGetProgramInfoLog;
    glGetProgramiv = func_glGetProgramiv;
    glGetShaderInfoLog = func_glGetShaderInfoLog;
    glGetShaderiv = func_glGetShaderiv;
    glGetUniformLocation = func_glGetUniformLocation;
    glLinkProgram = func_glLinkProgram;
    glShaderSource = func_glShaderSource;
    glUniform1f = func_glUniform1f;
    glUniform1i = func_glUniform1i;
    glUniform3fv = func_glUniform3fv;
    glUniform4fv = func_glUniform4fv;
    glUniformMatrix3fv = func_glUniformMatrix3fv;
    glUniformMatrix4fv = func_glUniformMatrix4fv;
    glUseProgram = func_glUseProgram;
    glVertexAttribPointer = func_glVertexAttribPointer;
}

}}
