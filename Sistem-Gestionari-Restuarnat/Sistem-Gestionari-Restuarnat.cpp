#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Rezervare {
protected:
    string nume;
    string data;
    string ora;
    int persoane;

public:
    Rezervare(string n, string d, string o, int p)
        : nume(n), data(d), ora(o), persoane(p) {
    }

    virtual int durata() { return 2; }

    virtual int calculeazaPret() = 0;
    virtual string tip() = 0;

    virtual void afisare() {
        cout << "Tip: " << tip() << endl;
        cout << "Client: " << nume << endl;
        cout << "Data: " << data << " " << ora << endl;
        cout << "Persoane: " << persoane << endl;
        cout << "Durata: " << durata() << " ore" << endl;
        cout << "Pret: " << calculeazaPret() << " lei\n";
        cout << "----------------------\n";
    }

    virtual ~Rezervare() {}
};

class RezervareZilnica : public Rezervare {
public:
    RezervareZilnica(string n, string d, string o, int p)
        : Rezervare(n, d, o, p) {
    }

    int calculeazaPret() override {
        if (persoane <= 2) return 50;
        return 50 + (persoane - 2) * 20;
    }

    string tip() override { return "RezervareZilnica"; }
};

class RezervareSpecial : public Rezervare {
    int durata_rezervarii;
public:
    RezervareSpecial(string n, string d, string o, int p, int durata)
        : Rezervare(n, d, o, p), durata_rezervarii(durata) {
    }

    int calculeazaPret() override {
        int pret = 200;
        if (durata_rezervarii > 4)
            pret += (durata_rezervarii - 4) * 50;
        return pret;
    }

    string tip() override { return "RezervareSpecial"; }

    int durata() override { return durata_rezervarii; }
};

class RezervareGrupMare : public Rezervare {
public:
    RezervareGrupMare(string n, string d, string o, int p)
        : Rezervare(n, d, o, p) {
    }

    int calculeazaPret() override {
        int pret = 500;
        if (persoane > 20) pret += (persoane - 20) * 10;
        return pret;
    }

    string tip() override { return "RezervareGrupMare"; }
};

class RezervareVIP : public Rezervare {
public:
    RezervareVIP(string n, string d, string o, int p)
        : Rezervare(n, d, o, p) {
    }

    int calculeazaPret() override {
        if (persoane <= 5) return 1000;
        return 1000 + (persoane - 5) * 200;
    }

    string tip() override { return "RezervareVIP"; }
};

int main() {
    vector<Rezervare*> rezervari;
    int opt;

    do {
        cout << "\n=== MENIU ===\n";
        cout << "1. Rezervare zilnica\n";
        cout << "2. Eveniment special\n";
        cout << "3. Grup mare\n";
        cout << "4. VIP\n";
        cout << "5. Afiseaza rezervari\n";
        cout << "0. Iesire\n";
        cout << "Alege: ";
        cin >> opt;
        cin.ignore();

        if (opt >= 1 && opt <= 4) {
            string nume, data, ora;
            int persoane, durata = 0;

            cout << "Nume client: ";
            getline(cin, nume);

            cout << "Data (YYYY-MM-DD): ";
            getline(cin, data);

            cout << "Ora (HH:MM): ";
            getline(cin, ora);

            cout << "Persoane: ";
            cin >> persoane;
            cin.ignore();

            if (opt == 2) {
                cout << "Durata (ore): ";
                cin >> durata;
                cin.ignore();
            }

            Rezervare* r = nullptr;

            if (opt == 1) r = new RezervareZilnica(nume, data, ora, persoane);
            else if (opt == 2) r = new RezervareSpecial(nume, data, ora, persoane, durata);
            else if (opt == 3) r = new RezervareGrupMare(nume, data, ora, persoane);
            else if (opt == 4) r = new RezervareVIP(nume, data, ora, persoane);

            if (r) {
                rezervari.push_back(r);

                
                ofstream fout("rezervari.txt", ios::app);
                fout << r->tip() << " "
                    << nume << " "
                    << data << " "
                    << ora << " "
                    << persoane;

                if (opt == 2) fout << " " << durata;

                fout << " Pret:" << r->calculeazaPret() << "lei" << endl;
                fout.close();

                cout << "Rezervare salvata! Pret de achitat: " << r->calculeazaPret() << " lei\n";
            }
        }

        if (opt == 5) {
            cout << "\n=== Rezervari ===\n";
            for (Rezervare* rez : rezervari)
                rez->afisare();
        }

    } while (opt != 0);

    for (Rezervare* rez : rezervari) delete rez;

    cout << "Program inchis.\n";
    return 0;
}