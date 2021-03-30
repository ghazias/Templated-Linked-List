#ifndef LINKED_LIST_HPP_
#define LINKED_LIST_HPP_

#include <cassert>
#include <sstream>

namespace dsc {
template <typename T>
class LinkedList {
 public:
  // ctors and dtors
  LinkedList() = default;  // empty list constructor
  LinkedList(const LinkedList& original);
  LinkedList(LinkedList&& other);
  LinkedList& operator=(const LinkedList& original);
  LinkedList& operator=(LinkedList&& other);
  ~LinkedList() { destroy(); }  // destructor

  // overloads
  bool operator==(const LinkedList& rhs) const;
  bool operator!=(const LinkedList& rhs) const { return !(*this == rhs); }

  // member functions
  void clear();
  std::size_t size() const;
  bool empty() const { return head_ == nullptr && tail_ == nullptr; }
  T& at(std::size_t index);
  const T& at(std::size_t index) const;
  void push_front(T value);
  void push_back(T value);
  T pop_front();
  T pop_back();
  void insert(T value, std::size_t index);
  void remove(std::size_t index);
  bool contains(T value) const;
  void resize(std::size_t newsize);

 private:
  struct Node {
    T value;
    Node* next;
    Node* previous;
  };

  Node* node_at(std::size_t index) const;
  void destroy();
  void copy_from(const LinkedList& other);
  Node* head_{};
  Node* tail_{};
};

template <typename T>
LinkedList<T>::LinkedList(const LinkedList& original) {
  copy_from(original);
}  // copy constructor

template <typename T>
LinkedList<T>::LinkedList(LinkedList&& other)
    : head_{other.head_}, tail_{other.tail_} {
  other.head_ = nullptr;
  other.tail_ = nullptr;
}  // move constructor

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& original) {
  if (this != &original) {
    destroy();
    copy_from(original);
  }

  return *this;
}  // copy assignment

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T>&& other) {
  if (this != &other) {
    destroy();

    head_ = other.head_;
    tail_ = other.tail_;

    other.head_ = nullptr;
    other.tail_ = nullptr;
  }
  return *this;
}  // move assignment

template <typename T>
bool LinkedList<T>::operator==(const LinkedList& rhs) const {
  for (Node *lhs_current = head_, rhs_current = rhs.head_;
       lhs_current != nullptr;
       lhs_current = lhs_current->next, rhs_current = rhs_current->next) {
    if (rhs_current == nullptr) {
      return false;
    }

    if (lhs_current->value != rhs_current->value) {
      return false;
    }
  }
  return true;
}

template <typename T>
std::size_t LinkedList<T>::size() const {
  int counter = 0;
  for (Node* current = head_; current != nullptr; current = current->next) {
    ++counter;
  }
  return counter;
}  // counts size of list

template <typename T>
T& LinkedList<T>::at(std::size_t index) {
  Node* target = node_at(index);
  if (target == nullptr) {
    std::ostringstream msg;
    msg << "Index " << index << " out of bounds in array of size " << size();
    throw std::out_of_range(std::string result = msg.str(););
  }

  return target->value;
}

template <typename T>
const T& LinkedList<T>::at(std::size_t index) const {
  Node* target = node_at(index);
  if (target == nullptr) {
    std::ostringstream msg;
    msg << "Index " << index << " out of bounds in array of size " << size();
    throw std::out_of_range(std::string result = msg.str(););
  }

  return target->value;
}

template <typename T>
void LinkedList<T>::push_front(T value) {
  Node* new_head = new Node{value, head_, nullptr};

  if (head_ != nullptr) {
    head_->previous = new_head;
  }
  tail_ = new_head;
  if (empty()) {
    head_ = tail_;
  }
}

template <typename T>
void LinkedList<T>::push_back(T value) {
  Node* new_tail = new Node{value, nullptr, tail_};

  if (tail_ != nullptr) {
    tail_->next = new_tail;
  }
  tail_ = new_tail;
  if (empty()) {
    head_ = tail_;
  }
}
template <typename T>
T LinkedList<T>::pop_front() {
  if (empty()) {
    throw std::out_of_range("List is empty");
  }

  Node* popped_node = head_;
  T tmp = popped_node->value;

  if (popped_node->next == nullptr) {
    assert(popped_node->previous == nullptr);
    head_ = tail_ = nullptr;
  } else {
    head_ = head_->next;
    head_->previous = nullptr;
  }
  delete popped_node;
  return tmp;
}

template <typename T>
T LinkedList<T>::pop_back() {
  if (empty()) {
    throw std::out_of_range("List is empty");
  }  // empty case

  Node* popped_node = tail_;
  T tmp = popped_node->value;

  if (popped_node->previous == nullptr) {  // single node case
    head_ = tail_ = nullptr;
  } else {  // multiple node case
    tail_ = tail_->previous;
    tail_->next = nullptr;
  }
  delete popped_node;
  return tmp;
}

template <typename T>
void LinkedList<T>::insert(T value, std::size_t index) {
  if (index == 0) {  // front case
    push_front(value);
    return;
  }

  Node* target = node_at(index);

  if (target == nullptr) {  // back case
    push_back(value);
    return;
  }

  Node* new_node = new Node{value, target, target->previous};
  target->previous->next = new_node;
  target->previous = new_node;
}

template <typename T>
void LinkedList<T>::remove(std::size_t index) {
  if (index == 0) {
    pop_front();
    return;
  }

  Node* target = node_at(index);

  if (target == nullptr) {
    throw std::out_of_range("index out of bounds");
  } else if (target->next == nullptr) {
    pop_back();
    return;
  }

  target->previous->next = target->next;
  target->next->previous = target->previous;

  delete target;
}

template <typename T>
bool LinkedList<T>::contains(T value) const {
  Node* current = head_;
  for (Node* current = head_; current != nullptr; current = current->next) {
    current->value == value ? return true : current = current->next;
  }

  return false;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::node_at(std::size_t index) const {
  Node* current = head_;

  for (std::size_t counter; counter < index; ++counter) {
    if (current == nullptr) {
      return nullptr;
    }
    current = current->next;
  }

  return current;
}

template <typename T>
void LinkedList<T>::copy_from(const LinkedList& original) {
  for (Node* current = original.head_; current != nullptr;
       current = current->next) {
    push_back(current->value);
  }
}

}  // namespace dsc
#endif

/*
  class Iterator {
   public:
    Iterator(dsc::LinkedList::Node& source) : source_{&source} {}

    Iterator& operator++();    // pre-fix increment
    Iterator operator++(int);  // post-fix increment
    T& operator*() const;      // dereference
    bool operator==(const Iterator& other) const;
    bool operator!=(const Iterator& other) const;

   private:
    dsc::LinkedList::Node* source_{};
  };
  */