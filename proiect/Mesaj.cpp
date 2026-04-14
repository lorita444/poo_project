#include "Mesaj.h"
#include "Afisator.h"

using namespace std;

list<Mesaj> Mesaj::listaMesaje;

Mesaj::Mesaj(){
    expeditor = nullptr;
    destinatar = nullptr;
    text = new char[256];
    strcpy(text, "");
    lungime = 0;
}

Mesaj::Mesaj(Utilizator* u1, Utilizator* u2, const char* txt, int l){
    expeditor = u1;
    destinatar = u2;
    text = new char[256];
    strcpy(text, txt);
    lungime = l;
}

Mesaj::Mesaj(Utilizator* u1, Utilizator* u2){
    expeditor = u1;
    destinatar = u2;
    text = new char[256];
    strcpy(text, "");
    lungime = 0;
}

Mesaj::Mesaj(Utilizator* u1, Utilizator* u2, const char* txt){
    expeditor = u1;
    destinatar = u2;
    text = new char[256];
    strcpy(text, txt);
    lungime = strlen(text);
}

Mesaj::Mesaj(const Mesaj& other){
    expeditor = new Utilizator(*other.expeditor);
    destinatar = new Utilizator(*other.destinatar);
    lungime = other.lungime;
    text = new char[256];
    strcpy(text, other.text);
}

Mesaj& Mesaj::operator=(const Mesaj& other){
    if (this != &other) {
        delete expeditor;
        delete destinatar;
        delete[] text;

        expeditor = new Utilizator(*other.expeditor);
        destinatar = new Utilizator(*other.destinatar);
        lungime = other.lungime;
        text = new char[256];
        strcpy(text, other.text);
    }
    return *this;
}

ostream& operator<<(ostream& out, const Mesaj& msj){
    out << "Numele expeditorului este: " << msj.expeditor->getNume() << endl;
    out << "Numele destinatar este: " << msj.destinatar->getNume() << endl;
    out << "Mesajul este: " << msj.text << endl;

    return out;
}

istream& operator>>(istream& in, Mesaj& msj){
    char m[256];
    cout << "Introdu numele expeditorului: ";
    // in.ignore();
    in.getline(m, 256);
    Utilizator* exp = Utilizator::cauta(m);
    if (exp == nullptr) {
        cout << "Expeditor invalid" << endl;
        return in;
    }
    msj.expeditor = exp;

    cout << "Introdu numele destinatarului: ";
    in.getline(m, 256);
    Utilizator* dest = Utilizator::cauta(m);
    if (dest == nullptr) {
        cout << "Destinatar invalid" << endl;
        return in;
    }
    msj.destinatar = dest;

    cout << "Introdu mesajul: ";
    in.getline(m, 256);

    delete[] msj.text;
    msj.lungime = strlen(m);
    msj.text = new char[256];
    strcpy(msj.text, m);

    Mesaj::listaMesaje.push_back(msj);

    return in;
}

// operatori matematici
Mesaj Mesaj::operator+(const Mesaj& other){
    char* nouText = new char[2 * 256];
    strcpy(nouText, text);
    strcat(nouText, "  ");
    strcat(nouText, other.text);

    Mesaj nou(expeditor, destinatar, nouText);
    delete[] nouText;
    return nou;
}

bool Mesaj::operator==(const Mesaj& other) const{
    if(strcmp(text, other.text) == 0 && *expeditor == *other.expeditor && *destinatar == *other.destinatar){
        return true;
    }else return false;
}

const char* Mesaj::getText() const{ 
    return text; 
}

Utilizator* Mesaj::getExp() const{
    return expeditor;
}

void Mesaj::setText(const char* txt){
    delete[] this->text;
    lungime = strlen(txt);
    text = new char[256];
    strcpy(text, txt);
}

Mesaj::~Mesaj() {
    delete[] this->text;
}

void Mesaj::afiseazaMesaje() {
    std::cout << "Lista mesajelor trimise: " << std::endl;
    Afisator<std::list<Mesaj>> afis;
    afis.afiseaza(listaMesaje);
}
