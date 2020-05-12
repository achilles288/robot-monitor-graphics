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


namespace rmg {

uint32_t Context::lastContextID = 0;
std::vector<Context*> Context::contextList;

/**
 * @brief Default constructor
 */
Context::Context() {
    id = ++lastContextID;
    contextList.push_back(this);
    width = 0;
    height = 0;
    bgColor = Color(0, 0, 0, 1);
    sizeUpdate = true;
    bgUpdate = true;
    viewMatrix = {
      {1, 0, 0, 0},
      {0, 1, 0,-5},
      {0, 0, 1, 0},
      {0, 0, 0, 1}
    };
    projectionMatrix = Mat4();
    VPMatrix = viewMatrix;
    minDistance = 0.5f;
    maxDistance = 50.0f;
    directionalLight = Vec3(-0.354f, 0.612f, -0.707f);
    directionalLightCamera = Vec3(-0.354f, 0.612f, -0.707f);
    directionalLightColor = Color(1, 1, 1, 1);
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
    
    // Matrix update
    
    VPMatrix = viewMatrix * projectionMatrix;
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
    viewMatrix[0][3] = -x;
    viewMatrix[1][3] = -y;
    viewMatrix[2][3] = -z;
    VPMatrix = viewMatrix * projectionMatrix;
}

/**
 * @brief Sets xyz position of the camera
 * 
 * Sets the translation part of the view matrix.
 * 
 * @param pos Camera position
 */
void Context::setCameraTranslation(const Vec3 &pos) {
    viewMatrix[0][3] = -pos.x;
    viewMatrix[1][3] = -pos.y;
    viewMatrix[2][3] = -pos.z;
    VPMatrix = viewMatrix * projectionMatrix;
}

/**
 * @brief Sets rotation of the camera
 * 
 * Sets the view matrix. Rotation of the camera is in Euler angles.
 * Rotation order is ZYX (Yaw-Pitch-Roll). Initial camera direction
 * or X-axis is along the Y-axis of the world (rotation values of
 * (0,0,0)).
 * 
 * @param x Roll
 * @param y Pitch
 * @param z Yaw
 */
void Context::setCameraRotation(float x, float y, float z) {
    float c1 = cos(x);
    float c2 = cos(y);
    float c3 = cos(z);
    float s1 = sin(-x);
    float s2 = sin(-y);
    float s3 = sin(-z);
    viewMatrix[0][0] = c2*c3;
    viewMatrix[0][1] = s1*s2*c3 - c1*s3;
    viewMatrix[0][2] = c1*s2*c3 + s1*s3;
    viewMatrix[1][0] = c2*s3;
    viewMatrix[1][1] = s1*s2*s3 + c1*c3;
    viewMatrix[1][2] = c1*s2*s3 - s1*c3;
    viewMatrix[2][0] = -s2;
    viewMatrix[2][1] = s1*c2;
    viewMatrix[2][2] = c1*c2;
    VPMatrix = viewMatrix * projectionMatrix;
    
    Mat4 viewRotation = viewMatrix;
    viewRotation[0][3] = 0;
    viewRotation[1][3] = 0;
    viewRotation[2][3] = 0;
    directionalLightCamera = (Vec3) (viewRotation * Vec4(directionalLight, 1));
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
        -viewMatrix[0][0],
        -viewMatrix[0][1],
        -viewMatrix[0][2]
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
    Euler rot;
    rot.pitch = -asin(viewMatrix[2][0]);
    float c2 = cos(rot.pitch);
    
    // cos(pitch) != 0
    if(fabs(c2) > 0.001f) {
        rot.roll = -atan2(viewMatrix[2][1]/c2, viewMatrix[2][2]/c2);
        rot.yaw = -atan2(viewMatrix[1][0]/c2, viewMatrix[0][0]/c2);
    }
    // Gimbal lock position
    else {
        if(rot.pitch > 0) { // pitch = pi/2
            rot.yaw = -atan2(-viewMatrix[0][1], viewMatrix[0][2]);
        }
        else { // pitch = -pi/2
            rot.yaw = -atan2(-viewMatrix[0][1], -viewMatrix[0][2]);
        }
        rot.roll = 0;
    }
    return rot;
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
    // Matrix set
    
    VPMatrix = viewMatrix * projectionMatrix;
}

/**
 * @brief Sets angle of view for perspective projection
 * 
 * @param fov Field of view
 */
void Context::setFieldOfView(float fov) {
    // Matrix update
    
    VPMatrix = viewMatrix * projectionMatrix;
}

/**
 * @brief Sets minimum distance for depth clipping
 * 
 * @param near Minimum clipping distance
 */
void Context::setMinimumDistance(float near) {
    // Matrix update
    
    VPMatrix = viewMatrix * projectionMatrix;
}

/**
 * @brief Sets maximum distance for depth clipping
 * 
 * @param far Maximum clipping distance
 */
void Context::setMaximumDistance(float far) {
    // Matrix update
    
    VPMatrix = viewMatrix * projectionMatrix;
}

/**
 * @brief Gets angle of view used in perspective projection
 * 
 * @return Field of view
 */
float Context::getFieldOfView() {
    return 0;
}
    
/**
 * @brief Gets minimum distance for depth clipping
 * 
 * @return Minimum clipping distance
 */
float Context::getMinimumDistance() {
    return 0;
}

/**
 * @brief Gets maximum distance for depth clipping
 * 
 * @return Maximum clipping distance
 */
float Context::getMaximumDistance() {
    return 0;
}

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
    directionalLightColor.red = r;
    directionalLightColor.green = g;
    directionalLightColor.blue = b;
    directionalLightColor.alpha = lum;
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
    directionalLightColor = col;
}

/**
 * @brief Gets the directional lighting color
 * 
 * RGB color. Light intensity is in place of alpha component.
 * 
 * @return Light color and intensity
 */
Color Context::getDirectionalLightColor() { return directionalLightColor; }

/**
 * @brief Sets the directional lighting angles
 * 
 * Directional light takes the main role in fragment shaders and
 * shadow mappings for 3D object viewing. Rotation order is
 * ZY (Yaw-Pitch). Rolling has no effect. Directional light vector
 * with angle values of zeros is pointed towards the Y-axis which
 * is the same as initial camera direction.
 * 
 * @param pitch Angle above xy-plane
 * @param yaw Angle about z-axis
 */
void Context::setDirectionalLightAngles(float pitch, float yaw) {
    directionalLight.x = - cos(yaw) * cos(pitch);
    directionalLight.y = - sin(yaw) * cos(pitch);
    directionalLight.z = - sin(pitch);
    
    Mat4 viewRotation = viewMatrix;
    viewRotation[0][3] = 0;
    viewRotation[1][3] = 0;
    viewRotation[2][3] = 0;
    directionalLightCamera = (Vec3) (viewRotation * Vec4(directionalLight, 1));
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
    rot.y = asin(-directionalLight.z);
    float c2 = cos(rot.y);
    rot.z = atan2(-directionalLight.y / c2, -directionalLight.x / c2);
    rot.y = 0;
    return rot;
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
    pt.x = (int16_t)((S.x + 1) * width/2);
    pt.y = (int16_t)((S.y + 1) * height/2);
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
    pt.x = (int16_t)((S.x + 1) * width/2);
    pt.y = (int16_t)((S.y + 1) * height/2);
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
