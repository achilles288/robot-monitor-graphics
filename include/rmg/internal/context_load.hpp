/**
 * @file context_load.hpp
 * @brief Loads data in memory into GPU
 * 
 * After preprocessing of 3D data like model reading, texture reading,
 * the parsed data are temporarily stored in a queue. When the OpenGL context
 * starts up, these data are loaded into the GPU, the memory data are deleted
 * and the newly obtained GPU resource is later used for rendering models
 * frequently.
 * 
 * @copyright Copyright (c) 2020 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#pragma once
#ifndef __RMG_CONTEXT_LOAD_H__
#define __RMG_CONTEXT_LOAD_H__

#include <cstdint>
#include <queue>


namespace rmg {
namespace internal {


/**
 * @brief Maintains the data to be loaded into OpenGL context before startup
 */
class ContextLoad {
  public:
    /**
     * @brief Loads the data to the GPU
     */
    virtual void load();
};


class ContextLoader;


/**
 * @brief Loads data in memory into GPU
 * 
 * After preprocessing of 3D data like model reading, texture reading,
 * the parsed data are temporarily stored in a queue. When the OpenGL context
 * starts up, these data are loaded into the GPU, the memory data are deleted
 * and the newly obtained GPU resource is later used for rendering models
 * frequently.
 */
class ContextLoader {
  public:
    /**
     * @brief Waits to be loaded into the GPU
     * 
     * This class makes load instances sharable among multiple 2D/3D objects.
     * Similar to STL shared pointer but in addition to pointer and reference
     * count, an extra shared data. This indicates whether the instance is in
     * the loading list and prevents data duplication in the queue.
     */
    class Pending {
      private:
        struct Shared {
            uint64_t use_count; /**< Reference count */
            bool added; /**< States if the instance is added to the list */
        };
        
        ContextLoad* data;
        Shared* shared;
        
        friend class ContextLoader;
        
      public:
        /**
         * @brief Default constructor
         */
        Pending();
        
        /**
         * @brief Constructor assigning the load pointer
         * 
         * @param load Instance containing data to be loaded into GPU
         */
        Pending(ContextLoad* load);
        
        /**
         * @brief Destructor
         */
        ~Pending();
        
        /**
         * @brief Copy constructor
         * 
         * @param p Source instance
         */
        Pending(const Pending& p);
        
        /**
         * @brief Move constructor
         * 
         * @param p Source instance
         */
        Pending(Pending&& p) noexcept;
        
        /**
         * @brief Copy assignment
         * 
         * @param p Source instance
         */
        Pending& operator=(const Pending& p);
        
        /**
         * @brief Move assignment
         * 
         * @param p Source instance
         */
        Pending& operator=(Pending&& p) noexcept;
        
        /**
         * @brief Gets the reference count
         * 
         * @return Reference count
         */
        uint64_t getUseCount();
    };
    
    /**
     * @brief Default constructor
     */
    ContextLoader();
    
    /**
     * @brief Destructor
     */
    virtual ~ContextLoader();
    
    /**
     * @brief Append load into the loading list
     * 
     * If the function is called again for the same load, the shared data
     * of the Pending class determines that it already exists and cancels.
     * 
     * @param elem Instance containing data to be loaded into GPU
     */
    void push(const Pending& elem);
    
    /**
     * @brief Loads the data to the GPU
     * 
     * Loads the data from the list to the GPU and then clear the memory
     * from the list. If the reference count of the load is zero, discard it
     * without loading into the GPU.
     */
    void load();
    
    /**
     * @brief Gets the number of loads in the queue
     * 
     * @return Size of pending list
     */
    uint64_t getLoadCount();
    
  private:
    std::queue<Pending> pendingList;
};

}}

#endif
