//
// Created by robin on 4/26/17.
//

#ifndef CONSTRUCT_AND_DESTROY_SDL_UI_RENDER_TEXT_OBJECT_H
#define CONSTRUCT_AND_DESTROY_SDL_UI_RENDER_TEXT_OBJECT_H

#include <SDL2/SDL_ttf.h>
#include "sdl_ui_render_object.h"

struct sdl_ui_text_data : public sdl_ui_data {
    const char *text;
    TTF_Font *font;

    sdl_ui_text_data(uint8_t r, uint8_t g, uint8_t b, const char *c, TTF_Font *f) {
        red = r;
        green = g;
        blue = b;
        text = c;
        font = f;
    }
};

class SDL_UI_RenderTextObject : public SDL_UI_RenderObject {
public:
    SDL_UI_RenderTextObject(const vec2 &position, const vec2 &size, sdl_ui_text_data *data);

    SDL_Texture *render(Renderer<SDL_Renderer> *) override;

    void init_texture(Renderer<SDL_Renderer> *);
};

#endif //CONSTRUCT_AND_DESTROY_SDL_UI_RENDER_TEXT_OBJECT_H