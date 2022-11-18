#ifndef WORDSEARCHSOLVER_HPP
#define WORDSEARCHSOLVER_HPP

#include <cstddef>
#include <string>
#include <vector>

#include "WordLocation.hpp"

enum class CheckDirection { kHorizontal, kVertical, kLeftDiag, kRightDiag };

class WordSearchSolver {
public:
  WordSearchSolver(const std::vector<std::vector<char>>& puzzle);
  WordLocation FindWord(const std::string& word);
  WordLocation FindWord(const std::string& word, CheckDirection direction);
  std::pair<bool, WordLocation> FindHorizontal(const std::string& word);
  std::pair<bool, WordLocation> FindVertical(const std::string& word);
  std::pair<bool, WordLocation> FindLeftDiag(const std::string& word);
  std::pair<bool, WordLocation> FindRightDiag(const std::string& word);
  bool LocationInBounds(size_t row, size_t col) const;

private:
  // bool LocationInBounds(size_t row, size_t col) const;
  std::vector<std::vector<char>> puzzle_;
  size_t puzzle_height_;
  size_t puzzle_width_;
};

#endif