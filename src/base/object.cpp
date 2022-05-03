/**
 * @file object.cpp
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


#define RMG_EXPORT


#include "rmg/object.hpp"

#include <utility>


#define DEFAULT_COLOR Color(1, 1, 1, 1)


namespace rmg {

uint64_t Object::lastID = 0;

// Class: Object

/**
 * @brief Default constructor
 */
Object::Object() {
    id = 0;
    color = DEFAULT_COLOR;
}

/**
 * @brief Constructor with its container
 * 
 * @param ctx Container context
 */
Object::Object(Context* ctx) {
    
    id = ++lastID;
    context = ctx;
    color = DEFAULT_COLOR;
}

/**
 * @brief Copy constructor
 * 
 * @param obj Source object
 */
Object::Object(const Object& obj) {
    id = ++lastID;
    context = obj.context;
    color = obj.color;
    hidden = obj.hidden;
    type = obj.type;
}

/**
 * @brief Move constructor
 * 
 * @param obj Source object
 */
Object::Object(Object&& obj) noexcept {
    id = std::exchange(obj.id, 0);
    context = std::exchange(obj.context, nullptr);
    color = std::exchange(obj.color, DEFAULT_COLOR);
    hidden = std::exchange(obj.hidden, false);
    type = std::exchange(obj.type, ObjectType::Default);
}
    
/**
 * @brief Copy assignment
 * 
 * @param obj Source object
 */
Object& Object::operator=(const Object& obj) {
    Object tmp = Object(obj);
    swap(tmp);
    return *this;
}

/**
 * @brief Move assignment
 * 
 * @param obj Source object
 */
Object& Object::operator=(Object&& obj) noexcept {
    Object tmp = std::move(obj);
    swap(tmp);
    return *this;
}

/**
 * @brief Swaps the values of member variables between two objects
 * 
 * @param x The other object
 */
void Object::swap(Object& x) noexcept {
    std::swap(id, x.id);
    std::swap(context, x.context);
    std::swap(color, x.color);
    std::swap(hidden, x.hidden);
    std::swap(type, x.type);
}

/**
 * @brief Gets object ID
 * 
 * @return Object ID
 */
uint64_t Object::getID() const { return id; }

/**
 * @brief Gets container context
 * 
 * @return Container context
 */
Context* Object::getContext() const { return context; }

/**
 * @brief Gets object type
 * 
 * @return Object type
 */
ObjectType Object::getObjectType() const { return type; }

/**
 * @brief Sets object color
 * 
 * @param r Red
 * @param g Green
 * @param b Blue
 */
void Object::setColor(float r, float g, float b) {
    color.red = r;
    color.green = g;
    color.blue = b;
    color.alpha = 1.0f;
}

/**
 * @brief Sets object color
 * 
 * @param r Red
 * @param g Green
 * @param b Blue
 * @param a Alpha
 */
void Object::setColor(float r, float g, float b, float a) {
    color.red = r;
    color.green = g;
    color.blue = b;
    color.alpha = a;
}

/**
 * @brief Sets object color
 * 
 * @param col RGBA color
 */
void Object::setColor(const Color &col) { color = col; }

/**
 * @brief Gets object color
 * 
 * @return RGBA color
 */
Color Object::getColor() const { return color; }

/**
 * @brief Sets object visibility
 * 
 * This determines whether the shaders process or skips the object
 * model. Skipping means the object is not shown in the context.
 * 
 * @param hide Hide flag
 */
void Object::setHidden(bool hide) { hidden = hide; }

/**
 * @brief Whether the object is hidden or not
 * 
 * @return True if the object is hidden
 */
bool Object::isHidden() const { return hidden; }




// Class: ObjectList

/**
 * @brief Destructor
 */
ObjectList::~ObjectList() {
    if(next != nullptr)
        delete next;
}

/**
 * @brief Destructor
 */
ObjectList::Node::~Node() {
    if(next != nullptr)
        delete next;
}

/**
 * @brief Copy constructor
 * 
 * @param list Source
 */
ObjectList::ObjectList(const ObjectList& list) {
    data = list.data;
    Node* node1 = nullptr;
    Node* node2 = list.next;
    if(node2 != nullptr) {
        next = new Node();
        next->data = node2->data;
        node1 = next;
        node2 = node2->next;
    }
    while(node2 != nullptr) {
        node1->next = new Node();
        node1 = node1->next;
        node1->data = node2->data;
        node2 = node2->next;
    }
    count = list.count;
}

/**
 * @brief Move constructor
 * 
 * @param list Source
 */
ObjectList::ObjectList(ObjectList&& list) noexcept {
    next = std::exchange(list.next, nullptr);
    data = std::exchange(list.data, nullptr);
    count = std::exchange(list.count, 0);
}

