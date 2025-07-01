#pragma once
#include "EngineSettings.h"


class Config {
    public:
    Config(const EngineSettings& settings);
    void save_data();
    EngineSettings get_data() const;
    

    private:
    EngineSettings m_settings;



};