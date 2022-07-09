#pragma once
#include "module/base/ModuleBase.h"
#include "client/MyClient.h"

//こちらが完成したらCMakelists.txtの作成 & モジュールの登録
//CMakelists.txt -> src/module/example/CMakeLists.txtへ
//モジュールの登録 -> src/client/RegisterModule.hへ

namespace Module {
	class ExampleModule : public ModuleBase {
	public:
		ExampleModule() 
			: ModuleBase(
				"Module name here",
				"command here"
			)
		{}

		//ModuleBaseの第二引数のコマンドと一致するコマンドが呼ばれた時、この関数が呼ばれる
		void Handler(const SleepyDiscord::Message& message) override {
			//ここに処理を記入

			//これでDiscordClientを得ることができる
			//auto client = MyClient::GetInstance();
		}

		//slash commandでコマンドが呼ばれた時にこの関数が呼ばれる
		void InteractionHandler(SleepyDiscord::Interaction& interaction) override {
			//ここにslash commandが呼ばれた時の処理を記入
		}

		//すべてのメッセージはここを通る
		//コマンド形式で呼ばれてない文字列を処理したいときに使う
		void PlainTextHandler(const SleepyDiscord::Message& message) override {
			//ここに処理を記入
		}

		//slash commandに関する初期化処理、登録処理を行う際に使用する
		//プログラムの初めに一度呼ばれる
		void InitializeAppCommand() override {
			//ここに処理を記入
			//追加方法についてはhttps://yourwaifu.dev/sleepy-discord/docs/slash-commandsを参照
			//登録するAppCommandは基底クラスのModuleBase::AppCommandを使用してください!
			// this->AppCommand
		}
	};
}
