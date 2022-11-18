// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Michael R. Nowak                Environment : ubuntu:latest
//
//  Date ......: 2022/02/07                      Compiler ...: clang-10 //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif
#include "catch.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

#include "board.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////
constexpr int kBoardWidth = 7;
constexpr int kBoardHeight = 6;

bool AreEqual(DiskType solution[][kBoardWidth],
              DiskType student[][kBoardWidth]) {
  for (int i = 0; i < kBoardHeight; ++i) {
    for (int j = 0; j < kBoardWidth; ++j) {
      if (solution[i][j] != student[i][j]) return false;
    }
  }
  return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Board initialization", "[board_init]") {
  // SECTION("Can use sections") {}
  // clang-format off
  DiskType solution[kBoardHeight][kBoardWidth] = {
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty,
    DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, {DiskType::kEmpty,
    DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty,
    DiskType::kEmpty, DiskType::kEmpty}, {DiskType::kEmpty, DiskType::kEmpty,
    DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty,
    DiskType::kEmpty}, {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty,
    DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty},
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty,
    DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, {DiskType::kEmpty,
    DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty,
    DiskType::kEmpty, DiskType::kEmpty}
  };
  // clang-format on
  Board student;  // NOLINT
  InitBoard(student);
  REQUIRE(AreEqual(solution, student.board));
}

TEST_CASE("lower left corner p1") {
  Board b;
  InitBoard(b);
  for (int i = 0; i < kBoardWidth; ++i) {
    for (int j = 0; j < kBoardHeight; ++j) {
      if ((i == 0 && j == 0) || (i == 0 && j == 1) || (i == 0 && j == 2) ||
          (i == 0 && j == 3) || (i == 1 && j == 0) || (i == 1 && j == 1) ||
          (i == 1 && j == 2) || (i == 2 && j == 0) || (i == 2 && j == 1) ||
          (i == 2 && j == 2) || (i == 3 && j == 0) || (i == 3 && j == 3)) {
        DropDiskToBoard(b, DiskType::kPlayer1, i);
      } else {
        DropDiskToBoard(b, DiskType::kPlayer2, i);
      }
    }
  }
  REQUIRE(
      SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kHorizontal));
  REQUIRE(SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kVertical));
  REQUIRE(SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kRightDiag));
  REQUIRE(SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kLeftDiag));
  // std::cout << "lower left corner p1" << std::endl;
  // std::cout << BoardToStr(b) << std::endl;
}

TEST_CASE("lower left corner p2") {
  Board b;
  InitBoard(b);
  for (int i = 0; i < kBoardWidth; ++i) {
    for (int j = 0; j < kBoardHeight; ++j) {
      if ((i == 0 && j == 0) || (i == 0 && j == 1) || (i == 0 && j == 2) ||
          (i == 0 && j == 3) || (i == 1 && j == 0) || (i == 1 && j == 1) ||
          (i == 1 && j == 2) || (i == 2 && j == 0) || (i == 2 && j == 1) ||
          (i == 2 && j == 2) || (i == 3 && j == 0) || (i == 3 && j == 3)) {
        DropDiskToBoard(b, DiskType::kPlayer2, i);
      } else {
        DropDiskToBoard(b, DiskType::kPlayer1, i);
      }
    }
  }
  REQUIRE(
      SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kHorizontal));
  REQUIRE(SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kVertical));
  REQUIRE(SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kRightDiag));
  REQUIRE(SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  // std::cout << "lower left corner p2" << std::endl;
  // std::cout << BoardToStr(b) << std::endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("upper left corner p1") {
  Board b;
  InitBoard(b);
  for (int i = 0; i < kBoardWidth; ++i) {
    for (int j = 0; j < kBoardHeight; ++j) {
      if ((i == 0 && j == 5) || (i == 0 && j == 4) || (i == 0 && j == 3) ||
          (i == 0 && j == 2) || (i == 1 && j == 5) || (i == 1 && j == 4) ||
          (i == 1 && j == 3) || (i == 2 && j == 5) || (i == 2 && j == 4) ||
          (i == 2 && j == 3) || (i == 3 && j == 5) || (i == 3 && j == 2)) {
        DropDiskToBoard(b, DiskType::kPlayer1, i);
      } else {
        DropDiskToBoard(b, DiskType::kPlayer2, i);
      }
    }
  }
  REQUIRE(
      SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kHorizontal));
  REQUIRE(SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kVertical));
  REQUIRE(SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kRightDiag));
  REQUIRE(SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kLeftDiag));
  // std::cout << "upper left corner p1" << std::endl;
  // std::cout << BoardToStr(b) << std::endl;
}

