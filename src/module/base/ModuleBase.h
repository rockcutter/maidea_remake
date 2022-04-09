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
		static std::vector<SleepyDiscord::AppCommand> allAppCommands;
		ModuleBase(const std::string& moduleName, const std::string& command, boost::program_options::options_description opt);
		virtual void Handler(const SleepyDiscord::Message& message) = 0;
		virtual void PlainTextHandler(const SleepyDiscord::Message& message);
		virtual void InitializeAppCommand() = 0;
		virtual void InteractionHandler(SleepyDiscord::Interaction& interaction) = 0;
		std::string GetCommand();
		SleepyDiscord::AppCommand appCommand;
	};
	
	inline void ModuleBase::PlainTextHandler(const SleepyDiscord::Message& message){}

	inline std::string ModuleBase::GetCommand() {
		return this->command;
	}
}
