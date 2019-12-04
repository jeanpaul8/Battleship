#include <iostream>
#include"Comando.cpp"
#include <chrono>

int main() {

    // HANDSHAKE TEAM 1
    Handshake* handshake = new Handshake;
    handshake->Grabar("FirstPlayer.in");

    // HANDSHAKE TEAM 2
    Handshake* handshake1 = new Handshake;
    handshake1->Grabar("SecondPlayer.in");
    _sleep(500);

    cout << "Primer equipo: " <<  "\n";
    handshake->printMapa(handshake->readOut("FirstPlayer.out"));
    cout << "Segundo equipo: " <<  "\n";
    handshake1->printMapa(handshake1->readOut("SecondPlayer.out"));
    cout << "\n";
    _sleep(500);

    // PLACE FLEET
    PlaceFleet* flota = new PlaceFleet;
    PlaceFleet* flota2 = new PlaceFleet;
    flota->readOut("FirstPlayer.out");
    flota2->readOut("SecondPlayer.out");
    flota->Grabar2("FirstPlayer.in");
    _sleep(500);
    flota2->Grabar2("SecondPlayer.in");
    _sleep(500);

    // CREACION DE ATAQUES
    Attack* attack = new Attack;
    Attack* attack2 = new Attack;

    bool game = true;
    //LOOP DE JUEGO?
    while(game == true) {
        //LOOPS DE TURNO ?
        bool turn1 = true;
        bool turn2 = true;
        while (turn1) {
            _sleep(500);
            if (attack->readOut("FirstPlayer.out")["STATUS"] == "ACCEPTED" &&
                attack->readOut("FirstPlayer.not")["NOTIFICATION"] == "YOUR TURN") {
                attack->Grabar2("FirstPlayer.in");
                _sleep(500);
                if(attack->readOut("FirstPlayer.not")["NOTIFICATION"] == "YOU WIN!" ||
                   attack->readOut("FirstPlayer.not")["NOTIFICATION"] == "YOU LOSE")
                    break;
                if ((attack->readOut("FirstPlayer.out")["MESSAGE"] == "DAMAGED" ||
                     attack2->readOut("SecondPlayer.out")["MESSAGE"] == "DESTROYED") &&
                    attack->readOut("FirstPlayer.not")["NOTIFICATION"] == "YOUR TURN")
                    turn1 = true;
                else
                    turn1 = false;
            }
        }
        _sleep(500);

        while (turn2) {
            _sleep(500);
            if (attack2->readOut("SecondPlayer.out")["STATUS"] == "ACCEPTED" &&
                attack2->readOut("SecondPlayer.not")["NOTIFICATION"] == "YOUR TURN") {
                attack2->Grabar2("SecondPlayer.in");
                _sleep(500);
                if(attack2->readOut("SecondPlayer.not")["NOTIFICATION"] == "YOU WIN!" ||
                   attack2->readOut("SecondPlayer.not")["NOTIFICATION"] == "YOU LOSE")
                    break;
                if ((attack2->readOut("SecondPlayer.out")["MESSAGE"] == "DAMAGED" ||
                     attack2->readOut("SecondPlayer.out")["MESSAGE"] == "DESTROYED") &&
                    attack2->readOut("SecondPlayer.not")["NOTIFICATION"] == "YOUR TURN")
                    turn2 = true;
                else
                    turn2 = false;
            }
        }
        _sleep(500);
        if(attack->readOut("FirstPlayer.not")["NOTIFICATION"] == "YOU WIN!" ||
           attack->readOut("FirstPlayer.not")["NOTIFICATION"] == "YOU LOSE"){
            cout << "JUEGO TERMINADO! \n";
            game = false;
        }
    }


    return 0;
}