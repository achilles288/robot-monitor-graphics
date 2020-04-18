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

#include <rmg/math.hpp>
#include <rmg/object.hpp>


class rmg::internal::SpriteShader;


namespace rmg {

/**
 * @brief 2D graphics displayed on top of the 3D graphics context
 *
 * All 2D objects use common vertex buffer object for shader programs.
 * Simple model matrix. No depth value and drawing order is according to
 * the z-order value (determines which object appears on top).
 */
class Object2D: public Object {
  private:
    glm::mat3 modelMatrix;
    int8_t zOrder;
    float t;
    float width;
    float height;
    
    friend class Text2D;
    friend class internal::SpriteShader;
    
  public:
    /**
     * @brief Constructor with its container
     * 
     * @param ctx Container context
     */
    Object2D(Context* ctx);
    
    /**
     * @brief Destructor
     */
    virtual ~Object2D();
    
    /**
     * @brief Copy constructor
     * 
     * @param obj Source object
     */
    Object2D(const Object2D& obj);
    
    /**
     * @brief Move constructor
     * 
     * @param obj Source object
     */
    Object2D(Object2D&& obj) noexcept;
    
    /**
     * @brief Copy assignment
     * 
     * @param obj Source object
     */
    Object2D& operator=(const Object2D& obj);
    
    /**
     * @brief Move assignment
     * 
     * @param obj Source object
     */
    Object2D& operator=(Object2D&& obj) noexcept;
    
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
    void setPosition(float x, float y);
    
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
    void setPosition(Vec2 pos);
    
    /**
     * @brief Gets the location of the 2D object
     * 
     * @return Position vector
     */
    Vec2 getPosition();
    
    /**
     * @brief Sets the rotation of the 2D object
     * 
     * @param t Rotation in degrees
     */
    virtual void setRotation(float t);
    
    /**
     * @brief Gets the rotation of the 2D object
     * 
     * @return Rotation in degrees
     */
    float getRotation();
    
    /**
     * @brief Sets the size of the 2D object
     * 
     * @param w Width
     * @param h Height
     */
    virtual void setSize(float w, float h);
    
    /**
     * @brief Sets the size of the 2D object
     * 
     * @param size Size
     */
    void setSize(Vec2 size);
    
    /**
     * @brief Gets the size of the 2D object
     * 
     * @return Width and height as a rectangular dimension
     */
    Vec2 getSize();
    
    /**
     * @brief Determines which 2D object is on top
     * 
     * This function is necessary when 2 objects overlap.
     * 
     * @param z Z-order
     */
    void setZOrder(int z);
    
    /**
     * @brief Gets the z-order of the 2D object
     * 
     * @return Z-order
     */
    int8_t getZOrder();
};

}

#endif
