#include <algorithm>
#include <iostream>
#include <string>
#include <cassert>
#include <vector>
#include <map>
#include <set>
#include <string.h>

using namespace std;


/////////////////////////
//Ide dolgozz!!
////////////////////////

class Telepes {
  string nev;
  string szulBolygo;
  string bolygo;
  unsigned ero;
  bool vegan;

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
  const bool& isVegan() const {
    return vegan;
  }
  void setVegan(const bool& ujVegan) {
    vegan = ujVegan;
  }

  Telepes() : nev(""), szulBolygo(""), bolygo(""), ero(1), vegan(false) {}
};



class Kolonia {
  vector<Telepes> benneLakoTelepesek;
  string nev;
  string bolygo;

public:
  const string& getNev() const {
    return nev;
  }
  const string& getBolygo() const {
    return bolygo;
  }
  const unsigned getLetszam() const {
    return benneLakoTelepesek.size();
  }
  const vector<Telepes> getLakos() const {
    return benneLakoTelepesek;
  }
  Kolonia(const string& nev, const string& bolygo) : nev(nev), bolygo(bolygo) {}
  Kolonia() : nev(""), bolygo("") {}

  void letelepszik(Telepes t) {
    if(benneLakoTelepesek.size() < 25) {
      if(veganE(*this)) {
        if(t.isVegan()) {
          benneLakoTelepesek.push_back(t);
          t.setBolygo(bolygo);
        } else {
          cerr << "A kolonia vegan" << endl;
        }
      } else {
        benneLakoTelepesek.push_back(t);
        t.setBolygo(bolygo);
      }
    } else {
      cout << "A kolonia megtelt" << endl;
    }
  }

  void nevsor() const {
    set<string> nevek;
    for (const auto& telepes : benneLakoTelepesek) {
      nevek.insert(telepes.getNev());
    }
    for (const auto& nev : nevek) {
      cout << nev << endl;
    }
  }

  const unsigned legerosebb() const {
    if (benneLakoTelepesek.size() == 0) {
      return 0;
    } else {
      unsigned maxPower = 0;
      for(const auto& telepes : benneLakoTelepesek) {
        if(telepes.getEro() > maxPower) {
          maxPower = telepes.getEro();
        }
      }
      return maxPower;
    }
  }

  int szamol(const string& bolygoNev) const {
    int counter = 0;
    for(const auto& telepes : benneLakoTelepesek) {
      if (strcasecmp(telepes.getSzulBolygo().c_str(), bolygoNev.c_str()) == 0) {
        counter++;
      }
    }
    return counter;
  }

  map<unsigned, unsigned> eroHisztogram() const {
    map<unsigned, unsigned> map;
    for(const auto& telepes : benneLakoTelepesek) {
      map[telepes.getEro()]++;
    }
    return map;
  }

  friend bool veganE(const Kolonia& k);
};




bool veganE(const Kolonia& k) {
  if(k.getLetszam() == 0) {
    return false;
  }
  unsigned veganCounter = 0;
  for(const auto& telepes : k.getLakos()) {
    if(telepes.isVegan()) {
      veganCounter++;
    }
  }
  if(veganCounter > k.getLetszam()/2) {
    return true;
  } else {
    return false;
  }
}

#ifndef TEST_BIRO
int main(){

  //telepes osztaly tesztek
/*
    Telepes t1;
    assert(t1.getNev() == "");
    assert(t1.getSzulBolygo() == "");
    assert(t1.getBolygo() == "");
    assert(t1.getEro() == 1);
    assert(!t1.isVegan());

    t1.setSzulBolygo("Mars");
    t1.setBolygo("Venus");
    t1.setNev("Jevgenyij Anyegin");
    t1.setEro(10);
    t1.setVegan(true);
    assert(t1.getNev() == "Jevgenyij Anyegin");
    assert(t1.getSzulBolygo() == "Mars");
    assert(t1.getBolygo() == "Venus");
    assert(t1.getEro() == 10);
    assert(t1.isVegan());
*/



  //kolonia letelepszik tesztek
  /*
    Kolonia k("Kolonia1", "Mars");
    Telepes t1;
    t1.setNev("Janos");
    t1.setEro(5);
    t1.setVegan(true);
    k.letelepszik(t1);
    assert(k.getLetszam() == 1);

    Telepes t2;
    t2.setNev("Juli");
    t2.setEro(3);
    t2.setVegan(false);
    k.letelepszik(t2);
    assert(k.getLetszam() == 1); // Juli nem lett telepes, mert a kolónia vegán

    for (int i = 0; i < 24; ++i) {
    Telepes t;
    t.setNev("Telepes" + std::to_string(i));
    t.setEro(2);
    t.setVegan(true);
    k.letelepszik(t);
    }
    assert(k.getLetszam() == 25);

    Telepes t26;
    t26.setNev("Telepes26");
    t26.setEro(4);
    t26.setVegan(true);
    k.letelepszik(t26); // Kolónia megtelt
    assert(k.getLetszam() == 25);
  */



  //kolonia nevsor teszt
/*
    Kolonia k("Kolonia1", "Mars");
    Telepes t1;
    t1.setNev("Janos");
    k.letelepszik(t1);

    Telepes t2;
    t2.setNev("Juli");
    k.letelepszik(t2);

    Telepes t3;
    t3.setNev("Julia");
    k.letelepszik(t3);

    Telepes t4;
    t4.setNev("Janos");
    k.letelepszik(t4); // Duplicate

    k.nevsor(); // Janos Juli Julia
*/



  //kolonia vegan teszt
  /*
    Kolonia k("Anarchy for all!", "Mars");
    assert(!veganE(k));

    Telepes t;
    t.setVegan(true);
    k.letelepszik(t);
    assert(veganE(k));
  */


 /*
  //kolonia legerosebb teszt

    Kolonia k("Kolonia1", "Mars");
    Telepes t1;
    t1.setNev("Janos");
    t1.setEro(5);
    k.letelepszik(t1);

    Telepes t2;
    t2.setNev("Juli");
    t2.setEro(3);
    k.letelepszik(t2);

    Telepes t3;
    t3.setNev("Julia");
    t3.setEro(8);
    k.letelepszik(t3);

    assert(k.legerosebb() == 8);
*/


  //kolonia szamol teszt
  /*
    Kolonia k("Kolonia1", "Mars");
    Telepes t1;
    t1.setNev("Janos");
    t1.setSzulBolygo("Mars");
    k.letelepszik(t1);

    Telepes t2;
    t2.setNev("Juli");
    t2.setSzulBolygo("mars");
    k.letelepszik(t2);

    Telepes t3;
    t3.setNev("Julia");
    t3.setSzulBolygo("Venus");
    k.letelepszik(t3);

    assert(k.szamol("Mars") == 2);
  */


  
  //kolonia eroHisztogram teszt
  /*
    Kolonia k("Kolonia1", "Mars");
    Telepes t1;
    t1.setNev("Janos");
    t1.setEro(5);
    k.letelepszik(t1);

    Telepes t2;
    t2.setNev("Juli");
    t2.setEro(2);
    k.letelepszik(t2);

    Telepes t3;
    t3.setNev("Julia");
    t3.setEro(1);
    k.letelepszik(t3);

    Telepes t4;
    t4.setNev("Janet");
    t4.setEro(1);
    k.letelepszik(t4);

    Telepes t5;
    t5.setNev("John");
    t5.setEro(5);
    k.letelepszik(t5);

    auto hist = k.eroHisztogram();
    assert(hist[1] == 2);
    assert(hist[2] == 1);
    assert(hist[5] == 2);
  */


  return 0;
}
#endif