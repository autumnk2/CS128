#include <iostream>

#include "illini_book.hpp"

std::ostream& operator<<(std::ostream& os, const std::vector<int>& v) {
  os << "{ ";
  for (const auto& e : v) os << e << " ";
  os << "}";
  return os;
}

int main() {
  IlliniBook ib("./example/persons.csv", "./example/relations.csv");
  ib.Print();

  std::cout << std::endl;
  std::cout << (ib.AreRelated(1, 2) ? "yes" : "no") << std::endl;
  std::cout << (ib.AreRelated(3, 2) ? "yes" : "no") << std::endl;
  std::cout << (ib.AreRelated(1, 9) ? "yes" : "no") << std::endl;

  std::cout << (ib.AreRelated(1, 2, "128") ? "yes" : "no") << std::endl;
  std::cout << (ib.AreRelated(1, 2, "124") ? "yes" : "no") << std::endl;
  std::cout << (ib.AreRelated(1, 6, "128") ? "yes" : "no") << std::endl;
  std::cout << (ib.AreRelated(1, 6, "124") ? "yes" : "no") << std::endl;

  std::cout << ib.GetRelated(1, 2) << std::endl;
  std::cout << ib.GetRelated(3, 2) << std::endl;
  std::cout << ib.GetRelated(1, 9) << std::endl;

  std::cout << ib.GetRelated(1, 2, "128") << std::endl;
  std::cout << ib.GetRelated(1, 2, "124") << std::endl;
  std::cout << ib.GetRelated(1, 6, "128") << std::endl;
  std::cout << ib.GetRelated(1, 6, "124") << std::endl;

  std::cout << ib.GetSteps(1, 1) << std::endl;
  std::cout << ib.GetSteps(1, 2) << std::endl;
  std::cout << ib.GetSteps(1, 3) << std::endl;
  std::cout << ib.GetSteps(9, 1) << std::endl;

  return 0;
}
