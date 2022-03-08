#pragma once
#include "sleepy_discord/sleepy_discord.h"
#include "module/base/ModuleBase.h"
#include "module/io/IOModule.h"
#include <string>

namespace Module {
	class Role : public ModuleBase {
	private:
		DiscordIO discordIO;
		struct marker{
			const std::string GRANT{"grant"};
			const std::string REMOVE{"remove"};
		} MARKER;
		static std::vector<std::string> MentionedRoleID(const std::string&);
	public:
		Role();
		void Handler(const SleepyDiscord::Message& msg)override {}
		void Handler(const SleepyDiscord::Channel& channel, const SleepyDiscord::Message& message, const SleepyDiscord::User& user, const SleepyDiscord::Emoji& emoji);
		bool Add(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& serverID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& userID, const SleepyDiscord::Snowflake<SleepyDiscord::Role>& roleID);
		bool AddUsingMarker(const SleepyDiscord::Message& message, const SleepyDiscord::Snowflake<SleepyDiscord::Server>& serverID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& userID);
		bool Remove(const SleepyDiscord::Snowflake<SleepyDiscord::Server>& serverID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& userID, const SleepyDiscord::Snowflake<SleepyDiscord::Role>& roleID);
		bool RemoveUsingMarker(const SleepyDiscord::Message& message, const SleepyDiscord::Snowflake<SleepyDiscord::Server>& serverID, const SleepyDiscord::Snowflake<SleepyDiscord::User>& userID);

	};
}

