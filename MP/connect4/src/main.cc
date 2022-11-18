#include <iostream>

#include "board.hpp"

int main() {
  Board b;
  InitBoard(b);

  DropDiskToBoard(b, DiskType::kPlayer2, 0);
  DropDiskToBoard(b, DiskType::kPlayer1, 0);
  DropDiskToBoard(b, DiskType::kPlayer1, 4);
  DropDiskToBoard(b, DiskType::kPlayer1, 5);
  DropDiskToBoard(b, DiskType::kPlayer1, 6);

  std::cout << BoardToStr(b) << std::endl;
}