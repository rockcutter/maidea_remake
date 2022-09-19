#pragma once
#include <sleepy_discord/sleepy_discord.h>

namespace Module {
	class TextProcessorBase {
	public:
		/// <summary>
		/// 流れてきたメッセージを受け取って処理する
		/// </summary>
		virtual void TextHandler(const SleepyDiscord::Message& message) = 0;
	};
}
