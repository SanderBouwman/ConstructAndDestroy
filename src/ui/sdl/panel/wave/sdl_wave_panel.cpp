//
// Created by robin on 5/16/17.
//

#include "sdl_wave_panel.h"
#include "sdl/panel/wave/state/wave_panel_preparing.h"
#include "sdl/text/sdl_render_solid_text.h"
#include "state/state_machine.h"
#include "wave/wave.h"
#include "wave/wave_manager.h"

SDLWavePanel::SDLWavePanel(SDLRenderSolidText *r, WaveManager *wave) : SDLPanel(r) {
    _wave_manager = wave;
    _wave_panel_state_machine = new StateMachine<SDLWavePanel>(this);
    _wave_panel_state_machine->change_state(new WavePanelPreparing());
}

SDLWavePanel::~SDLWavePanel() {
    _wave_manager = nullptr;
    _wave_panel_state_machine = nullptr;
}

void SDLWavePanel::render(SDLRenderer *renderer, mat2 &transformations, float delta) {
    _wave_manager->update(delta);
    _wave_panel_state_machine->update();
    SDL_UIComponent::render(renderer, transformations, delta);
}

Wave *SDLWavePanel::get_wave() {
    return _wave_manager->get_wave();
}

StateMachine<SDLWavePanel> *SDLWavePanel::get_state_machine() {
    return _wave_panel_state_machine;
}

void SDLWavePanel::resize(const vec2 &v) {
    vec2 offset = old_window_size - (*representation->get_position());
    representation->set_position(representation->get_position()->x, v.y - offset.y);
    old_window_size = v;
    resize_children(v);
}
