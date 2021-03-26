#ifndef LINKED_LIST_HPP_
#define LINKED_LIST_HPP_

namespace dsc {
template <typename T>
class LinkedList {
 public:
  LinkedList() = default;                             // empty list constructor
  LinkedList(const LinkedList& original);             // copy constructor
  LinkedList(LinkedList&& other);                     // move constructor
  LinkedList& operator=(const LinkedList& original);  // copy assignment
  LinkedList& operator=(LinkedList&& other);          // move assignment
  ~LinkedList();                                      // destructor

  bool operator==(const LinkedList& rhs);
  // member functions
  void clear();
  std::size_t size() const;
  bool empty() const;
  T& at(std::size_t index);
  const T& at(std::size_t index) const;
  void push_front(int value);
  void push_back(int value);
  T pop_front();
  T pop_back();
  void insert(T value, std::size_t index);
  void remove(std::size_t index);
  bool contains(T value) const;
  void resize(std::size_t newsize);

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

 private:
  template <typename T>
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

}  // namespace dsc
#endif
