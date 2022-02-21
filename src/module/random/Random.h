#pragma once
#include "sleepy_discord/sleepy_discord.h"
#include "module/base/ModuleBase.h"
#include "module/io/IOModule.h"

namespace Module {
	class Random : public ModuleBase {
		IOModule iomodule;
	public:
		Random();
		void Handler(const SleepyDiscord::Message& message)override ;
		void PlainTextHandler(const SleepyDiscord::Message& message) override;
	};
}
