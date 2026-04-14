#include <iostream>
#include "Utilizator.h"
#include "Meniu.h"
#include "Globals.h"

using namespace std;

int main() {
    Utilizator *u1 = new Utilizator("Andrei", 30, 'm', 1.80, "Taur", "Heterosexual", "Programator pasionat de tehnologie");
    Utilizator *u2 = new Utilizator("Maria", 30, 'f', 1.75, "Taur", "Heterosexual", "Designer creativ");
    Utilizator *u3 = new Utilizator("Ion", 20, 'm', 1.50, "Gemeni", "Heterosexual", "Sportiv și iubitor de natură");
    Utilizator *u4 = new Utilizator("Melysa", 22, 'f', 1.40, "Gemeni", "Heterosexual", "Buna rau");
    
    Utilizator::retineUtilizatorul(u1);
    Utilizator::retineUtilizatorul(u2);
    Utilizator::retineUtilizatorul(u3);
    Utilizator::retineUtilizatorul(u4);

    do {
        MeniuSingleton::getInstanta()->ruleazaMeniu();
#pragma warning(suppress: 4127) // ca să oprim warning la do { } while (true) in visual studio std
    } while (true);

    for (Utilizator* u : Utilizator::listaUtilizatori) {
        delete u;
    }
    Utilizator::listaUtilizatori.clear();

    fout.close();
    fmes.close();
    fmatch.close();

    return 0;
}
