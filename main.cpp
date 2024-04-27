#include <iostream>
#include "Player/Player.h"
#include "Enemy/Enemy.h"
#include "Combat/Combat.h"
#include "Files/FileHandler.h"
#include <fstream>

int main() {
    Player *player = new Player("Victor", 40, 10, 5, 3);
    /*FileHandler *fileHandler = new FileHandler();

    char* buffer = player->serialize();

    fileHandler->writeToFile("Personaje1.data",buffer, Player::BUFFER_SIZE);
    char* bufferLectura;
    fileHandler->readFromFile("Personaje1.data",bufferLectura, Player::BUFFER_SIZE);

    Player *unserializedPlayer = Player::unserialize(bufferLectura);
    cout << unserializedPlayer->toString();*/





    Enemy *enemy = new Enemy("Goblin", 60, 7, 3, 5, 10);
    Enemy *enemy2 = new Enemy("Orc", 40, 7, 2, 4, 10);
    Enemy *enemy3 = new Enemy("Cloe", 40, 7, 2, 4, 10);

    vector<Character*> participants;

    participants.push_back(player);
    participants.push_back(enemy);
    participants.push_back(enemy2);
    participants.push_back(enemy3);

    Combat *combat = new Combat(participants);
    combat->doCombat();

    delete player;
    delete enemy;
    delete combat;

    return 0;
}
