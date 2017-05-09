//
// Created by Sander on 14-3-2017.
//

#include <iostream>
#include "follow_path_goal.h"
#include "behaviour/strategy/explore_strategy.h"
#include "entity/goal/moving_entity_goal/atomic/obstacle_avoidance_goal.h"
#include "entity/goal/moving_entity_goal/atomic/explore_goal.h"
#include "entity/goal/moving_entity_goal/atomic/traverse_edge_goal.h"
#include "graph/graph.h"
#include "entity/moving/moving_entity.h"
#include "entity/goal/moving_entity_goal/atomic/wander_goal.h"
#include "strategy_goal_type.h"
#include "goal/goal_evaluator.h"
#include "behaviour/behaviour.h"

FollowPathGoal::FollowPathGoal(MovingEntity *e) : GoalComposite(e, FOLLOWPATH) {
    _owner = e;
}

void FollowPathGoal::determine_next_goal() {
    if(this->sub_goals.size() == 0){
        status = COMPLETED;
    }
}

void FollowPathGoal::set_goal_traverse_edge(vec2 *g) {
    this->sub_goals.push_front(new TraverseEdgeGoal(owner, g));
}

void FollowPathGoal::activate() {
    status = ACTIVE;
}

const int FollowPathGoal::process() {
    activate_if_inactive();
    if(owner->path.size()!=0){
        owner->path.erase (owner->path.begin(),owner->path.begin()+ 1);
        for(int i = 0; i < owner->path.size(); i++){
            set_goal_traverse_edge(owner->path.at(i));
        }
        owner->path.erase (owner->path.begin(),owner->path.begin()+ owner->path.size());
    }
    determine_next_goal();
    return process_subgoals();
}

void FollowPathGoal::terminate() {
    remove_all_subgoals();
}

const char *FollowPathGoal::get_name() const {
    return "FollowPath";
}

