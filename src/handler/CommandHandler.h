#pragma once
#include "sleepy_discord/sleepy_discord.h"

namespace Handler {
	constexpr int COMMAND_SPECIFIER_COUNT = 4;
	constexpr char* COMMAND_SPECIFIER[COMMAND_SPECIFIER_COUNT] = { ">", "!", "\\", "?"};
	
	void CommandHandler(SleepyDiscord::Message message);
}
