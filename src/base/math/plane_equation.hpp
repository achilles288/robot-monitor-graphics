/**
 * @file plane_equation.hpp
 * @brief Equation representing a plane in 3D space
 * 
 * Calculates point of intersection of a line with a plane or
 * calculates line of intersection of 2 planes.
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#pragma once
#ifndef __RMG_PLANE_EQ_H__
#define __RMG_PLANE_EQ_H__

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


#include "line_equation.hpp"


namespace rmg {

/**
 * @brief Equation representing a plane in 3D space
 * 
 * Calculates point of intersection of a line with a plane or
 * calculates line of intersection of 2 planes.
 */
struct RMG_API PlaneEq {
    Vec3 P; ///< Point in space
    Vec3 n; ///< Normal vector on the plane
    
    /**
     * @brief Default constructor
     */
    PlaneEq();
    
    /**
     * @brief Constructor
     * 
     * @param P Point in space
     * @param n Normal vector on the plane
     */
    PlaneEq(const Vec3 &P, const Vec3 &n);
    
    /**
     * @brief Calculates point of intersection of a line with a plane
     * 
     * @param plane Plane equation
     * @param line Straight line equation
     * 
     * @return Point of intersection. If they don't intersects, returns a
     *         vector of NANs.
     */
    static Vec3 intersects(const PlaneEq &plane, const LineEq &line);
    
    /**
     * @brief Calculates line of intersection of 2 planes
     * 
     * @param plane1 Plane-1
     * @param plane2 Plane-2
     * 
     * @return Line of intersection. If they don't intersects, returns an
     *         invalid line equation whose values are NANs.
     */
    static Vec3 intersects(const PlaneEq &plane1, const PlaneEq &plane2);
};

}

#endif
