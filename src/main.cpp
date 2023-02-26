#include <memory>
#include "util/Config.hpp"
#include "client/MyClient.h"
#include "Initialize.hpp"

constexpr char CONFIG_FILE_PATH[] = "maidea.cfg";
constexpr char CONFIG_DISCORD_TOKEN_KEY[] = "DISCORD_TOKEN";

int main(int argc, const char * const * const argv) {
	InitializeApp();
	auto&& configMap = Config::GetConfig();

	auto&& client = MyClientClass::InitInstance(configMap[CONFIG_DISCORD_TOKEN_KEY], SleepyDiscord::USER_CONTROLED_THREADS);
	client->setIntents(SleepyDiscord::Intent::SERVER_MESSAGES, SleepyDiscord::Intent::SERVER_MESSAGE_REACTIONS);
	client->run();

	return 0;
}
