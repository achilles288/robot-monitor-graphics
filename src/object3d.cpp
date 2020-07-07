/**
 * @file object3d.cpp
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


#include "rmg/object3d.hpp"

#include "rmg/internal/texture_load.hpp"


namespace rmg {

/**
 * @brief Default constructor
 */
Object3D::Object3D() {
    modelMatrix = Mat4();
    scale = Vec3(1, 1, 1);
    material = NULL;
    metalness = 0.0f;
    roughness = 0.6f;
    ambientOcculation = 0.6f;
}

/**
 * @brief Constructor with its container
 * 
 * @param ctx Container context
 */
Object3D::Object3D(Context* ctx): Object(ctx) {
    modelMatrix = Mat4();
    scale = Vec3(1, 1, 1);
    material = NULL;
    metalness = 0.0f;
    roughness = 0.6f;
    ambientOcculation = 0.6f;
    type = ObjectType::Object3D;
}

/**
 * @brief Sets the shared VBO of the object
 * 
 * Usually used to shared existing VBOs of basic geometries,
 * cubes, spheres and cylinders.
 * 
 * @param vbo Shared pointer
 */
void Object3D::setSharedVBO(std::shared_ptr<internal::VBO> vbo)
{
    this->vbo = vbo;
}

/**
 * @brief Sets the mesh of the 3D object
 * 
 * @param mesh 3D Mesh containing vertex coordinates
 */
void Object3D::setMesh(const Mesh& mesh) {
    internal::VBOLoad *load = new internal::VBOLoad(vbo.get(), mesh);
    vboLoad = internal::ContextLoader::Pending(load);
}

/**
 * @brief The matrix composed of all the transformations done by the object
 * 
 * @return Model matrix
 */
const Mat4& Object3D::getModelMatrix() const { return modelMatrix; }

/**
 * @brief Sets the 3D coordinate which the object appears
 * 
 * Assigns values to the model matrix's translation part.
 * 
 * @param x X-coordinate
 * @param y Y-coordinate
 * @param z Z-coordinate
 */
void Object3D::setTranslation(float x, float y, float z) {
    modelMatrix[0][3] = x;
    modelMatrix[1][3] = y;
    modelMatrix[2][3] = z;
}

/**
 * @brief Sets the 3D coordinate which the object appears
 * 
 * Assigns values to the model matrix's translation part.
 * 
 * @param pos Position vector
 */
void Object3D::setTranslation(const Vec3 &pos) {
    modelMatrix[0][3] = pos.x;
    modelMatrix[1][3] = pos.y;
    modelMatrix[2][3] = pos.z;
}

/**
 * @brief Gets the 3D coordinate which the object appears
 * 
 * Gets values from the translation part of the model matrix
 * 
 * @return Position vector
 */
Vec3 Object3D::getTranslation() const {
    return Vec3(modelMatrix[0][3], modelMatrix[1][3], modelMatrix[2][3]);
}

/**
 * @brief Sets the orientaion of the 3D object
 * 
 * Sets the rotation matrix and the model matrix. Rotation of the object
 * is in Euler angles. Rotation order is ZYX (Yaw-Pitch-Roll).
 * 
 * @param rot Euler angles
 */
void Object3D::setRotation(const Euler &rot) {
    Mat3 R = rot.toRotationMatrix();
    modelMatrix[0][0] = R[0][0] * scale.x;
    modelMatrix[0][1] = R[0][1];
    modelMatrix[0][2] = R[0][2];
    modelMatrix[1][0] = R[1][0];
    modelMatrix[1][1] = R[1][1] * scale.y;
    modelMatrix[1][2] = R[1][2];
    modelMatrix[2][0] = R[2][0];
    modelMatrix[2][1] = R[2][1];
    modelMatrix[2][2] = R[2][2] * scale.z;
}

/**
 * @brief Gets the orientaion of the 3D object
 * 
 * Calculates Euler angles from the rotation matrix.
 * 
 * @return Euler angles
 */
Euler Object3D::getRotation() const {
    Mat3 R = (Mat3) modelMatrix;
    R[0][0] /= scale.x;
    R[1][1] /= scale.y;
    R[2][2] /= scale.z;
    return Euler(R);
}

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
void Object3D::setScale(float x, float y, float z) {
    modelMatrix[0][0] *= x/scale.x;
    modelMatrix[1][1] *= y/scale.y;
    modelMatrix[2][2] *= z/scale.z;
    scale.x = x;
    scale.y = y;
    scale.z = z;
}

