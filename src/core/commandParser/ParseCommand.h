#pragma once
#include <string>
#include <vector>

namespace Core{
	std::string ParseCommand(std::vector<std::string> prefix, std::string commandLine);
	std::string ParseCommand(std::string prefix, std::string commandLine);
	std::vector<std::string> ParseArgument(std::string commandLine);
}
