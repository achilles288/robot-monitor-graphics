/**
 * @file shadow_map_shader.hpp
 * @brief Generates an image representing the distance from sun at every pixel
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#pragma once
#ifndef __RMG_SHADOW_MAP_SHADER_H__
#define __RMG_SHADOW_MAP_SHADER_H__

#ifndef RMG_API
#ifdef _WIN32
#ifdef RMG_EXPORT
#define RMG_API __declspec(dllexport)
#else
#define RMG_API __declspec(dllimport)
#endif
#else
#define RMG_API
#endif
#endif


#include "shader.hpp"
#include "../camera.hpp"
#include "../object.hpp"
#include "../math/vec.hpp"

namespace rmg {

namespace internal {

/**
 * @brief Generates an image representing the distance from sun at every pixel
 */
class RMG_API ShadowMapShader: public Shader {
  private:
    Camera shadowMapper;
    Vec3 cameraPosition;
    Vec3 cameraDirection;
    Vec3 lightDirection;
    float nearDist;
    float farDist;
    float mapCenterDist;
    
    uint32_t depthMapFBO = 0;
    uint32_t depthMap = 0;
    uint32_t idMVP;
    
    void calculateShadowMapperTranslation();
    
  public:
    /**
     * @brief Default constructor
     */
    ShadowMapShader();
    
    /**
     * @brief Destructor
     */
    virtual ~ShadowMapShader();
    
    /**
     * @brief Sets the camera position
     * 
     * Camera here means the world's camera. This function is used so that
     * the light's viewing point moves together with it.
     * 
     * @param x X-coordinate
     * @param y Y-coordinate
     * @param z Z-coordinate
     */
    void setCameraTranslation(float x, float y, float z);
    
    /**
     * @brief Sets the camera position
     * 
     * Camera here means the world's camera. This function is used so that
     * the light's viewing point moves together with it.
     * 
     * @param p Position vector
     */
    void setCameraTranslation(Vec3 p);

    /**
     * @brief Sets rotation of the camera
     * 
     * Sets the view matrix. Rotation of the camera is in Euler angles.
     * Rotation order is ZYX (Yaw-Pitch-Roll).
     * 
     * @param x Roll
     * @param y Pitch
     * @param z Yaw
     */
    inline void setCameraRotation(float x, float y, float z) {
        setCameraRotation(Euler(x, y, z));
    }
    
    /**
     * @brief Sets the camera rotation
     * 
     * Camera here means the world's camera. This function is used so that
     * the light's viewing direction moves together with it.
     * 
     * @param x Roll
     * @param y Pitch
     * @param z Yaw
     * @param unit The previous params are degree or radian
     */
    inline void setCameraRotation(float x, float y, float z, AngleUnit unit) {
        setCameraRotation(Euler(x, y, z, unit));
    }
    
    /**
     * @brief Sets the camera rotation
     * 
     * Camera here means the world's camera. This function is used so that
     * the light's viewing direction moves together with it.
     * 
     * @param rot Euler angles
     */
    void setCameraRotation(Euler rot);
    
    /**
     * @brief Sets minimum distance of the camera
     * 
     * @param n Minimum clipping distance
     */
    void setMinimumDistance(float n);
    
    /**
     * @brief Sets maximum distance of the camera
     * 
     * @param f Maximum clipping distance
     */
    void setMaximumDistance(float f);
    
    /**
     * @brief Sets the directional light vector
     * 
     * Contributes the view matrix of the shadow mapper. The shadow mapper
     * is a camera that views the world from the light's position.
     * 
     * @param v Light direction
     */
    void setDirectionalLightVector(Vec3 v);
    
    /**
     * @brief Gets the matrix to process shadow mapping
     * 
     * It is the composition of view and projection matrix from the position
     * of the light as a camera. Similar to the VP matrix of a normal camera.
     * 
     * @param v Light direction
     */
    const Mat4& getShadowMatrix() const;
    
    /**
     * @brief Compile, link and assign program parameters
     */
    void load() override;
    
    /**
     * @brief Generates the shadow map of the group of 3D objects
     * 
     * Renders depth image of the group of 3D objects which is then
     * used as the shadow map passing it to the general shader.
     * 
     * @param list List of 3D objects
     * 
     * @return Shadow map
     */
    uint32_t createShadowMap(const ObjectList &list);
};

}}

#endif
