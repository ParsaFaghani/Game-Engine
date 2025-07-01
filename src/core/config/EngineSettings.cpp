#include "EngineSettings.h"



EngineSettings::EngineSettings(){
    
}

void EngineSettings::set_fps(float fps) {
    m_fps = fps;
}
float EngineSettings::get_fps() const{
    return m_fps;
}

void EngineSettings::set_width(int width){
    m_width = width;
}
int EngineSettings::get_width() const{
    return m_width;
}

void EngineSettings::set_height(int height){
    m_height = height;
}
int EngineSettings::get_height() const{
    return m_height;
}
    
void EngineSettings::set_fullscreen(bool fullscreen){
    m_fullscreen = fullscreen;
}
bool EngineSettings::get_fullscreen() const{
    return m_fullscreen;
}
