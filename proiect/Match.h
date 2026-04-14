#pragma once

#include <iostream>
#include <map>
#include <set>
#include <cmath>
#include <string>
#include "Utilizator.h"

using namespace std;

class Match {
private:
    Utilizator* utilizator1;
    Utilizator* utilizator2;
    float scorCompatibilitate;
    bool comp;
    
public:
    static map<Utilizator*, set<Utilizator*>> listaMatch;

    Match();
    Match(Utilizator* u1, Utilizator* u2, float scor, bool c);
    Match(Utilizator* u1, Utilizator* u2);
    Match(Utilizator& u1, Utilizator& u2);
    Match(const Match& other);
    
    float calculeaza();

    friend ostream& operator<<(ostream& out, const Match& match);
    Match& operator=(const Match& other);
    bool operator==(const Match& other) const;
    bool operator<(const Match& other) const;
    bool operator>(const Match& other);

    float getScor();
    void setScor(float scor);
    bool getComp();
    const string getNumeU1() const;
    const string getNumeU2() const;
    void setComp(float c);
    void compatibilitate() const;

    ~Match();
};
