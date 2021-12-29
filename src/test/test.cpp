#include "../util/config/Config.h"
#include "../core/commandParser/ParseCommand.h"
#include <iostream>
#include <vector>

int main() {
	std::string test = ">command test arg1 arg2";
	std::vector<std::string> vec = {">"};
	std::vector<std::string> result;
	std::cout << Core::ParseCommand(">", test) << std::endl;
	result = Core::ParseArgument(test);
	for (std::string s : result) {
		std::cout << s << std::endl;
	}
}