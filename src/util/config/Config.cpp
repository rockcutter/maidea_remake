#include "Config.h"

constexpr char CONFIG_SPLITTER = '=';

namespace Util {
	std::unique_ptr<std::map<std::string, std::string>> LoadConfig(std::string filePath) {
		std::unique_ptr<std::map<std::string, std::string>> map(new std::map<std::string, std::string>());
		std::ifstream ifs(filePath);
		std::string buf;

		std::string key;
		std::string value;

		if (!ifs) {
			throw std::runtime_error("config file not found");
		}
		while (std::getline(ifs, buf)) {
			//‹ó”’Á‹Ž
			for (std::string::size_type spacePos = buf.find_first_of(" "); spacePos != std::string::npos;
				spacePos = buf.find_first_of(" ")) {
				buf.erase(spacePos, 1);
			}

			//splitter‚ð’T‚·
			std::string::size_type splitterPos = buf.find_first_of(CONFIG_SPLITTER);
			if (splitterPos == std::string::npos) {
				continue;
			}

			//•ªŠ„
			key = buf.substr(0, splitterPos);
			value = buf.substr(splitterPos + 1, buf.length() - splitterPos);
			map->emplace(key, value);
		}
		if (map->empty()) {
			return nullptr;
		}

		return map;
	}
}