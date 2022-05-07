#include "Hello.h"
#include "client/MyClient.h"
#include <boost/format.hpp>

namespace Module {
	const std::string Hello::Info::COMMAND{ "hello" };
	const std::string Hello::Info::MODULE_NAME{ "Hello" };
	const std::string Hello::Info::HELLO_MESSAGE{ "Hello!" };
	const std::string Hello::Info::COMMAND_DESCRIPTION{ "say hello" };

	Hello::Hello():
		ModuleBase(
			Hello::Info::MODULE_NAME, 
			Hello::Info::COMMAND,
			boost::program_options::options_description())
	{}


	void Hello::Send(const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channelID) {
		this->DiscordOut(channelID, Hello::Info::MODULE_NAME);
	}

	void Hello::Handler(const SleepyDiscord::Message& message) {
		this->Send(message.channelID);
	}

	void Hello::InteractionHandler(SleepyDiscord::Interaction& interaction) {

		SleepyDiscord::Interaction::Response<> response;
		response.type = SleepyDiscord::InteractionCallbackType::ChannelMessageWithSource;
		response.data.content = this->JoinModuleName(Hello::Info::HELLO_MESSAGE);
		auto clientPtr = MyClientClass::GetInstance();
		clientPtr->createInteractionResponse(interaction.ID, interaction.token, response);
		return;
	}

	void Hello::InitializeAppCommand() {
		this->appCommand.name = Hello::Info::COMMAND;
		this->appCommand.description = Hello::Info::COMMAND_DESCRIPTION;		
	}
}