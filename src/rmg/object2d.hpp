/**
 * @file object2d.hpp
 * @brief 2D graphics displayed on top of the 3D graphics context
 *
 * All 2D objects use common vertex buffer object for shader programs.
 * Simple model matrix. No depth value and drawing order is according to
 * the z-order value (determines which object appears on top).
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#pragma once
#ifndef __RMG_OBJECT_2D_H__
#define __RMG_OBJECT_2D_H__

#include "object.hpp"
#include "math/angle_unit.hpp"
#include "math/vec.hpp"
#include "math/mat3.hpp"


namespace rmg {

class Text2D;

namespace internal {
    class SpriteShader;
}


/**
 * @brief Type of 2D object (Sprite or Text)
 * 
 * Determines how the object should be processed by the sprite shader.
 */
enum class Object2DType {
    Default,
    Sprite,
    Text
};

/**
 * @brief 2D graphics displayed on top of the 3D graphics context
 *
 * All 2D objects use common vertex buffer object for shader programs.
 * Simple model matrix. No depth value and drawing order is according to
 * the z-order value (determines which object appears on top).
 */
class Object2D: public Object {
  private:
    Mat3 modelMatrix;
    int8_t zOrder;
    float rotation;
    Vec2 size;
    
    friend class Text2D;
    friend class internal::SpriteShader;
    
  protected:
    Object2DType type2D; ///< Sprite or Text
    
  public:
    /**
     * @brief Default constructor
     */
    Object2D();
    
    /**
     * @brief Constructor with its container
     * 
     * @param ctx Container context
     */
    Object2D(Context* ctx);
    
    /**
     * @brief Gets 2D object type
     * 
     * @return Object type
     */
    Object2DType getObject2DType() const;
    
    /**
     * @brief The matrix composed of all the transformations done by the object
     * 
     * @return Model matrix
     */
    const Mat3& getModelMatrix() const;
    
    /**
     * @brief Sets the location which the object appears
     * 
     * Assigns values to the model matrix's translation part.
     * Anchor of a 2D object is mostly at the center other than the top
     * left corner as in other 2D graphics API.
     * For Text2D, the anchor is according to text alignment.
     * 
     * @param x X-coordinate
     * @param y Y-coordinate
     */
    void setTranslation(float x, float y);
    
    /**
     * @brief Sets the location which the object appears
     * 
     * Assigns values to the model matrix's translation part.
     * Anchor of a 2D object is mostly at the center other than the top
     * left corner as in other 2D graphics API.
     * For Text2D, the anchor is according to text alignment.
     * 
     * @param pos Position vector
     */
    void setTranslation(const Vec2 &pos);
    
    /**
     * @brief Gets the location of the 2D object
     * 
     * @return Position vector
     */
    Vec2 getTranslation() const;
    
    /**
     * @brief Sets the rotation of the 2D object
     * 
     * @param t Rotation in radian
     */
    void setRotation(float t);
    
    /**
     * @brief Sets the rotation of the 2D object
     * 
     * @param t Rotation
     * @param unit If the rotation value is degree or radian
     */
    inline void setRotation(float t, AngleUnit unit) {
        setRotation((unit == AngleUnit::Radian) ? t : radian(t));
    }
    
    /**
     * @brief Gets the rotation of the 2D object
     * 
     * @return Rotation in degrees
     */
    float getRotation() const;
    
    /**
     * @brief Sets the size of the 2D object
     * 
     * @param w Width
     * @param h Height
     */
    void setSize(float w, float h);
    
    /**
     * @brief Sets the size of the 2D object
     * 
     * @param s Size
     */
    void setSize(const Vec2 &s);
    
    /**
     * @brief Gets the size of the 2D object
     * 
     * @return Width and height as a rectangular dimension
     */
    Vec2 getSize() const;
    
    /**
     * @brief Determines which 2D object is on top
     * 
     * This function is necessary when 2 objects overlap.
     * 
     * @param z Z-order
     */
    void setZOrder(int8_t z);
    
    /**
     * @brief Gets the z-order of the 2D object
     * 
     * @return Z-order
     */
    int8_t getZOrder() const;
};

}

#endif
