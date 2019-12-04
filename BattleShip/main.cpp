#include <iostream>
#include"Comando.cpp"

int main() {
    Handshake* handshake = new Handshake;
    handshake->Grabar("FirstPlayer.in");
    _sleep(5000);
    handshake->printMapa(handshake->readOut("FirstPlayer.out"));
    _sleep(5000);
    PlaceFleet* flota = new PlaceFleet;
    flota->readOut("FirstPlayer.out");
    flota->Grabar2("FirstPlayer.in");

    return 0;
}