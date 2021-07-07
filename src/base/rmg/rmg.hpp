/**
 * @file rmg.hpp
 * @brief Simple and quick 2D/3D graphics engine for simulation
 * 
 * Simple and quick 2D/3D graphics rendering engine with the aim for making
 * robotic simulations. Loads 2D/3D model files and texture files and easily
 * control the pose and appearance of those 2D/3D objects. Lighting and shadow
 * mapping are done in back-end processes. Performance is smooth since
 * rendering engine uses shader programs and GPU power. The project uses
 * OpenGL API and other external open source packages like GLFW and wxWidgets
 * and is made a cross-platform API.
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#pragma once
#ifndef __RM_GRAPHICS_H__
#define __RM_GRAPHICS_H__

#include "context.hpp"
#include "cube.hpp"
#include "cylinder.hpp"
#include "sphere.hpp"
#include "sprite.hpp"
#include <rmg/window.hpp>

#endif
