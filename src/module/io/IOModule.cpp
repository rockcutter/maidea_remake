#include "IOModule.h"
#include <sstream>
#include <boost/format.hpp>

namespace Module {	
	std::weak_ptr<MyClientClass> DiscordIO::client;
	
	DiscordIO::DiscordIO(): moduleName("") {}
	DiscordIO::DiscordIO(std::string moduleName): moduleName(moduleName) {}
	
	std::string DiscordIO::CombineName(const std::string& str) {
		return (boost::format("`%1%`\n%2%") % this->moduleName % str).str();
	}

	std::string DiscordIO::Send(const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channelID, const std::string& message) {
		if (this->client.expired()) {
			return "";
		}
		std::shared_ptr<MyClientClass> s = this->client.lock();
		s->sendMessage(channelID, message);
		return message;
	}

	std::string DiscordIO::Send(const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channelID, const boost::program_options::options_description& opt) {
		if (this->client.expired()) {
			return "";
		}
		std::shared_ptr<MyClientClass> s = this->client.lock();
		std::stringstream ss;
		ss << opt;
		s->sendMessage(channelID, ss.str());
		return ss.str();
	}

	std::string DiscordIO::SendWithName(const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channelID, const std::string& message) {
		return this->Send(channelID, this->CombineName(message));
	}

	std::string DiscordIO::SendWithName(const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channelID, const boost::program_options::options_description& opt) {
		if (this->client.expired()) {
			return "";
		}
		std::shared_ptr<MyClientClass> s = this->client.lock();
		std::stringstream ss;
		ss << boost::format("`%1%`\n") % this->moduleName;
		ss << opt;
		s->sendMessage(channelID, ss.str());
		return ss.str();
	}
}

std::weak_ptr<MyClientClass> IOModule::client;

IOModule::IOModule(std::string moduleName) : displayModuleName(moduleName) {}

void IOModule::RegisterClient(std::weak_ptr<MyClientClass> p) {
	IOModule::client = p;
}

std::string IOModule::Send(const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channelID, const std::string& message) {
	std::string str = "`" + this->displayModuleName + "`\n" + message;
	std::shared_ptr<MyClientClass> s;
	if (!(s = this->client.lock())) {
		return "";
	}
	s->sendMessage(channelID, str);
	return str;
}

std::string IOModule::Send(const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channelID, const boost::program_options::options_description& opt) {
	std::stringstream ss;
	ss << opt;
	return this->Send(channelID, ss.str());
}

void IOModule::DeleteMessage(const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channelID, const SleepyDiscord::Snowflake<SleepyDiscord::Message>& messageID) {
	try {
		if (std::shared_ptr<MyClientClass> p = this->client.lock()) {
			p->deleteMessage(channelID, messageID);
		}
	}
	catch (SleepyDiscord::ErrorCode) {
		this->Send(channelID, "missing permission to delete the message");
	}
}

void IOModule::AddReaction(const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channelID, const SleepyDiscord::Snowflake<SleepyDiscord::Message>& messageID, const std::string& emoji) {
	if (std::shared_ptr<MyClientClass> p = this->client.lock()) {
		p->addReaction(channelID, messageID, emoji);
	}
}
