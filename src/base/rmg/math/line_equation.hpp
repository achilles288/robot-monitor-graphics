/**
 * @file line_equation.hpp
 * @brief Equation representing a straight line in 3D space
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#pragma once
#ifndef __RMG_LINE_EQ_H__
#define __RMG_LINE_EQ_H__


#include "vec3.hpp"


namespace rmg {

/**
 * @brief Equation representing a straight line in 3D space
 */
struct LineEq {
    Vec3 P; ///< Initial point in space
    Vec3 v; ///< Change of coordinate per time step
    
    /**
     * @brief Default constructor
     */
    inline LineEq() {
        P = {NAN, NAN, NAN};
        v = {NAN, NAN, NAN};
    }
    
    /**
     * @brief Constructor
     * 
     * @param P Initial point in space
     * @param v Change of coordinate per time step
     */
    inline LineEq(const Vec3 &P, const Vec3 &v) {
        this->P = P;
        this->v = v;
    }
};

}

#endif
