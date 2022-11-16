#pragma once
#include "sleepy_discord/sleepy_discord.h"
#include "module/base/ModuleBase.h"
#include "module/base/TextProcessorBase.h"

#include <string>
#include <functional>

namespace Module {

	class Role : public ModuleBase, public TextProcessorBase {
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
			constexpr static std::string_view GRANT{"grant"};
			constexpr static std::string_view REMOVE{"remove"};
		};
		static std::vector<std::string> MentionedRoleID(const std::string&);
	public:
		//constants
		constexpr static std::string_view COMMAND{"role"};
		constexpr static std::string_view MODULE_NAME{"Role"};

		Role();		

		void TextHandler(const SleepyDiscord::Message& msg)override {}

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

	};
}

