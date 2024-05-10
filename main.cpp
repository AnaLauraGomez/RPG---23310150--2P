#include <iostream>
#include "Player/Player.h"
#include "Enemy/Enemy.h"
#include "Combat/Combat.h"
#include "Files/FileHandler.h"
#include <fstream>

Player* loadPlayerInfo() {
    try {
        char buffer[Player::BUFFER_SIZE];
        FileHandler fileHandler = FileHandler();
        fileHandler.readFromFile("Personaje1.data", buffer, Player::BUFFER_SIZE);
        cout << "--- Tus estadisticas guardadas son: ---" << endl;
        return Player::unserialize(buffer);
    } catch(int error) {
        //Preguntar al usuario el nombre de jugador
        //return new Player("Otro Jugador", 10, 5, 4, 3);
        cout << "--- No hay datos guardados, empiezas con estadisticas default ---" << endl;
        return new Player("Victor", 40, 10, 5, 3);
    }
}

int main() {

    Player *player = loadPlayerInfo();
    cout << player->toString() << endl;

    //Player *player = new Player("Victor", 40, 10, 5, 3);
    /*FileHandler *fileHandler = new FileHandler();

    char* buffer = player->serialize();

    fileHandler->writeToFile("Personaje1.data",buffer, Player::BUFFER_SIZE);
    char bufferLectura[Player::BUFFER_SIZE];
    fileHandler->readFromFile("Personaje1.data",bufferLectura, Player::BUFFER_SIZE);

    Player *unserializedPlayer = Player::unserialize(bufferLectura);
    cout << "--- Serializacion ---" << endl;
    cout << unserializedPlayer->toString();
    cout << "---------------------" << endl;*/



    Enemy *enemy = new Enemy("Goblin", 60, 7, 3, 5, 20);
    Enemy *enemy2 = new Enemy("Orc", 40, 7, 2, 4, 10);
    Enemy *enemy3 = new Enemy("Cloe", 40, 7, 2, 4, 5);

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
