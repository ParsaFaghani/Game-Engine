#include "Config.h"
#include <SimpleIni.h>
#include <iostream>

Config::Config(const EngineSettings& settings) {
    m_settings = settings;
    CSimpleIniA file_settings;
    SI_Error rc = file_settings.LoadFile("../assets/datas/EngineSettings.ini");
    if (rc < 0){
        std::cout << rc << std::endl;
    }
}
void save_data() {
    std::cout<<"save"<<std::endl;
}
