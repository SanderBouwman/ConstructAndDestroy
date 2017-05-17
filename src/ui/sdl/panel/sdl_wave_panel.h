//
// Created by robin on 5/16/17.
//

#ifndef CONSTRUCT_AND_DESTROY_SDL_WAVE_PANEL_H
#define CONSTRUCT_AND_DESTROY_SDL_WAVE_PANEL_H

#include "sdl_panel.h"

template<class T>
class StateMachine;

class Wave;

class SDLWavePanel : public SDLPanel {
private:
    std::string _title, _max_wave, _current_wave, _modifier, _wave_time;
    StateMachine<Wave> *_wave_machine;

    void update_wave_time();
    void update_stat_modifier();
    void update_representation();

public:
    explicit SDLWavePanel(SDLRenderSolidText *, Wave *);

    void render(SDLRenderer *, float) override;
};

#endif //CONSTRUCT_AND_DESTROY_SDL_WAVE_PANEL_H
