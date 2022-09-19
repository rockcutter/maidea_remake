#pragma once
#include <string>
#include <boost/program_options.hpp>
#include "sleepy_discord/sleepy_discord.h"
#include "module/base/ModuleBase.h"
#include "module/base/SlashCommandProcessorBase.h"
#include "SlashCommandProcessorBase.h"

namespace Module {
	class Hello : public ModuleBase, public SlashCommandProcessorBase{
	public:
		//constant
		static const std::string MODULE_NAME;
		static const std::string COMMAND;
		static const std::string HELLO_MESSAGE;
		static const std::string COMMAND_DESCRIPTION;

		Hello();
		void Send(const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channelID);
		void InteractionHandler(SleepyDiscord::Interaction& interaction) override;
		void InitializeAppCommand() override;
	};
}
