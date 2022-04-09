#pragma once
#include "sleepy_discord/sleepy_discord.h"
#include "module/base/ModuleBase.h"
#include "module/io/IOModule.h"
#include <string>
#include <functional>

namespace Module {

	class Role : public ModuleBase {
	private:
		struct Operation {
			struct Arguments {
				Role* objPtr;
				SleepyDiscord::Snowflake<SleepyDiscord::Server> serverID;
				SleepyDiscord::Snowflake<SleepyDiscord::User> userID;
				SleepyDiscord::Snowflake<SleepyDiscord::Role> roleID;
			};
			using RoleOperationType = const std::function<SleepyDiscord::BoolResponse(Arguments)>;
		};
		struct Marker {
			const static std::string GRANT;
			const static std::string REMOVE;
		};

		DiscordIO discordIO;
		static std::vector<std::string> MentionedRoleID(const std::string&);
	public:
		Role();		

		void Handler(const SleepyDiscord::Message& msg)override {}

		void Handler(
			const SleepyDiscord::Channel& channel,
			const SleepyDiscord::Message& message,
			const SleepyDiscord::User& user,
			const SleepyDiscord::Emoji& emoji);

		void InteractionHandler(SleepyDiscord::Interaction& interaction) {};

		bool ExecuteMarker(
			const SleepyDiscord::Message& message,
			const SleepyDiscord::Snowflake<SleepyDiscord::Server>& serverID,
			const SleepyDiscord::Snowflake<SleepyDiscord::User>& userID, 
			const Operation::RoleOperationType operation);

		SleepyDiscord::BoolResponse Add(
			const SleepyDiscord::Snowflake<SleepyDiscord::Server>& serverID,
			const SleepyDiscord::Snowflake<SleepyDiscord::User>& userID,
			const SleepyDiscord::Snowflake<SleepyDiscord::Role>& roleID);

		SleepyDiscord::BoolResponse Remove(
			const SleepyDiscord::Snowflake<SleepyDiscord::Server>& serverID,
			const SleepyDiscord::Snowflake<SleepyDiscord::User>& userID,
			const SleepyDiscord::Snowflake<SleepyDiscord::Role>& roleID);

		void InitializeAppCommand() override {}
	};
}

