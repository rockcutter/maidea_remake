#include "ReadConfig.h"
#include <boost/program_options.hpp>
#include <unordered_map>
#include <iostream>

namespace program_options = boost::program_options;

namespace Util {
	void ReadConfigFIle(const std::string& configFilePath, std::unordered_map<std::string, std::string>& configMap, const std::vector<std::string> configKeyArray) {
		program_options::options_description cfgDesc("config");
		program_options::variables_map configvm;

		//�z�肷��L�[�����ׂēo�^
		for (const auto& key : configKeyArray) {
			cfgDesc.add_options()(key.c_str(), program_options::value<std::string>());
		}

		//�L�[�����o��
		try {
			program_options::store(program_options::parse_config_file(configFilePath.c_str(), cfgDesc), configvm);
		}
		catch (std::exception& e) {
			std::cout << e.what();
			exit(1);
		}

		//�l��configMap�Ɋi�[
		for (const auto& key : configKeyArray) {
			configMap.emplace(key, configvm[key].as<std::string>());
		}
		return;
	}
}