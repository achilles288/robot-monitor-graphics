/**
 * @file shadow_map_shader.hpp
 * @brief Generates an image representing the distance from sun at every pixel
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#define RMG_EXPORT


#include "../rmg/internal/shadow_map_shader.hpp"

#include "../../config/rmg/config.h"
#include "../rmg/object3d.hpp"

#define SHADOW_COVERAGE 0.8f
#define SHADOW_MAP_WIDTH 512
#define SHADOW_MAP_HEIGHT 512
#define SHADOW_MAP_ASPECT ((float)SHADOW_MAP_WIDTH/SHADOW_MAP_HEIGHT)


namespace rmg {
namespace internal {

/**
 * @brief Default constructor
 */
ShadowMapShader::ShadowMapShader() {
    shadowMapper.setAspectRatio(SHADOW_MAP_ASPECT);
    shadowMapper.setOrthographicProjection();
    shadowMapper.setMinimumDistance(0);
    cameraPosition = Vec3(0, 0, 0);
    cameraDirection = Vec3(1, 0, 0);
    lightDirection = Vec3(1, 0, 0);
    nearDist = 1.0f;
    farDist = 10.0f;
    mapCenterDist = nearDist + SHADOW_COVERAGE * (farDist-nearDist)/2;
    calculateShadowMapperTranslation();
    shadowMapper.setFieldOfView(
        SHADOW_MAP_ASPECT * SHADOW_COVERAGE * (farDist-nearDist)
    );
}

/**
 * @brief Destructor
 */
ShadowMapShader::~ShadowMapShader() {
    if(depthMapFBO != 0)
        glDeleteFramebuffers(1, &depthMapFBO);
    if(depthMap != 0)
        glDeleteTextures(1, &depthMap);
}




void ShadowMapShader::calculateShadowMapperTranslation() {
    Vec3 pos =
        cameraPosition + 
        mapCenterDist * cameraDirection -
        SHADOW_COVERAGE * (farDist-nearDist) * lightDirection;
    
    shadowMapper.setTranslation(pos);
}

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
void ShadowMapShader::setCameraTranslation(float x, float y, float z) {
    cameraPosition.x = x;
    cameraPosition.y = y;
    cameraPosition.z = z;
    calculateShadowMapperTranslation();
}

/**
 * @brief Sets the camera position
 * 
 * Camera here means the world's camera. This function is used so that
 * the light's viewing point moves together with it.
 * 
 * @param p Position vector
 */
void ShadowMapShader::setCameraTranslation(Vec3 p) {
    cameraPosition = p;
    calculateShadowMapperTranslation();
}

/**
 * @brief Sets the camera rotation
 * 
 * Camera here means the world's camera. This function is used so that
 * the light's viewing direction moves together with it.
 * 
 * @param rot Euler angles
 */
void ShadowMapShader::setCameraRotation(Euler rot) {
    cameraDirection = Vec3(Mat4(rot.toRotationMatrix()) * Vec4(1,0,0,0));
    calculateShadowMapperTranslation();
}

/**
 * @brief Sets minimum distance of the camera
 * 
 * @param n Minimum clipping distance
 */
void ShadowMapShader::setMinimumDistance(float n) {
    nearDist = n;
    mapCenterDist = n + SHADOW_COVERAGE * (farDist-n)/2;
    calculateShadowMapperTranslation();
    shadowMapper.setFieldOfView(
        SHADOW_MAP_ASPECT * SHADOW_COVERAGE * (farDist-n)
    );
    shadowMapper.setMaximumDistance(2 * SHADOW_COVERAGE * (farDist-n));
}

/**
 * @brief Sets maximum distance of the camera
 * 
 * @param f Maximum clipping distance
 */
void ShadowMapShader::setMaximumDistance(float f) {
    farDist = f;
    mapCenterDist = nearDist + SHADOW_COVERAGE * (f-nearDist)/2;
    calculateShadowMapperTranslation();
    shadowMapper.setFieldOfView(
        SHADOW_MAP_ASPECT * SHADOW_COVERAGE * (f-nearDist)
    );
    shadowMapper.setMaximumDistance(2 * SHADOW_COVERAGE * (f-nearDist));
}

/**
 * @brief Sets the directional light vector
 * 
 * Contributes the view matrix of the shadow mapper. The shadow mapper
 * is a camera that views the world from the light's position.
 * 
 * @param v Light direction
 */
void ShadowMapShader::setDirectionalLightVector(Vec3 v) {
    float r = sqrt(v.x*v.x + v.y*v.y);
    Euler rot;
    rot.roll = 0;
    rot.pitch = -atan(v.z/r);
    rot.yaw = atan2(v.y, v.x);
    shadowMapper.setRotation(rot);
    lightDirection = v;
    calculateShadowMapperTranslation();
}

/**
 * @brief Gets the matrix to process shadow mapping
 * 
 * It is the composition of view and projection matrix from the position
 * of the light as a camera. Similar to the VP matrix of a normal camera.
 * 
 * @param v Light direction
 */
const Mat4& ShadowMapShader::getShadowMatrix() const {
    return shadowMapper.getVPMatrix();
}

/**
 * @brief Compiles and links shader program and assigns parameter IDs
 */
void ShadowMapShader::load() {
    id = compileShaderProgram(
        RMG_RESOURCE_PATH "/shaders/shadow_map.vs.glsl",
        RMG_RESOURCE_PATH "/shaders/shadow_map.fs.glsl"
    );
    idMVP = glGetUniformLocation(id, "MVP");
    
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_DEPTH_COMPONENT,
        SHADOW_MAP_WIDTH,
        SHADOW_MAP_HEIGHT,
        0,
        GL_DEPTH_COMPONENT,
        GL_FLOAT,
        NULL
    );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    glGenFramebuffers(1, &depthMapFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(
        GL_FRAMEBUFFER,
        GL_DEPTH_ATTACHMENT,
        GL_TEXTURE_2D,
        depthMap,
        0
    );
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

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
uint32_t ShadowMapShader::createShadowMap(const ObjectList &list) {
    if(id == 0)
        return 0;
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glViewport(0, 0, SHADOW_MAP_WIDTH, SHADOW_MAP_HEIGHT);
    glClearDepth(1.0);
    glClear(GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glDisable(GL_BLEND);
    glUseProgram(id);
    for(auto it=list.begin(); it!=list.end(); it++) {
        Object3D *obj = (Object3D*) &(*it);
        if(obj->isHidden() || obj->getVBO() == nullptr)
            continue;
        Mat4 MVP = shadowMapper.getVPMatrix() * obj->getModelMatrix();
        glUniformMatrix4fv(idMVP, 1, GL_TRUE, &MVP[0][0]);
        obj->getVBO()->draw();
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    return depthMap;
}

}}
