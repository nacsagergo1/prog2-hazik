#include <iostream>
#include <string>
#include <cassert>
#include <vector>

using namespace std;


class Kutya {
  string nev;
  unsigned kor;
public:
  const string& getNev() const {
    return nev;
  }
  const unsigned& getKor() const {
    return kor;
  }
  Kutya(const string& nev, const unsigned& kor) : nev(nev), kor(kor) {
    cout << "Kutya letrehozva" << endl;
  }

  virtual string pedigre() const {
    return "nev:" + nev + ", kor:" + to_string(kor) + " ev";
  }

  virtual vector<string> terel(const vector<string>& birkanyaj) const {
    return birkanyaj;
  }
  virtual ~Kutya() = default;
};

class BorderCollie final : public Kutya{
  unsigned tereloKapacitas;
public:
  const unsigned& getTereloKapacitas() const {
    return tereloKapacitas;
  }
  BorderCollie(const string& nev, const unsigned& kor, const unsigned& tereloKapacitas) : Kutya(nev, kor), tereloKapacitas(tereloKapacitas) {}

  string pedigre() const override {
    return Kutya::pedigre() + ", faj:border collie, terelo kapacitas:" + to_string(tereloKapacitas) + " db birka";
  }

  vector<string> terel(const vector<string>& birkanyaj) const override {
    vector<string> eredeti = birkanyaj;
    vector<string> ujBirkanyaj = birkanyaj;
    unsigned jelenTereloKapacitas = tereloKapacitas;
    unsigned irasIndex = 0;

    for (unsigned i = 0; i < eredeti.size(); i++) {
        if (!eredeti[i].empty()) {
            unsigned cost = i - irasIndex;
            if (cost <= jelenTereloKapacitas) {
                if (i != irasIndex) {
                    ujBirkanyaj[irasIndex] = eredeti[i];
                    ujBirkanyaj[i] = "";
                }
                jelenTereloKapacitas -= cost;
                irasIndex++;
            } else {
                break;
            }
        }
    }

    if (!ujBirkanyaj.empty()) {
        int lastNonEmpty = -1;
        for (unsigned i = 0; i < ujBirkanyaj.size(); i++) {
            if (!ujBirkanyaj[i].empty())
                lastNonEmpty = i;
        }
        if (lastNonEmpty != -1)
            ujBirkanyaj.resize(lastNonEmpty + 1);
        else
            ujBirkanyaj.clear();
    }

    return ujBirkanyaj;
}
};

void print(const Kutya& kutya) {
  cout << kutya.pedigre() << endl;
}

/////////////////////////
//Ide dolgozz!!
////////////////////////

int main(){

  //alap kutya
  {
 /*
    const Kutya k("Lassie", 3);
    assert(k.getNev() == "Lassie");
    assert(k.getKor() == 3);
  */
  }
  
  //alap kutya pedigre
  {
    /*
    const Kutya k("Lassie", 3);
    string s = k.pedigre();
    assert(s == "nev:Lassie, kor:3 ev");
    */
  }
  
  //alap kutya terel
  {
    /*
    const Kutya k("Lassie", 3);
    vector<string> dinamikus_nyaj = k.terel({"Frici", "Julcsa", "Gyuri", "Margit"});
    assert(dinamikus_nyaj[3] == "Margit");
    */
  }

  //test border collie
  {
    /*
    const BorderCollie bc("Jess", 13, 5);
    assert(bc.getNev() == "Jess");
    assert(bc.getKor() == 13);
    assert(bc.getTereloKapacitas() == 5);
    */
  }
  
  //pedigre border collie
  {
    /*
    const Kutya* bc = new BorderCollie("Jess", 13, 5);
    string s = bc->pedigre();
    assert(s == "nev:Jess, kor:13 ev, faj:border collie, terelo kapacitas:5 db birka");
    delete bc;
    */
  }
  

  //terel border collie
  {
    /*
    const Kutya* bc = new BorderCollie("Jess", 13, 3);
    vector<string> nyaj = {"Frici", "", "Julcsa", "Gyuri", "", "Margit"};
    vector<string> dinamikus_nyaj = bc->terel(nyaj);
    assert(dinamikus_nyaj[0] == "Frici");
    assert(dinamikus_nyaj[1] == "Julcsa");
    assert(dinamikus_nyaj[2] == "Gyuri");
    assert(dinamikus_nyaj[3] == "");//terelokapacitas!
    assert(dinamikus_nyaj[4] == "");
    assert(dinamikus_nyaj[5] == "Margit");
    */
  }

  return 0;
}
