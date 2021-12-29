#include "Hello.h"
#include <boost/format.hpp>

namespace Module {
	Hello::Hello(): ModuleBase(HELLO_MODULE_NAME, HELLO_COMMAND, boost::program_options::option_description()), iomodule(HELLO_MODULE_NAME){}

	void Hello::Send(SleepyDiscord::Snowflake<SleepyDiscord::Channel> channelID) {
		this->iomodule.Send(channelID, "Hello!");
	}

	void Hello::Handler(SleepyDiscord::Message message) {
		this->Send(message.channelID);
	}
}