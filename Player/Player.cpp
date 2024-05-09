#include "Player.h"
#include "../Files/FileHandler.h"
#include <iostream>

using namespace std;

Player::Player(const char* _name, int _health, int _attack, int _defense, int _speed) : Character(_name, _health, _health,_attack, _defense, _speed, true) {
    level = 1;
    experience = 0;
    originalDefense = _defense; // Almacena el valor original de la defensa
}

Player::Player(const char *_name, int _health, int _maxHealth, int _attack, int _defense, int _speed,bool _isPlayer, int _level, int _experience) : Character(_name, _health, _maxHealth,_attack, _defense, _speed, _isPlayer){
    level = _level;
    experience = _experience;
}

void Player::doAttack(Character *target) {
    target->takeDamage(attack);
}

void Player::takeDamage(int damage) {
    int trueDamage = damage - defense;
    if (trueDamage < 0) {
        trueDamage = 0; // El jugador no puede curarse debido a la defensa
    }

    health -= trueDamage;

    cout << name << " recibio " << trueDamage << " damage!" << endl;

    if(health <= 0) {
        cout << name << " has been defeated!" << endl;
        return;
    }

    // Si el enemigo ha sido derrotado
   /* if (damage >= health) {
        gainExperience(currentEnemy->getExperience());
    }*/

}

void Player::levelUp(vector<Enemy*> enemies) {
    level++;
    int requiredExperience = 10;

    // Restar la experiencia necesaria para subir de nivel
    experience -= requiredExperience;

    health += 2;
    attack += 2;
    defense += 2;
    speed += 2;
    cout << name << " ha subido al nivel " << level << "!" << endl;
    cout << "Nuevas estadísticas: Salud: " << health << ", Ataque: " << attack << ", Defensa: " << defense << ", Velocidad: " << speed << endl;
    cout << "Nivel de experiencia actual: " << experience << endl;

    levelUpEnemies(enemies);

    // Verificar si hay remanente de experiencia después de subir de nivel
    if (experience >= requiredExperience) {
        cout << "Tienes experiencia para subir de nivel" << endl;
        //levelUpEnemies(enemies);
        levelUp(enemies); // Llamar recursivamente para subir de nivel de nuevo si hay suficiente experiencia
    }
}

void Player::gainExperience(int exp, vector<Enemy*> enemies) {
    experience += exp;

    int requiredExperience = 10;

    if (experience >= requiredExperience) {
        levelUp(enemies); // Subir de nivel si se cumple la condición
    }
}

void Player::levelUpEnemies(const std::vector<Enemy*>& enemies) {
    int levelUpPoints = 2; // Puntos de aumento en las estadísticas al subir de nivel

    // Aumentar las estadísticas de cada enemigo en la lista
    for (auto enemy : enemies) {
        enemy->increaseStats(levelUpPoints);
    }
}

Character* Player::selectTarget(vector<Enemy*> possibleTargets) {
    int selectedTarget = 0;
    cout << "Select a target: " << endl;
    for (int i = 0; i < possibleTargets.size(); i++) {
        cout << i + 1 << ". " << possibleTargets[i]->getName() << endl;  // Sumar 1 para mostrar el número de enemigo correctamente
    }

    // TODO: Add input validation
    cin >> selectedTarget;

    // Ajustar el índice seleccionado para que coincida con el índice del vector
    selectedTarget--;

    return possibleTargets[selectedTarget];
}

void Player::resetDefense() {
    // Restablecer la defensa al valor original
    defense = originalDefense;
}

Action Player::takeAction(vector<Enemy*> enemies) {
    int action;
    cout << "Select an action: " << endl
         << "1. Attack" << endl
         << "2. Defend" << endl; // Agregar la opción de defenderse
    cin >> action;
    Action currentAction;
    Character* target = nullptr;
    int originalDefense = defense; // Mover la declaración aquí
    switch(action) {
        case 1:
            // Utilizar al enemigo seleccionado al principio del combate como objetivo
            if (!enemies.empty()) {
                target = selectedEnemy;
            } else {
                cout << "No hay enemigos disponibles." << endl;
                currentAction.action = nullptr;
                return currentAction;
            }
            currentAction.target = target;
            currentAction.action = [this, target](){
                doAttack(target);
            };
            currentAction.speed = getSpeed();
            break;
        case 2:
            defend(); // Llamar al método defend si se elige defenderse

            if (!enemies.empty()) {
                target = enemies[0];
            }
            if (target) {
                currentAction.target = target;
                currentAction.action = [this, target, originalDefense](){
                    // Restablecer la defensa al valor original después de defenderse
                    defense = originalDefense;
                };
                currentAction.speed = target->getSpeed();
            } else {
                cout << "No hay enemigos disponibles." << endl;
                currentAction.action = nullptr;
            }
            break;
        default:
            cout << "Invalid action" << endl;
            currentAction.action = nullptr;
            break;
    }

    return currentAction;
}

char* Player::serialize(){
    char* iterator = buffer;

    memcpy(iterator,&name, sizeof(name));
    iterator += sizeof(name);

    memcpy(iterator, &health, sizeof(health));
    iterator += sizeof(health);

    memcpy(iterator,&maxHealth,sizeof(maxHealth));
    iterator += sizeof(maxHealth);

    memcpy(iterator,&attack,sizeof(attack));
    iterator += sizeof(attack);

    memcpy(iterator,&defense,sizeof(defense));
    iterator += sizeof(defense);

    memcpy(iterator,&speed,sizeof(speed));
    iterator += sizeof(speed);

    memcpy(iterator,&isPlayer,sizeof(isPlayer));
    iterator += sizeof(isPlayer);

    memcpy(iterator,&level,sizeof(level));
    iterator += sizeof(level);
    memcpy(iterator,&experience,sizeof(experience));
    iterator += sizeof(experience);

    return buffer;

}

Player* Player::unserialize(char* buffer) {
    char *iterator = buffer;

    char name[30];
    int health, maxHealth, attack, defense, speed, level, experience;
    bool isPlayer;

    memcpy(&name, iterator, sizeof(name));
    iterator += sizeof(name);

    memcpy(&health, iterator, sizeof(health));
    iterator += sizeof(health);

    memcpy(&maxHealth, iterator, sizeof(maxHealth));
    iterator += sizeof(maxHealth);

    memcpy(&attack, iterator, sizeof(attack));
    iterator += sizeof(attack);

    memcpy(&defense, iterator, sizeof(defense));
    iterator += sizeof(defense);

    memcpy(&speed, iterator, sizeof(speed));
    iterator += sizeof(speed);

    memcpy(&isPlayer, iterator, sizeof(isPlayer));
    iterator += sizeof(isPlayer);

    memcpy(&level, iterator, sizeof(level));
    iterator += sizeof(level);

    memcpy(&experience, iterator, sizeof(experience));
    iterator += sizeof(experience);


    return new Player(name, health, maxHealth, attack, defense, speed, isPlayer, level, experience);

}

