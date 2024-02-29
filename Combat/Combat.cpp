//
// Created by Victor Navarro on 19/02/24.
//

#include "Combat.h"
#include <string>
#include <iostream>
#include <utility>
#include <algorithm>

using namespace std;

bool compareSpeed(Character *a, Character *b) {
    return a->getSpeed() > b->getSpeed();
}

Combat::Combat(vector<Character *> _participants) {
    participants = std::move(_participants);
    for(auto participant : participants) {
        if (participant->getIsPlayer()) {
            partyMembers.push_back((Player *) participant);
        } else {
            enemies.push_back((Enemy *) participant);
        }
    }
}

Combat::Combat(vector<Player*> _partyMembers, vector<Enemy*> _enemies) {
    partyMembers = std::move(_partyMembers);
    enemies = std::move(_enemies);
    participants = vector<Character*>();
    participants.insert(participants.end(), partyMembers.begin(), partyMembers.end());
    participants.insert(participants.end(), enemies.begin(), enemies.end());
}

Combat::Combat() {
    participants = vector<Character*>();
}

void Combat::addParticipant(Character *participant) {
    participants.push_back(participant);
    if(participant->getIsPlayer()){
        partyMembers.push_back((Player*) participant);
    } else {
        enemies.push_back((Enemy*) participant);
    }
}

void Combat::combatPrep() {
    // Sort participants by speed
    sort(participants.begin(), participants.end(), compareSpeed);
}

string Combat::toString() {
    string result = "";
    vector<Character*>::iterator it;
    for(it = participants.begin(); it != participants.end(); it++){
        result += (*it)->toString() + "\n";
    }
    cout<<"===================="<<endl;
    return result;
}

Character* Combat::getTarget(Character* attacker) {
    vector<Character*>::iterator it;
    for(it = participants.begin(); it != participants.end(); it++){
        if((*it)->getIsPlayer() != attacker->getIsPlayer()){
            return *it;
        }
    }
    //TODO: Handle this exception
    return nullptr;
}

void Combat::doCombat() {
    cout << "Inicio del combate" << endl;
    combatPrep();
    while (participants.size() > 1) {
        for (auto participant : participants) {
            cout << "------ Turno de " << participant->getName() << " ------" << endl;
            cout << participant->getName() << " (Salud: " << participant->getHealth() << ", Defensa: " << participant->getDefense() << ", Velocidad: " << participant->getSpeed() << ")" << endl;

            Character *target = nullptr;
            if (participant->getIsPlayer()) {
                cout << "Es tu turno, " << participant->getName() << endl;
                cout << "Selecciona una opción:\n1. Atacar\n2. Defender" << endl;
                int choice;
                cin >> choice;
                if (choice == 2) {
                    participant->defend();
                    cout << participant->getName() << " se ha defendido. Su defensa ha aumentado en un 20% por este turno." << endl;
                    cout << "Teniendo de nueva defensa por este turno: " << participant->getDefense() << endl;
                    // Restablecer la defensa del jugador al valor original al finalizar su turno
                    dynamic_cast<Player*>(participant)->resetDefense(); // Si participant es un jugador, se llama a resetDefense
                    continue; // Omite la fase de ataque si la jugadora elige defenderse.
                }
                target = ((Player *)participant)->selectTarget(enemies);
            } else {
                // Calcular el 15% de la salud máxima del participante
                double fifteenPercentMaxHealth = 0.15 * participant->getMaxHealth();
                // Verificar si la salud actual del participante es menor que el 15% de su salud máxima
                if (participant->getHealth() < fifteenPercentMaxHealth) {
                    int chance = rand();
                    //calcular el 40% de rand_max
                    int limite = static_cast<int>(RAND_MAX * 0.4);
                    cout << "Probabilidad generada: " << chance << endl; // Imprimir la probabilidad generada aleatoriamente
                    //verificar si el numero cae en el 40% del rango
                    if (chance <= limite) {
                        participant->defend();
                        cout << participant->getName() << " decide defenderse al tener menos del 15% de vida." << endl;
                        continue; // Omite la fase de ataque si la jugadora elige defenderse.
                    }
                }
                target = ((Enemy *)participant)->selectTarget(partyMembers);
            }
            cout << participant->getName() << " ataca a " << target->getName() << "!" << endl;
            participant->doAttack(target);
            if (target->getHealth() <= 0) {
                // Remove the defeated target from the combat
                participants.erase(remove(participants.begin(), participants.end(), target), participants.end());
                // Remove the target from their respective group (player or enemy)
                if (target->getIsPlayer()) {
                    partyMembers.erase(remove(partyMembers.begin(), partyMembers.end(), target), partyMembers.end());
                    if (partyMembers.empty()) {
                        cout << "Game Over" << endl;
                        return;
                    }
                } else {
                    cout << "You killed enemy " << target->getName() << endl;
                    enemies.erase(remove(enemies.begin(), enemies.end(), target), enemies.end());
                    if (enemies.empty()) {
                        cout << "Victory" << endl;
                        return;
                    }
                }
            }
        }
    }
}