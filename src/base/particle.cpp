/**
 * @file particle.cpp
 * @brief 2D graphics displayed in terms of 3D space
 * 
 * Less detailed 3D graphics like smoke, fog, spark, .etc.
 * Enables wider variety of graphics at low cost.
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#define RMG_EXPORT


#include "rmg/particle.hpp"

#include "rmg/bitmap.hpp"
#include "rmg/internal/sprite_load.hpp"

#include <utility>


namespace rmg {

/**
 * @brief Default constructor
 */
Particle3D::Particle3D() {
    position = Vec3(0, 0, 0);
    size = Vec2(1, 1);
    rotation = 0;
    modelMatrix = Mat3();
}

/**
 * @brief Constructs a particle object loading a particle image
 * 
 * @param ctx Container context
 * @param img Image file (supports the same format Texture class does)
 * @param size Particle size
 */
Particle3D::Particle3D(Context* ctx, const std::string &img, const Vec2 &s)
           :Object(ctx)
{
    texture = new internal::SpriteTexture();
    texShareCount = new uint32_t;
    *texShareCount = 1;
    auto load = new internal::SpriteLoad(texture, img);
    texLoad = internal::Pending(load);
    position = Vec3(0, 0, 0);
    rotation = 0;
    setSize(s);
    type = ObjectType::Particle3D;
}

/**
 * @brief Constructs a particle object loading a particle image
 * 
 * @param ctx Container context
 * @param bmp Particle image
 * @param size Particle size
 */
Particle3D::Particle3D(Context* ctx, const Bitmap &bmp, const Vec2 &s)
           :Object(ctx)
{
    texture = new internal::SpriteTexture();
    texShareCount = new uint32_t;
    *texShareCount = 1;
    auto load = new internal::SpriteLoad(texture, bmp);
    texLoad = internal::Pending(load);
    position = Vec3(0, 0, 0);
    rotation = 0;
    setSize(s);
    type = ObjectType::Particle3D;
}

/**
 * @brief Destructor
 */
Particle3D::~Particle3D() {
    if(texture != nullptr) {
        (*texShareCount)--;
        if(*texShareCount == 0) {
            delete texture;
            delete texShareCount;
        }
    }
}

/**
 * @brief Copy constructor
 * 
 * @param obj Source object
 */
Particle3D::Particle3D(const Particle3D& obj)
           :Object(obj)
{
    texture = obj.texture;
    texShareCount = obj.texShareCount;
    if(texShareCount != nullptr)
        (*texShareCount)++;
    texLoad = obj.texLoad;
    position = obj.position;
    size = obj.size;
    rotation = obj.rotation;
    modelMatrix = obj.modelMatrix;
}

/**
 * @brief Move constructor
 * 
 * @param obj Source object
 */
Particle3D::Particle3D(Particle3D&& obj) noexcept
           :Object(obj)
{
    texture = std::exchange(obj.texture, nullptr);
    texShareCount = std::exchange(obj.texShareCount, nullptr);
    internal::Pending load;
    texLoad = std::exchange(obj.texLoad, load);
    position = std::exchange(obj.position, Vec3(0, 0, 0));
    size = std::exchange(obj.size, Vec2(1, 1));
    rotation = std::exchange(obj.rotation, 0);
    modelMatrix = std::exchange(obj.modelMatrix, Mat3());
}

/**
 * @brief Copy assignment
 * 
 * @param obj Source object
 */
Particle3D& Particle3D::operator=(const Particle3D& obj) {
    Particle3D tmp = Particle3D(obj);
    swap(tmp);
    return *this;
}

/**
 * @brief Move assignment
 * 
 * @param obj Source object
 */
Particle3D& Particle3D::operator=(Particle3D&& obj) noexcept {
    Particle3D tmp = std::move(obj);
    swap(tmp);
    return *this;
}

/**
 * @brief Swaps the values of member variables between two objects
 * 
 * @param x The other object
 */
void Particle3D::swap(Particle3D& x) noexcept {
    std::swap(texture, x.texture);
    std::swap(texShareCount, x.texShareCount);
    std::swap(texLoad, x.texLoad);
    std::swap(position, x.position);
    std::swap(size, x.size);
    std::swap(rotation, x.rotation);
    std::swap(modelMatrix, x.modelMatrix);
    Object::swap(x);
}

/**
 * @brief The matrix composed of all the transformations done by the particle
 * 
 * @return Model matrix
 */
const Mat3& Particle3D::getModelMatrix() const { return modelMatrix; }

/**
 * @brief Sets the location which the particle appears
 * 
 * @param x X-coordinate
 * @param y Y-coordinate
 * @param z Z-coordinate
 */
void Particle3D::setTranslation(float x, float y, float z) {
    position.x = x;
    position.y = y;
    position.z = z;
}

/**
 * @brief Sets the location which the particle appears
 * 
 * @param pos Position vector
 */
void Particle3D::setTranslation(const Vec3 &pos) {
    position.x = pos.x;
    position.y = pos.y;
    position.z = pos.z;
}

/**
 * @brief Gets the location of the particle
 * 
 * @return Position vector
 */
Vec3 Particle3D::getTranslation() const { return position; }

/**
 * @brief Sets the rotation of the particle
 * 
 * @param t Rotation in radian
 */
void Particle3D::setRotation(float t) {
    rotation = t;
    modelMatrix[0][0] = cos(t) * size.x;
    modelMatrix[0][1] = -sin(t) * size.y;
    modelMatrix[1][0] = sin(t) * size.x;
    modelMatrix[1][1] = cos(t) * size.y;
}

/**
 * @brief Gets the rotation of the particle
 * 
 * @return Rotation in radian
 */
float Particle3D::getRotation() const { return rotation; }

/**
 * @brief Sets the size of the particle
 * 
 * @param w Width
 * @param h Height
 */
void Particle3D::setSize(float w, float h) {
    size.x = w;
    size.y = h;
    modelMatrix[0][0] = cos(rotation) * w;
    modelMatrix[0][1] = -sin(rotation) * h;
    modelMatrix[1][0] = sin(rotation) * w;
    modelMatrix[1][1] = cos(rotation) * h;
}

/**
 * @brief Sets the size of the particle
 * 
 * @param s Size
 */
void Particle3D::setSize(const Vec2 &s) {
    size = s;
    modelMatrix[0][0] = cos(rotation) * s.x;
    modelMatrix[0][1] = -sin(rotation) * s.y;
    modelMatrix[1][0] = sin(rotation) * s.x;
    modelMatrix[1][1] = cos(rotation) * s.y;
}

/**
 * @brief Gets the size of the particle
 * 
 * @return Width and height as a rectangular dimension
 */
Vec2 Particle3D::getSize() const { return size; }

/**
 * @brief Gets the pointer to the texture
 * 
 * @return Pointer to the texture
 */
const internal::SpriteTexture *Particle3D::getTexture() const {
    return texture;
}

/**
 * @brief Gets the texture loader
 * 
 * @return Texture loader
 */
const internal::Pending& Particle3D::getTextureLoad() const {
    return texLoad;
}

}
