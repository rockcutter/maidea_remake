#pragma once
#include <string>
#include "sleepy_discord/sleepy_discord.h"
#include <boost/program_options.hpp>

namespace Module {
	class ModuleBase {
	protected:
		std::string moduleName;
		std::string command;
		boost::program_options::option_description options;
	public:
		ModuleBase(std::string moduleName, std::string command, boost::program_options::option_description opt);
		virtual void Handler(SleepyDiscord::Message message) = 0;
	};
}
