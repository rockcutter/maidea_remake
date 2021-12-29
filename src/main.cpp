#include <iostream>
#include <memory>
#include "main.h"
#include "client/MyClient.h"
#include "Config.h"

constexpr char CONFIG_FILE_PATH[] = "maidea.cfg";
constexpr char CONFIG_DISCORD_TOKEN_KEY[] = "DISCORD_TOKEN";

std::string discordToken = Util::LoadConfig(CONFIG_FILE_PATH)->at(CONFIG_DISCORD_TOKEN_KEY);

std::shared_ptr<MyClientClass> client(
	new MyClientClass(
		discordToken,
		SleepyDiscord::USER_CONTROLED_THREADS
	)
);

int main() {
	client->run();	
}
