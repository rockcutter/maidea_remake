#include "MyClient.h"
//#include "handler/MessageHandler.h"
#include "util/ConsoleOut.h"
#include "handler/Handler.h"
#include "module/hello/Hello.h"
#include "module/timer/timer.h"
#include "module/urlshortening/URLShortening.h"
#include "module/checklist/Checklist.h"
#include "module/random/Random.h"
#include "module/role/Role.h"

void MyClientClass::onMessage(SleepyDiscord::Message message) {
	if (this->cmdHandler.IsCommand(message.content)) {
		this->cmdHandler.Run(message);
		return;
	}
	this->txtHandler.Run(message);
	return;
}

void MyClientClass::onReady(SleepyDiscord::Ready readyData) {
	this->cmdHandler.RegisterModule(std::make_unique<Module::Hello>());
	this->cmdHandler.RegisterModule(std::make_unique<Module::Timer>());
	this->cmdHandler.RegisterModule(std::make_unique<Module::URLShortening>());
	this->cmdHandler.RegisterModule(std::make_unique<Module::Checklist>());
	this->cmdHandler.RegisterModule(std::make_unique<Module::Random>());
	
	this->txtHandler.RegisterModule(std::make_unique<Module::Checklist>());
	this->txtHandler.RegisterModule(std::make_unique<Module::Random>());

	Util::ConsoleOut("Ready");
	return;
}

void MyClientClass::onReaction(
	SleepyDiscord::Snowflake<SleepyDiscord::User> userID, 
	SleepyDiscord::Snowflake<SleepyDiscord::Channel> channelID, 
	SleepyDiscord::Snowflake<SleepyDiscord::Message> messageID, 
	SleepyDiscord::Emoji emoji) {
	SleepyDiscord::User user = getUser(userID);
	if (user.bot) return;
	SleepyDiscord::Message message = getMessage(channelID, messageID).cast();	
	SleepyDiscord::Channel channel = getChannel(channelID);
	Module::Role role;
	role.Handler(channel, message, user, emoji);
	//repeat
	if (emoji.name == "🔁") {
		SleepyDiscord::Message message;
		addReaction(channelID, messageID, emoji.name);
		getMessage(channelID, messageID).cast(message);
		this->onMessage(message);
	}
	

	return;
}

