#ifndef LINKED_LIST_HPP_
#define LINKED_LIST_HPP_

namespace dsc {
template <typename T>
class LinkedList {
 public:
  LinkedList() = default;  // empty list constructor
  LinkedList(const LinkedList& original) {
    copy_from(original);
  }  // copy constructor
  LinkedList(LinkedList&& other) : head_{other.head_}, tail_{other.tail_} {
    other.head_ = nullptr;
    other.tail_ = nullptr;
  }  // move constructor
  LinkedList& operator=(const LinkedList& original) {
    if (this != &original) {
      destroy();
      copy_from(original);
    }

    return *this;
  }  // copy assignment

  LinkedList& operator=(LinkedList&& other) {
    if (this != &other) {
      destroy();

      head_ = other.head_;
      tail = other.tail_;

      other.head_ = nullptr;
      other.tail_ = nullptr;
    }
    return *this;
  }  // move assignment

  ~LinkedList() { destroy(); }  // destructor

  bool operator==(const LinkedList& rhs) const {
    return source_ == other.source_;
  }

  bool operator!=(const LinkedList& rhs) const { return !(*this == rhs); }

  // member functions
  void clear();
  std::size_t size() const {
    int counter = 0;
    for (Node* currnent = head_; current != nullptr; current = current->next) {
      ++counter;
    }
    return counter;
  }
  bool empty() const { return head == nullptr; }
  T& at(std::size_t index) {
    Node* target = node_at(index);
    if (target == nullptr) {
      throw std::out_of_range("index out of list bounds");  // TODO sstream ver
    }

    return target->value;
  }
  const T& at(std::size_t index) const {
    Node* target = node_at(index);
    if (target == nullptr) {
      throw std::out_of_range("index out of list bounds");  // TODO sstream ver
    }

    return target->value;
  }
  void push_front(int value) {
    Node* new_head = new Node{value, head_, nullptr};

    if (head_ != nullptr) {
      head_->previous = new_head;
    }
    tail_ = new_tail;
    if (empty()) {
      head_ = tail_;
    }
  }
  void push_back(int value) {
    Node* new_tail = new Node{value, nullptr, tail_};

    if (tail_ != nullptr) {
      tail_->next = new_tail;
    }
    tail_ = new_tail;
    if (empty()) {
      head_ = tail_;
    }
  }
  T pop_front() {
    if (empty()) {
      return;
    }  // best practice here?

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
  T pop_back() {
    if (empty()) {
      return;
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
  void insert(T value, std::size_t index) {
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
  void remove(std::size_t index) {
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
  bool contains(T value) const {
    Node* current = head_;

    while (current != nullptr) {
      if (current->value == value) {
        return true;
      }
      current = current->next;
    }

    return false;
  }
  void resize(std::size_t newsize);

 private:
  template <typename T>
  struct Node {
    T value;
    Node* next;
    Node* previous;
  };

  Node* node_at(std::size_t index) const {
    Node* current = head_;

    for (std::size_t counter; counter < index; ++counter) {
      if (current == nullptr) {
        return nullptr;
      }
      current = current->next;
    }

    return current;
  }
  void destroy();
  void copy_from(const LinkedList& other);
  Node* head_{};
  Node* tail_{};
};
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
  /*