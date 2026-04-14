#include "Meniu.h"
#include "Globals.h"
#include "Mesaj.h"
#include "Match.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstring>
#include <cstdlib>

using namespace std;

MeniuSingleton* MeniuSingleton::instanta = nullptr;

MeniuSingleton::MeniuSingleton() {
    utilizatorCurent = nullptr;
}

MeniuSingleton* MeniuSingleton::getInstanta() {
    if (!instanta)
        instanta = new MeniuSingleton();
    return instanta;
}

void MeniuSingleton::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void MeniuSingleton::asteaptaConfirmare() {
    cout << "\n> Apasa tasta Enter pentru a continua...";
    cin.clear();
    char c;
    while(cin.get(c) && c != '\n'); 
}

void MeniuSingleton::afiseazaStart() {
    clearScreen();
    cout << "         LOVELORITA" << endl;
    cout << endl;
    cout << " [1] Creeaza Cont (Profil Nou)" << endl;
    cout << " [2] Conectare Logare (Introducerea Numelui)" << endl;
    cout << " [3] Incarca Utilizatori (Machete din fisier)" << endl;
    cout << endl;
    cout << " [0] Iesire din program" << endl;
    cout << "Alege o optiune: ";
}

void MeniuSingleton::proceseazaComandaStart(int numberCommand) {
    switch(numberCommand) {
        case 1: {
            Utilizator* uti = new Utilizator;
            cin >> *uti;
            Utilizator::retineUtilizatorul(uti);
            cout << "Cont creat cu succes! Te poti conecta din Meniul de Start." << endl;
            asteaptaConfirmare();
            break;
        }
        case 2: {
            cout << "Introdu numele de utilizator cu care vrei sa te loghezi: ";
            char n[100];
            cin.getline(n, 100);
            if(n[0] == '\0') cin.getline(n, 100);

            Utilizator* gasit = Utilizator::cauta(n);
            if(gasit) {
                utilizatorCurent = gasit;
                cout << "Conectat cu succes ca " << utilizatorCurent->getNume() << "!" << endl;
            } else {
                cout << "Utilizator invalid. Contul nu a putut fi gasit." << endl;
            }
            asteaptaConfirmare();
            break;
        }
        case 3: {
            cout << "Introdu numele fisierului (ex: uti.txt): ";
            char fisier[256];
            cin.getline(fisier, 256);
            if(fisier[0] == '\0') cin.getline(fisier, 256);
            
            try {
                incarcaUtilizatori(fisier);
                cout << "Utilizatorii au fost incarcati din fisier cu succes." << endl;
            } catch (const exception& e) {
                cout << "Eroare la incarcare: " << e.what() << endl;
            }
            asteaptaConfirmare();
            break;
        }
        default:
            cout << "Optiune invalida!" << endl;
            asteaptaConfirmare();
            break;
    }
}

void incarcaUtilizatori(string numeFisier) {
    ifstream fin(numeFisier);
    if (!fin) throw runtime_error("Eroare la deschiderea fisierului pentru citire");

    string nume, zodie, bio;
    int varsta;
    char gen, orientare[256], descriere[256];
    float inaltime;

    while (fin >> nume >> varsta >> gen >> inaltime >> zodie >> orientare) {
        getline(fin, bio);
        Utilizator* u = new Utilizator(nume, varsta, gen, inaltime, zodie.c_str(), orientare, bio.c_str());
        Utilizator::retineUtilizatorul(u);
    }
    fin.close();
}

void MeniuSingleton::afiseazaLogat() {
    clearScreen();
    string statut = "Standard";
    if (dynamic_cast<PremiumGold*>(utilizatorCurent)) statut = "PremiumGold";
    else if (dynamic_cast<Premium*>(utilizatorCurent)) statut = "Premium";
    else if (dynamic_cast<Gold*>(utilizatorCurent)) statut = "Gold";

    cout << " LOGAT CA: " << utilizatorCurent->getNume() << " | STATUT: " << statut << endl;
    cout << " [1] Deconectare Sesiune Curenta" << endl;
    cout << " [2] Lasa Pasiunile Libere: Exploreaza Baza de Date de Utilizatori" << endl;
    cout << " [3] Meciul Viu: Verifica Compatibilitatea cu cineva direct" << endl;
    
    if (statut == "Standard") {
        cout << " [4] Treci la Nivelul Urmator: Upgrade gratuit la Pachetul [Gold]" << endl;
    }
    else if (statut == "Gold") {
        cout << " [4] Treci la Nivelul Urmator: Upgrade gratuit la Pachetul [Premium]" << endl;
    }
    else if (statut == "Premium") {
        cout << " [4] Treci la TIER FINAL: Upgrade gratuit la Pachetul Suprem [PremiumGold]" << endl;
    } else {
        cout << " [4] Revendica Statut: Detii Pachetul Suprem! Platforma e toata a ta." << endl;
    }

    cout << " * OPTIUNI AVANSATE SI FUNCTIONALITATI :" << endl;
    
    if (statut == "Premium" || statut == "PremiumGold") {
        cout << " [5] Trimite un Mesaj direct pe Platforma" << endl;
    } else {
        cout << " [5] (LOCKED) Trimite Mesaje -> *Deblocabil in Premium*" << endl;
    }

    if (statut == "Gold" || statut == "Premium" || statut == "PremiumGold") {
        cout << " [6] Functia Speciala de Analiza si Verificare a Planului" << endl;
    } else {
         cout << " [6] (LOCKED) Functie Speciala Model de Abonament -> *Deblocabil in Gold*" << endl;
    }
    cout << " [7] Verifica Istoric Conversatii Publice" << endl;
    cout << " [0] Iesire din program" << endl;
    cout << "Alege o optiune: ";
}

