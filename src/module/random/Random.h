#pragma once
#include "sleepy_discord/sleepy_discord.h"
#include "module/base/ModuleBase.h"

namespace Module {
	class Random : public ModuleBase {
	public:
		static struct Info {
			static const std::string MODULE_NAME;
			static const std::string COMMAND;
			static const std::string COMMAND_DESCRIPTION;
			static const int DEFAULT_LOWER_LIMIT;
			static const int DEFAULT_UPPER_LIMIT;
		};
		Random();
		void Handler(const SleepyDiscord::Message& message)override ;
		void PlainTextHandler(const SleepyDiscord::Message& message) override;
		void InteractionHandler(SleepyDiscord::Interaction& interaction) override;
		void InitializeAppCommand() override;
	};
}
