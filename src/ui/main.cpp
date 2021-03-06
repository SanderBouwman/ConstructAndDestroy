//
// Created by robin on 4/23/17.
//

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "settings.h"
#include "sdl/event/slot/sdl_mouse_event_slot.h"
#include "sdl/text/sdl_render_text_object.h"
#include "sdl/button/sdl_button.h"
#include "sdl/event/sdl_key_event_dispatcher.h"
#include "sdl/window/sdl_window.h"
#include "sdl/panel/sdl_panel.h"
#include "sdl/event/sdl_mouse_event_dispatcher.h"
#include "world/world.h"
#include "entity/resources.h"

int pos_x = 100, pos_y = 200, size_x = 800, size_y = 600, count = 4;

SDL_Window *window;
SDL_Renderer *renderer;

vec2 window_size = {800, 600};
float camera_zoom = 1.0f;

// initialize buildings and textures
std::vector<building_with_texture> buildings_with_textures = {
    {"castle.png", BuildingType::CASTLE, new Resources(0,0,5,0), "Castle", "This building can create new units"},
    {"warehouse.png", BuildingType::WAREHOUSE, new Resources(0,0,0,0), "Warehouse", "This building is used to store resources"}
};

std::vector<entity_with_texture> entities_with_textures = std::vector<entity_with_texture>{
    {"lumberjack.png", MovingEntityType::LUMBERJACK},
    {"goldminer.png",      MovingEntityType::GOLDMINER},
    {"stoneminer.png",      MovingEntityType::STONEMINER},
    {"knight.png",     MovingEntityType::KNIGHT}
};

std::string get_texture_of_entity(MovingEntityType type) {
    for (int i = 0; i < entities_with_textures.size(); i++) {
        if (entities_with_textures.at(i).type == type) {
            return entities_with_textures.at(i).texture;
        }
    }
}

std::string get_texture_of_building(BuildingType building) {
    for (int i = 0; i < buildings_with_textures.size(); i++) {
        if (buildings_with_textures.at(i).type == building) {
            return buildings_with_textures.at(i).texture;
        }
    }
}

bool init_sdl() {
    if (SDL_Init(0) == -1) {
        std::cout << " Failed to open SDL: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

bool create_window() {
    window = SDL_CreateWindow("Construct And Destroy", pos_x, pos_y, size_x, size_y, 0);

    if (!window) {
        std::cout << " Failed to open window: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

bool create_renderer() {
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
    if (!renderer) {
        std::cout << " Failed to create renderer: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

void setup_renderer() {
    // Set size of renderer to the same as window
    SDL_RenderSetLogicalSize(renderer, size_x, size_y);
    // Set color of renderer to green
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
}

bool init_font() {
    if (TTF_Init() == -1) {
        std::cout << "Failed to initialize font: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

// Initializes our window, renderer and sdl itself.
bool init_everything() {
    if (!init_sdl() || !create_window() || !create_renderer() || !init_font())
        return false;
    setup_renderer();
    return true;
}

int main(int argc, char **argv) {
    if (!init_everything()) {
        return -1;
    }

    SDL_Color f_color = {0, 0, 0, 255};
    TTF_Font *f_font = TTF_OpenFont("res/font/Roboto/Roboto-Regular.ttf", 26);

    SDL_MouseEventDispatcher *mouse_dispatcher = SDL_MouseEventDispatcher::get_instance();
    SDL_KeyEventDispatcher *key_dispatcher = SDL_KeyEventDispatcher::get_instance();

    SDLRenderer *r = new SDLRenderer(renderer, {window_size.x, window_size.y});

    vec2 main_window_position = {0, 0}, main_window_size = {800, 600};
    sdl_data main_window_data = {255, 0, 0};
    SDL_RenderObject window_o = SDL_RenderObject(main_window_position, main_window_size, &main_window_data);
    SDLWindow sdl_window(&window_o, window, r, mouse_dispatcher, key_dispatcher);

    vec2 right_panel_pos = {600, 0}, right_panel_size = {200, 600};
    sdl_data *right_panel_data = new sdl_data{0, 0, 255};
    SDL_RenderObject *panel_o = new SDL_RenderObject(right_panel_pos, right_panel_size, right_panel_data);
    SDLPanel right_panel(panel_o);

    vec2 right_panel_top_pos = {601, 1}, right_panel_top_size = {200, 200};
    sdl_data *right_panel_top_data = new sdl_data{1, 255, 0, 255};
    SDL_RenderObject *panel_top_o = new SDL_RenderObject(right_panel_top_pos, right_panel_top_size, right_panel_top_data);
    SDLPanel right_panel_top(panel_top_o);
    
    vec2 button_pos = {601, 250}, button_size = {100, 50};
    sdl_text *button_data = new sdl_text{255, 255, 50, "hallo", f_font};
    SDL_UI_RenderTextObject *button_o = new SDL_UI_RenderTextObject(button_pos, button_size, button_data);
    SDLButton button(button_o);
    
    right_panel.add_component(&button);
    right_panel.add_component(&right_panel_top);
    sdl_window.add_component(&right_panel);

    return sdl_window.show();
}