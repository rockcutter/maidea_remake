#pragma once
#include "sleepy_discord/sleepy_discord.h"
#include "handler/Handler.h"

class MyClientClass : public SleepyDiscord::DiscordClient {
private:
	Handler::CommandHandler cmdHandler;
	Handler::PlainTextHandler txtHandler;
public:
	using SleepyDiscord::DiscordClient::DiscordClient;
	void onReady(SleepyDiscord::Ready) override;
	void onMessage(SleepyDiscord::Message message) override;
	void onReaction(SleepyDiscord::Snowflake<SleepyDiscord::User> userID, SleepyDiscord::Snowflake<SleepyDiscord::Channel> channelID, SleepyDiscord::Snowflake<SleepyDiscord::Message> messageID, SleepyDiscord::Emoji emoji) override;
};

