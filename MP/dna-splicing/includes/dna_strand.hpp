#ifndef DNA_STRAND_HPP
#define DNA_STRAND_HPP

#include "node.hpp"

class DNAstrand {
public:
  DNAstrand() = default;
  DNAstrand(const DNAstrand& rhs) = delete;
  DNAstrand& operator=(const DNAstrand& rhs) = delete;
  ~DNAstrand();

  void SpliceIn(const char* pattern, DNAstrand& to_splice_in);
  Node* Find(const char* patter);

  void Addhead(Node* head) { head_ = head; }
  void Addtail(Node* tail) { tail_ = tail; }
  Node* Gethead() const { return head_; }
  Node* Gettail() const { return tail_; }
  // void Print() const {
  //   Node* curr = head_;
  //   while (curr != tail_) {
  //     std::cout << curr->data << " ";
  //     curr = curr->next;
  //   }
  //   std::cout << tail_->data;
  //   std::cout << std::endl;
  // }

private:
  unsigned int StrLen(const char* str) {
    unsigned int idx = 0;
    while (str[idx] != '\0') ++idx;
    return idx;
  }
  void UpdateTail() {
    Node* curr = head_;
    while (curr->next != nullptr) curr = curr->next;
    tail_ = curr;
  }
  Node* head_ = nullptr;
  Node* tail_ = nullptr;
};

#endif