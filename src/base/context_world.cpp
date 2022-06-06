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


#define RMG_EXPORT


#include "rmg/context.hpp"


namespace rmg {

/**
 * @brief Sets OpenGL viewport size
 * 
 * @param w Viewport width
 * @param h Viewport height
 */
void Context::setContextSize(uint16_t w, uint16_t h) {
    width = w;
    height = h;
    camera.setAspectRatio((float)w/h);
    object2dShader.setContextSize(w, h);
}

/**
 * @brief Gets the viewport size
 * 
 * @return Rectangular dimension
 */
Rect Context::getContextSize() const {
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
}

/**
 * @brief Sets context background color
 * 
 * @param col RGB color
 */
void Context::setBackgroundColor(const Color &col) {
    bgColor = col;
}

/**
 * @brief Gets context background color
 * 
 * @return RGB color
 */
Color Context::getBackgroundColor() const { return bgColor; }

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
    camera.setTranslation(x, y, z);
    shadowMapShader.setCameraTranslation(Vec3(x,y,z));
}

/**
 * @brief Sets xyz position of the camera
 * 
 * Sets the translation part of the view matrix.
 * 
 * @param pos Camera position
 */
void Context::setCameraTranslation(const Vec3 &pos) {
    camera.setTranslation(pos);
    shadowMapShader.setCameraTranslation(pos);
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
    camera.setRotation(x, y, z);
    dlCameraSpace = (Vec3) (camera.getViewMatrix() * Vec4(dlWorldSpace, 0));
    shadowMapShader.setCameraRotation(x, y, z);
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
 * @param unit The previous params are degree or radian
 */
void Context::setCameraRotation(float x, float y, float z, AngleUnit unit) {
    camera.setRotation(x, y, z, unit);
    dlCameraSpace = (Vec3) (camera.getViewMatrix() * Vec4(dlWorldSpace, 0));
    shadowMapShader.setCameraRotation(x, y, z, unit);
}

/**
 * @brief Sets rotation of the camera
 * 
 * Sets the view matrix. Rotation of the camera is in Euler angles.
 * Rotation order is ZYX (Yaw-Pitch-Roll).
 * 
 * @param rot Euler angles
 */
void Context::setCameraRotation(const Euler &rot) {
    camera.setRotation(rot);
    dlCameraSpace = (Vec3) (camera.getViewMatrix() * Vec4(dlWorldSpace, 0));
    shadowMapShader.setCameraRotation(rot);
}

/**
 * @brief Gets xyz position of the camera
 * 
 * Gets values from the translation part of the view matrix.
 * 
 * @return XYZ position
 */
Vec3 Context::getCameraTranslation() const { return camera.getTranslation(); }

/**
 * @brief Gets rotation of the camera
 * 
 * Calculates values from the rotation part of the view matrix.
 * Rotation order is ZYX (Yaw-Pitch-Roll).
 *
 * @return Rotation in Euler angles
 */
Euler Context::getCameraRotation() const { return camera.getRotation(); }

/**
 * @brief Sets the projection to perspective mode
 */
void Context::setPerspectiveProjection() {
    camera.setPerspectiveProjection();
    shadowMapShader.setMinimumDistance(1.0f);
    shadowMapShader.setMaximumDistance(10.0f);
}

/**
 * @brief Sets the parameters for perspective projection
 * 
 * Sets the perspective matrix.
 * 
 * @param fov Field of view
 * @param n Minimum clipping distance
 * @param f Maximum clipping distance
 */
void Context::setPerspectiveProjection(float fov, float n, float f) {
    camera.setPerspectiveProjection(fov, n, f);
    shadowMapShader.setMinimumDistance(n);
    shadowMapShader.setMaximumDistance(f);
}

/**
 * @brief Sets the projection to orthographic mode
 */
void Context::setOrthographicProjection() {
    camera.setOrthographicProjection();
    shadowMapShader.setMinimumDistance(1.0f);
    shadowMapShader.setMaximumDistance(10.0f);
}

/**
 * @brief Sets the parameters for orthographic projection
 * 
 * Sets the perspective matrix.
 * 
 * @param fov Viewing distance along Y-axis of the screen
 * @param near Minimum clipping distance
 * @param far Maximum clipping distance
 */
void Context::setOrthographicProjection(float fov, float n, float f) {
    camera.setOrthographicProjection(fov, n, f);
    shadowMapShader.setMinimumDistance(n);
    shadowMapShader.setMaximumDistance(f);
}

/**
 * @brief Sets angle of view for perspective projection
 * 
 * @param fov Field of view
 */
void Context::setFieldOfView(float fov) { camera.setFieldOfView(fov); }

/**
 * @brief Sets minimum distance for depth clipping
 * 
 * @param n Minimum clipping distance
 */
void Context::setMinimumDistance(float n) {
    camera.setMinimumDistance(n);
    shadowMapShader.setMinimumDistance(n);
}

/**
 * @brief Sets maximum distance for depth clipping
 * 
 * @param f Maximum clipping distance
 */
void Context::setMaximumDistance(float f) {
    camera.setMaximumDistance(f);
    shadowMapShader.setMaximumDistance(f);
}

/**
 * @brief Gets angle of view used in perspective projection
 * 
 * @return Field of view
 */
float Context::getFieldOfView() const { return camera.getFieldOfView(); }
    
/**
 * @brief Gets minimum distance for depth clipping
 * 
 * @return Minimum clipping distance
 */
float Context::getMinimumDistance() const {
    return camera.getMinimumDistance();
}

/**
 * @brief Gets maximum distance for depth clipping
 * 
 * @return Maximum clipping distance
 */
float Context::getMaximumDistance() const {
    return camera.getMinimumDistance();
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
Color Context::getDirectionalLightColor() const { return dlColor; }

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
    dlCameraSpace = Vec3(camera.getViewMatrix() * Vec4(dlWorldSpace, 0));
    shadowMapShader.setDirectionalLightVector(dlWorldSpace);
}

/**
 * @brief Gets the directional lighting angles
 * 
 * Rotation order is ZY (Yaw-Pitch). Rolling has no effect and the
 * x in returned instance is always zero.
 * 
 * @return Rotation in Euler angles
 */
Euler Context::getDirectionalLightAngles() const {
    Euler rot;
    rot.roll = 0;
    rot.pitch = asin(-dlWorldSpace.z);
    float c2 = cos(rot.pitch);
    rot.yaw = atan2(dlWorldSpace.y / c2, dlWorldSpace.x / c2);
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
Rect Context::worldToScreen(float x, float y, float z) const {
    Vec4 S = camera.getVPMatrix() * Vec4(x, y, z, 1);
    Rect pt;
    pt.x = (uint16_t)((S.x/S.w + 1) * width/2.0f);
    pt.y = (uint16_t)((1 - S.y/S.w) * height/2.0f);
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
Rect Context::worldToScreen(const Vec3 &p) const {
    Vec4 S = camera.getVPMatrix() * Vec4(p, 1);
    Rect pt;
    pt.x = (uint16_t)((S.x/S.w + 1) * width/2);
    pt.y = (uint16_t)((1 - S.y/S.w) * height/2);
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
LineEq Context::screenToWorld(uint16_t x, uint16_t y) const {
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
LineEq Context::screenToWorld(const Rect &p) const {
    return LineEq();
}

}
