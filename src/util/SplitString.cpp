#include "SplitString.hpp"

void SplitString(std::vector<std::string>& outArray, std::string_view src, const std::string_view separator) {
	outArray.clear();
	std::size_t pos = 0;

	while ((pos = src.find(separator)) != std::string::npos) {
		outArray.emplace_back(src.substr(0, pos));
		src = src.substr(pos + 1);
	}

	outArray.emplace_back(src);
	return;
}