#include "Hello.h"
#include "client/MyClient.h"
#include <boost/format.hpp>

namespace Module {
	Hello::Hello():
		ModuleBase(
			Hello::MODULE_NAME
		)
	{}


	void Hello::Send(const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channelID) {
		this->DiscordOut(channelID, Hello::MODULE_NAME);
	}

	void Hello::InteractionHandler(SleepyDiscord::Interaction& interaction) {

		SleepyDiscord::Interaction::Response<> response;
		response.type			 = SleepyDiscord::InteractionCallbackType::ChannelMessageWithSource;
		response.data.content	 = this->JoinModuleName(Hello::HELLO_MESSAGE);
		auto clientPtr			 = MyClientClass::GetInstance();
		clientPtr->createInteractionResponse(interaction.ID, interaction.token, response);
		return;
	}

	void Hello::InitializeAppCommand() {
		SleepyDiscord::AppCommand::Option appCommand;
		appCommand.name			= Hello::COMMAND;
		appCommand.description	= Hello::COMMAND_DESCRIPTION;		
		this->SetAppCommand(std::move(appCommand));
	}
}