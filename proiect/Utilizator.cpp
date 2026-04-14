#include "Utilizator.h"
#include "Match.h"
#include "Mesaj.h"
#include "Globals.h"
#include "Afisator.h"
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

int Utilizator::contorID = 1000;
vector<Utilizator*> Utilizator::listaUtilizatori;

Utilizator::Utilizator(const string &numeInit, int varstaInit, char genInit, float inaltimeInit, const char* zodieInit, const char* orientareInit, const char* bioInit)
    : id(contorID++) {
    nume = numeInit;
    varsta = varstaInit;
    gen = genInit;
    inaltime = inaltimeInit;
    try {
        zodie = new char[strlen(zodieInit) + 1];
        strcpy(zodie, zodieInit);
    } catch (const bad_alloc& e) {
        cout << "Eroare la alocarea memoriei " << e.what() << endl;
        throw;
    }
    try {
        bio = new char[strlen(bioInit) + 1];
        strcpy(bio, bioInit);
    } catch (const bad_alloc& e) {
        cout << "Eroare la alocarea memoriei " << e.what() << endl;
        throw;
    }
}

Utilizator::Utilizator() : id(contorID++) {  
    nume = "Anonim";
    varsta = 0;
    inaltime = 0;
    gen = 'X';
    try {
        zodie = new char[MAX_LENGTH];
        strcpy(zodie, "Necunoscuta");
    } catch (const bad_alloc& e) {
        cout << "Eroare la alocarea memoriei " << e.what() << endl;
        throw;
    }
    try {
        bio = new char[1000];
        strcpy(bio, "...");
    } catch (const bad_alloc& e) {
        cout << "Eroare la alocarea memoriei " << e.what() << endl;
        throw;
    }
}

Utilizator::Utilizator(string numeInit, int varstaInit)
    : id(contorID++) {
    nume = numeInit;
    varsta = varstaInit;
    gen = 'X';
    inaltime = 0.0;
    try {
        zodie = new char[MAX_LENGTH];
        strcpy(zodie, "Necunoscuta");
    } catch (const bad_alloc& e) {
        cout << "Eroare la alocarea memoriei " << e.what() << endl;
        throw;
    }
    try {
        bio = new char[1000];
        strcpy(bio, "...");
    } catch (const bad_alloc& e) {
        cout << "Eroare la alocarea memoriei " << e.what() << endl;
        throw;
    }
}

Utilizator::Utilizator(string numeInit, char genInit)
    : id(contorID++) {
    nume = numeInit;
    varsta = 0;
    gen = genInit;
    inaltime = 0.0;
    try {
        zodie = new char[MAX_LENGTH];
        strcpy(zodie, "Necunoscuta");
    } catch (const bad_alloc& e) {
        cout << "Eroare la alocarea memoriei " << e.what() << endl;
        throw;
    }
    try {
        bio = new char[1000];
        strcpy(bio, "...");
    } catch (const bad_alloc& e) {
        cout << "Eroare la alocarea memoriei " << e.what() << endl;
        throw;
    }
}

Utilizator::Utilizator(const Utilizator& other) : id(other.id) {  
    nume =  other.nume;

    try {
        zodie = new char[MAX_LENGTH];
        strcpy(zodie, other.zodie);
    } catch (const bad_alloc& e) {
        cout << "Eroare la alocarea memoriei " << e.what() << endl;
        throw;
    }

    try {
        bio = new char[1000];
        strcpy(bio, other.bio);
    } catch (const bad_alloc& e) {
        cout << "Eroare la alocarea memoriei " << e.what() << endl;
        throw;
    }

    varsta = other.varsta;
    gen = other.gen;
    inaltime = other.inaltime;
}

Utilizator& Utilizator::operator=(const Utilizator& other) {
    if (this != &other) {
        delete[] this->zodie;
        delete[] this->bio;

        nume = other.nume;

        try {
            zodie = new char[MAX_LENGTH];
            strcpy(zodie, other.zodie);
        } catch (const bad_alloc& e) {
            cout << "Eroare la alocarea memoriei " << e.what() << endl;
            throw;
        }

        try {
            bio = new char[MAX_LENGTH];
            strcpy(bio, other.bio);
        } catch (const bad_alloc& e) {
            cout << "Eroare la alocarea memoriei " << e.what() << endl;
            throw;
        }
        
        varsta = other.varsta;
        gen = other.gen;
        inaltime = other.inaltime;
    }
    return *this;
}

