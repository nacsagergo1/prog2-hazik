#include <algorithm>
#include <iostream>
#include <string>
#include <cassert>

using namespace std;

/////////////////////////
//Ide dolgozz!!
////////////////////////

class Telepes {
    string nev;
    string szulBolygo;
    string bolygo;
    unsigned ero;
public:
    const string& getNev() const {
        return nev;
    }
    void setNev(const string& ujNev) {
        nev = ujNev;
    }
    const string& getSzulBolygo() const {
        return szulBolygo;
    }
    void setSzulBolygo(const string& ujSzulBolygo) {
        szulBolygo = ujSzulBolygo;
    }
    const string& getBolygo() const {
        return bolygo;
    }
    void setBolygo(const string& ujBolygo) {
        bolygo = ujBolygo;
    }
    const unsigned& getEro() const {
        return ero;
    }
    void setEro(const unsigned& ujEro) {
        ero = ujEro;
    }

    Telepes(const string& nev, const string& szulBolygo, const string& bolygo, const unsigned& ero) : nev(nev), szulBolygo(szulBolygo), bolygo(bolygo), ero(ero) {}
    Telepes() : nev(""), szulBolygo(""), bolygo(""), ero(1) {}
    Telepes(const string& nev, const string& bolygo, const unsigned& ero = 1) : nev(nev), szulBolygo(bolygo), bolygo(bolygo), ero(ero) {}

    bool kivandorlo() const {
        string bolygoja = bolygo;
        string szuletesiBolygoja = szulBolygo;
        std::transform(bolygoja.begin(), bolygoja.end(), bolygoja.begin(), ::tolower);
        std::transform(szuletesiBolygoja.begin(), szuletesiBolygoja.end(), szuletesiBolygoja.begin(), ::tolower);
        if(bolygoja == szuletesiBolygoja) {
            return false;
        } else {
            return true;
        }
    }

    void dolgozik(string& munkak) const {
        size_t pos = 0;
        unsigned count = 0;
        while (count < ero) {
            pos = munkak.find(';');
            if (pos == std::string::npos) { // Ha nincs több pontosvessző, egyetlen feladat maradt
                if (!munkak.empty()) {
                    munkak.clear();
                }
                break;
            }
            munkak.erase(0, pos + 1);
            count++;
        }
        if (count < ero && !munkak.empty()) {
            munkak.clear();
        }
    }
};

#ifndef TEST_BIRO
int main(){

  //Telepes konstruktor
/*
    Telepes t1;
    assert(t1.getNev() == "");
    assert(t1.getSzulBolygo() == "");
    assert(t1.getBolygo() == "");
    assert(t1.getEro() == 1);

    t1.setSzulBolygo("Mars");
    t1.setBolygo("Venus");
    t1.setNev("Jevgenyij Anyegin");
    t1.setEro(10);
    assert(t1.getNev() == "Jevgenyij Anyegin");
    assert(t1.getSzulBolygo() == "Mars");
    assert(t1.getBolygo() == "Venus");
    assert(t1.getEro() == 10);
    */


  //Telepes parameteres konstruktor
/*
    const Telepes t1("Franz Kafka", "Mars", "Venus", 50);
    assert(t1.getNev() == "Franz Kafka");
    assert(t1.getSzulBolygo() == "Mars");
    assert(t1.getBolygo() == "Venus");
    assert(t1.getEro() == 50);
    */


  //Telepes parameteres konstruktor 2
/*
    const Telepes t1("Kurt Vonnegut", "Venus", 4);
    assert(t1.getNev() == "Kurt Vonnegut");
    assert(t1.getSzulBolygo() == "Venus");
    assert(t1.getBolygo() == "Venus");
    assert(t1.getEro() == 4);

    const Telepes t2("Kurt Vonnegut", "Venus");
    assert(t2.getNev() == "Kurt Vonnegut");
    assert(t2.getSzulBolygo() == "Venus");
    assert(t2.getBolygo() == "Venus");
    assert(t2.getEro() == 1);
   */

  //Kivandorlo teszt
  /*
    const Telepes t1("Franz Kafka", "Mars", "Px-2312", 50); //Kafka kivandorlo
    assert(t1.kivandorlo());
*/

  //Munkavegzes teszt
/*
    const Telepes t1("Kovacs Geza", "Uranus", "Px-2312", 2);
    string munkak = "b1;b22;c3;x823";
    t1.dolgozik(munkak);
    assert(munkak == "c3;x823");
*/

  return 0;
}
#endif