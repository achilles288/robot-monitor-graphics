/**
 * @file context_world.cpp
 * @brief 2D/3D graphics world environment model
 * 
 * Background model, camera settings and lighting models.
 * Also contains class construction.
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#include "rmg/context.hpp"

#include "rmg/color.hpp"
#include "rmg/math/line_equation.hpp"

#include <iostream>
using std::cout;
using std::endl;


namespace rmg {

uint32_t Context::lastContextID = 0;
std::vector<Context*> Context::contextList;

/**
 * @brief Default constructor
 */
Context::Context() {
    id = ++lastContextID;
    contextList.push_back(this);
    width = 1;
    height = 1;
    bgColor = Color(0, 0, 0, 1);
    sizeUpdate = true;
    bgUpdate = true;
    viewMatrix = {
      { 0,-1, 0, 0},
      { 0, 0, 1, 0},
      {-1, 0, 0, 0},
      { 0, 0, 0, 1}
    };
    projectionMatrix = {
      {2.414f, 0     ,  0     ,  0     },
      {0     , 2.414f,  0     ,  0     },
      {0     , 0     , 11/9.0f, 20/9.0f},
      {0     , 0     , -1     ,  0     }
    };
    VPMatrix = projectionMatrix * viewMatrix;
    minDistance = 1.0f;
    maxDistance = 10.0f;
    dlWorldSpace = Vec3(-0.354f, 0.612f, -0.707f);
    dlCameraSpace = Vec3(-0.354f, 0.612f, -0.707f);
    dlColor = Color(1, 1, 1, 1);
    destroyed = false;
    initDone = false;
    startTime = 0;
    fps = 0;
    errorCode = 0;
}

/**
 * @brief Destructor
 */
Context::~Context() {
    cleanup();
    if(!destroyed)
        destroy();
}

/**
 * @brief Gets the ID of the context
 * 
 * @return Context ID
 */
uint32_t Context::getID() { return id; }

/**
 * @brief Sets OpenGL viewport size
 * 
 * @param w Viewport width
 * @param h Viewport height
 */
void Context::setContextSize(uint16_t w, uint16_t h) {
    width = w;
    height = h;
    sizeUpdate = true;
    projectionMatrix[0][0] = (h/(float)w) * projectionMatrix[1][1];
    VPMatrix = projectionMatrix * viewMatrix;
}

/**
 * @brief Gets the viewport size
 * 
 * @return Rectangular dimension
 */
Rect Context::getContextSize() {
    return Rect(width, height);
}

/**
 * @brief Sets context background color
 * 
 * @param r Red
 * @param g Green
 * @param b Blue
 */
void Context::setBackgroundColor(float r, float g, float b) {
    bgColor.red = r;
    bgColor.green = g;
    bgColor.blue = b;
    bgUpdate = true;
}

/**
 * @brief Sets context background color
 * 
 * @param col RGB color
 */
void Context::setBackgroundColor(const Color &col) {
    bgColor = col;
    bgUpdate = true;
}

/**
 * @brief Gets context background color
 * 
 * @return RGB color
 */
Color Context::getBackgroundColor() { return bgColor; }

/**
 * @brief Sets xyz position of the camera
 * 
 * Sets the translation part of the view matrix.
 * 
 * @param x X-coordinate
 * @param y Y-coordinate
 * @param z Z-coordinate
 */
void Context::setCameraTranslation(float x, float y, float z) {
    viewMatrix[0][3] = y;
    viewMatrix[1][3] = -z;
    viewMatrix[2][3] = x;
    VPMatrix = projectionMatrix * viewMatrix;
}

/**
 * @brief Sets xyz position of the camera
 * 
 * Sets the translation part of the view matrix.
 * 
 * @param pos Camera position
 */
