//
// Created by robin on 2/21/17.
//

#ifndef C_AND_D_PROJECT_WORLD_H
#define C_AND_D_PROJECT_WORLD_H

#include <vector>
#include <SDL2/SDL.h>
#include "types.h"
#include <string>
#include "graph/graph.h"
#include "entity/base_entity.h"
#include "sdl/sdl_render_object.h"

class BSPTree;
class MovingEntity;
class Player;
class BaseEntity;

class World {
private:
    std::vector<BaseEntity *> entities;
    MovingEntity *controllable_character;
    Graph *graph;
    std::string texture_path;
    World();
    static World *_instance;

public:
    Player* player;
    SDL_RenderObject *_representation;

    ~World();

    void set_render_object(SDL_RenderObject *);

    /**
     * The render loop.
     */
    SDL_Texture *render(Renderer<SDL_Renderer> *);

    /**
     * The update loop, where we update our entities.
     */
    void update(float);

    World &add_entity(BaseEntity *);

    std::vector<BaseEntity *> getEntities();

    void add_graph(Graph *);

    void add_controllable_character(MovingEntity*);

//    void add_partition_tree(BSPTree*);
    void loop(SDL_Renderer *);
    Player* getPlayer();


    static World *get_instance();
};

#endif //C_AND_D_PROJECT_WORLD_H
