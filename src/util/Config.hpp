#pragma once
#include <unordered_map>
#include <string>
#include <string_view>
#include <fstream>


class Config {
private:
	static inline bool isConfigLoaded = false;
	static inline std::unordered_map<std::string, std::string> configMap{};
	
	static void LoadConfig() {

	}

public:
	static void ReloadConfig(){
		Config::LoadConfig();
	}

	static auto GetConfig(){
		if (!Config::isConfigLoaded) {
			Config::LoadConfig();
		}
		return Config::configMap;
	}
};