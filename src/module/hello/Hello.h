#pragma once
#include <string>
#include <boost/program_options.hpp>
#include "sleepy_discord/sleepy_discord.h"
#include "module/io/IOModule.h"
#include "module/base/ModuleBase.h"

namespace Module {
	constexpr char HELLO_MODULE_NAME[] = "Hello";
	constexpr char HELLO_COMMAND[] = "hello";

	class Hello : public ModuleBase {
	private:
		IOModule iomodule;
	public:
		Hello();
		void Send(const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channelID);
		void Handler(const SleepyDiscord::Message& message) override;
	};
}
