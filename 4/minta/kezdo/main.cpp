#include <string>
#include <vector>
#include <map>
#include <cassert>
#include <algorithm>
#include  <iostream>

using namespace std;

class Telepes{

  string nev, szul_bolygo, bolygo;
  unsigned oxigen;

public:

  Telepes(string _nev, string _szul_bolygo, string _bolygo, unsigned _oxigen):
          nev(_nev),
          szul_bolygo(_szul_bolygo),
          bolygo(_bolygo),
          oxigen(_oxigen){

  }

  Telepes():
          Telepes("", "", "", 100){
  }

  Telepes(string _nev, string _bolygo, unsigned _oxigen = 100):
          Telepes(_nev, _bolygo, _bolygo, _oxigen){
  }

  string getNev() const{
    return nev;
  }

  string getSzulBolygo() const{
    return szul_bolygo;
  }

  string getBolygo() const{
    return bolygo;
  }

  unsigned getOxigen() const{
    return oxigen;
  }

  void setNev(const string& _nev){
    nev = _nev;
  }

  void setSzulBolygo(const string& _szul_bolygo){
    szul_bolygo = _szul_bolygo;
  }

  void setBolygo(const string& _bolygo){
    bolygo = _bolygo;
  }

  void setOxigen(unsigned _oxigen){
    oxigen = _oxigen;
  }

  Telepes& operator-=(unsigned ox){
    if (ox <= oxigen) {
      oxigen -= ox;
    } else {
      oxigen = 0;
    }
    return *this;
  }

  operator string()const{
    return nev + " ("  + bolygo + ", " + to_string(oxigen) + ")";
  }

  Telepes& operator++() {
    if(oxigen < 100) {
      oxigen++;
    }
    return *this;
  }

  Telepes operator++(int) {
    Telepes temp = *this;
    ++(*this);
    return temp;
  }

};





bool operator==(const Telepes& t1, const Telepes& t2){
  return t1.getNev() == t2.getNev()
         && t1.getOxigen() == t2.getOxigen() && t1.getBolygo() == t2.getBolygo()
         && t1.getSzulBolygo() == t2.getSzulBolygo();
}

int operator+(const Telepes& t1, const Telepes& t2) {
  return t1.getOxigen() + t2.getOxigen();
}





class Korhaz {
  map<string, vector<Telepes>> betegek;
public:
  Korhaz(const map<string, vector<Telepes>>& betegek) : betegek(betegek) {}
  Korhaz() = default;

  const map<string, vector<Telepes>>& getBetegek() const {
    return betegek;
  }

  Korhaz& operator<<(const Telepes& t) {
    betegek[t.getBolygo()].push_back(t);
    return *this;
  }

  unsigned getLetszam() const {
    unsigned counter = 0;
    for(const auto& beteg : betegek) {
      counter += beteg.second.size();
    }
    return counter;
  }

  unsigned getLetszam(const string& bolygo) {
    return betegek.find(bolygo)->second.size();
  }

  operator string() const {
    string eredmeny = "";
    for(const auto& beteg : betegek) {
      eredmeny += beteg.first + "\n";
      for(const auto& vektor : beteg.second) {
        eredmeny += vektor.getNev() + " (" +  vektor.getBolygo() + ", " + to_string(vektor.getOxigen()) + ")\n";
      }
    }
    return eredmeny;
  }

  Korhaz& operator>>(const Telepes& t) {
    auto it = betegek.find(t.getBolygo());
    if (it != betegek.end()) {
      auto& vec = it->second;
      vec.erase(remove(vec.begin(), vec.end(), t), vec.end());
      if (vec.empty()) {
        betegek.erase(it);
      }
    }
    return *this;
  }

  bool operator<(const Korhaz& k) const {
    return (betegek.size() < k.betegek.size());
  }
};

Korhaz operator+(const Korhaz& k1, const Korhaz& k2) {
  Korhaz k;
  for(const auto& beteg : k1.getBetegek()) {
    for(const auto& vektor : beteg.second) {
      k<<vektor;
    }
  }
  for(const auto& beteg : k2.getBetegek()) {
    for(const auto& vektor : beteg.second) {
      k<<vektor;
    }
  }
  return k;
}



void test_telepes(){
  Telepes t1;
  assert(t1.getNev() == "");
  assert(t1.getSzulBolygo() == "");
  assert(t1.getBolygo() == "");
  assert(t1.getOxigen() == 100);

  t1.setSzulBolygo("Mars");
  t1.setBolygo("Venus");
  t1.setNev("Jevgenyij Anyegin");
  t1.setOxigen(70);
  assert(t1.getNev() == "Jevgenyij Anyegin");
  assert(t1.getSzulBolygo() == "Mars");
  assert(t1.getBolygo() == "Venus");
  assert(t1.getOxigen() == 70);

  Telepes t2("Jevgenyij Anyegin", "Mars", "Venus", 70);
  Telepes t3("Alekszej Vronszkij", "Mars", "Mars", 99);
  assert(t1 == t2);
  assert(!(t1 == t3)); //t1 es t3 nem egyenloek

  t1 -= 30;
  assert(t1.getOxigen() == 40);
  t1 -= 45;
  assert(t1.getOxigen() == 0); //max 0-ig csokkenhet az oxigenszint

  ((t2 -= 5) -= 30) -= 35;
  assert(t2.getOxigen() == 0); //0-ra kell csokkennie az oxigenszintnek

  assert(std::string(t2) == "Jevgenyij Anyegin (Venus, 0)");

  /* t2++;
   assert(t2.getOxigen() == 1);
   ++t2;
   assert(t2.getOxigen() == 2);*/
}

void test_korhaz(){
  /* Korhaz k;
   Telepes t1("T1", "SzuletesiBolygo", "LakoBolygo1", 70);
   Telepes t2("T2", "SzuletesiBolygo", "LakoBolygo2", 70);
   Telepes t3("T3", "SzuletesiBolygo", "LakoBolygo1", 33);

   k << t1 << t2 << t3;

   assert(k.getLetszam() == 3);
   assert(k.getLetszam("LakoBolygo1") == 2);
   assert(k.getLetszam("LakoBolygo2") == 1);

   std::string expected = "LakoBolygo1\nT1 (LakoBolygo1, 70)\nT3 (LakoBolygo1, 33)\nLakoBolygo2\nT2 (LakoBolygo2, 70)\n";
   assert(std::string(k) == expected);

   k >> t1;
   assert(k.getLetszam() == 2);
   assert(k.getLetszam("LakoBolygo1") == 1);
   expected = "LakoBolygo1\nT3 (LakoBolygo1, 33)\nLakoBolygo2\nT2 (LakoBolygo2, 70)\n";
   assert(std::string(k) == expected);

   Korhaz k2;
   k2 << t1;
   assert(k2.getLetszam() == 1);
   assert(k2.getLetszam("LakoBolygo1") == 1);

   Korhaz k3 = k + k2;
   assert(k3.getLetszam() == 3);

   assert(k2 < k);*/
}


int main(){
  test_telepes();
  test_korhaz();

  return 0;
}

