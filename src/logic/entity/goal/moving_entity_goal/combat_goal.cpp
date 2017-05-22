//
// Created by Sander on 10-5-2017.
//

#include <iostream>
#include "settings.h"
#include "graph/graph_manager.h"
#include "graph/graph.h"
#include "entity/goal/moving_entity_goal/atomic/fight_goal.h"
#include "entity/player_manager.h"
#include "entity/player.h"
#include "entity/goal/moving_entity_goal/atomic/plan_path_goal.h"
#include "combat_goal.h"
#include "think_goal.h"
#include "follow_path_goal.h"
#include "entity/moving/moving_entity.h"
#include "behaviour/behaviour.h"
#include "hunt_target_goal.h"

CombatGoal::CombatGoal(MovingEntity *e, MovingEntity *enemy) : GoalComposite(e, COMBAT) {
    if (!enemy) {
        PlayerManager *pm = PlayerManager::get_instance();

        Player *enemy_player;
        if (owner->get_player()->get_id() == computer_id) {
            enemy_player = pm->get_player(player_id);
        } else {
            enemy_player = pm->get_player(computer_id);
        }
        //todo:: change this, maybe pick the closest or the most threatening enemy
        if (!enemy_player->units.empty()) {
            _enemy = enemy_player->units.front();

            set_goal_hunt_target();
            set_goal_attack_enemy();
        }
            //No enemy found so goal is completed
        else {
            status = COMPLETED;
        }
    } else {
        _enemy = enemy;
        set_goal_attack_enemy();
    }
}

void CombatGoal::set_goal_hunt_target() {
    float distance_to_enemy = _enemy->get_position().distance(owner->get_position());
    if (distance_to_enemy < 40) {
        //fight
        _enemy->get_brain()->remove_all_subgoals();
        _enemy->get_brain()->set_goal_combat(owner);
    } else {
        this->sub_goals.push_front(new HuntTargetGoal(owner, _enemy));
    }
}

void CombatGoal::set_goal_attack_enemy() {
    this->sub_goals.push_front(new FightGoal(owner, _enemy));
}

void CombatGoal::activate() {
    status = ACTIVE;
}

const int CombatGoal::process() {
    activate_if_inactive();
    status = process_subgoals();

    if (sub_goal_is_completed(HUNTTARGET)) {
        terminate();
    }

    return status;
}

void CombatGoal::terminate() {
    status = COMPLETED;
    remove_all_subgoals();
}

const char *CombatGoal::get_name() const {
    return "Combat";
}

bool CombatGoal::sub_goal_is_completed(StrategyGoalType agt) {
    for (typename std::deque<Goal<MovingEntity> *>::iterator it = sub_goals.begin(); it != sub_goals.end(); it++) {
        Goal<MovingEntity> *current_goal = (*it);
        if (current_goal->get_type() == agt) {
            return current_goal->get_status() == COMPLETED;
        }
    }
}