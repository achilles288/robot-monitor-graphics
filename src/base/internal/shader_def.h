/**
 * @file shader_def.h
 * @brief Private defines for shaders
 * 
 * @copyright Copyright (c) 2022 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#pragma once
#ifndef __RMG_SHADER_DEF_H__
#define __RMG_SHADER_DEF_H__

#define TEXTURE_SPRITE     0
#define TEXTURE_SHADOW     1
#define TEXTURE_BASE       2
#define TEXTURE_HEIGHT     3
#define TEXTURE_NORMAL     4
#define TEXTURE_MRAO       5
#define TEXTURE_OPACITY    6
#define TEXTURE_EMMISIVITY 7

#define _GL_TEXTURE_SPRITE     GL_TEXTURE0
#define _GL_TEXTURE_SHADOW     GL_TEXTURE1
#define _GL_TEXTURE_BASE       GL_TEXTURE2
#define _GL_TEXTURE_HEIGHT     GL_TEXTURE3
#define _GL_TEXTURE_NORMAL     GL_TEXTURE4
#define _GL_TEXTURE_MRAO       GL_TEXTURE5
#define _GL_TEXTURE_OPACITY    GL_TEXTURE6
#define _GL_TEXTURE_EMMISIVITY GL_TEXTURE7

#endif
