#include "Hello.h"
#include <boost/format.hpp>

namespace Module {

	Hello::Hello():
		ModuleBase(
			"Hello", 
			"hello",
			boost::program_options::options_description())
	{}


	void Hello::Send(const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channelID) {
		this->DiscordOut(channelID, "Hello!");
	}

	void Hello::Handler(const SleepyDiscord::Message& message) {
		this->Send(message.channelID);
	}

	void Hello::InteractionHandler(SleepyDiscord::Interaction& interaction) {

		SleepyDiscord::Interaction::Response<> response;
		response.type = SleepyDiscord::InteractionCallbackType::ChannelMessageWithSource;
		response.data.content = this->JoinModuleName("Hello!");
		auto clientPtr = MyClientClass::GetInstance();
		clientPtr->createInteractionResponse(interaction.ID, interaction.token, response);
		return;
	}

	void Hello::InitializeAppCommand() {
		this->appCommand.name = "hello";
		this->appCommand.description = "say hello";		
	}
}