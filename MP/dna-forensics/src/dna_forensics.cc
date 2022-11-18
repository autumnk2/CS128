#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "functions.hpp"
#include "utilities.hpp"

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " [input_file] [dna_sequence]"
              << std::endl;
    return 1;
  }
  std::vector<std::string> category;
  std::map<std::string, std::vector<int>> data;
  ReadDnaDatabase(argv[1], category, data);
  std::string dna_seq = argv[2];
  std::vector<int> dna_seq_counts;
  for (unsigned int i = 0; i < category.size(); ++i)
    dna_seq_counts.push_back(
        LongestConsecutiveSequenceOf(dna_seq, category.at(i)));
  std::vector<std::string> ret_name;
  for (auto& p : data)
    if (p.second == dna_seq_counts) ret_name.push_back(p.first);
  if (ret_name.size() == 1)
    std::cout << ret_name.at(0) << '\n';
  else
    std::cout << "No match" << '\n';
  return 0;
}