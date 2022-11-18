#include "WordSearchSolver.hpp"

bool WordSearchSolver::LocationInBounds(size_t row, size_t col) const {
  return row < puzzle_height_ && col < puzzle_width_ && row >= 0 && col >= 0;
}

WordSearchSolver::WordSearchSolver(
    const std::vector<std::vector<char>>& puzzle):
    puzzle_(puzzle),
    puzzle_height_(puzzle.size()),
    puzzle_width_(puzzle.at(0).size()) {}

WordLocation WordSearchSolver::FindWord(const std::string& word) {
  auto h = FindHorizontal(word);
  auto v = FindVertical(word);
  auto l = FindLeftDiag(word);
  auto r = FindRightDiag(word);
  if (h.first) return h.second;
  if (v.first) return v.second;
  if (l.first) return l.second;
  if (r.first) return r.second;
  return WordLocation{};
}

WordLocation WordSearchSolver::FindWord(const std::string& word,
                                        CheckDirection direction) {
  if (direction == CheckDirection::kHorizontal)
    return FindHorizontal(word).second;
  if (direction == CheckDirection::kVertical) return FindVertical(word).second;
  if (direction == CheckDirection::kLeftDiag) return FindLeftDiag(word).second;
  if (direction == CheckDirection::kRightDiag)
    return FindRightDiag(word).second;
  return WordLocation{};
}

std::pair<bool, WordLocation> WordSearchSolver::FindHorizontal(
    const std::string& word) {
  size_t len = word.length();
  if (len > puzzle_width_) return {false, WordLocation{}};
  WordLocation res{};
  CharPositions cp{};
  for (size_t row = 0; row < puzzle_height_; ++row) {
    for (size_t col = 0; col < puzzle_width_ - len + 1; ++col) {
      for (size_t i = 0; i < len; ++i) {
        cp.row = row;
        cp.col = col + i;
        cp.character = puzzle_.at(cp.row).at(cp.col);
        res.word.push_back(cp.character);
        res.char_positions.push_back(cp);
      }
      if (res.word == word) return {true, res};
      res.word.clear();
      res.char_positions.clear();
    }
  }
  return {false, WordLocation{}};
}

std::pair<bool, WordLocation> WordSearchSolver::FindVertical(
    const std::string& word) {
  size_t len = word.length();
  if (len > puzzle_height_) return {false, WordLocation{}};
  WordLocation res{};
  CharPositions cp{};
  for (size_t row = 0; row < puzzle_height_ - len + 1; ++row) {
    for (size_t col = 0; col < puzzle_width_; ++col) {
      for (size_t i = 0; i < len; ++i) {
        cp.row = row + i;
        cp.col = col;
        cp.character = puzzle_.at(cp.row).at(cp.col);
        res.word.push_back(cp.character);
        res.char_positions.push_back(cp);
      }
      if (res.word == word) return {true, res};
      res.word.clear();
      res.char_positions.clear();
    }
  }
  return {false, WordLocation{}};
}

std::pair<bool, WordLocation> WordSearchSolver::FindLeftDiag(
    const std::string& word) {
  size_t len = word.length();
  if (len > puzzle_width_ || len > puzzle_height_)
    return {false, WordLocation{}};
  WordLocation res{};
  CharPositions cp{};
  for (size_t row = 0; row < puzzle_height_ - len + 1; ++row) {
    for (size_t col = len - 1; col < puzzle_width_; ++col) {
      for (size_t i = 0; i < len; ++i) {
        cp.row = row + i;
        cp.col = col - i;
        cp.character = puzzle_.at(cp.row).at(cp.col);
        res.word.push_back(cp.character);
        res.char_positions.push_back(cp);
      }
      if (res.word == word) return {true, res};
      res.word.clear();
      res.char_positions.clear();
    }
  }
  return {false, WordLocation{}};
}

std::pair<bool, WordLocation> WordSearchSolver::FindRightDiag(
    const std::string& word) {
  size_t len = word.length();
  if (len > puzzle_width_ || len > puzzle_height_)
    return {false, WordLocation{}};
  WordLocation res{};
  CharPositions cp{};
  for (size_t row = 0; row < puzzle_height_ - len + 1; ++row) {
    for (size_t col = 0; col < puzzle_width_ - len + 1; ++col) {
      for (size_t i = 0; i < len; ++i) {
        cp.row = row + i;
        cp.col = col + i;
        cp.character = puzzle_.at(cp.row).at(cp.col);
        res.word.push_back(cp.character);
        res.char_positions.push_back(cp);
      }
      if (res.word == word) return {true, res};
      res.word.clear();
      res.char_positions.clear();
    }
  }
  return {false, WordLocation{}};
}
