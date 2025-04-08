#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

class Etel {
    string nev;
    string leiras;
    unsigned ar;
public:
    Etel() : nev("amint kesz megtudod"), leiras("ami sikerul"), ar(0) {}
    Etel(const string& nev, const string& leiras, const unsigned& ar) : nev(nev), leiras(leiras), ar(ar) {}

    virtual const string get_nev() const {
        return nev;
    }
    const string& get_leiras() const {
        return leiras;
    }

    virtual operator unsigned() const {
        return ar;
    }

    virtual unsigned get_type() const {
        return 0;
    }

    const unsigned& get_ar() const {
        return ar;
    }
};




class Menu : public Etel {
    vector<Etel> menu;
public:
    Menu() : Etel(), menu(3, Etel()) {}
    Menu(const string& nev, const string& leiras) : Etel(nev, leiras, 0), menu(3, Etel()) {}
    Menu(const string& nev, const string& leiras, const Etel& etel1, const Etel& etel2, const Etel& etel3) : Etel(nev, leiras, 0), menu{etel1, etel2, etel3} {}

    const string get_nev() const override {
        return "Menu: " + Etel::get_nev();
    }

    operator unsigned() const override {
        unsigned osszeg = 0;
        for(const auto& etel : menu) {
            osszeg += etel;
        }
        return (osszeg * 9) / 10;;
    }

    const Etel& operator[](size_t i) const {
        if(i >= menu.size()) {
            throw exception();
        }
        return menu[i];
    }

    unsigned get_type() const override {
        return 1;
    }

};



class Vendeglo {
    vector<reference_wrapper<Etel>> kajak;
public:
    Vendeglo() = default;

    Vendeglo& operator<<(Etel& letarolando) {
        kajak.push_back(letarolando);
        return *this;
    }

    Etel& operator[](size_t index) {
        if (index >= kajak.size()) {
            throw std::exception();
        }
        return kajak[index].get();
    }

    operator Etel() const {
        bool found = false;
        Etel cheapest; // inicializálva default konstruktorról
        for (const auto& kaja : kajak) {
            const Etel& current = kaja.get();
            if (current.get_type() != 0) {
                continue; // csak egyszerű ételeket nézünk
            }
            if (!found) {
                cheapest = current;
                found = true;
            } else {
                if (static_cast<unsigned>(current) < static_cast<unsigned>(cheapest)) {
                    cheapest = current;
                }
            }
        }
        if (!found) {
            throw exception();
        }
        return cheapest;
    }
};

int main() {
    // 1. feladat: Etel osztály tesztelése
    Etel etel1;  // Default konstruktor
    Etel etel2("Pizza", "Sonkás-sajtos pizza", 1200);  // Paraméteres konstruktor

    std::cout << "Etel1 neve: " << etel1.get_nev() << ", leírása: " << etel1.get_leiras() << ", ára: " << (unsigned int)etel1 << "\n";
    std::cout << "Etel2 neve: " << etel2.get_nev() << ", leírása: " << etel2.get_leiras() << ", ára: " << (unsigned int)etel2 << "\n";

    // 2. feladat: Menu osztály tesztelése
    Etel etel3("Leves", "Zöldségleves", 600);
    Etel etel4("Tészta", "Spagetti bolognese", 1500);
    Menu menu1("Ebédmenü", "3 fogásos ebéd", etel2, etel3, etel4);

    std::cout << "Menu neve: " << menu1.get_nev() << "\n";
    std::cout << "Menu ára: " << (unsigned int)menu1 << "\n";  // 10% kedvezmény

    // 3. feladat: Vendeglo osztály tesztelése
    Vendeglo vendeglo;
    vendeglo << etel3 << etel2 << etel4 << menu1;

    try {
        std::cout << "A vendéglő legolcsóbb étele: " << vendeglo.operator Etel().get_nev() << "\n";
    } catch (const std::exception& e) {
        std::cout << "Hiba: " << e.what() << "\n";
    }

    return 0;
}