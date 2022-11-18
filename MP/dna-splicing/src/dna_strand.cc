#include "dna_strand.hpp"

#include <stdexcept>

void DNAstrand::SpliceIn(const char* pattern, DNAstrand& to_splice_in) {
  if (pattern[0] == '\0' || to_splice_in.head_ == nullptr ||
      &to_splice_in == this)
    return;
  Node* f = Find(pattern);
  if (f == nullptr) throw std::runtime_error("no matching patter");
  Node* new_head = f->next;
  if (f == head_) {
    for (unsigned int i = 0; i < StrLen(pattern) - 1; ++i)
      new_head = new_head->next;
    to_splice_in.tail_->next = new_head;
    Node* to_remove = head_;
    while (head_ != new_head) {
      head_ = head_->next;
      delete to_remove;
      to_remove = head_;
    }
    head_ = to_splice_in.head_;
  } else {
    for (unsigned int i = 0; i < StrLen(pattern); ++i)
      new_head = new_head->next;
    to_splice_in.tail_->next = new_head;
    Node *to_remove = f->next, *curr = f->next;
    while (curr != new_head) {
      curr = curr->next;
      delete to_remove;
      to_remove = curr;
    }
    f->next = to_splice_in.head_;
  }
  UpdateTail();
  to_splice_in.head_ = to_splice_in.tail_ = nullptr;
}

DNAstrand::~DNAstrand() {
  Node* to_remove = head_;
  while (head_ != nullptr) {
    head_ = head_->next;
    delete to_remove;
    to_remove = head_;
  }
}

Node* DNAstrand::Find(const char* pattern) {
  Node* to_return = nullptr;
  unsigned int idx = 0;
  if (head_->data == pattern[0]) {  // special case head_ matching
    Node* curr = head_;
    while (pattern[idx] != '\0' && curr != nullptr &&
           curr->data == pattern[idx])
      curr = curr->next, ++idx;
    if (pattern[idx] == '\0')  // pattern matched
      to_return = head_;
  }
  Node *l = head_, *r = head_;
  while (l->next != nullptr) {
    idx = 0;
    if (l->next->data == pattern[0]) {
      r = l->next;
      while (pattern[idx] != '\0' && r != nullptr && r->data == pattern[idx])
        r = r->next, ++idx;
      if (pattern[idx] == '\0') {  // pattern matched
        to_return = l;
      }
    }
    l = l->next;
  }
  return to_return;
}