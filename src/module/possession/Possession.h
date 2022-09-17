#pragma once
#include <string>
#include "sleepy_discord/sleepy_discord.h"
#include "module/base/ModuleBase.h"
#include "module/base/SlashCommandProcessorBase.h"

namespace Module {
	class Possession : public ModuleBase , public SlashCommandProcessorBase{
	private:
		bool possession;
		static std::vector<SleepyDiscord::Snowflake<SleepyDiscord::User>> privilegedUser;
		SleepyDiscord::Snowflake<SleepyDiscord::Channel> targetChannelID;
	public:
		struct Info {
			const static std::string MODULENAME;
			const static std::string COMMAND;
			const static std::string COMMAND_END;
			const static std::string COMMAND_SAY;
			const static std::string COMMAND_DESCRIPTION;			
			const static std::string COMMAND_START;
		};
		static void RegisterPrivilegedUser(const SleepyDiscord::Snowflake<SleepyDiscord::User>&);
		Possession();
		void Handler(const SleepyDiscord::Message& message) {};
		void PlainTextHandler(const SleepyDiscord::Message& message) {};
		void Start(const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channelID);
		void Stop();
		void InitializeAppCommand() override;
		void InteractionHandler(SleepyDiscord::Interaction& interaction) override;
	};
}