#include "functions.hpp"

void ReadDnaDatabase(const std::string& file,
                     std::vector<std::string>& category,
                     std::map<std::string, std::vector<int>>& people_data) {
  std::ifstream ifs{file};
  int c = 0;
  std::string line;
  std::vector<std::string> people_line;
  std::vector<int> people_counts;
  while (std::getline(ifs, line)) {
    if (c == 0) {
      category = utilities::GetSubstrs(line, ',');
      category.erase(category.begin());
      ++c;
      continue;
    }
    people_line = utilities::GetSubstrs(line, ',');
    for (unsigned int i = 1; i < people_line.size(); ++i) {
      people_counts.push_back(std::stoi(people_line.at(i)));
    }
    people_data.insert({people_line.at(0), people_counts});
    people_counts.clear();
  }
}

int LongestConsecutiveSequenceOf(std::string& dna_seq, std::string& str) {
  int max_count = 0;
  int count = 0;
  unsigned int dna_seq_len = dna_seq.length(), str_len = str.length();
  unsigned int idx1 = 0, idx2 = idx1 + str_len - 1;
  while (idx1 < dna_seq_len && idx2 < dna_seq_len) {
    if (dna_seq.substr(idx1, str_len) == str) {
      ++count;
      idx1 = idx2 + 1;
      idx2 = idx1 + str_len - 1;
    } else {
      ++idx1;
      ++idx2;
      max_count = max_count < count ? count : max_count;
      count = 0;
    }
  }
  return max_count < count ? count : max_count;
}