/**
 * @brief Copy assignment
 * 
 * @param list Source
 */
ObjectList& ObjectList::ObjectList::operator = (const ObjectList& list) {
    ObjectList tmp = ObjectList(list);
    std::swap(next, tmp.next);
    std::swap(data, tmp.data);
    std::swap(count, tmp.count);
    return *this;
}

/**
 * @brief Move assignment
 * 
 * @param list Source
 */
ObjectList& ObjectList::operator = (ObjectList&& list) {
    ObjectList tmp = ObjectList(list);
    std::swap(next, tmp.next);
    std::swap(data, tmp.data);
    std::swap(count, tmp.count);
    return *this;
}

/**
 * @brief Appends an element to the list beginning
 * 
 * @param elem New element to the list beginning
 */
void ObjectList::push_front(Object* elem) {
    Node* tmp = next;
    next = new Node();
    next->next = tmp;
    next->data = data;
    data = elem;
    count++;
}

/**
 * @brief Retrives an element from the beginning of the list
 * 
 * @return The retrived element
 */
Object* ObjectList::front() const { return data; }

/**
 * @brief Removes an element from the beginning of the list
 */
void ObjectList::pop_front() {
    if(count == 0)
        return;
    
    if(next != nullptr) {
        Node* tmp = next->next;
        next->next = nullptr;
        data = next->data;
        delete next;
        next = tmp;
    }
    else {
        data = nullptr;
    }
    count--;
}

/**
 * @brief Removes an element from the list
 * 
 * @param elem The element to be removed
 */
void ObjectList::remove(Object* elem) {
    if(data == elem) {
        pop_front();
        return;
    }
    Node* node = next;
    while(node != nullptr) {
        if(node->data == elem) {
            if(node->next != nullptr) {
                Node* node2 = node->next;
                Node* tmp = node2->next;
                node2->next = nullptr;
                node->data = node2->data;
                delete node->next;
                node->next = tmp;
                count--;
            }
            else {
                node->data = nullptr;
            }
        }
        node = node->next;
    }
}

/**
 * @brief Clears the contents
 */
void ObjectList::clear() {
    if(next != nullptr)
        delete next;
    next = nullptr;
    data = nullptr;
    count = 0;
}

/**
 * @brief Cleans up the list including the drawing objects
 * 
 * In the process of clearing the list contents, it also deletes the drawing
 * objects through the stored data pointers. Usually called at the end of an
 * application.
 */
void ObjectList::cleanup() {
    if(data != nullptr)
        delete data;
    Node* node = next;
    while(node != nullptr) {
        if(node->data != nullptr)
            delete node->data;
        node = node->next;
    }
    clear();
}

/**
 * @brief Gets the number of elements in the stack
 * 
 * @return The number of elements
 */
uint32_t ObjectList::size() const { return count; }

/**
 * @brief Constructs from pointer
 * 
 * @param ptr Pointer value
 */
ObjectList::iterator::iterator(Node* n, Object* d) {
    next = n;
    data = d;
}

/**
 * @brief Pointer dereferencing
 * 
 * @return The reference
 */
Object& ObjectList::iterator::operator * () { return *data; }

/**
 * @brief Pointer dereferencing
 * 
 * @return The pointer
 */
Object* ObjectList::iterator::operator -> () { return data; }

/**
 * @brief The prefix increment operator
 * 
 * @return Iterator to the next element
 */
ObjectList::iterator& ObjectList::iterator::operator ++ () {
    if(next != nullptr) {
        data = next->data;
        next = next->next;
    }
    else {
        data = nullptr;
    }
    return *this;
}

/**
 * @brief The postfix increment operator
 * 
 * @return Iterator to the next element
 */
ObjectList::iterator ObjectList::iterator::operator ++ (int) {
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

/**
 * @brief Compares the values
 * 
 * @param it Iterator 2
 * 
 * @return True if the pointers of the two are equal
 */
bool ObjectList::iterator::operator == (const iterator& it) {
    return next == it.next && data == it.data;
}

/**
 * @brief Compares the values
 * 
 * @param it Iterator 2
 * 
 * @return True if the pointers of the two are not equal
 */
bool ObjectList::iterator::operator != (const iterator& it) {
    return next != it.next || data != it.data;
}

/**
 * @brief Gets the beginning iterator
 * 
 * @return The iterator pointing to the first element of the list
 */
ObjectList::iterator ObjectList::begin() const {
    return iterator(next, data);
}

/**
 * @brief Gets the ending iterator
 * 
 * @return The iterator with the value that indicates the end of the list
 */
ObjectList::iterator ObjectList::end() const {
    return iterator(nullptr, nullptr);
}

}
