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


#include "object.hpp"
#include "math/euler.hpp"
#include "math/mat3.hpp"
#include "math/mat4.hpp"
#include "math/vec.hpp"
#include "internal/vbo_load.hpp"
#include "internal/context_load.hpp"


namespace rmg {

class Bitmap;
class Material;

namespace internal {

class Texture;
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
class RMG_API Object3D: public Object {
  private:
    Mat4 modelMatrix;
    Vec3 scale;
    
    Material* material = nullptr;
    float metalness;
    float roughness;
    float ambientOcculation;
    
    internal::VBO* vbo = nullptr;
    uint32_t* vboShareCount = nullptr;
    internal::Pending vboLoad;
    
    internal::Texture* texture = nullptr;
    uint32_t* texShareCount = nullptr;
    internal::Pending texLoad;
    
    void loadOBJ(const char* file, bool smooth=true);
    
    void dereferenceVBO();
    
    void dereferenceTexture();
    
  protected:
    /**
     * @brief Sets the mesh of the 3D object
     * 
     * @param mesh 3D Mesh containing vertex coordinates
     */
    void setMesh(const Mesh& mesh);
    
    /**
     * @brief Swaps the values of member variables between two objects
     * 
     * @param x The other object
     */
    void swap(Object3D& x) noexcept;
    
  public:
    /**
     * @brief Default constructor
     */
    Object3D();
    
    /**
     * @brief Constructor with its container
     * 
     * @param ctx Container context
     */
    Object3D(Context* ctx);
    
    /**
     * @brief Constructor loads 3D model from file.
     * 
     * @param ctx Container context
     * @param file 3D model file (.obj)
     * @param smooth Generate smooth surface normals if the 3D model does not
     *               contain an option about vertex normals
     */
    Object3D(Context* ctx, const char* file, bool smooth=true);
    
    /**
     * @brief Destructor
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
     * @brief The matrix composed of all the transformations done by the
     *        object
     * 
     * @return Model matrix
     */
    const Mat4& getModelMatrix() const;
    
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
    Vec3 getTranslation() const;
    
    /**
     * @brief Sets the orientaion of the 3D object
     * 
     * Sets the rotation matrix and the model matrix. Rotation of the object
     * is in Euler angles. Rotation order is ZYX (Yaw-Pitch-Roll).
     * 
     * @param rot Euler angles
     */
    void setRotation(const Euler &rot);
    
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
            setRotation(Euler(x, y, z));
        else
            setRotation(Euler(x, y, z, AngleUnit::Degree));
    }
    
    /**
     * @brief Gets the orientaion of the 3D object
     * 
     * Calculates Euler angles retriving the rotation matrix from the model
     * matrix. Additional scaling components involves in such process.
     * 
     * @return Euler angles
     */
    Euler getRotation() const;
    
    /**
     * @brief Sets the scale of the 3D object
     * 
     * Sets the scale and the model matrix.
     * 
     * @param x Scaling factor in x-component
     * @param y Scaling factor in y-component
     * @param z Scaling factor in z-component
     */
    void setScale(float x, float y, float z);
    
    /**
     * @brief Sets the scale of the 3D object
     * 
     * Sets the scale and the model matrix.
     * 
     * @param f Scaling factor
     */
    void setScale(float f);
    
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
    Vec3 getScale() const;
    
    /**
     * @brief Sets the material texture
     * 
     * Sets the object to use a predefined material. This material data uses
     * OpenGL context for texture image, normal maps, .etc.
     * 
     * @param mat Predefined material
     */
    virtual void setMaterial(Material* mat);
    
    /**
     * @brief Gets the material texture
     * 
     * Gets the object to use a predefined material. This material data uses
     * OpenGL context for texture image, normal maps, .etc.
     * 
     * @return Predefined material texture
     */
    Material *getMaterial() const;
    
    /**
     * @brief Loads texture from file
     * 
     * @param f Path to material textures (file, folder or zip)
     */
    void loadTexture(const char* f);
    
    /**
     * @brief Loads texture from bitmap
     * 
     * @param bmp Base image
     */
    void loadTexture(const Bitmap &bmp);
    
    /**
     * @brief Loads texture from bitmap
     * 
     * @param base Base image
     * @param h Height mapping
     * @param norm Normal mapping
     * @param m Metallic, rough, ambient occulation
     * @param e Emissivity
     */
    void loadTexture(const Bitmap& base, const Bitmap& h,
                     const Bitmap& norm, const Bitmap& m, const Bitmap& e);
    
    /**
     * @brief Sets the material properties of the 3D object
     * 
     * Sets all three material lighting properties by a single setter function.
     * 
     * @param m Metalness
     * @param r Roughness
     * @param ao Ambient occulation
     */
    void setMRAO(float m, float r, float ao);
    
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
    float getMetalness() const;
    
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
    float getRoughness() const;
    
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
    float getAmbientOcculation() const;
    
    /**
     * @brief Gets the pointer to VBO
     * 
     * @return Pointer to VBO
     */
    const internal::VBO *getVBO() const;
    
    /**
     * @brief Gets the pointer to the texture
     * 
     * @return Pointer to the texture
     */
    const internal::Texture *getTexture() const;
    
    /**
     * @brief Gets the VBO loader
     * 
     * @return VBO loader
     */
    const internal::Pending& getVBOLoad() const;
    
    /**
     * @brief Gets the texture loader
     * 
     * @return Texture loader
     */
    const internal::Pending& getTextureLoad() const;
};

}

#endif
