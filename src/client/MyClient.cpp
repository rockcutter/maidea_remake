#include "MyClient.h"
#include "handler/MessageHandler.h"
#include "util/ConsoleOut.h"


void MyClientClass::onMessage(SleepyDiscord::Message message) {	
	Handler::MessageHandler(message);
	return;
}

void MyClientClass::onReady(SleepyDiscord::Ready readyData) {
	Util::ConsoleOut("Ready");
	return;
}

void MyClientClass::onReaction(
	SleepyDiscord::Snowflake<SleepyDiscord::User> userID, 
	SleepyDiscord::Snowflake<SleepyDiscord::Channel> channelID, 
	SleepyDiscord::Snowflake<SleepyDiscord::Message> messageID, 
	SleepyDiscord::Emoji emoji) {
	
	SleepyDiscord::User user = getUser(userID);
	if (user.bot) {
		return;
	}

	//repeat
	if (emoji.name == "🔁") {
		SleepyDiscord::Message message;
		addReaction(channelID, messageID, emoji.name);
		getMessage(channelID, messageID).cast(message);
		this->onMessage(message);
	}

	return;
}

