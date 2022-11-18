#ifndef BRANCHED_LINKED_LIST_HPP
#define BRANCHED_LINKED_LIST_HPP

#include <cstddef>
#include <stdexcept>
#include <string>

#include "node.hpp"

class BLL {
public:
  BLL() = default;
  BLL(const BLL& to_copy);
  ~BLL();

  BLL& operator=(const BLL& rhs);
  Node* PushBack(char dat);
  char GetAt(size_t idx) const;
  void SetAt(size_t idx, char dat);
  void Join(size_t idx, BLL* list);
  std::string ToString() const;
  size_t Size() const;

private:
  // helper functions
  void Delete() {
    Node *curr = head_, *next = head_;
    while (curr != nullptr) {
      next = curr->next_node_;
      delete curr->next_bll_;
      delete curr;
      curr = next;
    }
    head_ = nullptr;
  }

  void Copy(const BLL& rhs) {
    Node* dummy_head = new Node('\0');
    Node *curr = dummy_head, *source_curr = rhs.head_;
    while (source_curr != nullptr) {
      curr->next_node_ = new Node(source_curr->data_);
      if (source_curr->next_bll_ != nullptr)
        curr->next_node_->next_bll_ = new BLL(*source_curr->next_bll_);
      curr = curr->next_node_;
      source_curr = source_curr->next_node_;
    }
    head_ = dummy_head->next_node_;
    delete dummy_head;
  }

  bool IsBLLAcyclic() const {
    Node *slow = head_, *fast = Next(head_);
    while (slow != nullptr && fast != nullptr) {
      if (slow == fast) return false;
      slow = Next(slow);
      fast = Next(Next(fast));
    }
    return true;
  }

  Node* Next(const Node* node) const {
    if (node == nullptr) return nullptr;
    if (node->next_bll_ != nullptr) return node->next_bll_->head_;
    return node->next_node_;
  }

  Node* head_ = nullptr;
};

#endif
