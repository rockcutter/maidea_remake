#include "IOModule.h"

std::weak_ptr<MyClientClass> IOModule::client;

IOModule::IOModule(std::string moduleName) : displayModuleName(moduleName) {}

void IOModule::RegisterClient(std::weak_ptr<MyClientClass> p) {
	IOModule::client = p;
}

std::string IOModule::Send(SleepyDiscord::Snowflake<SleepyDiscord::Channel> channelID, std::string message) {
	std::string str = "`" + this->displayModuleName + "`\n" + message;
	std::shared_ptr<MyClientClass> s;
	if (!(s = this->client.lock())) {
		return "";
	}
	s->sendMessage(channelID, str);
	return str;
}
