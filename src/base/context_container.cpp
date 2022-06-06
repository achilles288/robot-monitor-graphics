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
#include "rmg/line3d.hpp"
#include "rmg/object2d.hpp"
#include "rmg/object3d.hpp"
#include "rmg/particle.hpp"


namespace rmg {

// Class: Context

uint32_t Context::lastContextID = 0;
ContextList Context::contextList;

/**
 * @brief Default constructor
 */
Context::Context() {
    id = ++lastContextID;
    contextList.push_front(this);
    width = 0;
    height = 0;
    bgColor = Color(0, 0, 0, 1);
    dlWorldSpace = Vec3(1.0f, 0.0f, 0.0f);
    dlCameraSpace = Vec3(0.0f, 0.0f, -1.0f);
    dlColor = Color(1, 1, 1, 1);
    destroyed = false;
    initDone = false;
    fps = 0;
    errorCode = 0;
}

/**
 * @brief Destructor
 */
Context::~Context() {
    destroy();
}

/**
 * @brief Gets the ID of the context
 * 
 * @return Context ID
 */
uint32_t Context::getID() const { return id; }

/**
 * @brief Searches context model by ID
 * 
 * @return OpenGL context
 */
Context* Context::getContextByID(uint32_t id) {
    for(auto it=contextList.begin(); it!=contextList.end(); it++) {
        if(it->id == id)
            return &(*it);
    }
    return nullptr;
}

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
    
    contextList.remove(this);
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
    RMG_ASSERT(obj->getContext() == this);
    
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
        Particle3D* particle = (Particle3D*) obj;
        loader.push(particle->getTextureLoad());
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
    materials.push_front(mat);
    loader.push(mat->getTextureLoad());
}

/**
 * @brief Appends a font to the font list for matt drawing
 * 
 * @param ft Font
 */
void Context::addFont(Font* ft) {
    RMG_ASSERT(ft->getContext() == this);
    fonts.push_front(ft);
    loader.push(ft->getTextureLoad());
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
void Context::removeMaterial(Material* mat) { materials.remove(mat); }

/**
 * @brief Removes the font from the list cleaning the GPU resources
 * 
 * The remove function also deletes the dynamically allocated memory for
 * the instance.
 * 
 * @param ft Font
 */
void Context::removeFont(Font* ft) { fonts.remove(ft); }

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
    materials.cleanup();
    fonts.cleanup();
}

/**
 * @brief Destroys every RMG context cleaning all GPU resources allocated
 */
void Context::destroyAll() {
    for(auto it=contextList.begin(); it!=contextList.end(); it++) {
        it->destroy();
    }
}




// Class: ContextContainer

ContextList::iterator::iterator(LinkedList<Context>::Node* n, Context* d) {
    next = n;
    data = d;
}

Context& ContextList::iterator::operator * () { return *data; }

Context* ContextList::iterator::operator -> () { return data; }

ContextList::iterator& ContextList::iterator::operator ++ () {
    if(next != nullptr) {
        data = next->data;
        next = next->next;
    }
    else {
        data = nullptr;
    }
    return *this;
}

ContextList::iterator ContextList::iterator::operator ++ (int) {
    iterator tmp = iterator(next, data);
    if(next != nullptr) {
        data = next->data;
        next = next->next;
    }
    else {
        data = nullptr;
    }
    return tmp;
}

bool ContextList::iterator::operator == (const iterator& it) {
    return next == it.next && data == it.data;
}

bool ContextList::iterator::operator != (const iterator& it) {
    return next != it.next || data != it.data;
}

/**
 * @brief Gets the start of the list
 * 
 * @return An iterator as in C++ STL containers
 */
ContextList::iterator ContextList::begin() const {
    return iterator(next, data);
}

/**
 * @brief Gets the end of the list
 * 
 * @return An iterator as in C++ STL containers
 */
ContextList::iterator ContextList::end() const {
    return iterator(nullptr, nullptr);
}

}
