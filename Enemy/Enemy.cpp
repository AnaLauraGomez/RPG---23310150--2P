#include "Enemy.h"
#include "../Utils.h"
#include <iostream>
#include <random>


using namespace std;
using namespace combat_utils;

Enemy::Enemy(const char* _name, int _health, int _attack, int _defense, int _speed, int _experience) : Character(_name, _health,_health, _attack, _defense, _speed, false) {
    experience = _experience;
}

void Enemy::doAttack(Character *target) {
    target->takeDamage(getRolledAttack(attack));
}

void Enemy::takeDamage(int damage) {
    int trueDamage = damage - defense;
    health-= trueDamage;

    cout << name << " recibio " << trueDamage << " damage!" << endl;

    if(health <= 0) {
        cout << name << " has been defeated!" << endl;
    }
}

void Enemy::increaseStats(int points) {

    int healthPoints = points;
    int attackPoints = points;
    int defensePoints = points;
    int speedPoints = points;

    // Aumentar las estadísticas del enemigo
    health += healthPoints;
    attack += attackPoints;
    defense += defensePoints;
    speed += speedPoints;
}

int Enemy::getExperience() const {
    cout << "Experiencia ganada de este combate: " << experience << endl;
    return experience;
}

Character* Enemy::selectTarget(vector<Player*> possibleTargets) {
    //target with less health
    int lessHealth = 9999999;
    Character* target = nullptr;
    for(auto character : possibleTargets) {
        if(character->getHealth() < lessHealth) {
            lessHealth = character->getHealth();
            target = character;
        }
    }
    return target;
}

Action Enemy::takeAction(vector<Player*> partyMembers) {
    Action currentAction;
    currentAction.speed = getSpeed();

    double fifteenPercentMaxHealth = 0.15 * getMaxHealth();
    if (getHealth() < fifteenPercentMaxHealth) {
        double defenseProbability = static_cast<double>(rand()) / RAND_MAX;
        cout << "Tu probabilidad de defenderte fue: " << defenseProbability << endl;
        if (defenseProbability <= 0.4) {
            currentAction.action = [](){
                //Actualmente la defensa no esta pensada para ser una accion ejecutada por la maquina de estados
            };
            defend();
            cout << getName() << " decide defenderse al tener menos del 15% de vida." << endl;
            return currentAction; // Retorna una acción vacía si decide defenderse
        }
    }


    // Selección del objetivo si no decide defenderse
    Character* target = selectTarget(partyMembers);
    currentAction.target = target;
    currentAction.action = [this, target](){
        doAttack(target);
    };

    return currentAction;
}