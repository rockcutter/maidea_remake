#pragma once
#include <map>
#include <memory>
#include <string>
#include <fstream>

namespace Util {
	std::unique_ptr<std::map<std::string, std::string>> LoadConfig(std::string filePath);
}
