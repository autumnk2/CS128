#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "utilities.hpp"

void ReadDnaDatabase(const std::string& file,
                     std::vector<std::string>& category,
                     std::map<std::string, std::vector<int>>& people_data);

int LongestConsecutiveSequenceOf(std::string& dna_seq, std::string& str);

#endif