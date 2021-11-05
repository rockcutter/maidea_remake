#include "ParseCommand.h"

namespace Core {
	std::string ParseCommand(std::vector<std::string> prefix, std::string commandLine) {
		for (std::string s : prefix) {
			if (commandLine.rfind(s, 0) == 0) {
				commandLine.erase(0, s.length());
				std::string::size_type splitPos = commandLine.find(" ");
				if (splitPos == std::string::npos) {
					return commandLine;
				}
				return commandLine.substr(0, splitPos);
			}
		}
		return "";
	}

	std::string ParseCommand(std::string prefix, std::string commandLine) {
		if (commandLine.rfind(prefix, 0) == 0) {
			commandLine.erase(0, prefix.length());
			std::string::size_type splitPos = commandLine.find(" ");
			if (splitPos == std::string::npos) {
				return commandLine;
			}
			return commandLine.substr(0, splitPos);
		}
		return "";
	}
	
	std::vector<std::string> ParseArgument(std::string commandLine) {
		std::vector<std::string> arguments;
		std::string::size_type index;

		//ƒRƒ}ƒ“ƒh•”“Ç‚Ý”ò‚Î‚µ
		index = commandLine.find(" ");
		commandLine.erase(0, ++index);

		while ((index = commandLine.find(" ")) != std::string::npos) {
			arguments.emplace_back(commandLine.substr(0, index));
			commandLine.erase(0, ++index);
		}
		if (commandLine.length() != 0) {
			arguments.emplace_back(commandLine);
		}
		return arguments;
	}


}