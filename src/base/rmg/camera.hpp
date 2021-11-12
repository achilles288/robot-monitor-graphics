/**
 * @file camera.hpp
 * @brief Virtual camera in 3D space
 * 
 * Calculates view and projection matrices and pass them to shader processing.
 * Camera transform in 3D space and projection mode in perspective or
 * orthographic.
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#pragma once
#ifndef __RMG_CAMERA_H__
#define __RMG_CAMERA_H__

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


#include <cstdint>

#include "math/euler.hpp"
#include "math/mat3.hpp"
#include "math/mat4.hpp"
#include "math/vec.hpp"


namespace rmg {

/**
 * @brief Perspective or orthographic projection
 */
enum class ProjectionMode {
    Perspective,
    Orthographic,
    Null
};

/**
 * @brief Virtual camera in 3D space
 * 
 * Calculates view and projection matrices and pass them to shader processing.
 * Camera transform in 3D space and projection mode in perspective or
 * orthographic.
 */
class RMG_API Camera {
  private:
    Vec3 position;
    Mat3 rotation;
    Mat4 viewMatrix;
    Mat4 projectionMatrix;
    Mat4 VPMatrix;
    float aspect;
    float fov1;
    float fov2;
    float nearDist;
    float farDist;
    ProjectionMode projectionMode;
    
  public:
    /**
     * @brief Default constructor
     */
    Camera();
    
    /**
     * @brief Gets the view matrix
     */
    const Mat4& getViewMatrix() const;
    
    /**
     * @brief Gets the projection matrix
     */
    const Mat4& getProjectionMatrix() const;
    
    /**
     * @brief Gets the composition of view and projection matrix
     */
    const Mat4& getVPMatrix() const;
    
    /**
     * @brief Gets the projection mode of the camera
     */
    ProjectionMode getProjectionMode() const;
    
    /**
     * @brief Sets xyz position of the camera
     * 
     * Sets the translation part of the view matrix.
     * 
     * @param x X-coordinate
     * @param y Y-coordinate
     * @param z Z-coordinate
     */
    void setTranslation(float x, float y, float z);
    
    /**
     * @brief Sets xyz position of the camera
     * 
     * Sets the translation part of the view matrix.
     * 
     * @param pos Camera position
     */
    void setTranslation(const Vec3 &pos);
    
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
    void setRotation(float x, float y, float z);
    
    /**
     * @brief Sets rotation of the camera
     * 
     * Sets the view matrix. Rotation of the camera is in Euler angles.
     * Rotation order is ZYX (Yaw-Pitch-Roll).
     * 
     * @param x Roll
     * @param y Pitch
     * @param z Yaw
     * @param unit The previous params are degree or radian
     */
    inline void setRotation(float x, float y, float z, AngleUnit unit) {
        if(unit == AngleUnit::Radian)
            setRotation(x, y, z);
        else
            setRotation(radian(x), radian(y), radian(z));
    }
    
    /**
     * @brief Sets rotation of the camera
     * 
     * Sets the view matrix. Rotation of the camera is in Euler angles.
     * Rotation order is ZYX (Yaw-Pitch-Roll).
     * 
     * @param rot Euler angles
     */
    inline void setRotation(const Euler &rot) {
        setRotation(rot.roll, rot.pitch, rot.yaw);
    }
    
    /**
     * @brief Gets xyz position of the camera
     * 
     * Gets values from the translation part of the view matrix.
     * 
     * @return XYZ position
     */
    Vec3 getTranslation() const;
    
    /**
     * @brief Gets rotation of the camera
     * 
     * Calculates values from the rotation part of the view matrix.
     * Rotation order is ZYX (Yaw-Pitch-Roll).
     *
     * @return Rotation in Euler angles
     */
    Euler getRotation() const;
    
    /**
     * @brief Sets the projection to perspective mode
     */
    void setPerspectiveProjection();
    
    /**
     * @brief Sets the parameters for perspective projection
     * 
     * Sets the perspective matrix.
     * 
     * @param fov Field of view
     * @param n Minimum clipping distance
     * @param f Maximum clipping distance
     */
    void setPerspectiveProjection(float fov, float n, float f);
    
    /**
     * @brief Sets the projection to orthographic mode
     */
    void setOrthographicProjection();
    
    /**
     * @brief Sets the parameters for orthographic projection
     * 
     * Sets the perspective matrix.
     * 
     * @param fov Viewing distance along Y-axis of the screen
     * @param n Minimum clipping distance
     * @param f Maximum clipping distance
     */
    void setOrthographicProjection(float fov, float n, float f);
    
    /**
     * @brief Sets image aspect ratio
     * 
     * @param a Image width divided by height
     */
    void setAspectRatio(float a);
    
    /**
     * @brief Sets the field of view for the projection
     * 
     * For perspective projection, the parameter is the viewing angle along
     * the Y-axis. In case of orthographic projection, it is the distance of
     * view along Y-axis of the screen.
     * 
     * @param fov Field of view
     */
    void setFieldOfView(float fov);
    
    /**
     * @brief Sets minimum distance for depth clipping
     * 
     * @param n Minimum clipping distance
     */
    void setMinimumDistance(float n);
    
    /**
     * @brief Sets maximum distance for depth clipping
     * 
     * @param f Maximum clipping distance
     */
    void setMaximumDistance(float f);
    
    /**
     * @brief Gets the aspect ratio of the camera
     * 
     * @return Aspect ratio of camera image
     */
    float getAspectRatio() const;
    
    /**
     * @brief Gets angle of view used in the projection
     * 
     * @return Field of view
     */
    float getFieldOfView() const;
    
    /**
     * @brief Gets minimum distance for depth clipping
     * 
     * @return Minimum clipping distance
     */
    float getMinimumDistance() const;
    
    /**
     * @brief Gets maximum distance for depth clipping
     * 
     * @return Maximum clipping distance
     */
    float getMaximumDistance() const;
    
    /**
     * @brief Converts world space to OpenGL clip space
     * 
     * @param x X-coordinate
     * @param y Y-coordinate
     * @param z Z-coordinate
     * 
     * @return 3D coordinate in OpenGL clip space
     */
    Vec3 worldToClip(float x, float y, float z) const;
};

}

#endif