TEST_CASE("upper left corner p2") {
  Board b;
  InitBoard(b);
  for (int i = 0; i < kBoardWidth; ++i) {
    for (int j = 0; j < kBoardHeight; ++j) {
      if ((i == 0 && j == 5) || (i == 0 && j == 4) || (i == 0 && j == 3) ||
          (i == 0 && j == 2) || (i == 1 && j == 5) || (i == 1 && j == 4) ||
          (i == 1 && j == 3) || (i == 2 && j == 5) || (i == 2 && j == 4) ||
          (i == 2 && j == 3) || (i == 3 && j == 5) || (i == 3 && j == 2)) {
        DropDiskToBoard(b, DiskType::kPlayer2, i);
      } else {
        DropDiskToBoard(b, DiskType::kPlayer1, i);
      }
    }
  }
  REQUIRE(
      SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kHorizontal));
  REQUIRE(SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kVertical));
  REQUIRE(SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kRightDiag));
  REQUIRE(SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  // std::cout << "upper left corner p2" << std::endl;
  // std::cout << BoardToStr(b) << std::endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("lower right corner p1") {
  Board b;
  InitBoard(b);
  for (int i = 0; i < kBoardWidth; ++i) {
    for (int j = 0; j < kBoardHeight; ++j) {
      if ((i == 3 && j == 0) || (i == 3 && j == 3) || (i == 4 && j == 0) ||
          (i == 4 && j == 1) || (i == 4 && j == 2) || (i == 5 && j == 0) ||
          (i == 5 && j == 1) || (i == 5 && j == 2) || (i == 6 && j == 0) ||
          (i == 6 && j == 1) || (i == 6 && j == 2) || (i == 6 && j == 3)) {
        DropDiskToBoard(b, DiskType::kPlayer1, i);
      } else {
        DropDiskToBoard(b, DiskType::kPlayer2, i);
      }
    }
  }
  REQUIRE(
      SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kHorizontal));
  REQUIRE(SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kVertical));
  REQUIRE(SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kRightDiag));
  REQUIRE(SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kLeftDiag));
  // std::cout << "lower right corner p1" << std::endl;
  // std::cout << BoardToStr(b) << std::endl;
}

