#pragma once
#include <sleepy_discord/sleepy_discord.h>

namespace Module {
	class TextProcessorBase {
	public:
		/// <summary>
		/// ����Ă������b�Z�[�W���󂯎���ď�������
		/// </summary>
		virtual void TextHandler(const SleepyDiscord::Message& message) = 0;
	};
}
