#pragma once

#include <iostream>
#include <cstring>
#include <list>
#include "Utilizator.h"

using namespace std;

class Mesaj {
private:
    Utilizator* expeditor;
    Utilizator* destinatar;
    char* text;
    int lungime;
    static list<Mesaj> listaMesaje;

public:
    Mesaj();
    Mesaj(Utilizator* u1, Utilizator* u2, const char* txt, int l);
    Mesaj(Utilizator* u1, Utilizator* u2);
    Mesaj(Utilizator* u1, Utilizator* u2, const char* txt);
    Mesaj(const Mesaj& other);
    
    Mesaj& operator=(const Mesaj& other);

    friend ostream& operator<<(ostream& out, const Mesaj& msj);
    friend istream& operator>>(istream& in, Mesaj& msj);

    static void afiseazaMesaje();

    Mesaj operator+(const Mesaj& other);
    bool operator==(const Mesaj& other) const;

    const char* getText() const;
    Utilizator* getExp() const;
    void setText(const char* txt);

    ~Mesaj();
};
