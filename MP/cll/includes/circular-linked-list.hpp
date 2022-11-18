#ifndef CIRCULAR_LINKED_LIST_HPP
#define CIRCULAR_LINKED_LIST_HPP

#include <iostream>

#include "node.hpp"

enum class Order { kASC, kDESC };

template <typename T>
class CircularLinkedList {
public:
  CircularLinkedList() = default;
  CircularLinkedList(const CircularLinkedList<T>& source);
  CircularLinkedList<T>& operator=(const CircularLinkedList<T>& source);
  ~CircularLinkedList();

  void InsertInOrder(const T& data);
  void Reverse();

  template <typename U>
  friend std::ostream& operator<<(std::ostream& os,
                                  const CircularLinkedList<U>& cll);

private:
  // private helper functions
  void Copy(const CircularLinkedList<T>& source) {
    if (source.head_ == source.tail_) {
      if (source.head_ != nullptr) {
        head_ = tail_ = new Node(source.head_->data);
        head_->next = tail_, tail_->next = head_;
      }
      return;
    }
    Node<T>* dummy = new Node(T());
    Node<T>*curr = dummy, *s_curr = source.head_;
    while (s_curr != source.tail_) {
      curr->next = new Node(s_curr->data);
      s_curr = s_curr->next, curr = curr->next;
    }
    curr->next = new Node(s_curr->data, dummy->next);
    tail_ = curr->next, head_ = tail_->next;
    delete dummy;
  }

  void InsertInAscOrder(const T& data) {
    if (head_ == nullptr) {
      head_ = tail_ = new Node(data);
      head_->next = tail_, tail_->next = head_;
      return;
    }
    if (head_ == tail_) {
      head_->next = new Node(data, head_);
      if (data >= tail_->data)
        tail_ = head_->next;
      else
        head_ = head_->next;
      return;
    }
    if (tail_->data <= data) {
      Node<T>* new_node = new Node(data, head_);
      tail_->next = new_node, tail_ = tail_->next;
      return;
    }
    if (head_->data >= data) {
      Node<T>* new_node = new Node(data, head_);
      tail_->next = new_node, head_ = new_node;
      return;
    }
    Node<T>*curr = head_, *prev = tail_;
    while (curr->data < data) curr = curr->next, prev = prev->next;
    Node<T>* new_node = new Node(data, curr);
    prev->next = new_node;
  }

  void InsertInDescOrder(const T& data) {
    if (head_ == nullptr) {
      head_ = tail_ = new Node(data);
      head_->next = tail_, tail_->next = head_;
      return;
    }
    if (head_ == tail_) {
      Node<T>* new_node = new Node(data, head_);
      if (head_->data <= data)
        head_ = new_node, tail_->next = head_;
      else
        tail_ = new_node, head_->next = tail_;
      return;
    }
    if (tail_->data >= data) {
      Node<T>* new_node = new Node(data, head_);
      tail_->next = new_node, tail_ = tail_->next;
      return;
    }
    if (head_->data <= data) {
      Node<T>* new_node = new Node(data, head_);
      tail_->next = new_node, head_ = new_node;
      return;
    }
    Node<T>*curr = head_, *prev = tail_;
    while (curr->data > data) {
      curr = curr->next;
      prev = prev->next;
    }
    Node<T>* new_node = new Node(data, curr);
    prev->next = new_node;
  }

  void Delete() {
    Node<T>* to_remove = head_;
    while (head_ != tail_) {
      head_ = head_->next;
      delete to_remove;
      to_remove = head_;
    }
    delete tail_;
  }

  // private data member
  Node<T>* head_ = nullptr;
  Node<T>* tail_ = nullptr;
  Order node_order_ = Order::kASC;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const CircularLinkedList<T>& cll) {
  Node<T>* iter = cll.head_;
  // empty list condition
  if (iter == nullptr) {
    os << "Empty list";
    return os;
  }
  // non-empty list condition
  do {
    os << iter->data << '\t';
    iter = iter->next;
  } while (iter != cll.head_);

  return os;
}

template <typename T>
CircularLinkedList<T>::CircularLinkedList(const CircularLinkedList<T>& source):
    head_(nullptr), tail_(nullptr), node_order_(source.node_order_) {
  Copy(source);
}

template <typename T>
CircularLinkedList<T>& CircularLinkedList<T>::operator=(
    const CircularLinkedList<T>& source) {
  if (this == &source) return *this;
  Delete();
  head_ = tail_ = nullptr;
  node_order_ = source.node_order_;
  Copy(source);
  return *this;
}

template <typename T>
CircularLinkedList<T>::~CircularLinkedList() {
  Delete();
}

template <typename T>
void CircularLinkedList<T>::InsertInOrder(const T& data) {
  if (node_order_ == Order::kASC)
    InsertInAscOrder(data);
  else  // node_order_ == Order::kDESC
    InsertInDescOrder(data);
}

template <typename T>
void CircularLinkedList<T>::Reverse() {
  if (node_order_ == Order::kASC)
    node_order_ = Order::kDESC;
  else
    node_order_ = Order::kASC;
  if (head_ == tail_) return;
  if (head_->next == tail_) {
    Node<T>* tmp = head_;
    head_ = tail_, tail_ = tmp;
    return;
  }
  Node<T>*pre = tail_, *cur = head_, *nex = head_->next;
  while (nex != head_) {
    cur->next = pre;
    pre = cur, cur = nex, nex = nex->next;
  }
  cur->next = pre;
  Node<T>* tmp = head_;
  head_ = tail_, tail_ = tmp;
}

#endif