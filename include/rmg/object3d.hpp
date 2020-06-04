/**
 * @file object3d.hpp
 * @brief 3D object whose model and appearance can be controlled quickly
 *
 * The constructor builds a vertex buffer object to load into the GPU and
 * keeps the address to that resource. The model matrix and material
 * properties like color, diffusion and specularity coefficient are passed
 * into shader programs to render the 3D object. Mainpulation of position,
 * rotation and scale keep up with the model matrix.
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#pragma once
#ifndef __RMG_OBJECT_3D_H__
#define __RMG_OBJECT_3D_H__

#include <memory>

#include "object.hpp"
#include "math/euler.hpp"
#include "math/mat3.hpp"
#include "math/mat4.hpp"
#include "math/vec.hpp"
#include "internal/vbo_load.hpp"
#include "internal/context_load.hpp"


namespace rmg {

namespace internal {

class GeneralShader;
class ShadowMapShader;
class VBO;

}


/**
 * @brief 3D object whose model and appearance can be controlled quickly
 *
 * The constructor builds a vertex buffer object to load into the GPU and
 * keeps the address to that resource. The model matrix and material
 * properties like color, diffusion and specularity coefficient are passed
 * into shader programs to render the 3D object. Mainpulation of position,
 * rotation and scale keep up with the model matrix.
 */
class Object3D: public Object {
  private:
    Material* material;
    float metalness;
    float roughness;
    float ambientOcculation;
    
    friend class Context;
    friend class internal::GeneralShader;
    friend class internal::ShadowMapShader;
    
    std::shared_ptr<internal::VBO> vbo;
    internal::ContextLoader::Pending vboLoad;
    
  protected:
    /**
     * @brief The matrix composed of all the transformations done by the
     *        object
     */
    Mat4 modelMatrix;
    Mat3 rotationMatrix; ///< Rotation done by the object
    Vec3 scale; ///< Scaling factors as a vector
    
    /**
     * @brief Sets the shared VBO of the object
     * 
     * Usually used to shared existing VBOs of basic geometries,
     * cubes, spheres and cylinders.
     * 
     * @param vbo Shared pointer
     */
    void setSharedVBO(std::shared_ptr<internal::VBO> vbo);
    
    /**
     * @brief Sets the mesh of the 3D object
     * 
     * @param mesh 3D Mesh containing vertex coordinates
     */
    void setMesh(const Mesh& mesh);
    
  public:
    /**
     * @brief Constructor with its container
     * 
     * @param ctx Container context
     */
    Object3D(Context* ctx);
    
    /**
     * @brief Destructor decreases the VBO reference count
     * 
     * When the reference count of the shared pointer drops to zero, it
     * cleans up the GPU resource taken by the VBO.
     */
    virtual ~Object3D();
    
    /**
     * @brief The matrix composed of all the transformations done by the
     *        object
     * 
     * @return Model matrix
     */
    Mat4 getModelMatrix();
    
    /**
     * @brief Sets the 3D coordinate which the object appears
     * 
     * Assigns values to the model matrix's translation part.
     * 
     * @param x X-coordinate
     * @param y Y-coordinate
     * @param z Z-coordinate
     */
    void setTranslation(float x, float y, float z);
    
    /**
     * @brief Sets the 3D coordinate which the object appears
     * 
     * Assigns values to the model matrix's translation part.
     * 
     * @param pos Position vector
     */
    void setTranslation(const Vec3 &pos);
    
    /**
     * @brief Gets the 3D coordinate which the object appears
     * 
     * Gets values from the translation part of the model matrix
     * 
     * @return Position vector
     */
    Vec3 getTranslation();
    
    /**
     * @brief Sets the orientaion of the 3D object
     * 
     * Sets the rotation matrix and the model matrix. Rotation of the object
     * is in Euler angles. Rotation order is ZYX (Yaw-Pitch-Roll).
     * The function is virtual as the derived classes' handling of model
     * matrix involves additional scaling components.
     * 
     * @param rot Euler angles
     */
    virtual void setRotation(const Euler &rot) {
        setRotation(rot.roll, rot.pitch, rot.yaw);
    }
    
