#include <iostream>
#include <string>
#include <vector>

#include "WordSearchSolver.hpp"

bool operator==(const WordLocation& lhs, const WordLocation& rhs) {
  if (lhs.word != rhs.word) return false;
  if (lhs.char_positions.size() != rhs.char_positions.size()) return false;
  for (size_t i = 0; i < lhs.char_positions.size(); ++i) {
    if (lhs.char_positions.at(i).character !=
        rhs.char_positions.at(i).character)
      return false;
    if (lhs.char_positions.at(i).row != rhs.char_positions.at(i).row)
      return false;
    if (lhs.char_positions.at(i).col != rhs.char_positions.at(i).col)
      return false;
  }
  return true;
}

char random_char() { return rand() % 26 + 'a'; }

std::vector<std::vector<char>> generate_random_2dvec() {
  std::vector<std::vector<char>> res;
  std::vector<char> row;
  for (int i = 0; i < 20; ++i) {
    for (int j = 0; j < 18; ++j) {
      row.push_back(random_char());
    }
    res.push_back(row);
    row.clear();
  }
  return res;
}

std::string generate_random_matrix(std::vector<std::vector<char>> v) {
  std::string s = "        {";
  for (int i = 0; i < 20; ++i) {
    if (i == 0)
      s += "{";
    else
      s += "         {";
    for (int j = 0; j < 18; ++j) {
      s.push_back('\'');
      s.push_back(v.at(i).at(j));
      s.push_back('\'');
      s += ", ";
    }
    s.pop_back();
    s.pop_back();
    s += "},\n";
  }
  s.pop_back();
  s.pop_back();
  s += "};";
  return s;
}

std::string generate_word() {
  std::string res;
  for (int i = 0; i < 5; ++i) res.push_back(random_char());
  return res;
}

std::string generate_word_location(WordLocation wl) {
  if (wl == WordLocation{}) return "WordLocation wl = WordLocation{}";
  std::string res;
  res += "CharPositions c1, c2, c3, c4, c5;\n";
  int i = 1;
  for (CharPositions c : wl.char_positions) {
    res += "c" + std::to_string(i) + ".character" + " = \'" + c.character +
           "\';\n";
    res += "c" + std::to_string(i) + ".row" + " = " + std::to_string(c.row) +
           ";\n";
    res += "c" + std::to_string(i) + ".col" + " = " + std::to_string(c.col) +
           ";\n";
    ++i;
  }
  res += "WordLocation wl;\n";
  res += "wl.word = \"" + wl.word + "\";\n";
  res += "wl.char_positions = {c1, c2, c3, c4, c5};\n";
  return res;
}
// clang-format off
std::string generate_test_case() {
  std::string res = "TEST_CASE(\"\", \"\") {\n";
  res += "// clang-format off\n";
  std::vector<std::vector<char>> v = generate_random_2dvec();
  res += "    std::vector<std::vector<char>> puzzle = \n" + generate_random_matrix(v) + "\n";
  res += "// clang-format on\n";
  WordSearchSolver wss(v);
  WordLocation wl;
  bool isH = false, isV = false, isL = false, isR = false;
  do {
    std::string word = generate_word();
    wl = wss.FindWord(word);
    isH = wss.FindHorizontal(word).first;
    isV = wss.FindVertical(word).first;
    isL = wss.FindLeftDiag(word).first;
    isR = wss.FindRightDiag(word).first;
  } while (wl == WordLocation{});
  res += generate_word_location(wl);
  res += "\n";
  res += "WordSearchSolver wss(puzzle);\n";
  res += "REQUIRE(wss.FindWord(wl.word) == wl);\n";
  if (isH) res += "REQUIRE(wss.FindWord(wl.word, CheckDirection::kHorizontal) == wl);\n";
  else res += "REQUIRE(wss.FindWord(wl.word, CheckDirection::kHorizontal) == WordLocation{});\n";

  if (isV) res += "REQUIRE(wss.FindWord(wl.word, CheckDirection::kVertical) == wl);\n";
  else res += "REQUIRE(wss.FindWord(wl.word, CheckDirection::kVertical) == WordLocation{});\n";

  if (isL) res += "REQUIRE(wss.FindWord(wl.word, CheckDirection::kLeftDiag) == wl);\n";
  else res += "REQUIRE(wss.FindWord(wl.word, CheckDirection::kLeftDiag) == WordLocation{});\n";

  if (isR) res += "REQUIRE(wss.FindWord(wl.word, CheckDirection::kRightDiag) == wl);\n";
  else res += "REQUIRE(wss.FindWord(wl.word, CheckDirection::kRightDiag) == WordLocation{});\n";

  res += "}\n";
  return res;
}
// clang-format on

