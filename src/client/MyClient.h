#pragma once
#include "sleepy_discord/sleepy_discord.h"

class MyClientClass : public SleepyDiscord::DiscordClient {

public :
	using SleepyDiscord::DiscordClient::DiscordClient;
	void onReady(SleepyDiscord::Ready) override;
	void onMessage(SleepyDiscord::Message message) override;
	void onReaction(SleepyDiscord::Snowflake<SleepyDiscord::User> userID, SleepyDiscord::Snowflake<SleepyDiscord::Channel> channelID, SleepyDiscord::Snowflake<SleepyDiscord::Message> messageID, SleepyDiscord::Emoji emoji) override;
};

