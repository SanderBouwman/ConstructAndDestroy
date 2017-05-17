//
// Created by robin on 5/15/17.
//

#ifndef CONSTRUCT_AND_DESTROY_WAVE_H
#define CONSTRUCT_AND_DESTROY_WAVE_H

#include <vector>
#include "entity/moving/moving_entity_types.h"

class MovingEntityManager;

class Wave {
private:
    float _wave_duration, _stat_modifier_increment, _spawner_downtime,
        _delta_time_wave, _delta_time_spawner, _stat_modifier, _elapsed_time;

    unsigned int _wave_count, _current_wave;

    MovingEntityManager *_entity_manager;

    std::vector<MovingEntityType> _spawn_possibilities;

    /*!
     * Checks whether it's time to move on to the next wave.
     */
    void next_wave();

    /*!
     * Checks whether it's time to spawn a new entity.
     */
    void spawn_entity();

public:
    explicit Wave(unsigned int, unsigned int);

    void set_spawn_possibilities(std::vector<MovingEntityType> &);

    /*!
     * Increments the timers and calls the next_wave and spawn_entity methods.
     * @param float delta time
     */
    void update(float);

    const unsigned int get_wave_size();

    const unsigned int get_current_wave();

    const float get_stat_modifier();

    const float get_elapsed_time();
};

#endif //CONSTRUCT_AND_DESTROY_WAVE_H