void MeniuSingleton::proceseazaComandaLogat(int numberCommand) {
    string statut = "Standard";
    if (dynamic_cast<PremiumGold*>(utilizatorCurent)) statut = "PremiumGold";
    else if (dynamic_cast<Premium*>(utilizatorCurent)) statut = "Premium";
    else if (dynamic_cast<Gold*>(utilizatorCurent)) statut = "Gold";

    switch(numberCommand) {
        case 1: {
            utilizatorCurent = nullptr;
            cout << "Te-ai deconectat cu succes!" << endl;
            asteaptaConfirmare();
            break;
        }
        case 2: {
            Utilizator::afiseazaUtilizatori();
            asteaptaConfirmare();
            break;
        }
        case 3: {
            cout << "Introdu exact numele utilizatorului spre care doresti sa afli compatibilitatea: ";
            char u1[50];
            cin.getline(u1, 50);            
            if(u1[0] == '\0') cin.getline(u1, 50);

            Utilizator* gasit = Utilizator::cauta(u1);
            if (gasit) {
                // Afiseaza compatibilitatea
                cout << "=== Rularea Predictiei de Suflet Pereche: " << utilizatorCurent->getNume() << " + " << gasit->getNume() << " ===" << endl;
                Match potrivire(utilizatorCurent, gasit);
                potrivire.compatibilitate();
                
            } else {
                cout << "Nu am putut analiza! Utilizatorul precizat (" << u1 << ") nu a fost gasit in sistem." << endl;
            }
            asteaptaConfirmare();
            break;
        }
        case 4: {
            if (statut == "PremiumGold") {
                cout << "Esti Invingatorul Sistemului Dupa Acest Pachet. Iubirea e a ta!" << endl;
            } else {
                for (int i = 0; i < Utilizator::listaUtilizatori.size(); i++) {
                    if (*Utilizator::listaUtilizatori[i] == *utilizatorCurent) {
                        Utilizator* vechi = Utilizator::listaUtilizatori[i];
                        if (statut == "Standard") {
                            Utilizator::listaUtilizatori[i] = new Gold(*vechi);
                            cout << "-> Felicitari " << vechi->getNume() << "! Contul a avansat si este acum in pachetul superior: GOLD." << endl;
                        } else if (statut == "Gold") {
                            Utilizator::listaUtilizatori[i] = new Premium(*vechi);
                            cout << "-> Felicitari " << vechi->getNume() << "! Contul a avansat si este acum in pachetul superior: PREMIUM." << endl;
                        } else if (statut == "Premium") {
                            Utilizator::listaUtilizatori[i] = new PremiumGold(*vechi);
                            cout << "-> WOW " << vechi->getNume() << "! Ai cumparat Iubirea! Detii acum pachetul final: PREMIUMGOLD!" << endl;
                        }
                        utilizatorCurent = Utilizator::listaUtilizatori[i];
                        delete vechi;
                        break;
                    }
                }
            }
            asteaptaConfirmare();
            break;
        }
        case 5: {
            if (statut == "Premium" || statut == "PremiumGold") {
                cout << "=== Sistem Avansat Mesaje Directe (DM) ===" << endl;
                Platit* platit = dynamic_cast<Platit*>(utilizatorCurent);
                if (platit) {
                    cout << "[Avertisment] Confirmarea expeditorului este inca in vigoare." << endl;
                    platit->mesaj(*utilizatorCurent);
                }
            } else {
                cout << "[ L O C K E D ]\nInterfata restrictionata. Nivelul de Pachet: (" << statut << ") este prea scazut. Fa upgrade!" << endl;
            }
            asteaptaConfirmare();
            break;
        }
        case 6: {
            if (statut == "Gold" || statut == "Premium" || statut == "PremiumGold") {
                Platit* p = dynamic_cast<Platit*>(utilizatorCurent);
                if(p) {
                    cout << "=== Lansam Functia Speciala De Potrrivire (" << statut << ") PENTRU TINE... ===" << endl;
                    p->functie(*utilizatorCurent);
                }
            } else {
                cout << "[ L O C K E D ]\nPentru Functia Speciala Unica de Analiza a Pietei matrimoniale ai Neoie minimum de GOLD!" << endl;
            }
            asteaptaConfirmare();
            break;
        }
        case 7: {
            Mesaj::afiseazaMesaje();
            asteaptaConfirmare();
            break;
        }
        default:
            cout << "Optiune invalida!" << endl;
            asteaptaConfirmare();
            break;
    }
}

void MeniuSingleton::ruleazaMeniu() {
    while (true) {
        if (utilizatorCurent == nullptr) {
            afiseazaStart();
            cin >> command;
            cin.ignore(1000, '\n');
            if (strcmp(command, "0") == 0) {
                cout << "Programul a fost oprit. Ne bucuram ca ai trecut prin LoveLorita!" << endl;
                return;
            }
            proceseazaComandaStart(atoi(command));
        } else {
            afiseazaLogat();
            cin >> command;
            cin.ignore(1000, '\n');
            if (strcmp(command, "0") == 0) {
                cout << "Meniul a fost oprit. Intoarce-te curand!" << endl;
                return;
            }
            proceseazaComandaLogat(atoi(command));
        }
    }
}
