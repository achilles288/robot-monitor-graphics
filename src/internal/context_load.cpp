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


#include "../rmg/internal/context_load.hpp"


namespace rmg {
namespace internal {


// Class: ContextLoad

/**
 * @brief Loads the data to the GPU
 */
void ContextLoad::load() {}




// Class: ContextLoader::Pending

/**
 * @brief Default constructor
 */
ContextLoader::Pending::Pending() {
    data = NULL;
    shared = new Shared();
    shared->use_count = 1;
    shared->added = false;
}

/**
 * @brief Constructor assigning the load pointer
 * 
 * @param load Instance containing data to be loaded into GPU
 */
ContextLoader::Pending::Pending(ContextLoad* load) {
    data = load;
    shared = new Shared();
    shared->use_count = 1;
    shared->added = false;
}

/**
 * @brief Destructor
 */
ContextLoader::Pending::~Pending() {
    shared->use_count--;
    if(shared->use_count == 0) {
        delete data;
        delete shared;
    }
}

/**
 * @brief Copy constructor
 * 
 * @param p Source instance
 */
ContextLoader::Pending::Pending(const ContextLoader::Pending& p)
{
    data = p.data;
    shared = p.shared;
    shared->use_count++;
}

/**
 * @brief Copy assignment
 * 
 * @param p Source instance
 */
ContextLoader::Pending&
ContextLoader::Pending::operator=(const ContextLoader::Pending& p)
{
    data = p.data;
    shared = p.shared;
    shared->use_count++;
    return *this;
}




// Class: ContextLoader

/**
 * @brief Default constructor
 */
ContextLoader::ContextLoader() {}

/**
 * @brief Destructor
 */
ContextLoader::~ContextLoader() {}

/**
 * @brief Append load into the loading list
 * 
 * If the function is called again for the same load, the shared data
 * of the Pending class determines that it already exists and cancels.
 * 
 * @param elem Instance containing data to be loaded into GPU
 */
void ContextLoader::push(const ContextLoader::Pending& elem)
{
    if(elem.shared->added)
        return;
    ContextLoader::Pending p;
    p.data = elem.data;
    p.shared = elem.shared;
    p.shared->added = true;
    pendingList.push(p);
}

/**
 * @brief Loads the data to the GPU
 * 
 * Loads the data from the list to the GPU and then clear the memory
 * from the list. If the reference count of the load is zero, discard it
 * without loading into the GPU.
 */
void ContextLoader::load() {
    while(pendingList.size() != 0) {
        ContextLoader::Pending p = pendingList.front();
        if(p.shared->use_count != 0)
            p.data->load();
        pendingList.pop();
    }
}

/**
 * @brief Gets the number of loads in the queue
 * 
 * @return Size of pending list
 */
uint64_t ContextLoader::getLoadCount() {
    return pendingList.size();
}
    
}}
