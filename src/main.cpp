#include <memory>
#include <string_view>
#include "util/Config.hpp"
#include "client/MyClient.h"
#include "Initialize.hpp"

inline constexpr std::string_view CONFIG_FILE_PATH 			= "maidea.cfg";
inline constexpr std::string_view CONFIG_DISCORD_TOKEN_KEY 	= "DISCORD_TOKEN";

int main() {
	Config::SetConfigFilePath(CONFIG_FILE_PATH);
	InitializeApp();
	auto&& configMap = Config::GetConfig();

	auto&& client = MyClientClass::InitInstance(configMap[std::string{CONFIG_DISCORD_TOKEN_KEY}], SleepyDiscord::USER_CONTROLED_THREADS);
	client->setIntents(SleepyDiscord::Intent::SERVER_MESSAGES, SleepyDiscord::Intent::SERVER_MESSAGE_REACTIONS);
	client->run();

	return 0;
}
