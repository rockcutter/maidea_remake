#pragma once
#include <vector>
#include <memory>
#include <stdexcept>
#include "module/base/ModuleBase.h"
#include "module/base/TextProcessorBase.h"
#include "module/base/SlashCommandProcessorBase.h"
#include "module/hello/Hello.h"
#include "module/timer/timer.h"
#include "module/urlshortening/URLShortening.h"
#include "module/checklist/Checklist.h"
#include "module/random/Random.h"
#include "module/role/Role.h"
#include "module/possession/Possession.h"
#include "util/MultipleUnique.h"

//ここでモジュールを登録する
class ModulePackager {
public:
	
	//ここにはSlashCommandを実装したModuleを登録する テンプレートパラメータに書き加えるだけでよい(可変長パラメータ)
	static void GetSlashCommandProcessors(std::vector<std::unique_ptr<Module::SlashCommandProcessorBase>>& modules) {
		MultipleUnique<
			Module::SlashCommandProcessorBase,
			Module::Checklist,
			Module::Hello,
			Module::Timer,
			Module::Random,
			Module::Possession,
			Module::URLShortening
		>::Make(modules);
	}
	
	//ここにはTextCommandを処理するHandler関数を実装したModuleを登録する テンプレートパラメータに書き加えるだけでよい(可変長パラメータ)
	//static void GetTextCommandProcessors(std::vector<std::unique_ptr<Module::TextProcessorBase>>& modules) {
	//	MultipleUnique<
	//		Module::TextProcessorBase,
	//		Module::Hello
	//	>::Make(modules);
	//}

	//ここにはPlainTextHandlerを実装したModuleを登録する テンプレートパラメータに書き加えるだけでよい(可変長パラメータ)
	static void GetTextProcessors(std::vector<std::unique_ptr<Module::TextProcessorBase>>& modules) {
		MultipleUnique<
			Module::TextProcessorBase,
			Module::Random,
			Module::Checklist
		>::Make(modules);
	}
};



