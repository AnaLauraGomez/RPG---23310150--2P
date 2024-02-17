#include <iostream>
#include "Player/Player.h"
#include "Enemy/Enemy.h"

int main() {
    Player *player = new Player("Victor", 100, 8, 5, 10);
    Enemy *enemy = new Enemy("Estudiante de Redes", 100, 8, 5, 5, 10);

    cout << player->toString() << endl;
    cout << enemy->toString() << endl;

    cout << "=====================" << endl;

    player->doAttack(enemy);
    enemy->doAttack(player);

    cout << player->toString() << endl;
    cout << enemy->toString() << endl;

    delete player;
    delete enemy;
    return 0;
}
