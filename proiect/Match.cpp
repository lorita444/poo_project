#include "Match.h"
#include <algorithm>

using namespace std;

std::map<Utilizator*, std::set<Utilizator*>> Match::listaMatch;

Match::Match(){
    utilizator1 = nullptr;
    utilizator2 = nullptr;
    scorCompatibilitate = 0.0;
    comp = false;
}

Match::Match(Utilizator* u1, Utilizator* u2, float scor, bool c){
    utilizator1 = u1;
    utilizator2 = u2;
    scorCompatibilitate = scor;
    comp = c;
}

Match::Match(Utilizator* u1, Utilizator* u2) {
    utilizator1 = new Utilizator(*u1);
    utilizator2 = new Utilizator(*u2);
    scorCompatibilitate = calculeaza();
    comp = scorCompatibilitate > 50;
}

Match::Match(Utilizator& u1, Utilizator& u2) {
    utilizator1 = new Utilizator(u1);
    utilizator2 = new Utilizator(u2);
    scorCompatibilitate = calculeaza();
    comp = scorCompatibilitate > 50;
}

float Match::calculeaza(){
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

    if (utilizator1->getZodie() == std::string(utilizator2->getZodie())) {
        scor += 40;
    }

    return min(scor, 100.0f);
}

Match::Match(const Match& other){
    utilizator1 = new Utilizator(*other.utilizator1);
    utilizator2 = new Utilizator(*other.utilizator2);
    scorCompatibilitate = other.scorCompatibilitate;
    comp = other.comp;
}

ostream& operator<<(ostream& out, const Match& match) {
    out << "Primul utilizator: " << match.utilizator1 << endl;
    out << "Al doilea utilizator: " << match.utilizator2 << endl;
    out << "Procent de compatibilitate: " << match.scorCompatibilitate << endl;
    out << "Concluzia compatibilitatii: " << match.comp << endl;

    return out;
}

Match& Match::operator=(const Match& other){
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

bool Match::operator==(const Match& other) const{
    if ((*utilizator1 == *other.utilizator1 && *utilizator2 == *other.utilizator2) || (*utilizator1 == *other.utilizator2 && *utilizator2 == *other.utilizator1)){
        return true;
    }else{
        return false;
    }
}

bool Match::operator<(const Match& other) const {
    return scorCompatibilitate < other.scorCompatibilitate;
}

bool Match::operator>(const Match& other){
    return scorCompatibilitate > other.scorCompatibilitate;
}

float Match::getScor(){ 
    return scorCompatibilitate; 
}
void Match::setScor(float scor){
    scorCompatibilitate = scor; 
}

bool Match::getComp(){
    return comp;
}

const string Match::getNumeU1() const{
    return utilizator1->getNume();
}

const string Match::getNumeU2() const {
    return utilizator2->getNume();
}

void Match::setComp(float c){
    comp = c;
}

void Match::compatibilitate() const{
    cout << "Compatibilitatea între " << utilizator1->getNume() << " si " << utilizator2->getNume() << " este de " << scorCompatibilitate << "%" << endl;
}

Match::~Match(){
    delete utilizator1;
    delete utilizator2;
}
