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

//�����Ń��W���[����o�^����
class ModulePackager {
	using ModulePtrArray = std::vector<std::unique_ptr<Module::ModuleBase>>;
public:
	
	//�����ɂ�SlashCommand����������Module��o�^���� �e���v���[�g�p�����[�^�ɏ��������邾���ł悢(�ϒ��p�����[�^)
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
	
	//�����ɂ�TextCommand����������Handler�֐�����������Module��o�^���� �e���v���[�g�p�����[�^�ɏ��������邾���ł悢(�ϒ��p�����[�^)
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

	//�����ɂ�PlainTextHandler����������Module��o�^���� �e���v���[�g�p�����[�^�ɏ��������邾���ł悢(�ϒ��p�����[�^)
	static void GetTextProcessors(ModulePtrArray& modules) {
		MultipleUnique<
			Module::ModuleBase,
			Module::Checklist,
			Module::Random
		>::Make(modules);
	}
};



