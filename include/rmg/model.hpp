/**
 * @file model.hpp
 * @brief 3D object loaded from file other than basic geometries
 *
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#pragma once
#ifndef __RMG_MODEL_H__
#define __RMG_MODEL_H__

#include <rmg/object3d.hpp>

#include <string>


namespace rmg {

/**
 * @brief 3D object loaded from file other than basic geometries
 */
class Model3D: public Object3D {
  public:
    /**
     * @brief Constructor loads 3D model from file.
     * 
     * @param ctx Container context
     * @param file 3D model file (.obj)
     */
    Model3D(Context* ctx, std::string file);
    
    /**
     * @brief Destructor
     */
    virtual ~Model3D();
    
    /**
     * @brief Copy constructor
     * 
     * @param obj Source object
     */
    Model3D(const Model3D& obj);
    
    /**
     * @brief Move constructor
     * 
     * @param obj Source object
     */
    Model3D(Model3D&& obj) noexcept;
    
    /**
     * @brief Copy assignment
     * 
     * @param obj Source object
     */
    Model3D& operator=(const Model3D& obj);
    
    /**
     * @brief Move assignment
     * 
     * @param obj Source object
     */
    Model3D& operator=(Model3D&& obj) noexcept;
};

}

#endif
