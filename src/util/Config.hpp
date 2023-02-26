#pragma once
#include <unordered_map>
#include <string>
#include <string_view>
#include <fstream>
#include "SplitString.hpp"

class Config {
private:
	static inline bool isConfigLoaded = false;
	static inline std::unordered_map<std::string, std::string> configMap{};
	static inline std::string_view configFilePath = "maidea.cfg";
	
	static void LoadConfig() {
		configMap.clear();

		std::ifstream ifs{std::string{Config::configFilePath}};
		if(!ifs) {
			return;
		}

		std::string readLineStr;
		std::vector<std::string> splitedStrArray;
		while(getline(ifs, readLineStr)){
			SplitString(splitedStrArray, readLineStr, "=");
			if(splitedStrArray.size() != 2) continue;
			Config::configMap.emplace(splitedStrArray[0], splitedStrArray[1]);
		}
	}

public:

	static void SetConfigFilePath(std::string_view filePath){
		Config::configFilePath = filePath;
	}

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