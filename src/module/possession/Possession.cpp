#include "Possession.h"

namespace Module {
	
	std::vector<SleepyDiscord::Snowflake<SleepyDiscord::User>> Possession::privilegedUser{};

	void Possession::RegisterPrivilegedUser(const SleepyDiscord::Snowflake<SleepyDiscord::User>& userID) {
		Possession::privilegedUser.push_back(userID);
	}

	Possession::Possession():
		ModuleBase("Possession", "possession", boost::program_options::options_description()),
		possession(false),
		targetChannelID(),
		discordio("Possession")
	{}

	void Possession::InitializeAppCommand() {
		using CmdOption = SleepyDiscord::AppCommand::Option;

		this->appCommand.name = "possession";
		this->appCommand.description = "possess this bot";
		
		CmdOption start;
		start.type = CmdOption::Type::SUB_COMMAND;
		start.name = "start";
		start.description = "start possession";
		
		CmdOption end;
		end.type = CmdOption::Type::SUB_COMMAND;
		end.name = "end";
		end.description = "end possession";

		CmdOption say;
		say.type = CmdOption::Type::SUB_COMMAND;
		say.name = "say";
		say.description = "speak as the bot";

		CmdOption statement;
		statement.isRequired = true;
		statement.name = "statement";
		statement.description = "statement";
		statement.type = CmdOption::Type::STRING;

		say.options.push_back(std::move(statement));
		
		this->appCommand.options.push_back(std::move(say));		
		this->appCommand.options.push_back(std::move(start));		
		this->appCommand.options.push_back(std::move(end));		
		
	}

	void Possession::Start(const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channelID) {
		this->possession = true;
		this->targetChannelID = channelID;
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
			response.data.content = this->discordio.CombineName(u8"使用できません");
			response.data.flags = SleepyDiscord::InteractionAppCommandCallbackData::Flags::Ephemeral; //only for the user to see
			auto clientPtr = this->discordio.GetClientPtr().lock();
			clientPtr->createInteractionResponse(interaction, interaction.token, response);
			return;
		}

		for (auto& opt : interaction.data.options) {
			if (opt.name == "say") {
				if (!this->possession) {
					Response response;
					response.type = SleepyDiscord::InteractionCallbackType::ChannelMessageWithSource;
					response.data.content = this->discordio.CombineName(u8"有効ではありません");
					response.data.flags = SleepyDiscord::InteractionAppCommandCallbackData::Flags::Ephemeral; //only for the user to see
					auto clientPtr = this->discordio.GetClientPtr().lock();
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
				this->discordio.Send(this->targetChannelID, statement);
				
				Response response;
				response.type = SleepyDiscord::InteractionCallbackType::ChannelMessageWithSource;
				response.data.content = this->discordio.CombineName(u8"送信しました");
				response.data.flags = SleepyDiscord::InteractionAppCommandCallbackData::Flags::Ephemeral; //only for the user to see
				auto clientPtr = this->discordio.GetClientPtr().lock();
				clientPtr->createInteractionResponse(interaction, interaction.token, response);
			}
			else if (opt.name == "start") {
				this->Start(interaction.channelID);
				Response response;
				response.type = SleepyDiscord::InteractionCallbackType::ChannelMessageWithSource;
				response.data.content = this->discordio.CombineName(u8"有効化しました");
				response.data.flags = SleepyDiscord::InteractionAppCommandCallbackData::Flags::Ephemeral; //only for the user to see
				auto clientPtr = this->discordio.GetClientPtr().lock();
				clientPtr->createInteractionResponse(interaction, interaction.token, response);
			}
			else if (opt.name == "end") {
				this->Stop();
				Response response;
				response.type = SleepyDiscord::InteractionCallbackType::ChannelMessageWithSource;
				response.data.content = this->discordio.CombineName(u8"無効化しました");
				response.data.flags = SleepyDiscord::InteractionAppCommandCallbackData::Flags::Ephemeral; //only for the user to see
				auto clientPtr = this->discordio.GetClientPtr().lock();
				clientPtr->createInteractionResponse(interaction, interaction.token, response);
			}

		}
		return;
	}
}
