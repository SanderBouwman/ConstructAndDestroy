#include <iostream>
#include <SDL2/SDL.h>
#include <types.h>
#include <vector.h>
#include <behaviour/strategy/explore_strategy.h>
#include <entity/goal/moving_entity_goal/think_goal.h>
#include <graph/graph_manager.h>
#include <entity/goal/moving_entity_goal/work_goal.h>
#include <SDL2/SDL_ttf.h>
#include <textures/texture_manager.h>
#include <entity/moving/lumberjack_entity.h>
#include <entity/player_manager.h>
#include <sdl/panel/sdl_panel.h>
#include <sdl/panel/sdl_world_panel.h>
#include <sdl/image/sdl_image_render_object.h>
#include <sdl/window/sdl_window.h>
#include <entity/static/tree_entity.h>
#include <entity/goal/evaluator/obstacle_avoid_evaluator.h>
#include <entity/goal/evaluator/wander_evaluator.h>
#include <entity/moving/miner_entity.h>
#include <behaviour/calculator/basic_force_calculator.h>
#include <entity/goal/evaluator/work_evaluator.h>
#include <entity/static/warehouse_entity.h>
#include <SDL_image.h>
#include "logic/neighbourhood/neighbourhood_manager.h"
#include "renderer/mesh.h"
#include "logic/world/world.h"
#include "behaviour/behaviour.h"
#include "sdl/event/sdl_mouse_event_dispatcher.h"
#include "sdl/event/slot/mouse_handler_world.h"


int pos_x = 100, pos_y = 200, size_x = 800, size_y = 600, count = 4;

SDL_Window *window;
SDL_Renderer *renderer;

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
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
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
        std::cout << "Failed to initialize SDL2_TTF: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

bool init_img() {
    int flags = IMG_INIT_JPG | IMG_INIT_PNG;
    if (IMG_Init(flags) == -1) {
        std::cout << "Failed to initialize SDL2_IMG: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

// Initializes our window, renderer and sdl itself.
bool init_everything() {
    if (!init_sdl() || !create_window() || !create_renderer() || !init_font() || !init_img())
        return false;
    setup_renderer();
    return true;
}

int main(int argc, char **argv) {
    if (!init_everything()) {
        return -1;
    }

    PlayerManager *pm = PlayerManager::get_instance();
    pm->setup(4);

    TextureManager *tm = TextureManager::get_instance();
    tm->setup(renderer);

    GraphManager *gm = GraphManager::get_instance();
    gm->setup({(float) size_x, (float) size_y});

    std::vector<vec2 *> path = gm->graph->a_star_path(gm->graph->nodes[0], gm->graph->nodes[99]);

    World::get_instance()->add_graph(gm->graph);

    NeighbourhoodManager *n = NeighbourhoodManager::get_instance();
    n->setup({(float) size_x, (float) size_y}, {200.0f, 200.0f});

    vec2 default_shape[] = {
            {-20, -20},
            {20,  -20},
            {20,  20},
            {-20, 20},
    };
    mesh base = {4, default_shape};
    vec2 pos = {0, 0};
    vec2 velocity = {0, 0, 0};
    /*
   #pragma region Obstacle, Arrive entity
       vec2 v = {400, 300};
       BehaviourStrategy *avoid = new ObstacleAvoidanceStrategy();
       avoid->set_targets(&v);

       vec2 v2 = {700, 500};
       BehaviourStrategy *arrive = new ArriveStrategy();
       arrive->set_targets(&v2);

*/
    ForceCalculator *calculator = new BasicForceCalculator();
    Behaviour *behaviour = new Behaviour(calculator);
    MovingEntity *entity = new LumberJackEntity(&base, pos, 100, 0.2, 0.2);
    ThinkGoal *think_goal = new ThinkGoal(entity);

    think_goal->add_evaluator(new WorkEvaluator());

    entity->set_behaviour(behaviour);
    entity->set_goal(think_goal);
    entity->set_player(1);

    vec2 entity_size = {50, 50};
    sdl_image_data *entity_data = new sdl_image_data{"lumberjack.png"};
    SDL_ImageRenderObject *entity_render_object = new SDL_ImageRenderObject(pos, entity_size, entity_data);
    entity->set_representation(entity_render_object);

    World::get_instance()->add_entity(entity);
    /*
   #pragma endregion Obstacle, Arrive entity

   #pragma region Static entities
     */
    vec2 s_position = {400, 280}, s_size = {50, 50};
    ResourceEntity *s_entity = new TreeEntity(&base, s_position, 50);
    s_entity->set_textures(TextureTypes::TREETEXTURE, TextureTypes::TREEDEPLETEDTEXTURE);
    sdl_image_data *tree_data = new sdl_image_data{"tree.png"};
    SDL_ImageRenderObject *tree_object = new SDL_ImageRenderObject(s_position, s_size, tree_data);
    s_entity->set_representation(tree_object);

    vec2 s_position7 = {600, 400};
    ResourceEntity *s_entity7 = new WarehouseEntity(&base, s_position7, 50);
    sdl_image_data *entity7_data = new sdl_image_data{"warehouse.png"};
    SDL_ImageRenderObject *e7_object = new SDL_ImageRenderObject(s_position7, {50, 50}, entity7_data);
    s_entity7->set_representation(e7_object);

    World::get_instance()->add_entity(s_entity7);
    World::get_instance()->add_entity(s_entity);

    Renderer<SDL_Renderer> render_engine = Renderer<SDL_Renderer>(renderer);
    SDL_MouseEventDispatcher *mouse_dispatcher = SDL_MouseEventDispatcher::get_instance();

    sdl_image_data *world_data = new sdl_image_data{"world.png"};
    SDL_ImageRenderObject *world_representation = new SDL_ImageRenderObject({0, 0}, {800, 600}, world_data);

    World::get_instance()->set_render_object(world_representation);

    vec2 main_panel_position = {0, 0}, main_panel_size = {800, 600};
    sdl_data *panel_data = new sdl_data{255, 255, 255};

    SDL_RenderObject *main_panel_representation = new SDL_RenderObject(main_panel_position, main_panel_size,
                                                                       panel_data);
    SDLWorldPanel main_panel = SDLWorldPanel(main_panel_representation);
    main_panel.set_world(World::get_instance());

    SDLWindow *main_window = new SDLWindow(main_panel_representation, window, &render_engine, mouse_dispatcher);

    MouseHandlerWorld *world_panel_slot = new MouseHandlerWorld();

    main_panel.set_mouse_callback(world_panel_slot);

    mouse_dispatcher->register_callback(&main_panel, world_panel_slot);

    main_window->add_component(&main_panel);

    main_window->show();

    delete main_window;
    return 0;
}