#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <stdexcept>
#include <ctime>

// Forward declarations pentru a evita dependințe circulare
class Match;
class Mesaj;

using namespace std;

extern const unsigned int MAX_LENGTH;

class Utilizator {
protected:
    const int id;
    string nume;
    int varsta;
    char gen;
    float inaltime;
    char* zodie;
    char* bio;
    static int contorID;

public:
    static vector<Utilizator*> listaUtilizatori;

    Utilizator(const string &numeInit, int varstaInit, char genInit, float inaltimeInit, const char* zodieInit, const char* orientareInit, const char* bioInit);
    Utilizator();
    Utilizator(string numeInit, int varstaInit);
    Utilizator(string numeInit, char genInit);
    Utilizator(const Utilizator& other);
    Utilizator& operator=(const Utilizator& other);

    friend istream& operator>>(istream& in, Utilizator& u);
    friend ostream& operator<<(ostream& out, const Utilizator& u);

    int getId() const;
    static void retineUtilizatorul(Utilizator* uti);
    static void afiseazaUtilizatori();
    static Utilizator* cauta(char numeCautat[100]);

    bool operator==(const Utilizator& other) const;
    Utilizator operator+(const Utilizator& other);
    Utilizator operator-(const Utilizator& other);
    bool operator<(const Utilizator& other) const;

    void setNume(const string numeNou);
    const string getNume() const;
    void setVarsta(int varstaNoua);
    int getVarsta() const;
    void setGen(char genNou);
    char getGen() const;
    void setInaltime(float inaltimeNoua);
    float getInaltime() const;
    void setZodie(const char* zodieNoua);
    const char* getZodie() const;
    const char* getBio() const;
    void setBio(const char* bioNoua);

    void afiseazaCompatibilitatea(Utilizator uti);
    virtual void functie(Utilizator u);
    virtual ~Utilizator();
};

class Platit : virtual public Utilizator {
public:
    virtual void mesaj(Utilizator uti) = 0;
    virtual void functie(Utilizator u) override = 0;
    virtual ~Platit() {}
};

class Gold : virtual public Platit {
public:
    Gold();
    Gold(const string numeInit, int varstaInit, char genInit, float inaltimeInit, const char* zodieInit, const char* orientareInit, const char* bioInit);
    Gold(const string numeInit, char genInit);
    Gold(const string numeInit, int varstaInit);
    Gold(const Gold& other);
    Gold(const Utilizator other);
    Gold& operator=(const Gold& other);

    friend ostream& operator<<(ostream& out, const Gold& g);
    friend istream& operator>>(istream& in, Gold& g);

    void mesaj(Utilizator uti) override;
    void functie(Utilizator uti) override;

    ~Gold() {}
};

class Premium : virtual public Platit {
public:
    Premium();
    Premium(const string numeInit, int varstaInit, char genInit, float inaltimeInit, const char* zodieInit, const char* orientareInit, const char* bioInit);
    Premium(const string numeInit, char genInit);
    Premium(const string numeInit, int varstaInit);
    Premium(const Premium& other);
    Premium(const Utilizator other);
    Premium& operator=(const Premium& other);

    friend ostream& operator<<(ostream& out, const Premium& g);
    friend istream& operator>>(istream& in, Premium& g);

    void mesaj(Utilizator uti) override;
    void functie(Utilizator uti) override;

    ~Premium() {}
};

class PremiumGold : public Gold, public Premium {
public:
    PremiumGold();
    PremiumGold(const string numeInit, int varstaInit, char genInit, float inaltimeInit, const char* zodieInit, const char* orientareInit, const char* bioInit);
    PremiumGold(const string numeInit, char genInit);
    PremiumGold(const string numeInit, int varstaInit);
    PremiumGold(const PremiumGold& other);
    PremiumGold(const Utilizator other);
    PremiumGold& operator=(const PremiumGold& other);

    friend ostream& operator<<(ostream& out, const PremiumGold& g);
    friend istream& operator>>(istream& in, PremiumGold& g);

    void mesaj(Utilizator uti) override;
    void functie(Utilizator uti) override;

    ~PremiumGold() {}
};