istream& operator>>(istream& in, Utilizator& u) {
    string nume;
    int varsta;
    char gen;
    float inaltime;
    char zodie[256];
    char bio[1000];

    while (true) {
        try {
            cout << "Introdu numele: ";
            in.ignore();
            getline(in, nume);
            if (!regex_match(nume, regex("^[A-Za-z]{2,}(\\s[A-Za-z]+)*$")))
                throw invalid_argument("Nume invalid. Foloseste doar litere si spatii (minim 2 caractere).");
            break;
        } catch (const exception& e) {
            cerr << "Eroare: " << e.what() << endl;
        }
    }

    while (true) {
        try {
            cout << "Introdu varsta: ";
            in >> varsta;
            if (in.fail() || varsta <= 0 || varsta > 120)
                throw out_of_range("Varsta invalida.");
            in.ignore();
            break;
        } catch (const exception& e) {
            cerr << "Eroare: " << e.what() << endl;
            in.clear(); 
            in.ignore(1000, '\n'); 
        }
    }

    while (true) {
        try {
            cout << "Introdu genul (m/f): ";
            in >> gen;
            gen = tolower(gen);
            if (gen != 'm' && gen != 'f')
                throw invalid_argument("Gen invalid. Trebuie sa fie 'm' sau 'f'.");
            in.ignore();
            break;
        } catch (const exception& e) {
            cerr << "Eroare: " << e.what() << endl;
            in.clear();
            in.ignore(1000, '\n');
        }
    }

    while (true) {
        try {
            cout << "Introdu inaltimea in metri (ex: 1.75): ";
            in >> inaltime;
            if (in.fail() || inaltime < 0.5f || inaltime > 2.5f)
                throw out_of_range("Inaltime invalida.");
            in.ignore();
            break;
        } catch (const exception& e) {
            cerr << "Eroare: " << e.what() << endl;
            in.clear();
            in.ignore(1000, '\n');
        }
    }

    while (true) {
        try {
            cout << "Introdu zodia: ";
            in.getline(zodie, 256);
            if (!regex_match(string(zodie), regex("^[A-Za-z]{3,15}$")))
                throw invalid_argument("Zodie invalida. Trebuie sa fie un cuvant intre 3-15 litere.");
            break;
        } catch (const exception& e) {
            cerr << "Eroare: " << e.what() << endl;
        }
    }

    while (true) {
        try {
            cout << "Introdu o scurta descriere: ";
            in.getline(bio, 1000);
            if (strlen(bio) < 3)
                throw invalid_argument("Descriere prea scurta.");
            break;
        } catch (const exception& e) {
            cerr << "Eroare: " << e.what() << endl;
        }
    }

    u.setNume(nume);
    u.setVarsta(varsta);
    u.setGen(gen);
    u.setInaltime(inaltime);
    u.setZodie(zodie);
    u.setBio(bio);

    return in;
}

ostream& operator<<(ostream& out, const Utilizator& u) {
    out << "Datele utilizatorului sunt: " << endl;
    out << "ID: " << u.id << endl;
    out << "Nume: " << u.nume << endl;
    out << "Varsta: " << u.varsta << endl;
    out << "Gen: " << u.gen << endl;
    out << "Inaltimea: " << u.inaltime << " cm" << endl;
    out << "Zodie: " << u.zodie << endl;
    out << "Bio: " << u.bio << endl;
    out << endl;
    return out;
}

int Utilizator::getId() const { return id; }

void Utilizator::retineUtilizatorul(Utilizator* uti) {
    listaUtilizatori.push_back(uti);
    cout << "Utilizatorul cu ID: " << uti->getId() << " a fost adaugat." << endl;

    fout << "Utilizatorul cu ID: " << uti->getId() << " a fost adaugat." << endl;

    for (auto& alt : Utilizator::listaUtilizatori) {
                if (*alt == *uti) 
                    continue;

                Match m(uti, alt);
                if (m.getComp()) {
                    Match::listaMatch[uti].insert(alt);
                    Match::listaMatch[alt].insert(uti);
                    time_t now;
                    time(&now);
                    char* dt = ctime(&now);
                    fmatch << dt << " Un match între utilizatorul " << uti->getNume() << " și utilizatorul " << alt->getNume() << " a fost adăugat" << endl;
        }
    }
}

void Utilizator::afiseazaUtilizatori() {
    cout << endl;
    cout << "Lista utilizatorilor:" << endl;
    for (const auto& u : listaUtilizatori) {
        cout << "Utilizatorul " << u->getId() << " : " << u->getNume() << endl;
    }
}

Utilizator* Utilizator::cauta(char numeCautat[100]) {
    for (auto& u : listaUtilizatori) {
        if (u != nullptr) {
            if (u->getNume() == string(numeCautat)) {
                return u;
            }
        }
    }
    return nullptr;
}

bool Utilizator::operator==(const Utilizator& other) const { return this->id == other.id; }

