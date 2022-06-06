/**
 * @file linked_list.tpp
 * @brief Forward-linked list template
 * 
 * @copyright Copyright (c) 2022 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#include <utility>


namespace rmg {

/**
 * @brief Destructor
 */
template <typename T>
LinkedList<T>::~LinkedList<T>() {
    if(next != nullptr)
        delete next;
}

/**
 * @brief Destructor
 */
template <typename T>
LinkedList<T>::Node::~Node() {
    if(next != nullptr)
        delete next;
}

/**
 * @brief Copy constructor
 * 
 * @param list Source
 */
template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& list) {
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
template <typename T>
LinkedList<T>::LinkedList(LinkedList<T>&& list) noexcept {
    next = std::exchange(list.next, nullptr);
    data = std::exchange(list.data, nullptr);
    count = std::exchange(list.count, 0);
}

/**
 * @brief Copy assignment
 * 
 * @param list Source
 */
template <typename T>
LinkedList<T>& LinkedList<T>::operator = (const LinkedList<T>& list) {
    LinkedList<T> tmp = LinkedList<T>(list);
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
template <typename T>
LinkedList<T>& LinkedList<T>::operator = (LinkedList<T>&& list) {
    LinkedList<T> tmp = LinkedList<T>(list);
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
template <typename T>
void LinkedList<T>::push_front(T* elem) {
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
template <typename T>
T* LinkedList<T>::front() const { return data; }

/**
 * @brief Removes an element from the beginning of the list
 */
template <typename T>
void LinkedList<T>::pop_front() {
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
template <typename T>
void LinkedList<T>::remove(T* elem) {
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
template <typename T>
void LinkedList<T>::clear() {
    if(next != nullptr)
        delete next;
    next = nullptr;
    data = nullptr;
    count = 0;
}

/**
 * @brief Cleans up the list including the drawing elements
 * 
 * In the process of clearing the list contents, it also deletes the drawing
 * elements through the stored data pointers. Usually called at the end of an
 * application.
 */
template <typename T>
void LinkedList<T>::cleanup() {
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
template <typename T>
uint32_t LinkedList<T>::size() const { return count; }

}
