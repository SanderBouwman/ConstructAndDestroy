//
// Created by Sander on 18-5-2017.
//

#include "sdl_image_health_render_object.h"
#include "sdl/sdl_renderer.h"
#include "entity/base_entity.h"
#include "matrix.h"

SDL_ImageHealthRenderObject::SDL_ImageHealthRenderObject(const vec2 &position, const vec2 &size, sdl_image_data *data,
                                                         BaseEntity *owner)
        : SDL_ImageRenderObject(position, size, data) {
    _owner = owner;
}

SDL_ImageHealthRenderObject::~SDL_ImageHealthRenderObject() {
    _owner = nullptr;
}

void SDL_ImageHealthRenderObject::render(SDLRenderer *renderer, const mat2 &transformations) {
    if (!_result) {
        init_texture(renderer);
    }

    renderer->draw_to_buffer(_result, &get_transformed_rectangle(transformations));

    draw_health_bar(renderer, point_buffer[0]);
}

void SDL_ImageHealthRenderObject::draw_health_bar(SDLRenderer *renderer, vec2 owner_pos) {
    int x = owner_pos.x + 5;
    int y = owner_pos.y - 10;
    int health_bar_width = 30;
    int health_bar_height = 5;

    SDL_Rect background_rect = {x, y, health_bar_width, health_bar_height};
    SDL_SetRenderDrawColor(renderer->get_engine(), 0, 0, 0, 255);
    SDL_RenderFillRect(renderer->get_engine(), &background_rect);

    int hp_percentage = _owner->get_health_divided_by_max_health() * health_bar_width;
    SDL_Color color;
    if (_owner->get_health_divided_by_max_health() > 0.75) {
        color = {90, 255, 0, 255};
    } else if (_owner->get_health_divided_by_max_health() > 0.25 && _owner->get_health_divided_by_max_health() < 0.75) {
        color = {255, 165, 0, 255};
    } else {
        color = {255, 0, 0, 255};
    }
    SDL_Rect health_rect = {x, y, hp_percentage, health_bar_height};
    SDL_SetRenderDrawColor(renderer->get_engine(), color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer->get_engine(), &health_rect);
}
