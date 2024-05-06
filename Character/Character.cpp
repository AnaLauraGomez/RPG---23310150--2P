
#include "Character.h"
#include <cstring>
#include <cstdio>

Character::Character(const char* _name, int _health, int _maxHealth, int _attack, int _defense, int _speed, bool _isPlayer) {
    //name = _name;
    // Copiar el nombre proporcionado a la variable name
    strncpy(name, _name, sizeof(name));
    // Asegurarse de que el nombre tenga un terminador nulo
    name[sizeof(name) - 1] = '\0';

    health = _health;
    maxHealth = _maxHealth; // Inicializa maxHealth con el valor proporcionado
    attack = _attack;
    defense = _defense;
    speed = _speed;
    isPlayer = _isPlayer;
}

const char* Character::getName() {
    return name;
}

int Character::getHealth() {
    return health;
}

int Character::getAttack() {
    return attack;
}

int Character::getDefense() {
    return defense;
}

int Character::getSpeed() {
    return speed;
}

/*string Character::toString() {
    return "Name: " + name + "\nHealth: " + to_string(health) + "\nAttack: " + to_string(attack) + "\nDefense: " + to_string(defense) + "\nSpeed: " + to_string(speed);
}*/

char* Character::toString() {
    char* buffer = new char[256]; // Tamaño suficiente para almacenar los datos del personaje
    // Construir la cadena de caracteres con los datos del personaje
    snprintf(buffer, 256, "Name: %s\nHealth: %d\nAttack: %d\nDefense: %d\nSpeed: %d\n",
             name, health, attack, defense, speed);
    return buffer;
}

bool Character::getIsPlayer() {
    return isPlayer;
}

bool Character::flee(Character*target) {
    if(this->speed > target->speed)
        return true;

    int chance = rand() % 100;
    return chance > 30;
}