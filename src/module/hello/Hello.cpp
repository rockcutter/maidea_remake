#include "Hello.h"
#include <boost/format.hpp>

namespace Module {

	Hello::Hello():
		ModuleBase(
			HELLO_MODULE_NAME, HELLO_COMMAND,
			boost::program_options::options_description()),
		discordio(HELLO_MODULE_NAME)
	{}


	void Hello::Send(const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channelID) {
		this->discordio.SendWithName(channelID, "Hello!");
	}

	void Hello::Handler(const SleepyDiscord::Message& message) {
		this->Send(message.channelID);
	}

	void Hello::InteractionHandler(SleepyDiscord::Interaction& interaction) {

		SleepyDiscord::Interaction::Response<> response;
		response.type = SleepyDiscord::InteractionCallbackType::ChannelMessageWithSource;
		response.data.content = this->discordio.CombineName("Hello!");
		auto clientPtr = this->discordio.GetClientPtr().lock();
		clientPtr->createInteractionResponse(interaction.ID, interaction.token, response);
		return;
	}

	void Hello::InitializeAppCommand() {
		this->appCommand.name = "hello";
		this->appCommand.description = "say hello";		
	}
}