#include <iostream>

#include "circular-linked-list.hpp"

int main() {
  CircularLinkedList<int> cll{};
  cll.Reverse();
  cll.InsertInOrder(4);
  cll.InsertInOrder(0);
  cll.InsertInOrder(2);
  cll.InsertInOrder(-9);
  cll.InsertInOrder(10);
  std::cout << cll << std::endl;
  return 0;
}
