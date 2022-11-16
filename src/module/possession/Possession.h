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
		//constants
		constexpr static std::string_view MODULENAME{"Possession"};
		constexpr static std::string_view COMMAND{"possession"};
		constexpr static std::string_view COMMAND_END{"end"};
		constexpr static std::string_view COMMAND_SAY{"say"};
		constexpr static std::string_view COMMAND_DESCRIPTION{"possess this bot"};			
		constexpr static std::string_view COMMAND_START{"start"};

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