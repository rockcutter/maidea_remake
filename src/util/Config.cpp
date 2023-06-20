#include "Config.hpp"
#include <unordered_map>
#include <string>
#include <string_view>
#include <fstream>
#include "SplitString.hpp"

void Config::LoadConfig() {
    configMap.clear();

    std::ifstream ifs{std::string{Config::configFilePath}};
    if(!ifs) {
        throw std::runtime_error("config file not found");
    }

    std::string readLineStr;
    std::vector<std::string> splitedStrArray;
    while(getline(ifs, readLineStr)){
        SplitString(splitedStrArray, readLineStr, "=");
        if(splitedStrArray.size() != 2) continue;
        Config::configMap.emplace(splitedStrArray[0], splitedStrArray[1]);
    }
}

void Config::SetConfigFilePath(std::string_view filePath){
    Config::configFilePath = filePath;
}

void Config::ReloadConfig(){
    Config::LoadConfig();
}

std::unordered_map<std::string, std::string> Config::GetConfig(){
    if (!Config::isConfigLoaded) {
        Config::LoadConfig();
        Config::isConfigLoaded = true;
    }
    return Config::configMap;
}