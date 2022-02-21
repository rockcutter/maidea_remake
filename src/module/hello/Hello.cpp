#include "Hello.h"
#include <boost/format.hpp>

namespace Module {
	Hello::Hello(): ModuleBase(HELLO_MODULE_NAME, HELLO_COMMAND, boost::program_options::options_description()), iomodule(HELLO_MODULE_NAME){}

	void Hello::Send(const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channelID) {
		this->iomodule.Send(channelID, "Hello!");
	}

	void Hello::Handler(const SleepyDiscord::Message& message) {
		this->Send(message.channelID);
	}
}