#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <set>
#include <list>
#include <map>
#include <fstream>
#include <stdexcept>
#include <ctime>
#include <regex>
using namespace std;

const unsigned int MAX_LENGTH = 256;

ofstream fout("utilizatori.out");
ofstream fmatch("match.out");
ofstream fmes("mesaj.out");



template <typename Container>
class Afisator {
public:
    void afiseaza(const Container& cont) const {
    for (const auto& elem : cont) {
        if constexpr (std::is_pointer_v<typename Container::value_type>)
            cout << *elem << endl;
        else
            cout << elem << endl;
    }
}

    template <typename Predicate>
    bool cauta(Container& cont, Predicate predicat) const {
        auto it = find_if(cont.begin(), cont.end(), predicat);
        if (it != cont.end()) {
            return true;
        } else {
            return false;
        }
    }
};

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
    // constructor cu toti parametrii
    Utilizator(const string &numeInit, int varstaInit, char genInit, float inaltimeInit, const char* zodieInit, const char* orientareInit, const char* bioInit)
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

    // constructor fara parametri
    Utilizator() : id(contorID++) {  // id unic pt fiecare utilizator
        // dam valori implicite atributelor la creare
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

    // Constructor cu 2 parametri (nume și varsta)
    Utilizator(string numeInit, int varstaInit)
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

    // Constructor cu 2 parametri (nume și gen)
    Utilizator(string numeInit, char genInit)
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

    // constr de copiere
    Utilizator(const Utilizator& other) : id(other.id) {  // pastram id ul initial
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

    // operator de atribuire
    Utilizator& operator=(const Utilizator& other) {
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

    friend istream& operator>>(istream& in, Utilizator& u) {
        string nume;
        int varsta;
        char gen;
        float inaltime;
        char zodie[MAX_LENGTH];
        char bio[1000];

        // Nume
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

        // Varsta
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
                in.clear(); // resetam starea streamului
                in.ignore(1000, '\n'); // curatam restul liniei
            }
        }

        // Gen
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

        // Inaltime
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

        // Zodie
        while (true) {
            try {
                cout << "Introdu zodia: ";
                in.getline(zodie, MAX_LENGTH);
                if (!regex_match(string(zodie), regex("^[A-Za-z]{3,15}$")))
                    throw invalid_argument("Zodie invalida. Trebuie sa fie un cuvant intre 3-15 litere.");
                break;
            } catch (const exception& e) {
                cerr << "Eroare: " << e.what() << endl;
            }
        }

        // Bio
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

    friend ostream& operator<<(ostream& out, const Utilizator& u) {
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

    int getId() const {
        return id;
    }

    // creare cont
    static void retineUtilizatorul(Utilizator* uti);

    // afisare toti utilizatorii
    static void afiseazaUtilizatori() {
        cout << endl;
        cout << "Lista utilizatorilor:" << endl;
        for (const auto& u : listaUtilizatori) {
            cout << "Utilizatorul " << u->getId() << " : " << u->getNume() << endl;
        }
    }

    // gaseste un utilizator dupa nume
    static Utilizator* cauta(char numeCautat[100]) {
        for (auto& u : listaUtilizatori) {
            if (u != nullptr) {
                if (u->getNume() == numeCautat) {
                    return u;
                }
            }
        }
        return nullptr;
    }
    

    // operator == 
    bool operator==(const Utilizator& other) const {
        if (this->id == other.id){
            return true;
        }else
            return false;
    }

    // operator +
    Utilizator operator+(const Utilizator& other) {
        this->varsta += other.varsta;
        this->inaltime += other.inaltime;
        return *this;
    }

    // operator -
    Utilizator operator-(const Utilizator& other) {
        this->varsta -= other.varsta;
        this->inaltime -= other.inaltime;
        return *this;
    }

    bool operator<(const Utilizator& other) const {
        return this->nume < other.nume;
    }


    // setters si getters
    void setNume(const string numeNou) {
        nume = numeNou;
    }

    const string getNume() const {
        return nume;
    }

    void setVarsta(int varstaNoua) {
        if(varstaNoua > 0)
            varsta = varstaNoua;
    }

    int getVarsta() const {
        return varsta;
    }

    void setGen(char genNou) {
        if(genNou == 'f' || genNou == 'F' || genNou == 'm' || genNou == 'M')
            gen = genNou;
    }

    char getGen() const {
        return gen;
    }

    void setInaltime(float inaltimeNoua) {
        inaltime = inaltimeNoua;
    }

    float getInaltime() const {
        return inaltime;
    }

    void setZodie(const char* zodieNoua) {
        delete[] zodie;

        try {
                zodie = new char[strlen(zodieNoua) + 1];
                strcpy(zodie, zodieNoua);
            } catch (const bad_alloc& e) {
                cout << "Eroare la alocarea memoriei " << e.what() << endl;
                throw;
            }
    }

    const char* getZodie() const {
        return zodie;
    }

    const char* getBio() const {
        return bio;
    }

    void setBio(const char* bioNoua) {
        delete[] bio;
        try {
                bio = new char[strlen(bioNoua) + 1];
                strcpy(bio, bioNoua);
            } catch (const bad_alloc& e) {
                cout << "Eroare la alocarea memoriei " << e.what() << endl;
                throw;
            }
    }
    

    void afiseazaCompatibilitatea(Utilizator uti);

    virtual void functie(Utilizator u) {
        cout << "Functie standard" << endl;
    }

    // destructor
    virtual ~Utilizator() {
        delete[] this->zodie;
        delete[] this->bio;
    }

};

class Match {
private:
    Utilizator* utilizator1;
    Utilizator* utilizator2;
    float scorCompatibilitate;
    bool comp;
    
public:
    static map<Utilizator*, set<Utilizator*>> listaMatch;
    // constr fara parametri
    Match(){
        utilizator1 = nullptr;
        utilizator2 = nullptr;
        scorCompatibilitate = 0.0;
        comp = false;
    }

    // constr cu toti parametrii
    Match(Utilizator* u1, Utilizator* u2, float scor, bool c){
        utilizator1 = u1;
        utilizator2 = u2;
        scorCompatibilitate = scor;
        comp = c;
    }

    // constr cu 2 parametri (utilizator1 si utilizator2)
    Match(Utilizator* u1, Utilizator* u2) {
        utilizator1 = new Utilizator(*u1);
        utilizator2 = new Utilizator(*u2);
        scorCompatibilitate = calculeaza();
        comp = scorCompatibilitate > 50;
    }

    // o o
    Match(Utilizator& u1, Utilizator& u2) {
        utilizator1 = new Utilizator(u1);
        utilizator2 = new Utilizator(u2);
        scorCompatibilitate = calculeaza();
        comp = scorCompatibilitate > 50;
    }


    float calculeaza(){
        // for(int i = 0; i < listaMatch.size(); i++){
        //     cout << listaMatch[i].utilizator1->getNume() << endl << this->utilizator1->getNume() << endl;
        //     cout << listaMatch[i].utilizator2->getNume() << endl << this->utilizator2->getNume() << endl;
        //     if((strcmp(listaMatch[i].utilizator1->getNume(), this->utilizator1->getNume()) == 0 && strcmp(listaMatch[i].utilizator2->getNume(), this->utilizator2->getNume()) == 0)  || (strcmp(listaMatch[i].utilizator1->getNume(), this->utilizator2->getNume()) == 0 && strcmp(listaMatch[i].utilizator2->getNume(), this->utilizator1->getNume()) == 0)){
        //         return listaMatch[i].getScor();
        //     }
        // }

        // for (const auto& m : listaMatch) {
        //     if ((m.utilizator1 == utilizator1 && m.utilizator2 == utilizator2) ||
        //         (m.utilizator1 == utilizator2 && m.utilizator2 == utilizator1)) {
        //         return m.scorCompatibilitate;
        //     }
        // }

        float scor = 0;

        if ((utilizator1->getGen() == 'm' && utilizator2->getGen() == 'f') ||
            (utilizator1->getGen() == 'f' && utilizator2->getGen() == 'm')) {
            scor += 30;
        }

        int diferentaVarsta = abs(utilizator1->getVarsta() - utilizator2->getVarsta());
        if (diferentaVarsta <= 5){
            scor += 20;
        }else if (diferentaVarsta <= 10){
            scor += 10;
        }

        float diferentaInaltime = abs(utilizator1->getInaltime() - utilizator2->getInaltime());
        if (diferentaInaltime <= 0.15) 
            scor += 15;
        else if (diferentaInaltime <= 0.30) 
                scor += 10;

        if (utilizator1->getZodie() == utilizator2->getZodie()) {
            scor += 40;
        }

        return min(scor, 100.0f);
    }

    // constuctor de copiere
    Match(const Match& other){
        utilizator1 = new Utilizator(*other.utilizator1);
        utilizator2 = new Utilizator(*other.utilizator2);
        scorCompatibilitate = other.scorCompatibilitate;
        comp = other.comp;
    }

    // supraincarcarea operatorilor >> si <<
    // friend istream& operator>>(istream& in, Match& match) {
    //     cout << "Introdu numele primului utilizator: ";
    //     in >> match.utilizator1;

    //     cout << "Introdu numele celui de-al doilea utilizator: ";
    //     in >> match.utilizator2;

    //     return in;
    // }

    friend ostream& operator<<(ostream& out, const Match& match) {
        out << "Primul utilizator: " << match.utilizator1 << endl;
        out << "Al doilea utilizator: " << match.utilizator2 << endl;
        out << "Procent de compatibilitate: " << match.scorCompatibilitate << endl;
        out << "Concluzia compatibilitatii: " << match.comp << endl;

        return out;
    }

    // atribuire 
    Match& operator=(const Match& other){
        if (this != &other){
            delete utilizator1;
            delete utilizator2;
            utilizator1 = new Utilizator(*other.utilizator1);
            utilizator2 = new Utilizator(*other.utilizator2);
            scorCompatibilitate = other.scorCompatibilitate;
            comp = other.comp;
        }
        return *this;
    }

    // operatorul == verifica daca e aceeasi pereche
    bool operator==(const Match& other) const{
        if ((*utilizator1 == *other.utilizator1 && *utilizator2 == *other.utilizator2) || (*utilizator1 == *other.utilizator2 && *utilizator2 == *other.utilizator1)){
            return true;
        }else{
            return false;
        }
    }

    // operatorii < si > compara compatibilitatile
    bool operator<(const Match& other) const {
        return scorCompatibilitate < other.scorCompatibilitate;
    }

    bool operator>(const Match& other){
        return scorCompatibilitate > other.scorCompatibilitate;
    }

    // getteri si setteri
    float getScor(){ 
        return scorCompatibilitate; 
    }
    void setScor(float scor){
        scorCompatibilitate = scor; 
    }

    bool getComp(){
        return comp;
    }

    const string getNumeU1() const{
        return utilizator1->getNume();
    }

    const string getNumeU2() const {
        return utilizator2->getNume();
    }


    void setComp(float c){
        comp = c;
    }

    // afisare compatibilitate
    void compatibilitate() const{
        cout << "Compatibilitatea între " << utilizator1->getNume() << " si " << utilizator2->getNume() << " este de " << scorCompatibilitate << "%" << endl;
    }

    // destructor
    ~Match(){
        delete this->utilizator1;
        delete this->utilizator2;
    }

};


class Mesaj {
private:
    Utilizator* expeditor;
    Utilizator* destinatar;
    char* text;
    int lungime;
    static list<Mesaj> listaMesaje;

public:
    // constructor fara parametri
    Mesaj(){
        expeditor = nullptr;
        destinatar = nullptr;
        text = new char[MAX_LENGTH];
        strcpy(text, "");
        lungime = 0;
    }

    // constr cu toti parametrii
    Mesaj(Utilizator* u1, Utilizator* u2, const char* txt, int l){
        expeditor = u1;
        destinatar = u2;
        text = new char[MAX_LENGTH];
        strcpy(text, txt);
        lungime = l;
    }

    // constr cu 2 parametri (destinatar si expeditor)
    Mesaj(Utilizator* u1, Utilizator* u2){
        expeditor = u1;
        destinatar = u2;
        text = new char[MAX_LENGTH];
        strcpy(text, "");
        lungime = 0;
    }

    // constr cu 3 parametri (destinatar, expeditor si mesaj)
    Mesaj(Utilizator* u1, Utilizator* u2, const char* txt){
        expeditor = u1;
        destinatar = u2;
        text = new char[MAX_LENGTH];
        strcpy(text, txt);
        lungime = strlen(text);
    }

    // constructor de copiere
    Mesaj(const Mesaj& other){
        expeditor = new Utilizator(*other.expeditor);
        destinatar = new Utilizator(*other.destinatar);
        lungime = other.lungime;
        text = new char[MAX_LENGTH];
        strcpy(text, other.text);
    }

    // atribuire
    Mesaj& operator=(const Mesaj& other){
        if (this != &other) {
            delete this->expeditor;
            delete this->destinatar;
            delete[] this->text;

            expeditor = new Utilizator(*other.expeditor);
            destinatar = new Utilizator(*other.destinatar);
            lungime = other.lungime;
            text = new char[MAX_LENGTH];
            strcpy(text, other.text);
        }
        return *this;
    }

    // operatorii << si >>
    friend ostream& operator<<(ostream& out, const Mesaj& msj){
        out << "Numele expeditorului este: " << msj.expeditor->getNume() << endl;
        out << "Numele destinatar este: " << msj.destinatar->getNume() << endl;
        out << "Mesajul este: " << msj.text << endl;

        return out;
    }

    friend istream& operator>>(istream& in, Mesaj& msj){
        char m[MAX_LENGTH];
        cout << "Introdu numele expeditorului: ";
        in.ignore();
        in.getline(m, MAX_LENGTH);
        Utilizator* exp = Utilizator::cauta(m);
        if (exp == nullptr) {
            cout << "Expeditor invalid" << endl;
            return in;
        }
        msj.expeditor = exp;

        cout << "Introdu numele destinatarului: ";
        in.getline(m, MAX_LENGTH);
        Utilizator* dest = Utilizator::cauta(m);
        if (dest == nullptr) {
            cout << "Destinatar invalid" << endl;
            return in;
        }
        msj.destinatar = dest;

        cout << "Introdu mesajul: ";
        in.getline(m, MAX_LENGTH);

        delete[] msj.text;
        msj.lungime = strlen(m);
        msj.text = new char[MAX_LENGTH];
        strcpy(msj.text, m);

        listaMesaje.push_back(msj);

        return in;
    }

    static void afiseazaMesaje() {
        std::cout << "Lista mesajelor trimise: " << std::endl;

        Afisator<std::list<Mesaj>> afis;
        afis.afiseaza(listaMesaje);
    }


    // operatori matematici
    Mesaj operator+(const Mesaj& other){
        char* nouText = new char[2 * MAX_LENGTH];
        strcpy(nouText, text);
        strcat(nouText, "  ");
        strcat(nouText, other.text);

        Mesaj nou(expeditor, destinatar, nouText);
        delete[] nouText;
        return nou;
    }

    bool operator==(const Mesaj& other) const{
        if(strcmp(text, other.text) == 0 && *expeditor == *other.expeditor && *destinatar == *other.destinatar){
            return true;
        }else return false;
    }

    // getteri si setteri
    const char* getText() const{ 
        return text; 
    }

    Utilizator* getExp() const{
        return expeditor;
    }

    void setText(const char* txt){
        delete[] this->text;
        lungime = strlen(txt);
        text = new char[MAX_LENGTH];
        strcpy(text, txt);
    }

    // descr
    ~Mesaj() {
        delete[] this->text;
    }
};

void Utilizator :: retineUtilizatorul(Utilizator* uti) {
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

class Platit : virtual public Utilizator {
    public:
        virtual void mesaj(Utilizator uti) = 0;
        virtual void functie(Utilizator u) override = 0;
        virtual ~Platit() {}
    };

class Gold : virtual public Platit {
public:
    //constr fara parametri
    Gold() : Utilizator() {}

    //constr cu toti parametrii
    Gold(const string numeInit, int varstaInit, char genInit, float inaltimeInit, const char* zodieInit, const char* orientareInit, const char* bioInit) : Utilizator(numeInit, varstaInit, genInit, inaltimeInit, zodieInit, orientareInit, bioInit) {}

    // constr cu 2 parametri
    Gold(const string numeInit, char genInit) : Utilizator(numeInit, genInit) {}

    Gold(const string numeInit, int varstaInit) : Utilizator(numeInit, varstaInit) {}

    // constr de copiere
    Gold(const Gold& other) : Utilizator(other) {}

    Gold(const Utilizator other) : Utilizator(other) {}

    // operatorul de atribuire
    Gold& operator=(const Gold& other) {
        if (this != &other) {
            Utilizator::operator=(other);
        }
        return *this;
    }

    // operatorul <<
    friend ostream& operator<<(ostream& out, const Gold& g) {
        out << static_cast<const Utilizator&>(g);
        return out;
    }

    // operatorul >>
    friend istream& operator>>(istream& in, Gold& g) {
        in >> static_cast<Utilizator&>(g);
        return in;
    }

    void mesaj(Utilizator uti) override {
        cout << "Aceasta funcționalitate este disponibila doar pentru utilizatorii Premium și PremiumGold." << endl;
    }

    void functie(Utilizator uti) override {
        cout << "Utilizatorii compatibili cu " << uti.getNume() << " sunt:";
        int sw = 0;
        for(int i = 0; i < listaUtilizatori.size(); i++){
            if(*(listaUtilizatori[i]) == uti){
                continue;
            }
            else{
                Match match(uti, *(listaUtilizatori[i]));
                if(match.getComp() == true){
                    if(sw == 0){
                        cout << endl;
                    }
                    sw = 1;
                    cout << "Utilizatorul " <<listaUtilizatori[i]->getNume() << " cu varsta de " << listaUtilizatori[i]->getVarsta() << ", zodia " << listaUtilizatori[i]->getZodie() << ", inaltimea " << listaUtilizatori[i]->getInaltime() << " si care se descrie ca fiind #" << listaUtilizatori[i]->getBio() << "#." << endl;
                }
            }
        }
        if(sw == 0){
            cout << "inexistenti." << endl;
        }
    }

    // Destructor
    ~Gold() {}
};

class Premium : virtual public Platit {
    public:
        //constr fara parametri
        Premium() : Utilizator() {}
    
        //constr cu toti parametrii
        Premium(const string numeInit, int varstaInit, char genInit, float inaltimeInit, const char* zodieInit, const char* orientareInit, const char* bioInit) : Utilizator(numeInit, varstaInit, genInit, inaltimeInit, zodieInit, orientareInit, bioInit) {}
    
        // constr cu 2 parametri
        Premium(const string numeInit, char genInit) : Utilizator(numeInit, genInit) {}
    
        Premium(const string numeInit, int varstaInit) : Utilizator(numeInit, varstaInit) {}
    
        // constr de copiere
        Premium(const Premium& other) : Utilizator(other) {}

        Premium(const Utilizator other) : Utilizator(other) {}
    
        // operatorul de atribuire
        Premium& operator=(const Premium& other) {
            if (this != &other) {
                Utilizator::operator=(other);
            }
            return *this;
        }
    
        // operatorul <<
        friend ostream& operator<<(ostream& out, const Premium& g) {
            out << static_cast<const Utilizator&>(g);
            return out;
        }
    
        // operatorul >>
        friend istream& operator>>(istream& in, Premium& g) {
            in >> static_cast<Utilizator&>(g);
            return in;
        }

        void mesaj(Utilizator uti){
            Mesaj ms;
            cin >> ms;
            if(ms.getExp()->getNume() != uti.getNume()){
                cout << "Expeditor invalid." << endl;
            }else{
                cout << "Mesajul a fost înregistrat!" << endl;
                cout << endl << ms;
            } 
        }
    
        void functie(Utilizator uti) override {
            float maxi = 0;
            string pers;
            for(int i = 0; i < listaUtilizatori.size(); i++){
                if(*listaUtilizatori[i] == uti){
                    continue;
                }else{
                    Match meci(uti, *listaUtilizatori[i]);
                    if(meci.getScor() > maxi){
                        maxi = meci.getScor();
                        pers = listaUtilizatori[i]->getNume();
                    }
                }
            }
            cout << "Cea mai buna potrivire e utilizatorului Premium " << uti.getNume() << " este " << pers << " cu un scor de compatibilitate de "<< maxi << " puncte." << endl;
        }

        // Destructor
        ~Premium() {}
    };

class PremiumGold : public Gold, public Premium {
    public:
    //constr fara parametri
    PremiumGold() : Utilizator() {}

    //constr cu toti parametrii
    PremiumGold(const string numeInit, int varstaInit, char genInit, float inaltimeInit, const char* zodieInit, const char* orientareInit, const char* bioInit) : Utilizator(numeInit, varstaInit, genInit, inaltimeInit, zodieInit, orientareInit, bioInit) {}

    // constr cu 2 parametri
    PremiumGold(const string numeInit, char genInit) : Utilizator(numeInit, genInit) {}

    PremiumGold(const string numeInit, int varstaInit) : Utilizator(numeInit, varstaInit) {}

    // constr de copiere
    PremiumGold(const PremiumGold& other) : Utilizator(other) {}

    PremiumGold(const Utilizator other) : Utilizator(other) {}

    // operatorul de atribuire
    PremiumGold& operator=(const PremiumGold& other) {
        if (this != &other) {
            Utilizator::operator=(other);
        }
        return *this;
    }

    // operatorul <<
    friend ostream& operator<<(ostream& out, const PremiumGold& g) {
        out << static_cast<const Utilizator&>(g);
        return out;
    }

    // operatorul >>
    friend istream& operator>>(istream& in, PremiumGold& g) {
        in >> static_cast<Utilizator&>(g);
        return in;
    }

    void mesaj(Utilizator uti) override {
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

    void functie(Utilizator uti) override;

    ~PremiumGold() {}
};

int Utilizator::contorID = 1000;
vector<Utilizator*> Utilizator::listaUtilizatori;
list<Mesaj> Mesaj::listaMesaje;
map<Utilizator*, set<Utilizator*>> Match::listaMatch;

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

void PremiumGold::functie(Utilizator uti) {
    cout << "Alege un utilizator din lista de mai jos pentru a forma un match special:" << endl;
    Utilizator::afiseazaUtilizatori();

    cout << "Introdu numele utilizatorului ales: ";
    // cin.ignore(); 
    char numeCautat[100];
    cin.getline(numeCautat, 100);

    Utilizator* gasit = Utilizator::cauta(numeCautat);
    // cout << gasit;
    if (gasit == nullptr) {
        cout << "Utilizator inexistent." << endl;
        return;
    }

    // Cream match-ul forțat
    Match matchFortat(this, gasit, 100.0f, true);
    Match::listaMatch[this].insert(gasit);
    Match::listaMatch[gasit].insert(this);
    // cout << matchFortat;

    time_t now;
    time(&now);
    char* dt = ctime(&now);
    fmatch << dt << " Un match forțat între utilizatorul " << uti.getNume() << " și utilizatorul " << gasit->getNume() << " a fost adăugat" << endl;

    cout << "Utilizatorii " << this->getNume() << " si " << gasit->getNume() << " sunt acum suflete pereche cu scor 100%!" << endl;
}

void incarcaUtilizatori(string numeFisier) {
    ifstream fin(numeFisier);
    if (!fin) throw runtime_error("Eroare la deschiderea fișierului pentru citire");

    string nume, zodie, bio;
    int varsta;
    char gen, orientare[MAX_LENGTH], descriere[MAX_LENGTH];
    float inaltime;

    while (fin >> nume >> varsta >> gen >> inaltime >> zodie >> orientare) {
        getline(fin, bio);
        Utilizator* u = new Utilizator(nume, varsta, gen, inaltime, zodie.c_str(), orientare, bio.c_str());
        Utilizator::retineUtilizatorul(u);
    }
    fin.close();
}

class MeniuSingleton {
private:
    char command[MAX_LENGTH];
    static MeniuSingleton* instanta;
    MeniuSingleton() {}

    void afiseaza() {
        cout << endl;
        cout << "Bine ai venit la LoveLorita!" << endl;
        cout << "1. Creeaza profil." << endl;
        cout << "2. Afiseaza utilizatorii." << endl;
        cout << "3. Verifica compatibilitatea unui anumit utilizator." << endl;
        cout << "4. Trimite un mesaj." << endl;
        cout << "5. Afiseaza toate mesajele." << endl;
        cout << "6. Incarca utilizatori din fisier." << endl;
        
        cout << "Pentru a opri programul scrie stop." << endl;
    }

    void proceseazaComanda(int numberCommand) {
        switch (numberCommand) {
            case 1: {
                Utilizator* uti = new Utilizator;
                cin >> *uti;
                Utilizator::retineUtilizatorul(uti);

                break;
            }
            case 2: {
                Utilizator::afiseazaUtilizatori();
                cout << endl << "Vrei mai multe informatii despre utilizatori? Pentru a-ti upgrada profilul standard la statutul Gold scrie-ti numele." <<endl;
                cin.ignore();
                char n[100];
                cin.getline(n, 100);
                Utilizator* gasit = Utilizator::cauta(n);
                if(n){
                    for (int i = 0; i < Utilizator::listaUtilizatori.size(); i++) {
                        if (*Utilizator::listaUtilizatori[i] == *gasit) {
                            Utilizator* vechi = Utilizator::listaUtilizatori[i];
                            Utilizator::listaUtilizatori[i] = new Gold(*vechi);
                            delete vechi;

                            Utilizator* actual = Utilizator::listaUtilizatori[i];
                            cout << "Felicitari! " << actual->getNume() << " este acum utilizator Gold." << endl;
                            actual->functie(*actual);

                            cout << "Scrie da pentru upgrade la Premium: ";
                            char da[20];
                            cin.getline(da, 20);
                            if (strcmp(da, "da") == 0) {
                                vechi = Utilizator::listaUtilizatori[i];
                                Utilizator::listaUtilizatori[i] = new Premium(*vechi);
                                delete vechi;

                                actual = Utilizator::listaUtilizatori[i];
                                cout << "Acum esti utilizator Premium!" << endl;
                                actual->functie(*actual);

                                cout << "Scrie da pentru upgrade la PremiumGold: ";
                                cin.getline(da, 20);
                                if (strcmp(da, "da") == 0) {
                                    vechi = Utilizator::listaUtilizatori[i];
                                    Utilizator::listaUtilizatori[i] = new PremiumGold(*vechi);
                                    delete vechi;

                                    actual = Utilizator::listaUtilizatori[i];
                                    cout << "Acum esti utilizator PremiumGold!" << endl;
                                    actual->functie(*actual);
                                }
                            }

    break;
}
                    }
                    
                }else{
                    cout << "Utilizator invalid.";
                }
                break;
            }
            case 3: {
                char u1[50], u2[50];
                cin.ignore();
                cout << "Introdu numele utilizatorului: ";
                cin.getline(u1, 50);
                Utilizator* u1_gasit = Utilizator::cauta(u1);
                
                if (u1_gasit) {
                    u1_gasit->afiseazaCompatibilitatea(*u1_gasit);
                }else{
                    cout << "Utilizator invalid.";
                }
                break;

            }
            case 4: {
                char numeExp[100];
                cin.ignore();
                cout << "Introdu numele tau (expeditorul): ";
                cin.getline(numeExp, 100);
            
                Utilizator* exp = Utilizator::cauta(numeExp);
                if (exp == nullptr) {
                    cout << "Utilizator inexistent." << endl;
                    break;
                }
            
                Platit* utilizatorPlatit = dynamic_cast<Platit*>(exp);
                if (utilizatorPlatit != nullptr) {
                    utilizatorPlatit->mesaj(*exp);
                } else {
                    cout << "Ne pare rau! Doar utilizatorii Premium si PremiumGold pot trimite mesaje." << endl;
                }
                break;
            }
            
            case 5: {
                Mesaj::afiseazaMesaje();
                break;
            }

            case 6: {
                cout << "Introdu numele fisierului: ";
                char fisier[MAX_LENGTH];
                cin.ignore();
                cin.getline(fisier, MAX_LENGTH);
                incarcaUtilizatori(fisier);
                break;
            }
            default:
                cout << "Optiune invalida." << endl;
                break;
        }
    }

public:
    static MeniuSingleton* getInstanta() {
        if (!instanta)
            instanta = new MeniuSingleton();
        return instanta;
    }

    void ruleazaMeniu() {
        while (true) {
            afiseaza();
            cin >> command;

            if (!strcmp(command, "stop")) {
                cout << "Programul a fost oprit." << endl;
                return;
            }

            proceseazaComanda(atoi(command));
        }
    }

};

MeniuSingleton* MeniuSingleton::instanta = nullptr;

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