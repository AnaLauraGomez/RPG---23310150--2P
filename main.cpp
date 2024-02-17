#include <iostream>
#include "Player/Player.h"
#include "Enemy/Enemy.h"
#include "Utils.h"

int main() {
    Player *player = new Player("Victor", 10, 5, 5, 10);
    Enemy *enemy = new Enemy("Estudiante de Redes", 10, 8, 8, 5, 10);

   /* cout << player->toString() << endl;
    cout << enemy->toString() << endl;

    cout << "=====================" << endl;

    player->doAttack(enemy);
    enemy->doAttack(player);


    cout << player->toString() << endl;
    cout << enemy->toString() << endl;*/

    // Llamar a la función simulateCombat para manejar el combate
    combat_utils::simulateCombat(player, enemy);

    //delete player;
    //delete enemy;
    return 0;
}
