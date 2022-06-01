/**
 * @file linked_list.cpp
 * @brief Forward-linked list template
 * 
 * @copyright Copyright (c) 2022 Khant Kyaw Khaung
 * 
 * @license{This project is released under the MIT License.}
 */


#define RMG_EXPORT


#include "../rmg/util/linked_list.hpp"

#include "../rmg/object.hpp"
#include "../rmg/font.hpp"
#include "../rmg/material.hpp"


namespace rmg {

template class LinkedList<Object>;
template class LinkedList<Font>;
template class LinkedList<Material>;

}