TEST_CASE("lower right corner p2") {
  Board b;
  InitBoard(b);
  for (int i = 0; i < kBoardWidth; ++i) {
    for (int j = 0; j < kBoardHeight; ++j) {
      if ((i == 3 && j == 0) || (i == 3 && j == 3) || (i == 4 && j == 0) ||
          (i == 4 && j == 1) || (i == 4 && j == 2) || (i == 5 && j == 0) ||
          (i == 5 && j == 1) || (i == 5 && j == 2) || (i == 6 && j == 0) ||
          (i == 6 && j == 1) || (i == 6 && j == 2) || (i == 6 && j == 3)) {
        DropDiskToBoard(b, DiskType::kPlayer2, i);
      } else {
        DropDiskToBoard(b, DiskType::kPlayer1, i);
      }
    }
  }
  REQUIRE(
      SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kHorizontal));
  REQUIRE(SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kVertical));
  REQUIRE(SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kRightDiag));
  REQUIRE(SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  // std::cout << "lower right corner p2" << std::endl;
  // std::cout << BoardToStr(b) << std::endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("upper right corner p1") {
  Board b;
  InitBoard(b);
  for (int i = 0; i < kBoardWidth; ++i) {
    for (int j = 0; j < kBoardHeight; ++j) {
      if ((i == 3 && j == 5) || (i == 3 && j == 2) || (i == 4 && j == 5) ||
          (i == 4 && j == 4) || (i == 4 && j == 3) || (i == 5 && j == 5) ||
          (i == 5 && j == 4) || (i == 5 && j == 3) || (i == 6 && j == 5) ||
          (i == 6 && j == 4) || (i == 6 && j == 3) || (i == 6 && j == 2)) {
        DropDiskToBoard(b, DiskType::kPlayer1, i);
      } else {
        DropDiskToBoard(b, DiskType::kPlayer2, i);
      }
    }
  }
  REQUIRE(
      SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kHorizontal));
  REQUIRE(SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kVertical));
  REQUIRE(SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kRightDiag));
  REQUIRE(SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kLeftDiag));
  // std::cout << "upper right corner p1" << std::endl;
  // std::cout << BoardToStr(b) << std::endl;
}

