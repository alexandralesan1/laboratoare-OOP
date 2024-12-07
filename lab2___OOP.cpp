#include <iostream>
#include <fstream>
#include <vector>
#include <string>


using namespace std;

enum class Specialitate {
    MECHANICAL_ENGINEERING,
    FOOD_ALIMENTATION,
    INFORMATION_TECHNOLOGY,
    SOFTWARE_ENGINEERING,
    URBANISM_ARCHITECTURE
};

string getSpecialitateString(Specialitate sp) {
    switch (sp) {
    case Specialitate::MECHANICAL_ENGINEERING: return "Mechanical Engineering";
    case Specialitate::FOOD_ALIMENTATION: return "Food Alimentation";
    case Specialitate::INFORMATION_TECHNOLOGY: return "Information Technology";
    case Specialitate::SOFTWARE_ENGINEERING: return "Software Engineering";
    case Specialitate::URBANISM_ARCHITECTURE: return "Urbanism Architecture";
    default: return "Unknown";
    }
}

class Student {
public:
    string nume, prenume, data_inrolarii, data_nasterii, email;
    bool licentiat;
    Specialitate specialitate;

    Student(string n, string p, string di, string dn, string em, Specialitate sp, bool lic)
        : nume(n), prenume(p), data_inrolarii(di), data_nasterii(dn), email(em), specialitate(sp), licentiat(lic) {}
};

class Facultate {
public:
    string nume_facultate, abreviere;
    vector<Student> studenti;

    Facultate(string nf, string ab) : nume_facultate(nf), abreviere(ab) {}

    void adaugaStudent(Student student) {
        studenti.push_back(student);
        string nume_fisier = nume_facultate + "_" + getSpecialitateString(student.specialitate) + ".txt";
        ofstream fisier(nume_fisier, ios::app);
        fisier << "Nume: " << student.nume << ", Prenume: " << student.prenume
            << ", Data inrolarii: " << student.data_inrolarii << ", Email: " << student.email
            << ", Licentiat: " << (student.licentiat ? 1 : 0) << endl;
        fisier.close();
    }

    void inscriereStudentLot() {
        ofstream outfile("enrolled.txt", ios::app);
        if (!outfile.is_open()) {
            cout << "Nu am putut deschide fisierul enrolled.txt\n";
            return;
        }

        for (const auto& student : studenti) {
            if (!student.licentiat) {
                outfile << "Nume: " << student.nume << ", Prenume: " << student.prenume
                    << ", Data inrolarii: " << student.data_inrolarii << ", Email: " << student.email
                    << ", Specialitate: " << getSpecialitateString(student.specialitate) << endl;
            }
        }

        outfile.close();
        cout << "Studentii inscrisi au fost adaugati in enrolled.txt.\n";
    }

    void absolvireStudentLot() {
        ofstream outfile("graduated.txt", ios::app);
        if (!outfile.is_open()) {
            cout << "Nu am putut deschide fisierul graduated.txt\n";
            return;
        }

        for (const auto& student : studenti) {
            if (student.licentiat) {
                outfile << "Nume: " << student.nume << ", Prenume: " << student.prenume
                    << ", Data inrolarii: " << student.data_inrolarii << ", Email: " << student.email
                    << ", Specialitate: " << getSpecialitateString(student.specialitate) << endl;
            }
        }

        outfile.close();
        cout << "Studentii licentiati au fost adaugati in graduated.txt.\n";
    }

    void afiseazaStudentiInrolati() {
        cout << "Studentii inrolati in facultatea " << nume_facultate << ":\n";
        for (const auto& student : studenti) {
            if (!student.licentiat) {
                cout << student.nume << " " << student.prenume << " - " << getSpecialitateString(student.specialitate) << endl;
            }
        }
    }

    void afiseazaStudentiLicentiati() {
        cout << "Studentii licentiati in facultatea " << nume_facultate << ":\n";
        for (const auto& student : studenti) {
            if (student.licentiat) {
                cout << student.nume << " " << student.prenume << " - " << getSpecialitateString(student.specialitate) << endl;
            }
        }
    }

    bool cautaStudentDupaEmail(string email) {
        for (const auto& student : studenti) {
            if (student.email == email) {
                cout << "Student gasit: " << student.nume << " " << student.prenume << endl;
                return true;
            }
        }
        cout << "Studentul cu emailul " << email << " nu a fost gasit.\n";
        return false;
    }

