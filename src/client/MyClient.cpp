#include "MyClient.h"
//#include "handler/MessageHandler.h"
#include "util/ConsoleOut.h"
#include "handler/Handler.h"
#include "module/hello/Hello.h"
#include "module/timer/timer.h"
#include "module/urlshortening/URLShortening.h"
#include "module/checklist/Checklist.h"

Handler::MessageHandler handler;

void MyClientClass::onMessage(SleepyDiscord::Message message) {	
	handler.Execute(message);
	return;
}

void MyClientClass::onReady(SleepyDiscord::Ready readyData) {
	handler.RegisterModuleIntoCommandHandler(std::make_unique<Module::Hello>());
	handler.RegisterModuleIntoCommandHandler(std::make_unique<Module::Timer>());
	handler.RegisterModuleIntoCommandHandler(std::make_unique<Module::URLShortening>());
	handler.RegisterModuleIntoCommandHandler(std::make_unique<Module::Checklist>());
	
	handler.RegisterModuleIntoPlainTextHandler(std::make_unique<Module::Checklist>());

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

