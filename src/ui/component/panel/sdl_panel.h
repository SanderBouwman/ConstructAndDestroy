//
// Created by robin on 4/24/17.
//

#ifndef CONSTRUCT_AND_DESTROY_SDL_PANEL_H
#define CONSTRUCT_AND_DESTROY_SDL_PANEL_H


#include "component/sdl/sdl_ui_component.h"

class SDLPanel : public SDL_UIComponent {
public:
    explicit SDLPanel(SDL_UI_RenderObject *);
};


#endif //CONSTRUCT_AND_DESTROY_SDL_PANEL_H
