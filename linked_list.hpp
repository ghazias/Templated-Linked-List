#ifndef LINKED_LIST_HPP_
#include LINKED_LIST_HPP_

namespace dsc {
class LinkedList {
    LinkedList() = default; // default constructor
    ~LinkedList() // destructor
    LinkedList(const LinkedList& original); // copy constructor
    LinkedList(LinkedList&& other); // move constructor
    LinkedList& operator=(const LinkedList& original); // copy assignment
    LinkedList& operator=(LinkedList&& other); // move assignment
    

}
} // namespace dsc