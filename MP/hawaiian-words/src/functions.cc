#include "functions.hpp"

#include <cctype>

std::string PhoneticsOf(const std::string& hawaiian_word) {
  std::string phonetics;
  for (unsigned int i = 0; i < hawaiian_word.length(); ++i) {
    char c1 = static_cast<char>(tolower(hawaiian_word.at(i)));
    char c2 = (i == hawaiian_word.length() - 1)
                  ? c2 = ' '
                  : static_cast<char>(tolower(hawaiian_word.at(i + 1)));
    if (c1 == ' ') {
      phonetics.push_back(c1);
      continue;
    }
    if (IsNotHawaiianWord(c1, c2)) {
      return hawaiian_word +
             " contains a character not a part of the Hawaiian language.";
    }
    if (IsConsonant(c1)) {
      phonetics.push_back(c1);
      continue;
    }
    if (c1 == 'a') {
      CaseA(c2, phonetics, i);
    } else if (c1 == 'e') {
      CaseE(c2, phonetics, i);
    } else if (c1 == 'i') {
      CaseI(c2, phonetics, i);
    } else if (c1 == 'o') {
      CaseO(c2, phonetics, i);
    } else if (c1 == 'u') {
      CaseU(c2, phonetics, i);
    }
    if ((c2 == ' ' || c2 == '\'') && phonetics.back() == '-') {
      phonetics.pop_back();
    }
  }
  if (phonetics.back() == '-') {
    phonetics.pop_back();
  }
  return phonetics;
}

bool IsConsonant(const char& c) {
  return (c == 'p' || c == 'k' || c == 'h' || c == 'l' || c == 'm' ||
          c == 'n' || c == 'w' || c == '\'');
}

bool IsNotHawaiianWord(const char& c1, const char& c2) {
  return (c1 != 'a' && c1 != 'e' && c1 != 'i' && c1 != 'o' && c1 != 'u' &&
          c1 != 'p' && c1 != 'k' && c1 != 'h' && c1 != 'l' && c1 != 'm' &&
          c1 != 'n' && c1 != 'w' && c1 != '\'' && c2 != 'a' && c2 != 'e' &&
          c2 != 'i' && c2 != 'o' && c2 != 'u' && c2 != 'p' && c2 != 'k' &&
          c2 != 'h' && c2 != 'l' && c2 != 'm' && c2 != 'n' && c2 != 'w' &&
          c2 != '\'');
}

void CaseA(char& c2, std::string& phonetics, unsigned int& i) {
  switch (c2) {
  case 'w':
    phonetics.append("ah-");
    phonetics.push_back(c2);
    ++i;
    break;
  case 'i':
  case 'e':
    phonetics.append("eye-");
    ++i;
    break;
  case 'o':
  case 'u':
    phonetics.append("ow-");
    ++i;
    break;
  default:
    phonetics.append("ah-");
    break;
  }
}

void CaseE(char& c2, std::string& phonetics, unsigned int& i) {
  switch (c2) {
  case 'w':
    phonetics.append("eh-");
    phonetics.push_back('v');
    ++i;
    break;
  case 'i':
    phonetics.append("ay-");
    ++i;
    break;
  case 'u':
    phonetics.append("eh-oo-");
    ++i;
    break;
  default:
    phonetics.append("eh-");
    break;
  }
}

void CaseI(char& c2, std::string& phonetics, unsigned int& i) {
  switch (c2) {
  case 'w':
    phonetics.append("ee-");
    phonetics.push_back('v');
    ++i;
    break;
  case 'u':
    phonetics.append("ew-");
    ++i;
    break;
  default:
    phonetics.append("ee-");
    break;
  }
}

void CaseO(char& c2, std::string& phonetics, unsigned int& i) {
  switch (c2) {
  case 'w':
    phonetics.append("oh-");
    phonetics.push_back('w');
    ++i;
    break;
  case 'i':
    phonetics.append("oy-");
    ++i;
    break;
  case 'u':
    phonetics.append("ow-");
    ++i;
    break;
  default:
    phonetics.append("oh-");
    break;
  }
}

void CaseU(char& c2, std::string& phonetics, unsigned int& i) {
  switch (c2) {
  case 'w':
    phonetics.append("oo-");
    phonetics.push_back('w');
    ++i;
    break;
  case 'i':
    phonetics.append("ooey-");
    ++i;
    break;
  default:
    phonetics.append("oo-");
    break;
  }
}