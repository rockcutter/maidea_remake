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
	static inline std::string_view configFilePath = "";
	
	static void LoadConfig();
public:

	static void SetConfigFilePath(std::string_view filePath);
	static void ReloadConfig();
	static std::unordered_map<std::string, std::string> GetConfig();
	};