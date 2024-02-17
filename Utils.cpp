//
// Created by agome on 16/02/2024.
//

#include "Utils.h"

namespace combat_utils {
    int getRolledAttack(int attack) {
        int lowerLimit = attack * .80;
        return (rand() % (attack - lowerLimit + 1)) + lowerLimit;
    }

    void simulateCombat(Player* player, Enemy* enemy) {
        while (player->getHealth() > 0 && enemy->getHealth() > 0) {
            // Turno del jugador
            int playerDamage = getRolledAttack(player->getAttack());
            enemy->takeDamage(playerDamage);
            cout << player->getName() << " ataca a " << enemy->getName() << " y le causa " << playerDamage << " puntos de lesion." << endl;

            // Verificar si el enemigo sigue vivo después del ataque del jugador
            if (enemy->getHealth() <= 0) {
                cout << "||" << player->getName() << " ha derrotado a " << enemy->getName() << "||" << endl;
                break;
            }

            // Turno del enemigo
            int enemyDamage = getRolledAttack(enemy->getAttack());
            player->takeDamage(enemyDamage);
            cout << enemy->getName() << " ataca a " << player->getName() << " y le causa " << enemyDamage << " puntos de lesion." << endl;

            // Verificar si el jugador sigue vivo después del ataque del enemigo
            if (player->getHealth() <= 0) {
                cout << "||" << enemy->getName() << " ha derrotado a " << player->getName() << "||" << endl;
                break;
            }

            // Mostrar el estado actual de los personajes
            cout << "Estado actual:" << endl;
            cout << player->toString() << endl;
            cout << enemy->toString() << endl;
        }
    }
}