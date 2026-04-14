#pragma once
#include <iostream>
#include <string>
#include "Utilizator.h"

using namespace std;

void incarcaUtilizatori(string numeFisier);

class MeniuSingleton {
private:
    char command[256];
    static MeniuSingleton* instanta;
    Utilizator* utilizatorCurent;

    MeniuSingleton();
    
    void afiseazaStart();
    void proceseazaComandaStart(int numberCommand);

    void afiseazaLogat();
    void proceseazaComandaLogat(int numberCommand);

    void asteaptaConfirmare();
    void clearScreen();

public:
    static MeniuSingleton* getInstanta();
    void ruleazaMeniu();
};
