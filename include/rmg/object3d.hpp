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

#include <rmg/math.hpp>
#include <rmg/object.hpp>

#include <memory>


namespace rmg {

class Context;
class Cube3D;
class Cylinder3D;
class Sphere3D;

namespace internal {

class VBOLoad;
class GeneralShader;
class ShadowMapShader;

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
    using internal::VBOLoad;
    
    VBOLoad* vbo;
    std::shared_ptr<VBOLoadPending> loadPending;
    glm::mat4 modelMatrix;
    glm::mat3 rotationMatrix;
    Vec3 scale;
    float diffuse;
    float specular;
    
    friend class Context;
    friend class Cube3D;
    friend class Cylinder3D;
    friend class Sphere3D;
    friend class internal::GeneralShader;
    friend class internal::ShadowMapShader;
    
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
     * @brief Copy constructor
     * 
     * @param obj Source object
     */
    Object3D(const Object3D& obj);
    
    /**
     * @brief Move constructor
     * 
     * @param obj Source object
     */
    Object3D(Object3D&& obj) noexcept;
    
    /**
     * @brief Copy assignment
     * 
     * @param obj Source object
     */
    Object3D& operator=(const Object3D& obj);
    
    /**
     * @brief Move assignment
     * 
     * @param obj Source object
     */
    Object3D& operator=(Object3D&& obj) noexcept;
    
    /**
     * @brief Sets the 3D coordinate which the object appears
     * 
     * Assigns values to the model matrix's translation part.
     * 
     * @param x X-coordinate
     * @param y Y-coordinate
     * @param z Z-coordinate
     */
    void setPosition(float x, float y, float z);
    
    /**
     * @brief Sets the 3D coordinate which the object appears
     * 
     * Assigns values to the model matrix's translation part.
     * 
     * @param pos Position vector
     */
    void setPosition(const Vec3 &pos);
    
    /**
     * @brief Gets the 3D coordinate which the object appears
     * 
     * Gets values from the translation part of the model matrix
     * 
     * @return Position vector
     */
    Vec3 getPosition();
    
    /**
     * @brief Sets the orientaion of the 3D object
     * 
     * Sets the rotation matrix and the model matrix. Rotation of the object
     * is in Euler angles. Rotation order is ZYX (Yaw-Pitch-Roll).
     * The function is virtual as the derived classes' handling of model
     * matrix involves additional scaling components.
     * 
     * @param x Roll
     * @param y Pitch
     * @param z Yaw
     */
    virtual void setRotation(float x, float y, float z);
    
    /**
     * @brief Sets the orientaion of the 3D object
     * 
     * Sets the rotation matrix and the model matrix. Rotation of the object
     * is in Euler angles. Rotation order is ZYX (Yaw-Pitch-Roll).
     * The function is virtual as the derived classes' handling of model
     * matrix involves additional scaling components.
     * 
     * @param x Roll
     * @param y Pitch
     * @param z Yaw
     * @param unit If the previous params are degree or radian
     */
    inline void setRotation(float x, float y, float z, AngleUnit unit) {
        if(unit == UNIT_RADIAN)
            setRotation(x, y, z);
        else
            setRotation(radian(x), radian(y), radian(z));
    }
    
    /**
     * @brief Sets the orientaion of the 3D object
     * 
     * Sets the rotation matrix and the model matrix. Rotation of the object
     * is in Euler angles. Rotation order is ZYX (Yaw-Pitch-Roll).
     * 
     * @param rot Euler angles
     */
    inline void setRotation(const Euler &rot) {
        setRotation(rot.x, rot.y, rot.z);
    }
    
    /**
     * @brief Gets the orientaion of the 3D object
     * 
     * Calculates Euler angles from the rotation matrix.
     * 
     * @return Euler angles
     */
    Vec3 getRotation();
    
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
     * @brief Sets the diffusion coefficient of the 3D object material
     * 
     * Diffused light diffuses along the whole surface almost uniformly.
     * 
     * @param diff Diffusion coefficient
     */
    void setDiffusion(float diff);
    
    /**
     * @brief Gets the diffusion coefficient of the 3D object material
     * 
     * Diffused light diffuses along the whole surface almost uniformly.
     * 
     * @return Diffusion coefficient
     */
    float getDiffusion();
    
    /**
     * @brief Sets the specularity coefficient of the 3D object material
     * 
     * Specular light means reflected light and this property usually forms
     * bright spot at some angles of the object.
     * 
     * @param spec Specularity coefficient
     */
    void setSpecularity(float spec);
    
    /**
     * @brief Gets the specularity coefficient of the 3D object material
     * 
     * Specular light means reflected light and this property usually forms
     * bright spot at some angles of the object.
     * 
     * @return Specularity coefficient
     */
    float getSpecularity();
};

}

#endif
