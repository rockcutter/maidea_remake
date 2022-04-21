#pragma once
#include <string>
#include <boost/program_options.hpp>
#include "sleepy_discord/sleepy_discord.h"
#include "module/io/IOModule.h"
#include "module/base/ModuleBase.h"

namespace Module {
	class Hello : public ModuleBase {
	public:
		static struct Info {
			static const std::string MODULE_NAME;
			static const std::string COMMAND;
			static const std::string HELLO_MESSAGE;
			static const std::string COMMAND_DESCRIPTION;
		};
		Hello();
		void Send(const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channelID);
		void Handler(const SleepyDiscord::Message& message) override;
		void InitializeAppCommand() override;
		void InteractionHandler(SleepyDiscord::Interaction& interaction) override;
	};
}
