#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <string>
std::string PhoneticsOf(const std::string& hawaiian_word);
bool IsConsonant(const char& c);
bool IsNotHawaiianWord(const char& c1, const char& c2);
void CaseA(char& c2, std::string& phonetics, unsigned int& i);
void CaseE(char& c2, std::string& phonetics, unsigned int& i);
void CaseI(char& c2, std::string& phonetics, unsigned int& i);
void CaseO(char& c2, std::string& phonetics, unsigned int& i);
void CaseU(char& c2, std::string& phonetics, unsigned int& i);

#endif