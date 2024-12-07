#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class biblioteca {
public:
    string nume_biblioteca;
    string adresa_biblioteca;
    int numar_biblioteca;

    biblioteca(string nume = "", string adresa = "", int numar = 0)
        : nume_biblioteca(nume), adresa_biblioteca(adresa), numar_biblioteca(numar) {}

    
    ~biblioteca() {
        cout << "Biblioteca " << nume_biblioteca << " a fost distrusa!" << endl;
    }

    void afiseaza_info() const {
        cout << "Biblioteca: " << nume_biblioteca
            << ", Adresa: " << adresa_biblioteca
            << ", Numar: " << numar_biblioteca << endl;
    }
    friend class carte;
};

class carte : public biblioteca {
public:
    string nume_carte;
    string autor;
    int isbn;

    carte(string numeBiblioteca = "", string adresaBiblioteca = "", int numarBiblioteca = 0,
        string numeCarte = "", string autor = "", int barcode = 0)
        : biblioteca(numeBiblioteca, adresaBiblioteca, numarBiblioteca),
        nume_carte(numeCarte), autor(autor), isbn(barcode) {}

    
    ~carte() {
        cout << "Carte " << nume_carte << " scrisa de " << autor << " a fost distrusa!" << endl;
    }

    void afiseaza_detalii() const {
        afiseaza_info();
        cout << "Carte: " << nume_carte
            << ", Autor: " << autor
            << ", Barcode: " << isbn << endl;
    }
    friend class biblioteca;
};

vector<biblioteca> biblioteci;
vector<carte> carti;

void creeaza_biblioteca() {
    string nume, adresa;
    int numar;
    cout << "Introdu numele bibliotecii: ";
    getline(cin, nume);
    cout << "Introdu adresa bibliotecii: ";
    getline(cin, adresa);
    cout << "Introdu numarul bibliotecii: ";
    cin >> numar;
    cin.ignore();
    biblioteci.push_back(biblioteca(nume, adresa, numar));
    cout << "Biblioteca adaugata cu succes!" << endl;
}

void modifica_biblioteca() {
    int numar;
    cout << "Introdu numarul bibliotecii pe care doresti sa o modifici: ";
    cin >> numar;
    cin.ignore();

    for (auto& bibl : biblioteci) {
        if (bibl.numar_biblioteca == numar) {
            cout << "Introdu noul nume al bibliotecii: ";
            getline(cin, bibl.nume_biblioteca);
            cout << "Introdu noua adresa a bibliotecii: ";
            getline(cin, bibl.adresa_biblioteca);
            cout << "Biblioteca modificata cu succes!" << endl;
            return;
        }
    }
    cout << "Biblioteca cu numarul " << numar << " nu a fost gasita!" << endl;
}

void sterge_biblioteca() {
    int numar;
    cout << "Introdu numarul bibliotecii pe care doresti sa o stergi: ";
    cin >> numar;
    cin.ignore();

    auto it = remove_if(biblioteci.begin(), biblioteci.end(),
        [numar](const biblioteca& bibl) { return bibl.numar_biblioteca == numar; });
    if (it != biblioteci.end()) {
        biblioteci.erase(it, biblioteci.end());
        cout << "Biblioteca stearsa cu succes!" << endl;
    }
    else {
        cout << "Biblioteca cu numarul " << numar << " nu a fost gasita!" << endl;
    }
}

void adauga_carte() {
    string nume_carte, autor;
    int barcode, numar_bibliotecaa;
    cout << "Introdu numarul bibliotecii in care se va afla cartea: ";
    cin >> numar_bibliotecaa;
    cin.ignore();

    biblioteca* bibl = nullptr;
    for (const auto& b : biblioteci) {
        if (b.numar_biblioteca == numar_bibliotecaa) {
            bibl = const_cast<biblioteca*>(&b); 
            break;
        }
    }

    if (!bibl) {
        cout << "Biblioteca cu numarul " << numar_bibliotecaa << " nu a fost gasita!" << endl;
        return;
    }

    cout << "Introdu numele cartii: ";
    getline(cin, nume_carte);
    cout << "Introdu numele autorului: ";
    getline(cin, autor);
    cout << "Introdu barcode-ul: ";
    cin >> barcode;
    cin.ignore();

    carti.push_back(carte(bibl->nume_biblioteca, bibl->adresa_biblioteca, bibl->numar_biblioteca, nume_carte, autor, barcode));
    cout << "Carte adaugata cu succes!" << endl;
}

void toate_cartile() {
    if (carti.empty()) {
        cout << "Nu sunt carti inregistrate!" << endl;
        return;
    }

    for (const auto& carte : carti) {
        carte.afiseaza_detalii();
    }
}

void cautare_carte() {
    int barcode;
    cout << "Introdu barcode-ul cartii pe care doresti sa o cauti: ";
    cin >> barcode;
    cin.ignore();

    for (const auto& carte : carti) {
        if (carte.isbn == barcode) {
            carte.afiseaza_detalii();
            return;
        }
    }
    cout << "Carte cu barcode-ul " << barcode << " nu a fost gasita!" << endl;
}

void sterge_carte() {
    int barcode;
    cout << "Introdu barcode-ul cartii pe care doresti sa o stergi: ";
    cin >> barcode;
    cin.ignore();

    auto it = remove_if(carti.begin(), carti.end(),
        [barcode](const carte& c) { return c.isbn == barcode; });
    if (it != carti.end()) {
        carti.erase(it, carti.end());
        cout << "Carte stearsa cu succes!" << endl;
    }
    else {
        cout << "Carte cu barcode-ul " << barcode << " nu a fost gasita!" << endl;
    }
}


void distruge_obiect() {
    int optiune;
    cout << "1. Distruge o biblioteca\n";
    cout << "2. Distruge o carte\n";
    cout << "Alege optiunea: ";
    cin >> optiune;
    cin.ignore();

    if (optiune == 1) {
        sterge_biblioteca();
    }
    else if (optiune == 2) {
        sterge_carte();
    }
    else {
        cout << "Optiune invalida!" << endl;
    }
}

int main() {
    int optiune;
    do {
        cout << "\nMeniu:\n";
        cout << "1. Creeaza biblioteca\n";
        cout << "2. Modifica/sterge biblioteca\n";
        cout << "3. Adauga carte\n";
        cout << "4. Vezi toate cartile\n";
        cout << "5. Cauta o carte\n";
        cout << "6. Sterge o carte\n";
        cout << "7. Distruge obiect\n";
        cout << "8. Iesi din program\n";
        cout << "Alege optiunea: ";
        cin >> optiune;
        cin.ignore();

        switch (optiune) {
        case 1:
            creeaza_biblioteca();
            break;
        case 2:
            int subopt;
            cout << "1. Modifica o biblioteca\n";
            cout << "2. Sterge o biblioteca\n";
            cout << "Alege optiunea: ";
            cin >> subopt;
            cin.ignore();
            if (subopt == 1) {
                modifica_biblioteca();
            }
            else if (subopt == 2) {
                sterge_biblioteca();
            }
            else {
                cout << "Optiune invalida!" << endl;
            }
            break;
        case 3:
            adauga_carte();
            break;
        case 4:
            toate_cartile();
            break;
        case 5:
            cautare_carte();
            break;
        case 6:
            sterge_carte();
            break;
        case 7:
            distruge_obiect(); 
            break;
        case 8:
            cout << "Program incheiat!" << endl;
            break;
        default:
            cout << "Optiune invalida!" << endl;
        }
    } while (optiune != 8);

    return 0;
}