TEST_CASE("upper right corner p2") {
  Board b;
  InitBoard(b);
  for (int i = 0; i < kBoardWidth; ++i) {
    for (int j = 0; j < kBoardHeight; ++j) {
      if ((i == 3 && j == 5) || (i == 3 && j == 2) || (i == 4 && j == 5) ||
          (i == 4 && j == 4) || (i == 4 && j == 3) || (i == 5 && j == 5) ||
          (i == 5 && j == 4) || (i == 5 && j == 3) || (i == 6 && j == 5) ||
          (i == 6 && j == 4) || (i == 6 && j == 3) || (i == 6 && j == 2)) {
        DropDiskToBoard(b, DiskType::kPlayer2, i);
      } else {
        DropDiskToBoard(b, DiskType::kPlayer1, i);
      }
    }
  }
  REQUIRE(
      SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kHorizontal));
  REQUIRE(SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kVertical));
  REQUIRE(SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kRightDiag));
  REQUIRE(SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kLeftDiag));
  // std::cout << "upper right corner p2" << std::endl;
  // std::cout << BoardToStr(b) << std::endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("1 not 2") {
  Board b;
  InitBoard(b);
  for (int i = 0; i < 4; ++i) {
    DropDiskToBoard(b, DiskType::kPlayer1, i);
  }
  REQUIRE(
      SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kHorizontal));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kHorizontal));

  REQUIRE(CheckForWinner(b, DiskType::kPlayer1));
  REQUIRE_FALSE(CheckForWinner(b, DiskType::kPlayer2));
}

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("≤3*3 is not ok") {
  Board b;
  InitBoard(b);
  SECTION("lower left") {
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        DropDiskToBoard(b, DiskType::kPlayer1, i);
      }
    }
  }

  SECTION("upper left") {
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        DropDiskToBoard(b, DiskType::kPlayer2, i);
      }
    }
    for (int i = 0; i < 3; ++i) {
      for (int j = 0; j < 3; ++j) {
        DropDiskToBoard(b, DiskType::kPlayer1, i);
      }
    }
  }

  SECTION("lower right") {
    for (int i = 4; i < 7; ++i) {
      for (int j = 0; j < 3; ++j) {
        DropDiskToBoard(b, DiskType::kPlayer1, i);
      }
    }
  }

  SECTION("upper right") {
    for (int i = 4; i < 7; ++i) {
      for (int j = 0; j < 2; ++j) {
        DropDiskToBoard(b, DiskType::kPlayer2, i);
      }
    }
    for (int i = 4; i < 7; ++i) {
      for (int j = 0; j < 3; ++j) {
        DropDiskToBoard(b, DiskType::kPlayer1, i);
      }
    }
  }

  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kHorizontal));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kVertical));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kRightDiag));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kLeftDiag));

  REQUIRE_FALSE(CheckForWinner(b, DiskType::kPlayer1));

  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kHorizontal));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kVertical));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kRightDiag));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kLeftDiag));

  REQUIRE_FALSE(CheckForWinner(b, DiskType::kPlayer2));
}

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Board Location In Bounds", "[BoardLocationInBounds]") {
  REQUIRE(BoardLocationInBounds(6, 7) == false);
  REQUIRE(BoardLocationInBounds(6, 0) == false);
  REQUIRE(BoardLocationInBounds(7, 0) == false);
  REQUIRE(BoardLocationInBounds(-1, -99) == false);
  REQUIRE(BoardLocationInBounds(5, 3) == true);
  REQUIRE(BoardLocationInBounds(0, 0) == true);
  REQUIRE(BoardLocationInBounds(1, 0) == true);
  REQUIRE(BoardLocationInBounds(0, 1) == true);
}

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Drop disk to board", "[DropDiskToBoard]") {
  // clang-format off
  DiskType solution[kBoardHeight][kBoardWidth] = {
    {DiskType::kPlayer1, DiskType::kPlayer2, DiskType::kPlayer1,
    DiskType::kPlayer1, DiskType::kPlayer1, DiskType::kPlayer1,
    DiskType::kPlayer1}, {DiskType::kPlayer1, DiskType::kPlayer2,
    DiskType::kPlayer2, DiskType::kPlayer2, DiskType::kPlayer2,
    DiskType::kPlayer2, DiskType::kPlayer2}, {DiskType::kPlayer1,
    DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty,
    DiskType::kEmpty, DiskType::kEmpty}, {DiskType::kPlayer1,
    DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty,
    DiskType::kEmpty, DiskType::kEmpty}, {DiskType::kPlayer1,
    DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty,
    DiskType::kEmpty, DiskType::kEmpty}, {DiskType::kPlayer1,
    DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty,
    DiskType::kEmpty, DiskType::kEmpty}
  };
  // clang-format on
  Board b;
  InitBoard(b);
  for (int i = 0; i < Board::kBoardHeight; ++i) {
    DropDiskToBoard(b, DiskType::kPlayer1, 0);
  }
  DropDiskToBoard(b, DiskType::kPlayer2, 1);
  DropDiskToBoard(b, DiskType::kPlayer2, 1);

  DropDiskToBoard(b, DiskType::kPlayer1, 2);
  DropDiskToBoard(b, DiskType::kPlayer2, 2);

  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);

  DropDiskToBoard(b, DiskType::kPlayer1, 4);
  DropDiskToBoard(b, DiskType::kPlayer2, 4);

  DropDiskToBoard(b, DiskType::kPlayer1, 5);
  DropDiskToBoard(b, DiskType::kPlayer2, 5);

  DropDiskToBoard(b, DiskType::kPlayer1, 6);
  DropDiskToBoard(b, DiskType::kPlayer2, 6);

  REQUIRE(AreEqual(solution, b.board));

  REQUIRE_THROWS_AS(DropDiskToBoard(b, DiskType::kPlayer1, -1),
                    std::runtime_error);
  REQUIRE_THROWS_AS(DropDiskToBoard(b, DiskType::kPlayer1, 100),
                    std::runtime_error);
  REQUIRE_THROWS_AS(DropDiskToBoard(b, DiskType::kPlayer1, 7),
                    std::runtime_error);

  REQUIRE_THROWS_AS(DropDiskToBoard(b, DiskType::kPlayer1, 0),
                    std::runtime_error);
}

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("No winner", "") {
  Board b;
  InitBoard(b);

  DropDiskToBoard(b, DiskType::kPlayer1, 0);
  DropDiskToBoard(b, DiskType::kPlayer2, 0);
  DropDiskToBoard(b, DiskType::kPlayer1, 0);
  DropDiskToBoard(b, DiskType::kPlayer2, 0);
  DropDiskToBoard(b, DiskType::kPlayer1, 0);
  DropDiskToBoard(b, DiskType::kPlayer2, 0);

  DropDiskToBoard(b, DiskType::kPlayer2, 1);
  DropDiskToBoard(b, DiskType::kPlayer1, 1);
  DropDiskToBoard(b, DiskType::kPlayer2, 1);
  DropDiskToBoard(b, DiskType::kPlayer1, 1);
  DropDiskToBoard(b, DiskType::kPlayer2, 1);
  DropDiskToBoard(b, DiskType::kPlayer1, 1);

  DropDiskToBoard(b, DiskType::kPlayer2, 2);
  DropDiskToBoard(b, DiskType::kPlayer1, 2);
  DropDiskToBoard(b, DiskType::kPlayer2, 2);
  DropDiskToBoard(b, DiskType::kPlayer1, 2);
  DropDiskToBoard(b, DiskType::kPlayer2, 2);
  DropDiskToBoard(b, DiskType::kPlayer1, 2);

  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);

  DropDiskToBoard(b, DiskType::kPlayer1, 4);
  DropDiskToBoard(b, DiskType::kPlayer2, 4);
  DropDiskToBoard(b, DiskType::kPlayer1, 4);
  DropDiskToBoard(b, DiskType::kPlayer2, 4);
  DropDiskToBoard(b, DiskType::kPlayer1, 4);
  DropDiskToBoard(b, DiskType::kPlayer2, 4);

  DropDiskToBoard(b, DiskType::kPlayer1, 5);
  DropDiskToBoard(b, DiskType::kPlayer2, 5);
  DropDiskToBoard(b, DiskType::kPlayer1, 5);
  DropDiskToBoard(b, DiskType::kPlayer2, 5);
  DropDiskToBoard(b, DiskType::kPlayer1, 5);
  DropDiskToBoard(b, DiskType::kPlayer2, 5);

  DropDiskToBoard(b, DiskType::kPlayer2, 6);
  DropDiskToBoard(b, DiskType::kPlayer1, 6);
  DropDiskToBoard(b, DiskType::kPlayer2, 6);
  DropDiskToBoard(b, DiskType::kPlayer1, 6);
  DropDiskToBoard(b, DiskType::kPlayer2, 6);
  DropDiskToBoard(b, DiskType::kPlayer1, 6);

  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kHorizontal));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kVertical));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kRightDiag));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kLeftDiag));

  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kHorizontal));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kVertical));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kRightDiag));
  REQUIRE_FALSE(
      SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kLeftDiag));

  REQUIRE(CheckForWinner(b, DiskType::kPlayer1) == false);
  REQUIRE(CheckForWinner(b, DiskType::kPlayer2) == false);
}

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("4 same", "") {
  Board b;
  InitBoard(b);
  for (int i = 0; i < 4; ++i) {
    DropDiskToBoard(b, DiskType::kPlayer2, 0);
    DropDiskToBoard(b, DiskType::kPlayer1, 1);
  }
  REQUIRE(SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kVertical) ==
          true);
  REQUIRE(SearchForWinner(b, DiskType::kPlayer2, WinningDirection::kVertical) ==
          true);

  REQUIRE(CheckForWinner(b, DiskType::kPlayer1));
  REQUIRE(CheckForWinner(b, DiskType::kPlayer2));
}

