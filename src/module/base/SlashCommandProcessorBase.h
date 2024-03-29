#pragma once
#include <sleepy_discord/sleepy_discord.h>

namespace Module {
	class SlashCommandProcessorBase {
	private:
		std::string command;
		SleepyDiscord::AppCommand::Option appCommand;
	protected:
		void SetAppCommand(SleepyDiscord::AppCommand::Option&& appcmd) { 
			this->command = appcmd.name;
			this->appCommand = std::move(appcmd); 
		}
	public:
		SlashCommandProcessorBase():
			command(),
			appCommand()
		{}

		std::string GetCommand() const						{ return this->command; }
		SleepyDiscord::AppCommand::Option&& GetAppCommand() { return std::move(this->appCommand); }

		/// <summary>
		/// Moduleの初期化時に呼ばれる
		/// </summary>
		virtual void InitializeAppCommand()										 = 0;

		/// <summary>
		/// slashCommandが実行された時に呼ばれる
		/// </summary>
		virtual void InteractionHandler(SleepyDiscord::Interaction& interaction) = 0;

	};
}