void Context::setCameraTranslation(const Vec3 &pos) {
    viewMatrix[0][3] = pos.y;
    viewMatrix[1][3] = -pos.z;
    viewMatrix[2][3] = pos.x;
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
void Context::setCameraRotation(float x, float y, float z) {
    Mat3 adjust = {
        { 0,-1, 0},
        { 0, 0, 1},
        {-1, 0, 0}
    };
    Mat3 R = adjust * Euler(x,y,z).toRotationMatrix().inverse();
    
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++)
            viewMatrix[i][j] = R[i][j];
    }
    
    VPMatrix = projectionMatrix * viewMatrix;
    dlCameraSpace = (Vec3) (viewMatrix * Vec4(dlWorldSpace, 0));
}

/**
 * @brief Gets xyz position of the camera
 * 
 * Gets values from the translation part of the view matrix.
 * 
 * @return XYZ position
 */
Vec3 Context::getCameraTranslation() {
    return Vec3(
        viewMatrix[2][3],
        viewMatrix[0][3],
        -viewMatrix[1][3]
    );
}

/**
 * @brief Gets rotation of the camera
 * 
 * Calculates values from the rotation part of the view matrix.
 * Rotation order is ZYX (Yaw-Pitch-Roll).
 *
 * @return Rotation in Euler angles
 */