/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("test horizon") {
  Board b;
  InitBoard(b);
  for (int i = 0; i < 4; ++i) {
    DropDiskToBoard(b, DiskType::kPlayer1, i);
  }
  REQUIRE(
      SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kHorizontal));
}

TEST_CASE("test vertical") {
  Board b;
  InitBoard(b);
  for (int i = 0; i < 4; ++i) {
    DropDiskToBoard(b, DiskType::kPlayer1, 0);
  }
  REQUIRE(SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kVertical));
}

TEST_CASE("test leftdiag") {
  Board b;
  InitBoard(b);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);
  DropDiskToBoard(b, DiskType::kPlayer2, 4);
  DropDiskToBoard(b, DiskType::kPlayer2, 4);
  DropDiskToBoard(b, DiskType::kPlayer2, 5);

  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  DropDiskToBoard(b, DiskType::kPlayer1, 4);
  DropDiskToBoard(b, DiskType::kPlayer1, 5);
  DropDiskToBoard(b, DiskType::kPlayer1, 6);

  REQUIRE(SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kLeftDiag));
}

TEST_CASE("test leftdiagA") {
  Board b;
  InitBoard(b);
  DropDiskToBoard(b, DiskType::kPlayer2, 0);
  DropDiskToBoard(b, DiskType::kPlayer2, 0);
  DropDiskToBoard(b, DiskType::kPlayer2, 0);
  DropDiskToBoard(b, DiskType::kPlayer2, 1);
  DropDiskToBoard(b, DiskType::kPlayer2, 1);
  DropDiskToBoard(b, DiskType::kPlayer2, 2);

  DropDiskToBoard(b, DiskType::kPlayer1, 0);
  DropDiskToBoard(b, DiskType::kPlayer1, 1);
  DropDiskToBoard(b, DiskType::kPlayer1, 2);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);

  REQUIRE(SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kLeftDiag));
}

