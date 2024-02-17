//
// Created by Victor Navarro on 15/02/24.
//
#include <iostream>
#include <cstdlib>
#include "Player/Player.h"
#include "Enemy/Enemy.h"

namespace combat_utils {
    int getRolledAttack(int attack);
    void simulateCombat(Player *player, Enemy *enemy);
}