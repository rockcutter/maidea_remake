#pragma once
#include <string>
#include "sleepy_discord/sleepy_discord.h"
#include <boost/program_options.hpp>

namespace Module {
	class ModuleBase {
	protected:
		const std::string moduleName;

		/// <summary>
		/// 文字列の先頭にモジュール名を結合して表示用に整形する
		/// </summary>
		std::string JoinModuleName(const std::string& str);
	public:
		ModuleBase(
			const std::string& moduleName
		);
		//getter
		const std::string& GetModuleName() { return this->moduleName; }

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