Euler Context::getCameraRotation() {
    Mat3 adjust = {
        { 0, 0,-1},
        {-1, 0, 0},
        { 0, 1, 0}
    };
    Mat3 R = (adjust * Mat3(viewMatrix)).inverse();
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
void Context::setPerspectiveProjection(float fov, float near, float far) {
    minDistance = near;
    maxDistance = far;
    float d = 1/tan(fov/2);
    float aspect = height/(float)width;
    float A = (near+far)/(far-near);
    float B = (2*near*far)/(far-near);
    /**
     * projectionMatrix = {
     *   {d*aspect, 0,  0, 0},
     *   {    0   , d,  0, 0},
     *   {    0   , 0,  A, B},
     *   {    0   , 0, -1, 0}
     * };
     */
    projectionMatrix[0][0] = d*aspect;
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
void Context::setFieldOfView(float fov) {
    float d = 1/tan(fov/2);
    float aspect = height/(float)width;
    projectionMatrix[0][0] = d*aspect;
    projectionMatrix[1][1] = d;
    VPMatrix = projectionMatrix * viewMatrix;
}

/**
 * @brief Sets minimum distance for depth clipping
 * 
 * @param near Minimum clipping distance
 */
void Context::setMinimumDistance(float near) {
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
void Context::setMaximumDistance(float far) {
    maxDistance = far;
    projectionMatrix[2][2] = (minDistance+maxDistance) /
                             (maxDistance-minDistance);
    projectionMatrix[2][3] = (2*minDistance*maxDistance) /
                             (maxDistance-minDistance);
    VPMatrix = projectionMatrix * viewMatrix;
}

/**
 * @brief Gets angle of view used in perspective projection
 * 
 * @return Field of view
 */
float Context::getFieldOfView() {
    return 2*atan(1/projectionMatrix[1][1]);
}
    
/**
 * @brief Gets minimum distance for depth clipping
 * 
 * @return Minimum clipping distance
 */
float Context::getMinimumDistance() { return minDistance; }

/**
 * @brief Gets maximum distance for depth clipping
 * 
 * @return Maximum clipping distance
 */
float Context::getMaximumDistance() { return maxDistance; }

/**
 * @brief Sets the directional lighting color
 * 
 * Directional light takes the main role in fragment shaders and
 * shadow mappings for 3D object viewing.
 * 
 * @param r Red
 * @param g Green
 * @param b Blue
 * @param lum Light intensity
 */
void Context::setDirectionalLightColor(float r, float g, float b, float lum)
{
    dlColor.red = r;
    dlColor.green = g;
    dlColor.blue = b;
    dlColor.alpha = lum;
}

/**
 * @brief Sets the directional lighting color
 * 
 * Directional light takes the main role in fragment shaders and
 * shadow mappings for 3D object viewing.
 * 
 * @param col RGBA color. Alpha component is used as light intensity.
 */
void Context::setDirectionalLightColor(const Color &col) {
    dlColor = col;
}

/**
 * @brief Gets the directional lighting color
 * 
 * @return RGBA color. Alpha component is used as light intensity.
 */
Color Context::getDirectionalLightColor() { return dlColor; }

/**
 * @brief Sets the directional lighting angles
 * 
 * Directional light takes the main role in fragment shaders and
 * shadow mappings for 3D object viewing. Rotation order is
 * ZY (Yaw-Pitch). Rolling has no effect.
 * 
 * @param pitch Angle above xy-plane
 * @param yaw Angle about z-axis
 */
void Context::setDirectionalLightAngles(float pitch, float yaw) {
    dlWorldSpace.x = cos(yaw) * cos(pitch);
    dlWorldSpace.y = sin(yaw) * cos(pitch);
    dlWorldSpace.z = -sin(pitch);
    dlCameraSpace = Vec3(viewMatrix * Vec4(dlWorldSpace, 0));
}

/**
 * @brief Gets the directional lighting angles
 * 
 * Rotation order is ZY (Yaw-Pitch). Rolling has no effect and the
 * x in returned instance is always zero.
 * 
 * @return Rotation in Euler angles
 */
Euler Context::getDirectionalLightAngles() {
    Euler rot;
    rot.roll = 0;
    rot.pitch = asin(-dlWorldSpace.z);
    float c2 = cos(rot.pitch);
    rot.yaw = atan2(dlWorldSpace.y / c2, dlWorldSpace.x / c2);
    return rot;
}

/**
 * @brief Converts world space to OpenGL clip space
 * 
 * @param x X-coordinate
 * @param y Y-coordinate
 * @param z Z-coordinate
 * 
 * @return 3D coordinate in OpenGL clip space
 */
Vec3 Context::worldToClip(float x, float y, float z) {
    Vec4 v = VPMatrix * Vec4(x, y, z, 1);
    return Vec3(v.x/v.w, v.y/v.w, v.z/v.w);
}

/**
 * @brief Converts world coordinate to screen coordinate
 * 
 * Useful when displaying 2D sprites and texts around 3D objects.
 * 
 * @param x X-coordinate
 * @param y Y-coordinate
 * @param z Z-coordinate
 * 
 * @return 2D point on screen
 */
Rect Context::worldToScreen(float x, float y, float z) {
    Vec4 S = VPMatrix * Vec4(x, y, z, 1);
    Rect pt;
    pt.x = (int16_t)((S.x/S.w + 1) * width/2);
    pt.y = (int16_t)((S.y/S.w + 1) * height/2);
    return pt;
}

/**
 * @brief Converts world coordinate to screen coordinate
 * 
 * Useful when displaying 2D sprites and texts around 3D objects.
 * 
 * @param p 3D point in world space
 * 
 * @return 2D point on screen
 */
Rect Context::worldToScreen(const Vec3 &p) {
    Vec4 S = VPMatrix * Vec4(p, 1);
    Rect pt;
    pt.x = (int16_t)((S.x/S.w + 1) * width/2);
    pt.y = (int16_t)((S.y/S.w + 1) * height/2);
    return pt;
}

/**
 * @brief Converts screen coordinate to world coordinate
 * 
 * Useful when interacting 3D objects with a mouse.
 * 
 * @param x X-coordinate
 * @param y Y-coordinate
 * 
 * @return Line equation in 3D world
 */
LineEq Context::screenToWorld(uint16_t x, uint16_t y) {
    return LineEq();
}

/**
 * @brief Converts screen coordinate to world coordinate
 * 
 * Useful when interacting 3D objects with a mouse.
 * 
 * @param p Point on screen
 * 
 * @return Line equation in 3D world
 */
LineEq Context::screenToWorld(const Rect &p) {
    return LineEq();
}

/**
 * @brief Searches context model by ID
 * 
 * @return OpenGL context
 */
Context* Context::getContextByID(uint32_t id) {
    for(auto it=contextList.begin(); it!=contextList.end(); it++) {
        if((*it)->id == id)
            return *it;
    }
    return NULL;
}

}
