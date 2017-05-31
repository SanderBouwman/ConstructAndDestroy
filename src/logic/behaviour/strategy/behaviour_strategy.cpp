//
// Created by robin on 3/1/17.
//

#include "behaviour/behaviour_strategy.h"

void BehaviourStrategy::set_targets(vec2 *v, int size) {
    _targets = v;
    _target_size = size;
}

BehaviourStrategy::~BehaviourStrategy() {
    _targets = nullptr;
}
