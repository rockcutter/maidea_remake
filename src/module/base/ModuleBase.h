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
		
		SleepyDiscord::ObjectResponse<SleepyDiscord::Message> DiscordOut(
			const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channelID,
			const std::string& str
		);
		
		SleepyDiscord::ObjectResponse<SleepyDiscord::Message> ModuleBase::DiscordOut(
			const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channelID,
			const boost::program_options::options_description& opt
		);

		std::string JoinModuleName(const std::string& str);
		virtual void Handler(const SleepyDiscord::Message& message);
		virtual void PlainTextHandler(const SleepyDiscord::Message& message);
		virtual void InitializeAppCommand();
		virtual void InteractionHandler(SleepyDiscord::Interaction& interaction);
		std::string GetCommand();
		SleepyDiscord::AppCommand appCommand;
	};
	
	inline void ModuleBase::PlainTextHandler(const SleepyDiscord::Message& message){}
	inline void ModuleBase::Handler(const SleepyDiscord::Message& message) {}
	inline void ModuleBase::InitializeAppCommand() {}
	inline void ModuleBase::InteractionHandler(SleepyDiscord::Interaction& interaction){}

	inline std::string ModuleBase::GetCommand() {
		return this->command;
	}
}
