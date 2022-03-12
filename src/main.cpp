#include <boost/program_options.hpp>
#include <stdexcept>
#include <iostream>
#include <memory>
#include "main.h"
#include "client/MyClient.h"
#include "module/io/IOModule.h"

constexpr char CONFIG_FILE_PATH[] = "maidea.cfg";
constexpr char CONFIG_DISCORD_TOKEN_KEY[] = "DISCORD_TOKEN";

namespace program_options = boost::program_options;

int main() {
	program_options::options_description configDescription("configration");
	std::shared_ptr<MyClientClass> client(nullptr);
	program_options::variables_map configvm;
	
	configDescription.add_options()
		(CONFIG_DISCORD_TOKEN_KEY, program_options::value<std::string>(),"token of discord bot");
	program_options::store(program_options::parse_config_file(CONFIG_FILE_PATH, configDescription), configvm);

	client.reset(new MyClientClass(
		configvm[CONFIG_DISCORD_TOKEN_KEY].as<std::string>(), SleepyDiscord::USER_CONTROLED_THREADS)
	);
	IOModule::RegisterClient(client);
	Module::DiscordIO::RegisterClient(client);
	client->setIntents(SleepyDiscord::Intent::SERVER_MESSAGES, SleepyDiscord::Intent::SERVER_MESSAGE_REACTIONS);
	client->run();	
}
