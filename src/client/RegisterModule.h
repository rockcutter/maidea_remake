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

//�����Ń��W���[����o�^����
class ModulePackager {
public:
	
	//�����ɂ�SlashCommand����������Module��o�^���� �e���v���[�g�p�����[�^�ɏ��������邾���ł悢(�ϒ��p�����[�^)
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
	
	//�����ɂ�TextCommand����������Handler�֐�����������Module��o�^���� �e���v���[�g�p�����[�^�ɏ��������邾���ł悢(�ϒ��p�����[�^)
	//static void GetTextCommandProcessors(std::vector<std::unique_ptr<Module::TextProcessorBase>>& modules) {
	//	MultipleUnique<
	//		Module::TextProcessorBase,
	//		Module::Hello
	//	>::Make(modules);
	//}

	//�����ɂ�PlainTextHandler����������Module��o�^���� �e���v���[�g�p�����[�^�ɏ��������邾���ł悢(�ϒ��p�����[�^)
	static void GetTextProcessors(std::vector<std::unique_ptr<Module::TextProcessorBase>>& modules) {
		MultipleUnique<
			Module::TextProcessorBase,
			Module::Random,
			Module::Checklist
		>::Make(modules);
	}
};



