/**
 * @file object.hpp
 * @brief A foundation of all RMG graphical object data structures
 * 
 * Doesn't have much features and not directly used by the context.
 * Stores a unique key and parent context. Common features like textures,
 * color and visibility control.
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#pragma once
#ifndef __RMG_OBJECT_H__
#define __RMG_OBJECT_H__

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


#include <cstdint>

#include "color.hpp"


namespace rmg {

class Context;


/**
 * @brief Type of object (Object3D, Sprite2D, .etc)
 * 
 * Determines which object list to append by the Context and which
 * method of operations by Shader(s) (internal operations).
 */
enum class ObjectType {
    Default,
    Object2D,
    Object3D,
    Particle3D,
    Line3D
};


/**
 * @brief A foundation of all RMG graphical object data structures
 * 
 * Doesn't have much features and not directly used by the context.
 * Stores a unique key and parent context. Common features like textures,
 * color and visibility control.
 */
class RMG_API Object {
  private:
    uint64_t id;
    Context* context = nullptr;
    Color color;
    bool hidden = false;
    
    static uint64_t lastID;
    
  protected:
    /**
     * @brief Type of object (Object3D, Sprite2D, .etc)
     * 
     * Determines which object list to append by the Context and which
     * method of operations by Shader(s) (internal operations).
     */
    ObjectType type = ObjectType::Default;
    
    /**
     * @brief Swaps the values of member variables between two objects
     * 
     * @param x The other object
     */
    void swap(Object& x) noexcept;
    
  public:
    /**
     * @brief Default constructor
     */
    Object();
    
    /**
     * @brief Constructor with its container
     * 
     * @param ctx Container context
     */
    Object(Context* ctx);
    
    /**
     * @brief Destructor
     */
    virtual ~Object() = default;
    
    /**
     * @brief Copy constructor
     * 
     * @param obj Source object
     */
    Object(const Object& obj);
    
    /**
     * @brief Move constructor
     * 
     * @param obj Source object
     */
    Object(Object&& obj) noexcept;
    
    /**
     * @brief Copy assignment
     * 
     * @param obj Source object
     */
    Object& operator=(const Object& obj);
    
    /**
     * @brief Move assignment
     * 
     * @param obj Source object
     */
    Object& operator=(Object&& obj) noexcept;
    
    /**
     * @brief Gets object ID
     * 
     * @return Object ID
     */
    uint64_t getID() const;
    
    /**
     * @brief Gets container context
     * 
     * @return Container context
     */
    Context* getContext() const;
    
    /**
     * @brief Gets object type
     * 
     * @return Object type
     */
    ObjectType getObjectType() const;
    
    /**
     * @brief Sets object color
     * 
     * @param r Red
     * @param g Green
     * @param b Blue
     */
    void setColor(float r, float g, float b);
    
    /**
     * @brief Sets object color
     * 
     * @param r Red
     * @param g Green
     * @param b Blue
     * @param a Alpha
     */
    void setColor(float r, float g, float b, float a);
    
    /**
     * @brief Sets object color
     * 
     * @param col RGBA color
     */
    void setColor(const Color &col);
    
    /**
     * @brief Gets object color
     * 
     * @return RGBA color
     */
    Color getColor() const;
    
    /**
     * @brief Sets object visibility
     * 
     * This determines whether the shaders process or skips the object
     * model. Skipping means the object is not shown in the context.
     * 
     * @param hide Hide flag
     */
    void setHidden(bool hide);
    
    /**
     * @brief Whether the object is hidden or not
     * 
     * @return True if the object is hidden
     */
    bool isHidden() const;
};


/**
 * @brief A list to store a bunch of drawing objects
 */
class RMG_API ObjectList {
    /**
     * @brief Node of the forward link list
     */
    struct Node {
        Node* next = nullptr; ///< Next node
        Object* data = nullptr; ///< The object to be stored
        
        /**
         * @brief Destructor
         */
        ~Node();
    };
    
  private:
    Node* next = nullptr;
    Object* data = nullptr;
    uint32_t count = 0;
    
  public:
    /**
     * @brief Default constructor
     */
    ObjectList() = default;
    
    /**
     * @brief Destructor
     */
    ~ObjectList();
    
    /**
     * @brief Copy constructor
     * 
     * @param list Source
     */
    ObjectList(const ObjectList& list);
    
    /**
     * @brief Move constructor
     * 
     * @param list Source
     */
    ObjectList(ObjectList&& list) noexcept;
    
    /**
     * @brief Copy assignment
     * 
     * @param list Source
     */
    ObjectList& operator = (const ObjectList& list);
    
    /**
     * @brief Move assignment
     * 
     * @param list Source
     */
    ObjectList& operator = (ObjectList&& list);
    
    /**
     * @brief Appends an element to the list beginning
     * 
     * @param elem New element to the list beginning
     */
    void push_front(Object* elem);
    
    /**
     * @brief Retrives an element from the beginning of the list
     * 
     * @return The retrived element
     */
    Object* front() const;
    
    /**
     * @brief Removes an element from the beginning of the list
     */
    void pop_front();
    
    /**
     * @brief Removes an element from the list
     * 
     * @param elem The element to be removed
     */
    void remove(Object* elem);
    
    /**
     * @brief Clears the contents
     */
    void clear();
    
    /**
     * @brief Cleans up the list including the drawing objects
     * 
     * In the process of clearing the list contents, it also deletes the
     * drawing objects through the stored data pointers. Usually called at the
     * end of an application.
     */
    void cleanup();
    
    /**
     * @brief Gets the number of elements in the stack
     * 
     * @return The number of elements
     */
    uint32_t size() const;
    
    /**
     * @brief Iterator class for the list of serial ports
     */
    class RMG_API iterator {
      private:
        Node* next = nullptr;
        Object* data = nullptr;
        
      public:
        /**
         * @brief Constructs from node and object
         * 
         * @param n The list node
         * @param d The object data
         */
        iterator(Node* n, Object* d);
        
        /**
         * @brief Pointer dereferencing
         */
        Object& operator * ();
        
        /**
         * @brief Pointer dereferencing
         */
        Object* operator -> ();
        
        /**
         * @brief The prefix increment operator
         */
        iterator& operator ++ ();
        
        /**
         * @brief The postfix increment operator
         */
        iterator operator ++ (int);
        
        /**
         * @brief Compares the values
         */
        bool operator == (const iterator& it);
        
        /**
         * @brief Compares the values
         */
        bool operator != (const iterator& it);
    };
    
    /**
     * @brief Gets the beginning iterator
     * 
     * @return The iterator pointing to the first element of the list
     */
    iterator begin() const;
    
    /**
     * @brief Gets the ending iterator
     * 
     * @return The iterator with the value that indicates the end of the list
     */
    iterator end() const;
};

}

#endif
