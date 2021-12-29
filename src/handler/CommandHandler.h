#pragma once
#include <memory>
#include <unordered_map>
#include <string>
#include "sleepy_discord/sleepy_discord.h"
#include "module/base/ModuleBase.h"

namespace Handler {
	constexpr int COMMAND_SPECIFIER_COUNT = 4;
	constexpr char* COMMAND_SPECIFIER[COMMAND_SPECIFIER_COUNT] = { ">", "!", "\\", "?"};
	
	std::unordered_map<std::string, std::unique_ptr<Module::ModuleBase>> FillCommandMap();
	void CommandHandler(SleepyDiscord::Message message);
}
