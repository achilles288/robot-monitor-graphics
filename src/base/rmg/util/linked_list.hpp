/**
 * @file linked_list.hpp
 * @brief Forward-linked list template
 * 
 * @copyright Copyright (c) 2022 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#pragma once
#ifndef __RMG_LINKED_LIST_H__
#define __RMG_LINKED_LIST_H__

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


namespace rmg {

/**
 * @brief Forward-linked list template
 */
template <typename T>
class RMG_API LinkedList {
    struct Node {
        Node* next = nullptr;
        T* data = nullptr;
        
        ~Node();
    };
    
  private:
    Node* next = nullptr;
    T* data = nullptr;
    uint32_t count = 0;
    
  public:
    /**
     * @brief Default constructor
     */
    LinkedList() = default;
    
    /**
     * @brief Destructor
     */
    ~LinkedList();
    
    /**
     * @brief Copy constructor
     * 
     * @param list Source
     */
    LinkedList(const LinkedList& list);
    
    /**
     * @brief Move constructor
     * 
     * @param list Source
     */
    LinkedList(LinkedList&& list) noexcept;
    
    /**
     * @brief Copy assignment
     * 
     * @param list Source
     */
    LinkedList& operator = (const LinkedList& list);
    
    /**
     * @brief Move assignment
     * 
     * @param list Source
     */
    LinkedList& operator = (LinkedList&& list);
    
    /**
     * @brief Appends an element to the list beginning
     * 
     * @param elem New element to the list beginning
     */
    void push_front(T* elem);
    
    /**
     * @brief Retrives an element from the beginning of the list
     * 
     * @return The retrived element
     */
    T* front() const;
    
    /**
     * @brief Removes an element from the beginning of the list
     */
    void pop_front();
    
    /**
     * @brief Removes an element from the list
     * 
     * @param elem The element to be removed
     */
    void remove(T* elem);
    
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
        T* data = nullptr;
        
      public:
        /**
         * @brief Constructs from node and element
         * 
         * @param n The list node
         * @param d The element
         */
        iterator(Node* n, T* d);
        
        /**
         * @brief Pointer dereferencing
         */
        T& operator * ();
        
        /**
         * @brief Pointer dereferencing
         */
        T* operator -> ();
        
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

#include "linked_list.tpp"

#endif
