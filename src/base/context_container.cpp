/**
 * @file context_container.cpp
 * @brief 2D/3D graphics context resource manager
 * 
 * Manages GPU resources of 2D/3D objects, maintaining them in lists of
 * different object catagories.
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#define RMG_EXPORT


#include "rmg/context.hpp"

#include <algorithm>

#include "rmg/assert.hpp"
#include "rmg/font.hpp"
#include "rmg/line3d.hpp"
#include "rmg/material.hpp"
#include "rmg/object.hpp"
#include "rmg/object2d.hpp"
#include "rmg/object3d.hpp"
#include "rmg/particle.hpp"


namespace rmg {

/**
 * @brief Cleans up GPU resources
 */
void Context::destroy() {
    if(destroyed)
        return;
    setCurrent();
    cleanup();
    generalShader = internal::GeneralShader();
    shadowMapShader = internal::ShadowMapShader();
    object2dShader = internal::Object2DShader();
    particleShader = internal::ParticleShader();
    line3dShader = internal::Line3DShader();
    
    contextList.erase(std::find(
        contextList.begin(),
        contextList.end(),
        this
    ));
    destroyed = true;
}

/**
 * @brief To see if the context is still active and usable
 * 
 * @return True if the context is destroyed
 */
bool Context::isDestroyed() const { return destroyed; }

/**
 * @brief Appends a 2D/3D object to the display list
 * 
 * @param obj 2D/3D object
 */
void Context::addObject(Object* obj) {
    RMG_EXPECT(obj->getContext() == this);
    #ifndef NDEBUG
    if(obj->getContext() != this)
        return;
    #endif
    
    ObjectType type = obj->getObjectType();
    
    if(type == ObjectType::Object2D) {
        Object2D* obj2d = (Object2D*) obj;
        if(obj2d->getObject2DType() == Object2DType::Sprite) {
            Sprite2D* sprite = (Sprite2D*) obj;
            loader.push(sprite->getTextureLoad());
        }
        object2d_list.push_front(obj);
    }
    else if(type == ObjectType::Object3D) {
        Object3D* obj3d = (Object3D*) obj;
        loader.push(obj3d->getVBOLoad());
        object3d_list.push_front(obj);
    }
    else if(type == ObjectType::Particle3D) {
        particle3d_list.push_front(obj);
    }
    else if(type == ObjectType::Line3D) {
        line3d_list.push_front(obj);
    }
}

/**
 * @brief Appends a matture to the list loading GPU resources
 * 
 * @param mat Material
 */
void Context::addMaterial(Material* mat) {
    RMG_ASSERT(mat->getContext() == this);
    auto elem = std::pair<uint32_t,Material*>(mat->getID(),mat);
    materials.insert(elem);
    loader.push(mat->textureLoad);
}

/**
 * @brief Appends a font to the font list for matt drawing
 * 
 * @param font Font
 */
void Context::addFont(Font* font) {
    RMG_ASSERT(font->getContext() == this);
    auto elem = std::pair<uint32_t,Font*>(font->getID(),font);
    fonts.insert(elem);
    loader.push(font->textureLoad);
}

/**
 * @brief Removes the object from the list cleaning the GPU resources
 * 
 * The remove function also deletes the dynamically allocated memory for
 * the instance.
 * 
 * @param obj 2D/3D object
 */
void Context::removeObject(Object* obj) {
    ObjectType type = obj->getObjectType();
    if(type == ObjectType::Object2D)
        object2d_list.remove(obj);
    else if(type == ObjectType::Object3D)
        object3d_list.remove(obj);
    else if(type == ObjectType::Particle3D)
        particle3d_list.remove(obj);
    else if(type == ObjectType::Line3D)
        line3d_list.remove(obj);
}

/**
 * @brief Removes the matture from the list cleaning the GPU resources
 * 
 * The remove function also deletes the dynamically allocated memory for
 * the instance.
 * 
 * @param mat Material
 */
void Context::removeMaterial(Material* mat) {
    auto it = materials.find(mat->getID());
    if(it != materials.end())
        materials.erase(it);
}

/**
 * @brief Removes the font from the list cleaning the GPU resources
 * 
 * The remove function also deletes the dynamically allocated memory for
 * the instance.
 * 
 * @param font Font
 */
void Context::removeFont(Font* font) { 
    auto it = fonts.find(font->getID());
    if(it != fonts.end())
        fonts.erase(it);
}

/**
 * @brief Gets the number of objects in the object list
 * 
 * @return Total number of objects from lists of every type
 */
uint64_t Context::getObjectCount() const {
    return object2d_list.size() + object3d_list.size() +
           particle3d_list.size() + line3d_list.size();
}

/**
 * @brief Gets the number of materials in the list
 * 
 * @return Number of materials
 */
uint64_t Context::getMaterialCount() const { return materials.size(); }

/**
 * @brief Gets the number of fonts in the list
 * 
 * @return Number of fonts
 */
uint64_t Context::getFontCount() const { return fonts.size(); }

/**
 * @brief Removes all context resources
 * 
 * Clears the lists of objects, materials, fonts and their GPU resources.
 */
void Context::cleanup() {
    object2d_list.cleanup();
    object3d_list.cleanup();
    particle3d_list.cleanup();
    line3d_list.cleanup();
    for(auto it=materials.begin(); it!=materials.end(); it++)
        delete it->second;
    for(auto it=fonts.begin(); it!=fonts.end(); it++)
        delete it->second;
    materials.clear();
    fonts.clear();
}

/**
 * @brief Destroys every RMG context cleaning all GPU resources allocated
 */
void Context::destroyAll() {
    while(contextList.size() != 0)
        contextList[0]->destroy();
}

}
