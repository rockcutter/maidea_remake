#include <unordered_map>
#include <vector>
#include <boost/algorithm/string.hpp>
#include "CommandHandler.h"
#include "module/hello/Hello.h"
#include "module/timer/timer.h"


namespace Handler {
	std::unordered_map<std::string, std::unique_ptr<Module::ModuleBase>> commandMap = std::move(FillCommandMap());

	std::unordered_map<std::string, std::unique_ptr<Module::ModuleBase>> FillCommandMap() {
		std::unordered_map<std::string, std::unique_ptr<Module::ModuleBase>> m;
		std::vector<std::unique_ptr<Module::ModuleBase>> moduleArray;

		//ここで追加したモジュールのインスタンスをemplace_back
		moduleArray.emplace_back(new Module::Hello());
		moduleArray.emplace_back(new Module::Timer());

		//ここまで
		for (auto& p : moduleArray) {
			m[p->GetCommand()] = std::move(p);
		}
		return m;
	}

	void CommandHandler(SleepyDiscord::Message message) {
		if (message.author.bot) {
			return;
		}
		std::vector<std::string> tmp;
		boost::algorithm::split(tmp, message.content, boost::is_space());
		tmp.at(0).erase(0, 1);

		if (commandMap.count(tmp.at(0)) == 0) {
			return;
		}

		commandMap.at(tmp.at(0))->Handler(message);
		return;
	}
}