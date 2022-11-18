#include <iostream>

#include "branched-linked-list.hpp"

int main() {
  /* EXAMPLE INTERACTIONS WITH BLL */
  BLL* first = new BLL();
  first->PushBack('h');
  first->PushBack('i');

  std::cout << first->ToString() << std::endl;  // hi

  // /////////////////////////////////////

  BLL* second = new BLL();
  second->PushBack('i');
  second->PushBack('!');
  second->PushBack('@');

  std::cout << second->ToString() << std::endl;  // i!@

  // /////////////////////////////////////

  first->Join(1, second);

  std::cout << first->ToString() << std::endl;
  std::cout << first->Size() << std::endl;

  // /////////////////////////////////////

  BLL* third = new BLL();
  third->PushBack('1');
  third->PushBack('2');

  first->Join(4, third);
  std::cout << "t" << std::endl;
  third->Join(1, second);
  std::cout << "here" << std::endl;

  std::cout << first->ToString() << std::endl;

  return 0;
}