int main() {
  // std::cout << generate_random_matrix() << std::endl << std::endl;

  // // clang-format off
  // std::vector<std::vector<char>> puzzle = {
  //   {'o', 'o', 'o', 'b', 'p', 'p', 'l', 'e', 'q', 'l', 'w', 'p', 'h', 'a',
  //   'p'},
  //   {'j', 'n', 'a', 'd', 'q', 'h', 'd', 'c', 'n', 'v', 'w', 'd', 't', 'x',
  //   'j'},
  //   {'b', 'm', 'y', 'p', 'p', 'p', 'h', 'a', 'u', 'x', 'n', 's', 'p', 'u',
  //   's'},
  //   {'g', 'd', 'h', 'i', 'i', 'x', 'q', 'm', 'b', 'f', 'j', 'x', 'j', 'c',
  //   'v'},
  //   {'u', 'd', 'j', 's', 'u', 'y', 'i', 'b', 'y', 'e', 'b', 'm', 'w', 's',
  //   'i'},
  //   {'q', 'y', 'o', 'y', 'g', 'y', 'x', 'y', 'm', 'z', 'e', 'v', 'y', 'p',
  //   'z'},
  //   {'v', 'j', 'e', 'g', 'e', 'b', 'e', 'o', 'c', 'f', 'u', 'f', 't', 's',
  //   'x'},
  //   {'d', 'i', 'x', 't', 'i', 'g', 's', 'i', 'e', 'e', 'h', 'k', 'c', 'h',
  //   'z'},
  //   {'d', 'f', 'l', 'i', 'l', 'r', 'j', 'q', 'f', 'n', 'x', 'z', 't', 'q',
  //   'r'},
  //   {'s', 'v', 'b', 's', 'p', 'k', 'y', 'h', 's', 'e', 'n', 'b', 'p', 'p',
  //   'k'}};
  // // clang-format on

  // WordSearchSolver wss(puzzle);
  // std::string word = generate_word();
  // wss.FindWord(word);

  // CharPositions c1, c2, c3, c4, c5;
  // c1.character = 'a';
  // c1.row = 1;
  // c1.col = 3;
  // c2.character = 'b';
  // c2.row = 2;
  // c2.col = 2;
  // c3.character = 'c';
  // c3.row = 4;
  // c3.col = 34;
  // c4.character = 'd';
  // c4.row = 6;
  // c4.col = 12;
  // c5.character = 'e';
  // c5.row = 16;
  // c5.col = 31;

  // WordLocation wl;
  // wl.word = "abcde";
  // wl.char_positions = {c1, c2, c3, c4, c5};

  // WordSearchSolver wss(puzzle);
  // for (int i = 0; i < 100; ++i) {
  //   std::cout << "============" << std::endl << std::endl;
  //   std::string word = generate_word();
  //   std::cout << generate_word_location(wss.FindWord(word)) << std::endl;
  //   std::cout << "============" << std::endl << std::endl;
  // }
  srand(time(nullptr));
  for (int i = 0; i < 10; ++i) {
    std::cout << generate_test_case() << std::endl;
  }
}