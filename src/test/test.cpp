#include "../util/config/Config.h"
#include "sleepy_discord/sleepy_discord.h"
#include "test.h"
#include "../module/io/IOModule.h"
#include "../client/MyClient.h"
using namespace SleepyDiscord;

int main() {
	std::unique_ptr<std::map<std::string, std::string>> config = std::move(Util::LoadConfig("maidea.cfg"));
	
	if (!config) {
		std::cout << "‚Ó‚Ÿ‚¢‚é‚Ð‚ç‚¯‚Ê";
		return 0;
	}

	for (auto iter = config->begin(); iter != config->end(); iter++) {
		std::cout << iter->first << " : " << iter->second << std::endl;
	}
	


	return 0;
}