/**
 * @brief Sets the scale of the 3D object
 * 
 * Sets the scale and the model matrix.
 * The function is virtual as the derived classes' handling of model
 * matrix involves additional scaling components.
 * 
 * @param f Scaling factor
 */
void Object3D::setScale(float f) {
    modelMatrix[0][0] *= f/scale.x;
    modelMatrix[1][1] *= f/scale.y;
    modelMatrix[2][2] *= f/scale.z;
    scale.x = f;
    scale.y = f;
    scale.z = f;
}

/**
 * @brief Gets the scale of the 3D object
 * 
 * @return Scaling factors in x, y and z components
 */
Vec3 Object3D::getScale() const { return scale; }

/**
 * @brief Sets the material texture
 * 
 * Sets the object to use a predefined material. This material data uses
 * OpenGL context for texture image, normal maps, .etc.
 * 
 * @param mat Predefined material
 */
void Object3D::setMaterial(Material* mat) { material = mat; }

/**
 * @brief Gets the material texture
 * 
 * Gets the object to use a predefined material. This material data uses
 * OpenGL context for texture image, normal maps, .etc.
 * 
 * @return Predefined material texture
 */
Material *Object3D::getMaterial() const { return material; }

/**
 * @brief Loads texture from file
 * 
 * @param f Path to material textures (file, folder or zip)
 */
void Object3D::loadTexture(const std::string &f) {
    auto texture = std::make_shared<internal::Texture>(internal::Texture());
    auto load = new internal::TextureLoad(texture.get(), f);
    vboLoad = internal::ContextLoader::Pending(load);
}

/**
 * @brief Loads texture from bitmap
 * 
 * @param bmp Base image
 */
void Object3D::loadTexture(const Bitmap &bmp) {
    auto texture = std::make_shared<internal::Texture>(internal::Texture());
    auto load = new internal::TextureLoad(texture.get(), bmp);
    vboLoad = internal::ContextLoader::Pending(load);
}

/**
 * @brief Loads texture from bitmap
 * 
 * @param base Base image
 * @param h Height mapping
 * @param norm Normal mapping
 * @param m Metallic, rough, ambient occulation
 * @param e Emissivity
 */
void Object3D::loadTexture(const Bitmap& base, const Bitmap& h,
                           const Bitmap& norm, const Bitmap& m,
                           const Bitmap& e)
{
    auto texture = std::make_shared<internal::Texture>(internal::Texture());
    auto load = new internal::TextureLoad(texture.get(), base, h, norm, m, e);
    vboLoad = internal::ContextLoader::Pending(load);
}

/**
 * @brief Sets the material properties of the 3D object
 * 
 * Sets all three material lighting properties by a single setter function.
 * 
 * @param m Metalness
 * @param r Roughness
 * @param ao Ambient occulation
 */
void Object3D::setMRAO(float m, float r, float ao) {
    metalness = m;
    roughness = r;
    ambientOcculation = ao;
}

/**
 * @brief Sets the metalness coefficient of the texture
 * 
 * @param m Metalness coefficient
 */
void Object3D::setMetalness(float m) { metalness = m; }

/**
 * @brief Gets the metalness coefficient of the texturey.
 * 
 * @return Metalness coefficient
 */
float Object3D::getMetalness() const { return metalness; }

/**
 * @brief Sets the roughness coefficient of the texture.
 * 
 * @param r Roughness coefficient
 */
void Object3D::setRoughness(float r) { roughness = r; }

/**
 * @brief Gets the roughness coefficient of the texture
 * 
 * @return Roughness coefficient
 */
float Object3D::getRoughness() const { return roughness; }

/**
 * @brief Sets the ambient occulation of the texture.
 * 
 * @param ao Ambient occulation
 */
void Object3D::setAmbientOcculation(float ao) { ambientOcculation = ao; }

/**
 * @brief Gets the ambient occulation of the texture
 * 
 * @return Ambient occulation
 */
float Object3D::getAmbientOcculation() const { return ambientOcculation; }

/**
 * @brief Gets the pointer to VBO
 * 
 * @return Pointer to VBO
 */
const internal::VBO *Object3D::getVBO() const { return vbo.get(); }

/**
 * @brief Gets the pointer to the texture
 * 
 * @return Pointer to the texture
 */
const internal::Texture *Object3D::getTexture() const {
    return texture.get();
}

using Pending = internal::ContextLoader::Pending;

/**
 * @brief Gets the VBO loader
 * 
 * @return VBO loader
 */
const Pending& Object3D::getVBOLoad() const { return vboLoad; }

/**
 * @brief Gets the texture loader
 * 
 * @return Texture loader
 */
const Pending& Object3D::getTextureLoad() const { return texLoad; }

}
