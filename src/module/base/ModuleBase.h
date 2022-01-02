#pragma once
#include <string>
#include "sleepy_discord/sleepy_discord.h"
#include <boost/program_options.hpp>

namespace Module {
	class ModuleBase {
	protected:
		std::string moduleName;
		std::string command;
		boost::program_options::options_description options;
	public:
		ModuleBase(std::string moduleName, std::string command, boost::program_options::options_description opt);
		virtual void Handler(SleepyDiscord::Message message) = 0;
		std::string GetCommand();
	};

	inline std::string ModuleBase::GetCommand() {
		return this->command;
	}
}
