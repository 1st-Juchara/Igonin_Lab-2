#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

void inputString(std::istream& in, std::string& str);

bool inString(std::string str_where, std::string str_what);

float tryInputNum(float min, float max);

int tryChoose(int min, int max);

void enterInterval(const std::vector <int>& index, std::vector <int>& index_ch);

void enterPacket(const std::vector <int>& index, std::vector <int>& index_ch);

void enterElement(const std::vector <int>& index, std::vector <int>& index_ch);

void choosingElements(const std::vector <int>& index, std::vector <int>& index_ch);