#pragma once
#include <string>
#include "sleepy_discord/sleepy_discord.h"
#include "module/base/ModuleBase.h"
#include "module/io/IOModule.h"

namespace Module {
	class Possession : public ModuleBase {
	private:
		DiscordIO discordio;
		bool possession;
		static std::vector<SleepyDiscord::Snowflake<SleepyDiscord::User>> privilegedUser;
		SleepyDiscord::Snowflake<SleepyDiscord::Channel> targetChannelID;
	public:
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