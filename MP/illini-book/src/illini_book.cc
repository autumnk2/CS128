#include "illini_book.hpp"

IlliniBook::IlliniBook(const std::string& people_fpath,
                       const std::string& relations_fpath) {
  std::ifstream people_ifs{people_fpath};
  std::ifstream relations_ifs{relations_fpath};
  std::string line;
  while (std::getline(people_ifs, line)) {
    graph_.AddVertex(std::stoi(line));
  }
  std::vector<std::string> comps;
  while (std::getline(relations_ifs, line)) {
    comps = utilities::Split(line, ',');
    graph_.AddEdge(std::stoi(comps.at(0)), std::stoi(comps.at(1)), comps.at(2));
  }
}

bool IlliniBook::AreRelated(int uin_1, int uin_2) const {
  return graph_.HasPath(uin_1, uin_2) != -1;
}

bool IlliniBook::AreRelated(int uin_1,
                            int uin_2,
                            const std::string& relationship) const {
  return graph_.HasPath(uin_1, uin_2, relationship) != -1;
}

int IlliniBook::GetRelated(int uin_1, int uin_2) const {
  return graph_.HasPath(uin_1, uin_2);
}

int IlliniBook::GetRelated(int uin_1,
                           int uin_2,
                           const std::string& relationship) const {
  return graph_.HasPath(uin_1, uin_2, relationship);
}

std::vector<int> IlliniBook::GetSteps(int uin, int n) const {
  return graph_.VerticesReachedByNSteps(uin, n);
}

size_t IlliniBook::CountGroups() const { return graph_.CountParts(); }

size_t IlliniBook::CountGroups(const std::string& relationship) const {
  return graph_.CountPartsWithFilter(relationship);
}

size_t IlliniBook::CountGroups(
    const std::vector<std::string>& relationships) const {
  return graph_.CountPartsWithFilters(relationships);
}