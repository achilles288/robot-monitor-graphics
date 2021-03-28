/**
 * @file line3d.cpp
 * @brief Draws a line in 3D space
 * 
 * Graphics without a polygon. Renders a straight through a special line
 * shader program. Just manipulate the locations of two end points, thickness
 * and color.
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#define RMG_EXPORT


#include "line3d.hpp"


namespace rmg {

/**
 * @brief Constructor with thickness, color and 2 initial end-points
 * 
 * @param ctx Container context
 * @param t Line thickness
 * @param col RGBA color
 * @param p1 Position vector of point-1
 * @param p2 Position vector of point-2
 */
Line3D::Line3D(Context* ctx, float t, const Color &col,
               const Vec3 &p1, const Vec3 &p2)
       :Object(ctx)
{
    thickness = t;
    setColor(col);
    point1 = p1;
    point2 = p2;
}

/**
 * @brief Sets the location of point-1
 * 
 * @param x X-coordinate
 * @param y Y-coordinate
 * @param z Z-coordinate
 */
void Line3D::setPoint1(float x, float y, float z) {
    point1.x = x;
    point1.y = y;
    point1.z = z;
}

/**
 * @brief Sets the location of point-2
 * 
 * @param x X-coordinate
 * @param y Y-coordinate
 * @param z Z-coordinate
 */
void Line3D::setPoint2(float x, float y, float z) {
    point2.x = x;
    point2.y = y;
    point2.z = z;
}

/**
 * @brief Sets the location of point-1
 * 
 * @param p Position vector
 */
void Line3D::setPoint1(const Vec3 &p) { point1 = p; }

/**
 * @brief Sets the location of point-2
 * 
 * @param p Position vector
 */
void Line3D::setPoint2(const Vec3 &p) { point2 = p; }

/**
 * @brief Gets the location of point-1
 * 
 * @return Position vector
 */
Vec3 Line3D::getPoint1() const { return point1; }

/**
 * @brief Gets the location of point-1
 * 
 * @return Position vector
 */
Vec3 Line3D::getPoint2() const { return point2; }

/**
 * @brief Sets the line thickness
 * 
 * @param t Line thickness
 */
void Line3D::setThickness(float t) { thickness = t; }

/**
 * @brief Gets the line thickness
 * 
 * @return Line thickness
 */
float Line3D::getThickness() const { return thickness; }

}
