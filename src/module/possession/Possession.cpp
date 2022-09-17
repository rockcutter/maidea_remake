#include "Possession.h"
#include "client/MyClient.h"

namespace Module {
	
	const std::string Possession::MODULENAME			= {"Possession"};
	const std::string Possession::COMMAND				= {"possession"};
	const std::string Possession::COMMAND_START			= {"start"};
	const std::string Possession::COMMAND_END			= {"end"};
	const std::string Possession::COMMAND_SAY			= {"say"};
	const std::string Possession::COMMAND_DESCRIPTION	= {"possess this bot"};

	std::vector<SleepyDiscord::Snowflake<SleepyDiscord::User>> Possession::privilegedUser{};

	void Possession::RegisterPrivilegedUser(const SleepyDiscord::Snowflake<SleepyDiscord::User>& userID) {
		Possession::privilegedUser.push_back(userID);
	}

	Possession::Possession():
		ModuleBase(MODULENAME),
		possession(false),
		targetChannelID()
	{}

	void Possession::InitializeAppCommand() {
		using CmdOption = SleepyDiscord::AppCommand::Option;
		
		SleepyDiscord::AppCommand::Option appCommand;

		appCommand.name			= COMMAND;
		appCommand.description	= COMMAND_DESCRIPTION;
		
		CmdOption start;
		start.type			= CmdOption::Type::SUB_COMMAND;
		start.name			= COMMAND_START;
		start.description	= COMMAND_DESCRIPTION;
		
		CmdOption end;
		end.type		= CmdOption::Type::SUB_COMMAND;
		end.name		= COMMAND_END;
		end.description = COMMAND_DESCRIPTION;

		CmdOption say;
		say.type		= CmdOption::Type::SUB_COMMAND;
		say.name		= COMMAND_SAY;
		say.description = COMMAND_DESCRIPTION;

		CmdOption statement;
		statement.isRequired	= true;
		statement.name			= "statement";
		statement.description	= "statement";
		statement.type			= CmdOption::Type::STRING;

		say.options.push_back(std::move(statement));
		
		appCommand.options.emplace_back(std::move(say));		
		appCommand.options.emplace_back(std::move(start));		
		appCommand.options.emplace_back(std::move(end));		

		this->SetAppCommand(std::move(appCommand));
	}

	void Possession::Start(const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channelID) {
		this->possession		= true;
		this->targetChannelID	= channelID;
		return ;
	}

	void Possession::Stop() {
		this->possession = false;
		return;
	}

	void Possession::InteractionHandler(SleepyDiscord::Interaction& interaction) {
		using Response = SleepyDiscord::Interaction::Response<>;

		if (!([&] {// if not user is privileged user
			for (auto& user : this->privilegedUser) {
				if (interaction.member.ID == user.number()) {
					return true;
				}
			}
			return false;
			}())) 
		{
			Response response;
			response.type = SleepyDiscord::InteractionCallbackType::ChannelMessageWithSource;
			response.data.content = this->JoinModuleName("使用できません");
			
			response.data.flags = SleepyDiscord::InteractionAppCommandCallbackData::Flags::Ephemeral; //only for the user to see
			auto clientPtr = MyClientClass::GetInstance();
			clientPtr->createInteractionResponse(interaction, interaction.token, response);
			return;
		}

		for (auto& opt : interaction.data.options) {
			if (opt.name == COMMAND_SAY) {
				if (!this->possession) {
					Response response;
					response.type = SleepyDiscord::InteractionCallbackType::ChannelMessageWithSource;
					response.data.content = this->JoinModuleName("有効ではありません");
					response.data.flags = SleepyDiscord::InteractionAppCommandCallbackData::Flags::Ephemeral; //only for the user to see
					auto clientPtr = MyClientClass::GetInstance();
					clientPtr->createInteractionResponse(interaction, interaction.token, response);
					return;
				}
				std::string statement;

				for (auto& opt2 : opt.options) {
					if (opt2.name == "statement") {
						if (!opt2.get<std::string>(statement)) return;
						continue;
					}
				}
				if (statement == "") return;
				auto clientPtr = MyClientClass::GetInstance();
				clientPtr->sendMessage(this->targetChannelID, statement);

				Response response;
				response.type = SleepyDiscord::InteractionCallbackType::ChannelMessageWithSource;
				response.data.content = this->JoinModuleName("送信しました");
				response.data.flags = SleepyDiscord::InteractionAppCommandCallbackData::Flags::Ephemeral; //only for the user to see
				clientPtr->createInteractionResponse(interaction, interaction.token, response);
			}
			else if (opt.name == COMMAND_START) {
				this->Start(interaction.channelID);
				Response response;
				response.type = SleepyDiscord::InteractionCallbackType::ChannelMessageWithSource;
				response.data.content = this->JoinModuleName("有効化しました");
				response.data.flags = SleepyDiscord::InteractionAppCommandCallbackData::Flags::Ephemeral; //only for the user to see
				auto clientPtr = MyClientClass::GetInstance();
				clientPtr->createInteractionResponse(interaction, interaction.token, response);
			}
			else if (opt.name == COMMAND_END) {
				this->Stop();
				Response response;
				response.type = SleepyDiscord::InteractionCallbackType::ChannelMessageWithSource;
				response.data.content = this->JoinModuleName("無効化しました");
				response.data.flags = SleepyDiscord::InteractionAppCommandCallbackData::Flags::Ephemeral; //only for the user to see
				auto clientPtr = MyClientClass::GetInstance();
				clientPtr->createInteractionResponse(interaction, interaction.token, response);
			}

		}
		return;
	}
}
