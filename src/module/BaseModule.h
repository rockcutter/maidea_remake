#pragma once
#include <string>
#include "sleepy_discord/sleepy_discord.h"

class BaseModule {
protected:
	std::string moduleName;
public:
	virtual void Handler(SleepyDiscord::Message message) = 0;
};

