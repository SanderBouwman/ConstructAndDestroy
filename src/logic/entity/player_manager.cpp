//
// Created by Sander on 20-4-2017.
//

#include "player_manager.h"
#include "player.h"

PlayerManager* PlayerManager::_instance = nullptr;

PlayerManager::PlayerManager() {
    _players = std::map<int, Player*>();
}

void PlayerManager::setup(int p) {
    if(_players.size() == 0){
        for(int i = 1; i <= p; i++){
            _players.insert(std::make_pair(i, new Player));
        }
    }
}

PlayerManager *PlayerManager::get_instance() {
    if (!_instance)
        _instance = new PlayerManager();
    return _instance;
}

Player *PlayerManager::get_player(int player) {
    return _players[player];
}