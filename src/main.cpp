#include <boost/program_options.hpp>
#include <boost/lexical_cast.hpp>
#include <stdexcept>
#include <iostream>
#include <memory>
#include "main.h"
#include "client/MyClient.h"
#include "module/possession/Possession.h"
#include "util/ReadConfig.h"

constexpr char CONFIG_FILE_PATH[] = "maidea.cfg";
constexpr char CONFIG_DISCORD_TOKEN_KEY[] = "DISCORD_TOKEN";

namespace program_options = boost::program_options;

#define DEBUG

int main() {
	//config�ǂݎ��
	std::unordered_map<std::string, std::string> configMap;
	std::vector<std::string> configKeyArray = {
		CONFIG_DISCORD_TOKEN_KEY,
		"PRIVILEGED_USER",
	};
	Util::ReadConfigFIle(CONFIG_FILE_PATH, configMap, configKeyArray);

	//PossesionModule�̂��߂̏�����
	Module::Possession::RegisterPrivilegedUser(
		configMap["PRIVILEGED_USER"]
	);

	//bot client�N��
	auto client = MyClientClass::InitInstance(configMap[CONFIG_DISCORD_TOKEN_KEY], SleepyDiscord::USER_CONTROLED_THREADS);
	client->setIntents(SleepyDiscord::Intent::SERVER_MESSAGES, SleepyDiscord::Intent::SERVER_MESSAGE_REACTIONS);
	client->run();

	return 0;
	

#ifndef DEBUG
	//�R���t�B�O�t�@�C������R���t�B�O���擾
	program_options::options_description configDescription("configration");	
	program_options::variables_map configvm;
	configDescription.add_options()
		(CONFIG_DISCORD_TOKEN_KEY, program_options::value<std::string>(), "token of discord bot")
		("PRIVILEGED_USER", program_options::value<std::string>(), "privileged user id")
		;
	program_options::store(program_options::parse_config_file(CONFIG_FILE_PATH, configDescription), configvm);

	//������
	Module::Possession::RegisterPrivilegedUser(
		configvm["PRIVILEGED_USER"].as<std::string>()
	);
	auto client = MyClientClass::InitInstance(configvm[CONFIG_DISCORD_TOKEN_KEY].as<std::string>(), SleepyDiscord::USER_CONTROLED_THREADS);

	//���s
	client->setIntents(SleepyDiscord::Intent::SERVER_MESSAGES, SleepyDiscord::Intent::SERVER_MESSAGE_REACTIONS);
	client->run();
#endif
}
