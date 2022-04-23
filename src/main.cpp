#include <boost/program_options.hpp>
#include <boost/lexical_cast.hpp>
#include <stdexcept>
#include <iostream>
#include <memory>
#include "main.h"
#include "client/MyClient.h"
#include "module/possession/Possession.h"

constexpr char CONFIG_FILE_PATH[] = "maidea.cfg";
constexpr char CONFIG_DISCORD_TOKEN_KEY[] = "DISCORD_TOKEN";

namespace program_options = boost::program_options;

int main() {
	//コンフィグファイルからコンフィグを取得
	program_options::options_description configDescription("configration");	
	program_options::variables_map configvm;
	configDescription.add_options()
		(CONFIG_DISCORD_TOKEN_KEY, program_options::value<std::string>(), "token of discord bot")
		("PRIVILEGED_USER", program_options::value<std::string>(), "privileged user id")
		;
	program_options::store(program_options::parse_config_file(CONFIG_FILE_PATH, configDescription), configvm);

	//初期化
	Module::Possession::RegisterPrivilegedUser(
		configvm["PRIVILEGED_USER"].as<std::string>()
	);
	auto client = MyClientClass::InitInstance(configvm[CONFIG_DISCORD_TOKEN_KEY].as<std::string>(), SleepyDiscord::USER_CONTROLED_THREADS);

	//実行
	client->setIntents(SleepyDiscord::Intent::SERVER_MESSAGES, SleepyDiscord::Intent::SERVER_MESSAGE_REACTIONS);
	client->run();
}