TEST_CASE("test rightdiag") {
  Board b;
  InitBoard(b);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);
  DropDiskToBoard(b, DiskType::kPlayer2, 2);
  DropDiskToBoard(b, DiskType::kPlayer2, 2);
  DropDiskToBoard(b, DiskType::kPlayer2, 1);

  DropDiskToBoard(b, DiskType::kPlayer1, 0);
  DropDiskToBoard(b, DiskType::kPlayer1, 1);
  DropDiskToBoard(b, DiskType::kPlayer1, 2);
  DropDiskToBoard(b, DiskType::kPlayer1, 3);

  REQUIRE(SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kRightDiag));
}

TEST_CASE("test rightdiagA") {
  Board b;
  InitBoard(b);
  DropDiskToBoard(b, DiskType::kPlayer2, 6);
  DropDiskToBoard(b, DiskType::kPlayer2, 6);
  DropDiskToBoard(b, DiskType::kPlayer2, 6);
  DropDiskToBoard(b, DiskType::kPlayer2, 6);
  DropDiskToBoard(b, DiskType::kPlayer2, 5);
  DropDiskToBoard(b, DiskType::kPlayer2, 5);
  DropDiskToBoard(b, DiskType::kPlayer2, 5);
  DropDiskToBoard(b, DiskType::kPlayer2, 4);
  DropDiskToBoard(b, DiskType::kPlayer2, 4);
  DropDiskToBoard(b, DiskType::kPlayer2, 3);

  DropDiskToBoard(b, DiskType::kPlayer1, 3);
  DropDiskToBoard(b, DiskType::kPlayer1, 4);
  DropDiskToBoard(b, DiskType::kPlayer1, 5);
  DropDiskToBoard(b, DiskType::kPlayer1, 6);

  REQUIRE(SearchForWinner(b, DiskType::kPlayer1, WinningDirection::kRightDiag));
}

TEST_CASE("tricky", "[h]") {
  Board b;
  InitBoard(b);

  DropDiskToBoard(b, DiskType::kPlayer2, 0);
  DropDiskToBoard(b, DiskType::kPlayer1, 0);
  DropDiskToBoard(b, DiskType::kPlayer1, 4);
  DropDiskToBoard(b, DiskType::kPlayer1, 5);
  DropDiskToBoard(b, DiskType::kPlayer1, 6);

  REQUIRE_FALSE(CheckForWinner(b, DiskType::kPlayer1));
  REQUIRE_FALSE(CheckForWinner(b, DiskType::kPlayer2));
}