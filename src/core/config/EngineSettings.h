#pragma once

class EngineSettings {
    public:
    EngineSettings();
    void set_fps(float fps);
    float get_fps() const;

    void set_width(int width);
    int get_width() const;

    void set_height(int height);
    int get_height() const;
    
    void set_fullscreen(bool fullscreen);
    bool get_fullscreen() const;

    private:
    float m_fps = 60.0f;
    int m_width = 800;
    int m_height = 600;
    bool m_fullscreen = false;

};