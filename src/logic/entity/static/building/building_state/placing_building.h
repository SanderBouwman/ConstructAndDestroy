//
// Created by Stephan Schrijver on 20-4-2017.
//

#ifndef CONSTRUCT_AND_DESTROY_PLACING_BUILDING_H
#define CONSTRUCT_AND_DESTROY_PLACING_BUILDING_H

#include "state/state.h"

class Player;

class PlacingBuilding: public State<Player>{
public: void enter(Player *);
    void execute(Player *);
    void exit(Player *);
};
#endif //CONSTRUCT_AND_DESTROY_PLACING_BUILDING_H
