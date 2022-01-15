#pragma once
#include <string>
#include "sleepy_discord/sleepy_discord.h"
#include <boost/program_options.hpp>

namespace Module {
	class ModuleBase {
	protected:
		const std::string moduleName;
		const std::string command;
		boost::program_options::options_description options;
	public:
		ModuleBase(const std::string& moduleName, const std::string& command, boost::program_options::options_description opt);
		virtual void Handler(SleepyDiscord::Message message) = 0;
		virtual void PlainTextHandler(SleepyDiscord::Message message);
		std::string GetCommand();
	};
	
	inline void ModuleBase::PlainTextHandler(SleepyDiscord::Message message){}

	inline std::string ModuleBase::GetCommand() {
		return this->command;
	}
}
