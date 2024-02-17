//
// Created by Victor Navarro on 15/02/24.
//

#include "Player.h"
#include "../Utils.h"

Player::Player(string _name, int _health, int _attack, int _defense, int _speed) : Character(_name, _health, _attack, _defense, _speed) {
    level = 1;
    experience = 0;
}

void Player::doAttack(Character *target) {
    int damage = combat_utils::getRolledAttack(attack);
    // Ajustar el daño teniendo en cuenta la defensa del objetivo
    damage -= target->getDefense();
    // Asegurarnos de que el daño no sea negativo
    damage = max(damage, 0);
    target->takeDamage(damage);
}

void Player::takeDamage(int damage) {
    int trueDamage = max(damage - defense, 0);
    health -= trueDamage;
}

void Player::levelUp() {
    level++;
}

void Player::gainExperience(int exp) {
    experience += exp;
    if (experience >= 100) {
        levelUp();
        experience = 100-experience;
    }
}