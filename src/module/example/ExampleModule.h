#pragma once
#include "module/base/ModuleBase.h"
#include "client/MyClient.h"

//�����炪����������CMakelists.txt�̍쐬 & ���W���[���̓o�^
//CMakelists.txt -> src/module/example/CMakeLists.txt��
//���W���[���̓o�^ -> src/client/RegisterModule.h��

namespace Module {
	class ExampleModule : public ModuleBase {
	public:
		ExampleModule() 
			: ModuleBase(
				"Module name here",
				"command here"
			)
		{}

		//ModuleBase�̑������̃R�}���h�ƈ�v����R�}���h���Ă΂ꂽ���A���̊֐����Ă΂��
		void Handler(const SleepyDiscord::Message& message) override {
			//�����ɏ������L��

			//�����DiscordClient�𓾂邱�Ƃ��ł���
			//auto client = MyClient::GetInstance();
		}

		//slash command�ŃR�}���h���Ă΂ꂽ���ɂ��̊֐����Ă΂��
		void InteractionHandler(SleepyDiscord::Interaction& interaction) override {
			//������slash command���Ă΂ꂽ���̏������L��
		}

		//���ׂẴ��b�Z�[�W�͂�����ʂ�
		//�R�}���h�`���ŌĂ΂�ĂȂ�������������������Ƃ��Ɏg��
		void PlainTextHandler(const SleepyDiscord::Message& message) override {
			//�����ɏ������L��
		}

		//slash command�Ɋւ��鏉���������A�o�^�������s���ۂɎg�p����
		//�v���O�����̏��߂Ɉ�x�Ă΂��
		void InitializeAppCommand() override {
			//�����ɏ������L��
			//�ǉ����@�ɂ��Ă�https://yourwaifu.dev/sleepy-discord/docs/slash-commands���Q��
			//�o�^����AppCommand�͊��N���X��ModuleBase::AppCommand���g�p���Ă�������!
			// this->AppCommand
		}
	};
}
