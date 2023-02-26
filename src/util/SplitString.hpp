#pragma once 
#include <vector>
#include <string>
#include <string_view>

void SplitString(std::vector<std::string>& outArray, std::string_view src, const std::string_view separator);