Utilizator Utilizator::operator+(const Utilizator& other) {
    this->varsta += other.varsta;
    this->inaltime += other.inaltime;
    return *this;
}

Utilizator Utilizator::operator-(const Utilizator& other) {
    this->varsta -= other.varsta;
    this->inaltime -= other.inaltime;
    return *this;
}

bool Utilizator::operator<(const Utilizator& other) const { return this->nume < other.nume; }

void Utilizator::setNume(const string numeNou) { nume = numeNou; }
const string Utilizator::getNume() const { return nume; }

void Utilizator::setVarsta(int varstaNoua) { if(varstaNoua > 0) varsta = varstaNoua; }
int Utilizator::getVarsta() const { return varsta; }

void Utilizator::setGen(char genNou) { if(genNou == 'f' || genNou == 'F' || genNou == 'm' || genNou == 'M') gen = genNou; }
char Utilizator::getGen() const { return gen; }

void Utilizator::setInaltime(float inaltimeNoua) { inaltime = inaltimeNoua; }
float Utilizator::getInaltime() const { return inaltime; }

void Utilizator::setZodie(const char* zodieNoua) {
    delete[] zodie;
    try {
        zodie = new char[strlen(zodieNoua) + 1];
        strcpy(zodie, zodieNoua);
    } catch (const bad_alloc& e) {
        cout << "Eroare la alocarea memoriei " << e.what() << endl;
        throw;
    }
}
const char* Utilizator::getZodie() const { return zodie; }

const char* Utilizator::getBio() const { return bio; }

void Utilizator::setBio(const char* bioNoua) {
    delete[] bio;
    try {
        bio = new char[strlen(bioNoua) + 1];
        strcpy(bio, bioNoua);
    } catch (const bad_alloc& e) {
        cout << "Eroare la alocarea memoriei " << e.what() << endl;
        throw;
    }
}

void Utilizator::afiseazaCompatibilitatea(Utilizator uti) {
    cout << "Lista utilizatorilor cu care " << uti.getNume() << " este compatibil este ";

    auto it = Match::listaMatch.find(&uti);
    if (it == Match::listaMatch.end() || it->second.empty()) {
        cout << "goala" << endl;
        return;
    }

    Afisator<set<Utilizator*>> afisator;
    afisator.afiseaza(it->second);
}

void Utilizator::functie(Utilizator u) {
    cout << "Functie standard" << endl;
}

Utilizator::~Utilizator() {
    delete[] this->zodie;
    delete[] this->bio;
}

// Gold Implementations
Gold::Gold() : Utilizator() {}
Gold::Gold(const string numeInit, int varstaInit, char genInit, float inaltimeInit, const char* zodieInit, const char* orientareInit, const char* bioInit) : Utilizator(numeInit, varstaInit, genInit, inaltimeInit, zodieInit, orientareInit, bioInit) {}
Gold::Gold(const string numeInit, char genInit) : Utilizator(numeInit, genInit) {}
Gold::Gold(const string numeInit, int varstaInit) : Utilizator(numeInit, varstaInit) {}
Gold::Gold(const Gold& other) : Utilizator(other) {}
Gold::Gold(const Utilizator other) : Utilizator(other) {}
Gold& Gold::operator=(const Gold& other) { if (this != &other) Utilizator::operator=(other); return *this; }
ostream& operator<<(ostream& out, const Gold& g) { out << static_cast<const Utilizator&>(g); return out; }
istream& operator>>(istream& in, Gold& g) { in >> static_cast<Utilizator&>(g); return in; }
void Gold::mesaj(Utilizator uti) { cout << "Aceasta funcționalitate este disponibila doar pentru utilizatorii Premium și PremiumGold." << endl; }
void Gold::functie(Utilizator uti) {
    cout << "Utilizatorii compatibili cu " << uti.getNume() << " sunt:";
    int sw = 0;
    for(int i = 0; i < listaUtilizatori.size(); i++){
        if(*(listaUtilizatori[i]) == uti) continue;
        Match match(uti, *(listaUtilizatori[i]));
        if(match.getComp() == true){
            if(sw == 0) cout << endl;
            sw = 1;
            cout << "Utilizatorul " <<listaUtilizatori[i]->getNume() << " cu varsta de " << listaUtilizatori[i]->getVarsta() << ", zodia " << listaUtilizatori[i]->getZodie() << ", inaltimea " << listaUtilizatori[i]->getInaltime() << " si care se descrie ca fiind #" << listaUtilizatori[i]->getBio() << "#." << endl;
        }
    }
    if(sw == 0) cout << "inexistenti." << endl;
}

