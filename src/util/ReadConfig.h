#pragma once
#include <string>
#include <unordered_map>
#include <vector>

namespace Util {
	void ReadConfigFIle(const std::string& configFilePath, std::unordered_map<std::string, std::string>& configMap, const std::vector<std::string> configKeyArray);
}
