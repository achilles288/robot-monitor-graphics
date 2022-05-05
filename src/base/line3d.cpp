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


#include "rmg/line3d.hpp"

#include "rmg/math/euler.hpp"
#include "rmg/math/mat3.hpp"


namespace rmg {

/**
 * @brief Constructor with thickness and color
 * 
 * @param ctx Container context
 * @param t Line thickness
 * @param col RGBA color
 */
Line3D::Line3D(Context* ctx, float t, const Color &col)
       :Object(ctx)
{
    thickness = t;
    setColor(col);
    modelMatrix[3][3] = 1;
    type = ObjectType::Line3D;
}

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
    modelMatrix[3][3] = 1;
    calculateMatrix();
    type = ObjectType::Line3D;
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
    calculateMatrix();
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
    calculateMatrix();
}

/**
 * @brief Sets the location of point-1
 * 
 * @param p Position vector
 */
void Line3D::setPoint1(const Vec3 &p) {
    point1 = p;
    calculateMatrix();
}

/**
 * @brief Sets the location of point-2
 * 
 * @param p Position vector
 */
void Line3D::setPoint2(const Vec3 &p) {
    point2 = p;
    calculateMatrix();
}

/**
 * @brief Sets the location of the end points
 * 
 * @param p1 Position vector of point-1
 * @param p2 Position vector of point-2
 */
void Line3D::setPoints(const Vec3 &p1, const Vec3 &p2) {
    point1 = p1;
    point2 = p2;
    calculateMatrix();
}

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
void Line3D::setThickness(float t) {
    thickness = t;
    calculateMatrix();
}

/**
 * @brief Gets the line thickness
 * 
 * @return Line thickness
 */
float Line3D::getThickness() const { return thickness; }
    
/**
 * @brief The matrix composed of all the transformations done by the object
 * 
 * @return Model matrix
 */
const Mat4& Line3D::getModelMatrix() const { return modelMatrix; }


void Line3D::calculateMatrix() {
    Vec3 v = point2 - point1;
    float l = v.magnitude();
    float a = Vec2(v).magnitude();
    float yaw = atan2(v.y, v.x);
    float pitch = -atan(v.z/a);
    Mat3 R = Euler(0, pitch, yaw).toRotationMatrix();
    modelMatrix[0][0] = R[0][0] * l;
    modelMatrix[0][1] = R[0][1] * thickness;
    modelMatrix[0][2] = R[0][2] * thickness;
    modelMatrix[1][0] = R[1][0] * l;
    modelMatrix[1][1] = R[1][1] * thickness;
    modelMatrix[1][2] = R[1][2] * thickness;
    modelMatrix[2][0] = R[2][0] * l;
    modelMatrix[2][1] = R[2][1] * thickness;
    modelMatrix[2][2] = R[2][2] * thickness;
    modelMatrix[0][3] = point1.x;
    modelMatrix[1][3] = point1.y;
    modelMatrix[2][3] = point1.z;
}

}
