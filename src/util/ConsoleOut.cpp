#include <time.h>
#include <iostream>
#include "ConsoleOut.h"

namespace Util {
	void ConsoleOut(std::string message) {
		char date[64];
		time_t t = time(NULL);
		strftime(date, sizeof(date), "%Y-%m-%d %H:%M:%S", localtime(&t));
		std::cout << "[" << date << "] " << message << std::endl;
		return;
	}
}