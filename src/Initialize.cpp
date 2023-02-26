#include "Initialize.hpp"
#include "module/possession/Possession.h"
#include "util/Config.hpp"

void InitializeApp(){
    static bool isFirstTime = false;
    auto&& configMap        = Config::GetConfig();

    if(isFirstTime){
        return;
    }

	Module::Possession::RegisterPrivilegedUser(
		configMap["PRIVILEGED_USER"]
	);

}