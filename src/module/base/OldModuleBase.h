#pragma once
#include <string>
#include "sleepy_discord/sleepy_discord.h"
#include <boost/program_options.hpp>

namespace Module {
	class OldModuleBase {
	private:
		SleepyDiscord::AppCommand::Option appCommand;
	protected:
		const std::string moduleName;
		std::string command;

		/// <summary>
		/// 文字列の先頭にモジュール名を結合して表示用に整形する
		/// </summary>
		std::string JoinModuleName(const std::string& str);
	public:
		OldModuleBase(
			const std::string& moduleName,
			const std::string& command
		);

		//handlers
		virtual void InteractionHandler(SleepyDiscord::Interaction& interaction) {}
		virtual void PlainTextHandler(const SleepyDiscord::Message& message)	 {}
		virtual void Handler(const SleepyDiscord::Message& message)				 {}

		//setter
		void SetAppCommand(SleepyDiscord::AppCommand::Option&& appCommand);

		//getter
		const std::string& GetModuleName()					 { return this->moduleName; }
		const std::string& GetCommand()						 { return this->command; }
		SleepyDiscord::AppCommand::Option& GetAppCommand()	 { return this->appCommand; }

		/// <summary>
		/// モジュールがインスタンス化されるよりも前に呼び出される。
		/// AppCommandを設定するときはこのメソッドをオーバーライドしてその中でSetAppCommandを呼べばよい
		/// </summary>
		virtual void InitializeAppCommand() {}


		/// <summary>
		/// 文字列をdiscordで送信する
		/// </summary>
		template <class T>
		SleepyDiscord::ObjectResponse<SleepyDiscord::Message> DiscordOut(
			const SleepyDiscord::Snowflake<SleepyDiscord::Channel>& channelID,
			const T& str)
		{
			std::stringstream ss{};
			ss << str;
			std::shared_ptr<MyClientClass> client = MyClientClass::GetInstance();
			return client->sendMessage(channelID, this->JoinModuleName(ss.str()));
		}

	};

}
