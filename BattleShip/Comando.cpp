//
// Created by Windows 10 on 30/11/2019.
//

#include <string>
#include <fstream>
#include<sstream>
#include <map>
#include <iostream>
#include <time.h>
#include<stdlib.h>
#include <vector>
#include <algorithm>


using namespace std;

class Comando{
protected:
    string token;
    map<string,string> mapa;
public:
    const string &getToken() const {
        return token;
    }

    Comando() {
        map<string,string>* mapa = new map<string,string>;
    }

    void Grabar(string nombreArchivo){
        fstream* archivo = new fstream(nombreArchivo, ios_base::out);
        if(archivo)
        {
            *archivo << generarComando();
        }
        archivo->close();
        delete archivo;
    }

    void Grabar2(string nombreArchivo){
        fstream* archivo = new fstream(nombreArchivo,ios_base::out);
        if(archivo){
            *archivo << "TOKEN=" << mapa["TOKEN"] << "\n" << generarComando();
        }
        archivo->close();
        delete archivo;
    }



    virtual string generarComando()=0;

    void divideLine(string line, string *cmd, string *value){
        string info;
        unsigned int counter = 0;
        stringstream stream(line);
        while(getline(stream,info,'=')){
            if(counter %2 == 0)
                *cmd = info;
            else
                *value = info;
            counter++;
        }
    }

    auto readOut(string nombreArchivo){
        string cmd, value, linea;
        fstream* archivo = new fstream(nombreArchivo, ios_base::in);
        if(archivo){
            while(getline(*archivo,linea)){
                divideLine(linea, &cmd, &value);
                mapa[cmd]=value;
            }
            archivo->close();
        }
        delete archivo;
        return mapa;
    }

    void printMapa(map<string,string> mapa){
        for(auto it = mapa.begin(); it !=mapa.end() ; ++it){
            cout << (*it).first << ": " << (*it).second << "\n";
        }
        token = mapa["TOKEN"];
        cout << token;
    }

};

class Handshake : public Comando{
public:
    string generarComando() override{
        return "HANDSHAKE=GRUPO1";
    }

};

class PlaceFleet : public Comando{

public:
    PlaceFleet() {}

    string AirCraft(){
        srand (time(NULL));
        int x=8+rand()%(11-8);
        return "PLACE_FLEET=A-F"+to_string(x)+"-H\n";
    }

    string Battlecruiser(){
        int x=1+rand()%(4-1);
        return "PLACE_FLEET=B-F"+to_string(x)+"-H\n";
    }

    string Battlecruiser2(){
        int x=1+rand()%(5-1);
        return "PLACE_FLEET=B-A"+to_string(x)+"-H\n";
    }

    string Torpedo(){
        string arr[4]={"A","E","J","G"};
          return "PLACE_FLEET=T-" + arr[0] + "7-H\n"+"PLACE_FLEET=T-" + arr[1]+ "7-H\n"+"PLACE_FLEET=T-" + arr[2] + "7-H\n"+"PLACE_FLEET=T-" + arr[3] + "7-H\n";
    }
//4 barcos en la fila 7

    string Submarine(){
        int x=8+rand()%(11-8);
        return "PLACE_FLEET=S-A"+to_string(x)+"-H\n";
    }
    string Submarine2(){
        int x=5+rand()%(7-5);
        return "PLACE_FLEET=S-D"+to_string(x)+"-H\n";
    }

    string generarComando() {

        return AirCraft()+
               Battlecruiser()+
               Battlecruiser2()+
               Submarine()+Submarine2()+
               "PLACE_FLEET=S-I5-V\n"+
               Torpedo();
    }
};





class Attack : public Comando{
    private:
        vector<string>* posicionesValidas;
    public:
        vector<string> *getPosicionesValidas() const {
            return posicionesValidas;
        }

        Attack() {
            posicionesValidas = new vector<string>();
        }

        void llenarVec(){
            for(int i = 1 ; i <= 10; i++ ){
                posicionesValidas->push_back("A" + to_string(i));
                posicionesValidas->push_back("B" + to_string(i));
                posicionesValidas->push_back("C" + to_string(i));
                posicionesValidas->push_back("D" + to_string(i));
                posicionesValidas->push_back("E" + to_string(i));
                posicionesValidas->push_back("F" + to_string(i));
                posicionesValidas->push_back("G" + to_string(i));
                posicionesValidas->push_back("H" + to_string(i));
                posicionesValidas->push_back("I" + to_string(i));
                posicionesValidas->push_back("J" + to_string(i));
            }
        }

        void printVec(){
            for(auto elemento: *posicionesValidas)
                cout << elemento << ", ";
        }

        bool validarAtaque(string coord){
            bool found = false;
            for( auto elem : *posicionesValidas){
                if( elem == coord){
                    found = true;
                    break;
                }
            }
            if(found){
                posicionesValidas->erase(remove(posicionesValidas->begin(),posicionesValidas->end(), coord), posicionesValidas->end());
            } else
                return false;
        }
/*
        string lados(string &word){
            const string ps[10]={"A","B","C","D","E","F","G","H","I","J"};
            string w;
            for(int i=0;i<10;i++) {
                if (ps[i] == word) {
                    w = ps[i + 1];
                }
            }
            return w;

        }

        int arriba(int &x){
            return x-1;
        }
*/
        string atacar() {
            srand(time(NULL));
            int x = rand() % (10);
            const string pos[10] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"};
            string word = pos[rand() % 10];
            if (validarAtaque(word + to_string(x))) {
                string z = "ATTACK=" + word + to_string(x) + "\n";
                return z;
            } else
                atacar();
        }

        string generarComando(){
            return atacar();
        }

    };



