/**
 * @file camera.cpp
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


#include "rmg/camera.hpp"


#define CAMERA_PERSPECTIVE  0
#define CAMERA_ORTHOGRAPHIC 1


namespace rmg {

static const Mat4 adjust1 = {
    { 0,-1, 0, 0},
    { 0, 0, 1, 0},
    {-1, 0, 0, 0},
    { 0, 0, 0, 1}
};

/**
 * @brief Default constructor
 */
Camera::Camera() {
    aspect = 1.0f;
    viewMatrix = adjust1;
    projectionMatrix = {
      {2.414f, 0     ,  0     ,  0     },
      {0     , 2.414f,  0     ,  0     },
      {0     , 0     , 11/9.0f, 20/9.0f},
      {0     , 0     , -1     ,  0     }
    };
    VPMatrix = projectionMatrix * viewMatrix;
    minDistance = 1.0f;
    maxDistance = 10.0f;
    projectionMode = CAMERA_PERSPECTIVE;
}

/**
 * @brief Gets the view matrix
 */
const Mat4& Camera::getViewMatrix() const { return viewMatrix; }

/**
 * @brief Gets the projection matrix
 */
const Mat4& Camera::getProjectionMatrix() const { return projectionMatrix; }

/**
 * @brief Gets the composition of view and projection matrix
 */
const Mat4& Camera::getVPMatrix() const { return VPMatrix; }

/**
 * @brief Sets xyz position of the camera
 * 
 * Sets the translation part of the view matrix.
 * 
 * @param x X-coordinate
 * @param y Y-coordinate
 * @param z Z-coordinate
 */
void Camera::setTranslation(float x, float y, float z) {
    position.x = x;
    position.y = y;
    position.z = z;
    Mat4 translation = {
        {1, 0, 0, -x},
        {0, 1, 0, -y},
        {0, 0, 1, -z},
        {0, 0, 0,  1}
    };
    viewMatrix = adjust1 * Mat4(rotation) * translation;
    VPMatrix = projectionMatrix * viewMatrix;
}

/**
 * @brief Sets xyz position of the camera
 * 
 * Sets the translation part of the view matrix.
 * 
 * @param pos Camera position
 */
void Camera::setTranslation(const Vec3 &pos) {
    position = pos;
    Mat4 translation = {
        {1, 0, 0, -pos.x},
        {0, 1, 0, -pos.y},
        {0, 0, 1, -pos.z},
        {0, 0, 0,    1  }
    };
    viewMatrix = adjust1 * Mat4(rotation) * translation;
    VPMatrix = projectionMatrix * viewMatrix;
}

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
void Camera::setRotation(float x, float y, float z) {
    rotation = Euler(x,y,z).toRotationMatrix().inverse();
    Mat4 translation = {
        {1, 0, 0, -position.x},
        {0, 1, 0, -position.y},
        {0, 0, 1, -position.z},
        {0, 0, 0,      1     }
    };
    viewMatrix = adjust1 * Mat4(rotation) * translation;
    VPMatrix = projectionMatrix * viewMatrix;
}

/**
 * @brief Gets xyz position of the camera
 * 
 * Gets values from the translation part of the view matrix.
 * 
 * @return XYZ position
 */
Vec3 Camera::getTranslation() const { return position; }

/**
 * @brief Gets rotation of the camera
 * 
 * Calculates values from the rotation part of the view matrix.
 * Rotation order is ZYX (Yaw-Pitch-Roll).
 *
 * @return Rotation in Euler angles
 */
Euler Camera::getRotation() const {
    Mat3 R = rotation.inverse();
    return Euler(R);
}

/**
 * @brief Sets the parameters for perspective projection
 * 
 * Sets the perspective matrix.
 * 
 * @param fov Field of view
 * @param near Minimum clipping distance
 * @param far Maximum clipping distance
 */
void Camera::setPerspectiveProjection(float fov, float near, float far) {
    projectionMode = CAMERA_PERSPECTIVE;
    minDistance = near;
    maxDistance = far;
    float d = 1/tan(fov/2);
    float A = (near+far)/(far-near);
    float B = (2*near*far)/(far-near);
    /**
     * projectionMatrix = {
     *   {d/aspect, 0,  0, 0},
     *   {    0   , d,  0, 0},
     *   {    0   , 0,  A, B},
     *   {    0   , 0, -1, 0}
     * };
     */
    projectionMatrix[0][0] = d/aspect;
    projectionMatrix[1][1] = d;
    projectionMatrix[2][2] = A;
    projectionMatrix[2][3] = B;
    
    VPMatrix = projectionMatrix * viewMatrix;
}

/**
 * @brief Sets angle of view for perspective projection
 * 
 * @param fov Field of view
 */
void Camera::setFieldOfView(float fov) {
    float d = 1/tan(fov/2);
    projectionMatrix[0][0] = d/aspect;
    projectionMatrix[1][1] = d;
    VPMatrix = projectionMatrix * viewMatrix;
}

/**
 * @brief Gets angle of view used in perspective projection
 * 
 * @return Field of view
 */
float Camera::getFieldOfView() const {
    return 2*atan(1/projectionMatrix[1][1]);
}

/**
 * @brief Sets image aspect ratio
 * 
 * @param a Image width divided by height
 */
void Camera::setAspectRatio(float a) {
    aspect = a;
    projectionMatrix[0][0] = projectionMatrix[1][1] / a;
    VPMatrix = projectionMatrix * viewMatrix;
}

/**
 * @brief Sets minimum distance for depth clipping
 * 
 * @param near Minimum clipping distance
 */
void Camera::setMinimumDistance(float near) {
    minDistance = near;
    projectionMatrix[2][2] = (minDistance+maxDistance) /
                             (maxDistance-minDistance);
    projectionMatrix[2][3] = (2*minDistance*maxDistance) /
                             (maxDistance-minDistance);
    VPMatrix = projectionMatrix * viewMatrix;
}

/**
 * @brief Sets maximum distance for depth clipping
 * 
 * @param far Maximum clipping distance
 */
void Camera::setMaximumDistance(float far) {
    maxDistance = far;
    projectionMatrix[2][2] = (minDistance+maxDistance) /
                             (maxDistance-minDistance);
    projectionMatrix[2][3] = (2*minDistance*maxDistance) /
                             (maxDistance-minDistance);
    VPMatrix = projectionMatrix * viewMatrix;
}

/**
 * @brief Gets the aspect ratio of the camera
 * 
 * @return Aspect ratio of camera image
 */
float Camera::getAspectRatio() const { return aspect; }

/**
 * @brief Gets minimum distance for depth clipping
 * 
 * @return Minimum clipping distance
 */
float Camera::getMinimumDistance() const { return minDistance; }

/**
 * @brief Gets maximum distance for depth clipping
 * 
 * @return Maximum clipping distance
 */
float Camera::getMaximumDistance() const { return maxDistance; }

/**
 * @brief Converts world space to OpenGL clip space
 * 
 * @param x X-coordinate
 * @param y Y-coordinate
 * @param z Z-coordinate
 * 
 * @return 3D coordinate in OpenGL clip space
 */
Vec3 Camera::worldToClip(float x, float y, float z) const {
    Vec4 v = VPMatrix * Vec4(x, y, z, 1);
    return Vec3(v.x/v.w, v.y/v.w, v.z/v.w);
}

}
