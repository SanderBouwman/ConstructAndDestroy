//
// Created by robin on 3/1/17.
//

#include <string>
#include <iostream>
#include <cmath>
#include <cstring>
#include "base_entity.h"
#include "player_manager.h"
#include "sdl/label/sdl_render_resource_label.h"

BaseEntity::BaseEntity(int type, vec2 position, float mass) {
    _type = type;
    _mass = mass;
    _position = position;
    _max_health = 100;
    _health = 100;
    _attack_damage = 2;
    _attack_speed = 1;
    _marking = 0;
}

void BaseEntity::set_representation(SDL_RenderObject *r) {
    _representation = r;
}

BaseEntity::~BaseEntity() {
    if(_representation) {
        delete _representation;
    }
    _player = nullptr;
}

vec2 &BaseEntity::get_position() {
    return _position;
}

void BaseEntity::set_position(int x, int y) {
    _position.x = x;
    _position.y = y;
    _representation->set_position(x, y);
}

void BaseEntity::add_to_position(vec2 v) {
    _position += v;
    _representation->set_position(_position.x, _position.y);
}

const bool BaseEntity::is(int type) {
    return _type == type;
}

void BaseEntity::render(SDLRenderer *renderer, const mat2 &transformations) {
    upsert_attribute("health.png", this->get_health());

    _representation->render(renderer, transformations);
}

Player *BaseEntity::get_player() {
    return _player;
}

void BaseEntity::set_player(int p) {
    PlayerManager *pm = PlayerManager::get_instance();
    _player = pm->get_player(p);
}

void BaseEntity::select() {std::cout << "Can't select base entity" << std::endl;}
void BaseEntity::deselect() {std::cout << "Can't deselect base entity" << std::endl;}

SDL_RenderObject *BaseEntity::get_representation() {
    return _representation;
}

float BaseEntity::get_health() {
    return _health;
}

float BaseEntity::get_health_divided_by_max_health() {
    return _health / _max_health;
}

void BaseEntity::attack(float damage) {
    _health -= damage;
}

float BaseEntity::get_attack_damage() {
    return _attack_damage;
}

void BaseEntity::add_mark(uint8_t m) {
    _marking |= (1 << m);
}

bool BaseEntity::has_mark(uint8_t m) {
    return _marking & (1 << m) == (1 << m);
}

void BaseEntity::multiply_stats(float f) {
    _max_health *= f;
    _health *= f;
    _attack_damage *= f;
    _attack_speed *= f;
}

std::map<std::string, const char *> BaseEntity::get_info_attributes() {
    return _info_attributes;
}

void BaseEntity::upsert_attribute(std::string image, const char *value) {
    auto existing = _info_attributes.find(image);
    if (existing == _info_attributes.end())
    {
        _info_attributes.insert(std::pair<std::string, const char *>(image, value));
    }
    else
    {
        _info_attributes[image] = value;
    }
}

void BaseEntity::upsert_attribute(std::string image, float value) {
    std::string temp_str = std::to_string(static_cast<int>(std::round(value)));
    char* char_type = new char[temp_str.length()];
    strcpy(char_type, temp_str.c_str());
    return upsert_attribute(image, char_type);
}