// Premium Implementations
Premium::Premium() : Utilizator() {}
Premium::Premium(const string numeInit, int varstaInit, char genInit, float inaltimeInit, const char* zodieInit, const char* orientareInit, const char* bioInit) : Utilizator(numeInit, varstaInit, genInit, inaltimeInit, zodieInit, orientareInit, bioInit) {}
Premium::Premium(const string numeInit, char genInit) : Utilizator(numeInit, genInit) {}
Premium::Premium(const string numeInit, int varstaInit) : Utilizator(numeInit, varstaInit) {}
Premium::Premium(const Premium& other) : Utilizator(other) {}
Premium::Premium(const Utilizator other) : Utilizator(other) {}
Premium& Premium::operator=(const Premium& other) { if (this != &other) { Utilizator::operator=(other); } return *this; }
ostream& operator<<(ostream& out, const Premium& g) { out << static_cast<const Utilizator&>(g); return out; }
istream& operator>>(istream& in, Premium& g) { in >> static_cast<Utilizator&>(g); return in; }
void Premium::mesaj(Utilizator uti){
    Mesaj ms;
    cin >> ms;
    if(ms.getExp()->getNume() != uti.getNume()){
        cout << "Expeditor invalid." << endl;
    }else{
        cout << "Mesajul a fost înregistrat!" << endl;
        cout << endl << ms;
    } 
}
void Premium::functie(Utilizator uti) {
    float maxi = 0;
    string pers;
    for(int i = 0; i < listaUtilizatori.size(); i++){
        if(*listaUtilizatori[i] == uti) continue;
        Match meci(uti, *listaUtilizatori[i]);
        if(meci.getScor() > maxi){
            maxi = meci.getScor();
            pers = listaUtilizatori[i]->getNume();
        }
    }
    cout << "Cea mai buna potrivire e utilizatorului Premium " << uti.getNume() << " este " << pers << " cu un scor de compatibilitate de "<< maxi << " puncte." << endl;
}

// PremiumGold Implementations
PremiumGold::PremiumGold() : Utilizator() {}
PremiumGold::PremiumGold(const string numeInit, int varstaInit, char genInit, float inaltimeInit, const char* zodieInit, const char* orientareInit, const char* bioInit) : Utilizator(numeInit, varstaInit, genInit, inaltimeInit, zodieInit, orientareInit, bioInit) {}
PremiumGold::PremiumGold(const string numeInit, char genInit) : Utilizator(numeInit, genInit) {}
PremiumGold::PremiumGold(const string numeInit, int varstaInit) : Utilizator(numeInit, varstaInit) {}
PremiumGold::PremiumGold(const PremiumGold& other) : Utilizator(other) {}
PremiumGold::PremiumGold(const Utilizator other) : Utilizator(other) {}
PremiumGold& PremiumGold::operator=(const PremiumGold& other) { if (this != &other) Utilizator::operator=(other); return *this; }
ostream& operator<<(ostream& out, const PremiumGold& g) { out << static_cast<const Utilizator&>(g); return out; }
istream& operator>>(istream& in, PremiumGold& g) { in >> static_cast<Utilizator&>(g); return in; }
void PremiumGold::mesaj(Utilizator uti) {
    Mesaj ms;
    cin >> ms;
    if (ms.getExp()->getNume() != uti.getNume()) {
        cout << "Expeditor invalid." << endl;
    } else {
        cout << "Mesajul a fost înregistrat!" << endl;
        cout << endl << ms;
        time_t now;
        time(&now);
        char* dt = ctime(&now);
        fmes << "La data de " << dt << "Mesajul a fost înregistrat" << endl << ms << endl;
    }
}
void PremiumGold::functie(Utilizator uti) {
    cout << "Alege un utilizator din lista de mai jos pentru a forma un match special:" << endl;
    Utilizator::afiseazaUtilizatori();

    cout << "Introdu numele utilizatorului ales: ";
    char numeCautat[100];
    cin.ignore();
    cin.getline(numeCautat, 100);

    Utilizator* gasit = Utilizator::cauta(numeCautat);
    if (gasit == nullptr) {
        cout << "Utilizator inexistent." << endl;
        return;
    }

    Match matchFortat(this, gasit, 100.0f, true);
    Match::listaMatch[this].insert(gasit);
    Match::listaMatch[gasit].insert(this);

    time_t now;
    time(&now);
    char* dt = ctime(&now);
    fmatch << dt << " Un match forțat între utilizatorul " << uti.getNume() << " și utilizatorul " << gasit->getNume() << " a fost adăugat" << endl;

    cout << "Utilizatorii " << this->getNume() << " si " << gasit->getNume() << " sunt acum suflete pereche cu scor 100%!" << endl;
}
