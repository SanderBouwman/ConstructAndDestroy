//
// Created by robin on 4/26/17.
//

#include "sdl_world_panel.h"
#include "world/world.h"

SDLWorldPanel::SDLWorldPanel(SDL_RenderObject *r) : SDLPanel(r) {
    _current_world = nullptr;
    dragging = false;
}

void SDLWorldPanel::set_world(World *world) {
    _current_world = world;
}

SDL_Texture *SDLWorldPanel::render(Renderer<SDL_Renderer> *renderer, float d) {
//    SDLPanel::render(renderer, d);
    _current_world->update(d);
    SDL_Texture *world_texture = _current_world->render(renderer);

    // Draw rectangle if dragging
    if (dragging) {
        SDL_SetRenderTarget(renderer->get_engine(), world_texture);
        this->draw_selection_rect((int) start_drag.x, (int) start_drag.y, (int) end_drag.x, (int) end_drag.y,
                                  renderer->get_engine());
        SDL_SetRenderTarget(renderer->get_engine(), NULL);
    }
    return world_texture;
}

void SDLWorldPanel::draw_selection_rect(int start_x, int start_y, int end_x, int end_y, SDL_Renderer *_renderer) {

    SDL_SetRenderDrawColor(_renderer, 255, 0, 0, 255);
    SDL_Rect *rect = new SDL_Rect;

    //starting coordinates from the rectangle
    rect->x = start_x;
    rect->y = start_y;

    //coordinates the lines of the rectangle end.
    rect->h = (int) std::abs(start_y - end_y);

    //if rect's origin coordinates are greater then end coordinates use * -1 so the height/weight is negative.
    if (start_y > end_y) { rect->h = rect->h * -1; }

    rect->w = (int) std::abs(end_x - start_x);
    if (start_x > end_x) { rect->w = rect->w * -1; }

    SDL_RenderDrawRect(_renderer, rect);
}