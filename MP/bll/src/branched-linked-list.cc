#include "branched-linked-list.hpp"

BLL::BLL(const BLL& to_copy) { Copy(to_copy); }

BLL::~BLL() { Delete(); }

BLL& BLL::operator=(const BLL& rhs) {
  if (this == &rhs) return *this;
  Delete();
  Copy(rhs);
  return *this;
}

Node* BLL::PushBack(char dat) {
  Node* curr = head_;
  if (curr == nullptr) {
    head_ = new Node(dat);
    return head_;
  }
  while (curr->next_node_ != nullptr) curr = curr->next_node_;
  curr->next_node_ = new Node(dat);
  return curr->next_node_;
}

char BLL::GetAt(size_t idx) const {
  if (idx < 0 || idx >= Size()) throw std::runtime_error("idx out of bound");
  Node* curr = head_;
  while (curr != nullptr) {
    if (idx == 0) return curr->data_;
    --idx;
    if (curr->next_bll_ != nullptr) {
      size_t branch_size = curr->next_bll_->Size();
      if (branch_size > idx) return curr->next_bll_->GetAt(idx);
      idx -= branch_size;
    }
    curr = curr->next_node_;
  }
  return '\0';
}

void BLL::SetAt(size_t idx, char dat) {
  if (idx < 0 || idx >= Size()) throw std::runtime_error("idx out of bound");
  Node* curr = head_;
  while (curr != nullptr) {
    if (idx == 0) {
      curr->data_ = dat;
      return;
    }
    --idx;
    if (curr->next_bll_ != nullptr) {
      size_t branch_size = curr->next_bll_->Size();
      if (branch_size > idx) curr->next_bll_->SetAt(idx, dat);
      idx -= branch_size;
    }
    curr = curr->next_node_;
  }
}

void BLL::Join(size_t idx, BLL* list) {
  if (idx < 0 || idx >= Size()) throw std::runtime_error("idx out of bound");
  Node* curr = head_;
  while (curr != nullptr) {
    if (idx == 0) {
      if (curr->next_bll_ != nullptr)
        throw std::runtime_error("there is already next_bll_");
      curr->next_bll_ = list;
      if (!IsBLLAcyclic()) throw std::runtime_error("cyclic");
    }
    --idx;
    if (curr->next_bll_ != nullptr) {
      size_t branch_size = curr->next_bll_->Size();
      if (branch_size > idx) curr->next_bll_->Join(idx, list);
      idx -= branch_size;
    }
    curr = curr->next_node_;
  }
}

std::string BLL::ToString() const {
  std::string res;
  Node* curr = head_;
  while (curr != nullptr) {
    res.push_back(curr->data_);
    if (curr->next_bll_ != nullptr) res += curr->next_bll_->ToString();
    curr = curr->next_node_;
  }
  return res;
}

size_t BLL::Size() const {
  size_t size = 0;
  Node *curr = head_, *next = head_;
  while (curr != nullptr) {
    next = curr->next_node_;
    ++size;
    if (curr->next_bll_ != nullptr) size += curr->next_bll_->Size();
    curr = next;
  }
  return size;
}