#pragma once
#include "sleepy_discord/sleepy_discord.h"

class MyClientClass : public SleepyDiscord::DiscordClient {

public :
	using SleepyDiscord::DiscordClient::DiscordClient;
	void onReady(SleepyDiscord::Ready) override;
	void onMessage(SleepyDiscord::Message message) override;
};