    /**
     * @brief Sets the orientaion of the 3D object
     * 
     * Sets the rotation matrix and the model matrix. Rotation of the object
     * is in Euler angles. Rotation order is ZYX (Yaw-Pitch-Roll).
     * 
     * @param x Roll
     * @param y Pitch
     * @param z Yaw
     */
    inline void setRotation(float x, float y, float z) {
        setRotation(Euler(x, y, z));
    }
    
    /**
     * @brief Sets the orientaion of the 3D object
     * 
     * Sets the rotation matrix and the model matrix. Rotation of the object
     * is in Euler angles. Rotation order is ZYX (Yaw-Pitch-Roll).
     * 
     * @param x Roll
     * @param y Pitch
     * @param z Yaw
     * @param unit If the previous params are degree or radian
     */
    inline void setRotation(float x, float y, float z, AngleUnit unit) {
        if(unit == AngleUnit::Radian)
            setRotation(x, y, z);
        else
            setRotation(radian(x), radian(y), radian(z));
    }
    
    /**
     * @brief Gets the orientaion of the 3D object
     * 
     * Calculates Euler angles from the rotation matrix.
     * 
     * @return Euler angles
     */
    Euler getRotation();
    
    /**
     * @brief Sets the scale of the 3D object
     * 
     * Sets the scale and the model matrix.
     * The function is virtual as the derived classes' handling of model
     * matrix involves additional scaling components.
     * 
     * @param x Scaling factor in x-component
     * @param y Scaling factor in y-component
     * @param z Scaling factor in z-component
     */
    virtual void setScale(float x, float y, float z);
    
    /**
     * @brief Sets the scale of the 3D object
     * 
     * Sets the scale and the model matrix.
     * The function is virtual as the derived classes' handling of model
     * matrix involves additional scaling components.
     * 
     * @param f Scaling factor
     */
    virtual void setScale(float f);
    
    /**
     * @brief Sets the scale of the 3D object
     * 
     * @param scale Scale vector
     */
    inline void setScale(const Vec3 &scale) {
        setScale(scale.x, scale.y, scale.z);
    }
    
    /**
     * @brief Gets the scale of the 3D object
     * 
     * @return Scaling factors in x, y and z components
     */
    Vec3 getScale();
    
    /**
     * @brief Sets the material properties of the 3D object
     * 
     * Color is 4-channel. Diffused light diffuses along the whole surface
     * almost uniformly. Specular light means reflected light and this
     * property usually forms bright spot at some angles of the object.
     * 
     * @param col RGBA color
     * @param diff Diffusion coefficient
     * @param spec Specularity coefficient
     */
    void setMaterial(Color col, float diff, float spec);
    
    /**
     * @brief Sets the material texture
     * 
     * Sets the object to use a predefined material. This material data uses
     * OpenGL context for texture image, normal maps, .etc.
     * 
     * @param mat Predefined material
     */
    void setMaterial(Material* mat);
    
    /**
     * @brief Sets the metalness coefficient of the texture
     * 
     * @param m Metalness coefficient
     */
    void setMetalness(float m);
    
    /**
     * @brief Gets the metalness coefficient of the texturey.
     * 
     * @return Metalness coefficient
     */
    float getMetalness();
    
    /**
     * @brief Sets the roughness coefficient of the texture.
     * 
     * @param r Roughness coefficient
     */
    void setRoughness(float r);
    
    /**
     * @brief Gets the roughness coefficient of the texture
     * 
     * @return Roughness coefficient
     */
    float getRoughness();
    
    /**
     * @brief Sets the ambient occulation of the texture.
     * 
     * @param a Ambient occulation
     */
    void setAmbientOcculation(float a);
    
    /**
     * @brief Gets the ambient occulation of the texture
     * 
     * @return Ambient occulation
     */
    float getAmbientOcculation();
};

}

#endif
