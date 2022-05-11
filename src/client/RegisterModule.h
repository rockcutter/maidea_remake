#pragma once
#include <vector>
#include <memory>
#include <stdexcept>
#include "module/base/ModuleBase.h"
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
	using ModulePtrArray = std::vector<std::unique_ptr<Module::ModuleBase>>;
public:
	
	//ここにはSlashCommandを実装したModuleを登録する テンプレートパラメータに書き加えるだけでよい(可変長パラメータ)
	static void GetSlashCommandProcessors(ModulePtrArray& modules) {
		MultipleUnique<
			Module::ModuleBase,
			Module::Hello,
			Module::Timer,
			Module::URLShortening,
			Module::Checklist,
			Module::Random,
			Module::Possession
		>::Make(modules);
	}
	
	//ここにはTextCommandを処理するHandler関数を実装したModuleを登録する テンプレートパラメータに書き加えるだけでよい(可変長パラメータ)
	static void GetTextCommandProcessors(ModulePtrArray& modules) {
		MultipleUnique<
			Module::ModuleBase,
			Module::Hello,
			Module::Timer,
			Module::URLShortening,
			Module::Checklist,
			Module::Random
		>::Make(modules);
	}

	//ここにはPlainTextHandlerを実装したModuleを登録する テンプレートパラメータに書き加えるだけでよい(可変長パラメータ)
	static void GetTextProcessors(ModulePtrArray& modules) {
		MultipleUnique<
			Module::ModuleBase,
			Module::Checklist,
			Module::Random
		>::Make(modules);
	}
};