    void logOperation(const string& operatiune) {
        ofstream log("log_operatiuni.txt", ios::app);
        if (!log.is_open()) {
            cout << "Nu am putut deschide fisierul log_operatiuni.txt\n";
            return;
        }
        log << operatiune << endl;
        log.close();
    }
};

void meniu() {
    vector<Facultate> facultati;
    vector<string> istoric_optiuni;

    int optiune;
    do {
        cout << "\nMeniu:\n";
        cout << "1. Creeaza facultate\n";
        cout << "2. Adauga student\n";
        cout << "3. Afiseaza studenti inrolati\n";
        cout << "4. Afiseaza studenti licentiati\n";
        cout << "5. Cauta student dupa email\n";
        cout << "6. Inscriere studenti ne-licentiati in enrolled.txt\n";
        cout << "7. Absolvire studenti licentiati in graduated.txt\n";
        cout << "8. Afiseaza istoric optiuni\n";
        cout << "0. Iesire\n";
        cout << "Alege o optiune: ";
        cin >> optiune;
        cin.ignore();

        if (optiune != 0) {
            istoric_optiuni.push_back(to_string(optiune));
        }

        if (optiune == 1) {
            string nume_facultate, abreviere;
            cout << "Nume facultate: ";
            getline(cin, nume_facultate);
            cout << "Abreviere facultate: ";
            getline(cin, abreviere);
            facultati.emplace_back(nume_facultate, abreviere);
            facultati.back().logOperation("Creeaza facultate: " + nume_facultate);
            cout << "Facultatea a fost creata.\n";
        }
        else if (optiune == 2) {
            string nume, prenume, data_inrolarii, data_nasterii, email;
            int licentiat, specialitate_int;

            cout << "Nume student: ";
            getline(cin, nume);
            cout << "Prenume student: ";
            getline(cin, prenume);
            cout << "Data inrolarii: ";
            getline(cin, data_inrolarii);
            cout << "Data nasterii: ";
            getline(cin, data_nasterii);
            cout << "Email student: ";
            getline(cin, email);
            cout << "Licentiat (1 pentru da, 0 pentru nu): ";
            cin >> licentiat;
            cout << "Specialitate (0-Mechanical Engineering, 1-Food Alimentation, 2-Information Technology, 3-Software Engineering, 4-Urbanism Architecture): ";
            cin >> specialitate_int;

            Specialitate specialitate = static_cast<Specialitate>(specialitate_int);
            Student student(nume, prenume, data_inrolarii, data_nasterii, email, specialitate, licentiat);
            if (!facultati.empty()) {
                facultati.back().adaugaStudent(student);
                facultati.back().logOperation("Adauga student: " + nume + " " + prenume);
            }
        }
        else if (optiune == 6) {
            if (!facultati.empty()) {
                facultati.back().inscriereStudentLot();
                facultati.back().logOperation("Inscriere studenti ne-licentiati in enrolled.txt");
            }
        }
        else if (optiune == 7) {
            if (!facultati.empty()) {
                facultati.back().absolvireStudentLot();
                facultati.back().logOperation("Absolvire studenti licentiati in graduated.txt");
            }
        }
        else if (optiune == 3) {
            if (!facultati.empty()) {
                facultati.back().afiseazaStudentiInrolati();
                facultati.back().logOperation("Afiseaza studenti inrolati");
            }
        }
        else if (optiune == 4) {
            if (!facultati.empty()) {
                facultati.back().afiseazaStudentiLicentiati();
                facultati.back().logOperation("Afiseaza studenti licentiati");
            }
        }
        else if (optiune == 5) {
            string email;
            cout << "Introdu email student: ";
            getline(cin, email);
            if (!facultati.empty()) {
                facultati.back().cautaStudentDupaEmail(email);
                facultati.back().logOperation("Cauta student dupa email: " + email);
            }
        }
        else if (optiune == 8) {
            cout << "Istoric optiuni:\n";
            for (const auto& optiune : istoric_optiuni) {
                cout << optiune << endl;
            }
        }

    } while (optiune != 0);
}

int main() {
    meniu();
    return 0;
}
