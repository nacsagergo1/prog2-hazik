#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <numeric>

using namespace std;

class Jarat {
  string honnan, hova;
  unsigned ar;


public:
  Jarat(const string& honnan, const string& hova, unsigned ar) :
          honnan(honnan), hova(hova),
          ar(ar) { }


  const string &getHonnan() const {
    return honnan;
  }

  const string &getHova() const {
    return hova;
  }

  unsigned int getAr() const {
    return ar;
  }

  void setAr(unsigned a){
    ar = a;
  }

  bool operator<(const Jarat& masik) const {
    if(honnan != masik.honnan) {
      return honnan < masik.honnan;
    }
    return hova < masik.hova;
  }

  friend ostream& operator<<(ostream& os, const Jarat& t) {
    return os << t.honnan << "-" << t.hova << " (" << t.ar << " forint)";
  }
};

set<Jarat> jarat_set(const vector<Jarat>& jaratok) {
  return set<Jarat>(jaratok.begin(), jaratok.end());
}

void legolcsobb(const vector<Jarat>& jaratok, map<string, unsigned>& result) {
  for(const auto& jarat : jaratok) {
    string kulcs = jarat.getHonnan() + jarat.getHova();
    auto iterator = result.find(kulcs);
    if(iterator == result.end() || jarat.getAr() < iterator->second) {
      result[kulcs] = jarat.getAr();
    }
  }
}

unsigned szamol(const vector<Jarat>& jaratok, const string& varos) {
  return count_if(jaratok.begin(), jaratok.end(), [&](const Jarat& jarat){return jarat.getHova() == varos;});
}

vector<Jarat> filter(const vector<Jarat>& jaratok, const string& param1, const string& param2) {
  vector<Jarat> result;
  for(const auto& jarat : jaratok) {
    if(jarat.getHonnan() == param1 && jarat.getHova() == param2) {
      result.push_back(jarat);
    }
  }

  for(const auto& jarat : jaratok) {
    if(jarat.getHonnan() == param2 && jarat.getHova() == param1) {
      result.push_back(jarat);
    }
  }

  return result;
}

void fullSort(vector<Jarat>& jaratok) {
  sort(jaratok.begin(), jaratok.end(), [](const Jarat& lhs, const Jarat& rhs){
      return lhs.getAr() < rhs.getAr();
  });
}

unsigned fullCost(const vector<Jarat>& jaratok, unsigned limit) {
  return accumulate(jaratok.begin(), jaratok.end(), 0u, [&](unsigned sum, const Jarat& j) {
          return sum + (j.getAr() < limit ? j.getAr() : 0u);
      }
  );
}

vector<Jarat> akcio(const vector<Jarat>& jaratok, unsigned szazalek) {
  if (szazalek > 100)
    throw std::exception();
  vector<Jarat> ered;
  ered.reserve(jaratok.size());
  transform(jaratok.begin(), jaratok.end(), back_inserter(ered),
      [&](Jarat j) {
          unsigned ujAr = j.getAr() * (100u - szazalek) / 100u;
          j.setAr(ujAr);
          return j;
      }
  );
  return ered;
}




void test_jarat_set() {
  cout << endl << " --- test_jarat_set ---" << endl << endl;

  vector<Jarat> jaratok;
  jaratok.emplace_back("Budapest","Berlin", 32000);
  jaratok.emplace_back("Budapest","Bagdad", 86000);
  jaratok.emplace_back("Budapest","Berlin", 2000);
  jaratok.emplace_back("Tokio","Berlin", 200220);
  jaratok.emplace_back("Tokio","Budapest", 221000);


  set<Jarat> halmaz = jarat_set(jaratok);
  for(auto j : halmaz){
    cout << j << endl;
  }


  //kimenet
  //Budapest-Bagdad (86000 forint)
  //Budapest-Berlin (32000 forint)
  //Tokio-Berlin (200220 forint)
  //Tokio-Budapest (221000 forint)

}

void test_min_ar() {
  cout << endl << " --- test_legolcsobb ---" << endl << endl;

  vector<Jarat> jaratok;
  jaratok.emplace_back("Budapest","Berlin", 2000);
  jaratok.emplace_back("Budapest","Bagdad", 86000);
  jaratok.emplace_back("Budapest","Berlin", 32000);
  jaratok.emplace_back("Tokio","Berlin", 200220);
  jaratok.emplace_back("Tokio","Budapest", 221000);
  jaratok.emplace_back("Budapest","Bagdad", 8600);
  jaratok.emplace_back("Tokio","Berlin", 200);
  jaratok.emplace_back("Tokio","Berlin", 100);


  map<string, unsigned> olcso_jaratok;
  legolcsobb(jaratok, olcso_jaratok);

  for(const auto& p : olcso_jaratok){
    cout << p.first << " : " << p.second << endl;
  }

  // kimenet
  //BudapestBagdad : 8600
  //BudapestBerlin : 2000
  //TokioBerlin : 100
  //TokioBudapest : 221000


}

void test_szamol() {
  cout << endl << " --- szamol ---" << endl << endl;

  vector<Jarat> jaratok;
  jaratok.emplace_back("Budapest","Berlin", 2000);
  jaratok.emplace_back("Budapest","Bagdad", 86000);
  jaratok.emplace_back("Budapest","Berlin", 32000);
  jaratok.emplace_back("Tokio","Berlin", 200220);
  jaratok.emplace_back("Tokio","Budapest", 221000);
  jaratok.emplace_back("Budapest","Bagdad", 8600);
  jaratok.emplace_back("Tokio","Berlin", 200);


  cout << szamol(jaratok, "Berlin") << endl;

  jaratok.emplace_back("Tokio","Berlin", 100);
  jaratok.emplace_back("Berlin","Moszkva", 10340);

  cout << szamol(jaratok, "Berlin") << endl;

  // kimenet
  //4
  //5


}

void test_filter() {
  cout << endl << " --- filter ---" << endl << endl;

  vector<Jarat> jaratok;
  jaratok.emplace_back("Budapest","Berlin", 2000);
  jaratok.emplace_back("Budapest","Bagdad", 86000);
  jaratok.emplace_back("Berlin","Budapest", 32000);
  jaratok.emplace_back("Berlin","Bagdad", 200220);
  jaratok.emplace_back("Berlin","Budapest", 52000);

  auto result = filter(jaratok, "Berlin", "Budapest");
  for(const auto& j : result){
    cout << j << endl;
  }
  cout << "----" << endl;

  result = filter(jaratok, "Budapest", "Berlin");
  for(const auto& j : result){
    cout << j << endl;
  }



  // kimenet
  //Berlin-Budapest (32000 forint)
  //Berlin-Budapest (52000 forint)
  //Budapest-Berlin (2000 forint)
  //----
  //Budapest-Berlin (2000 forint)
  //Berlin-Budapest (32000 forint)
  //Berlin-Budapest (52000 forint)



}


void test_fullsort() {
  cout << endl << " --- fullSort ---" << endl << endl;

  vector<Jarat> jaratok;
  jaratok.emplace_back("Budapest","Berlin", 2000);

  fullSort(jaratok);
  for(const auto& j : jaratok){
    cout << j << endl;
  }
  cout << endl;

  jaratok.emplace_back("Budapest","Bagdad", 86000);
  jaratok.emplace_back("Berlin","Budapest", 32000);
  jaratok.emplace_back("Berlin","Bagdad", 200220);
  jaratok.emplace_back("Berlin","Budapest", 52000);
  jaratok.emplace_back("Budapest","Bagdad", 76000);
  jaratok.emplace_back("Budapest","Washington", 1900);

  fullSort(jaratok);
  for(const auto& j : jaratok){
    cout << j << endl;
  }

}


  // kimenet
  //Budapest-Berlin (2000 forint)
  //
  //Budapest-Washington (1900 forint)
  //Budapest-Berlin (2000 forint)
  //Berlin-Budapest (32000 forint)
  //Berlin-Budapest (52000 forint)
  //Budapest-Bagdad (76000 forint)
  //Budapest-Bagdad (86000 forint)
  //Berlin-Bagdad (200220 forint)

void test_fullcost() {
  cout << endl << " --- fullCost ---" << endl << endl;

  vector<Jarat> jaratok;
  jaratok.emplace_back("Budapest","Berlin", 2000);

  cout << "Repjegyek összege 5000-es limittel:" << fullCost(jaratok, 5000) << endl;
  cout << "Repjegyek összege 1000-es limittel:" << fullCost(jaratok, 1000) << endl;

  jaratok.emplace_back("Budapest","Bagdad", 86000);
  jaratok.emplace_back("Berlin","Budapest", 32000);
  jaratok.emplace_back("Berlin","Bagdad", 200220);
  jaratok.emplace_back("Berlin","Budapest", 52000);
  jaratok.emplace_back("Budapest","Bagdad", 76000);
  jaratok.emplace_back("Budapest","Washington", 1900);

  cout << "Repjegyek összege 80000-es limittel:" << fullCost(jaratok, 80000) << endl;

}
// kimenet
//Repjegyek összege 5000-es limittel:2000
//Repjegyek összege 1000-es limittel:0
//Repjegyek összege 80000-es limittel:163900


void test_akcio() {
  cout << endl << " --- akcio ---" << endl << endl;

  vector<Jarat> jaratok;
  jaratok.emplace_back("Budapest","Berlin", 2000);
  jaratok.emplace_back("Budapest","Bagdad", 86000);
  jaratok.emplace_back("Berlin","Budapest", 32000);
  jaratok.emplace_back("Berlin","Bagdad", 200220);
  jaratok.emplace_back("Berlin","Budapest", 52000);
  jaratok.emplace_back("Budapest","Bagdad", 76000);
  jaratok.emplace_back("Budapest","Washington", 1900);

  vector<Jarat> results = akcio(jaratok, 20);
  for(const auto& j : results){
    cout << j << endl;
  }

}
// kimenet
//Budapest-Berlin (1600 forint)
//Budapest-Bagdad (68800 forint)
//Berlin-Budapest (25600 forint)
//Berlin-Bagdad (160176 forint)
//Berlin-Budapest (41600 forint)
//Budapest-Bagdad (60800 forint)
//Budapest-Washington (1520 forint)





int main() {
  test_jarat_set();
  test_min_ar();
  test_szamol();
  test_filter();
  test_fullsort();
  test_fullcost();
  test_akcio();
  return 0;
}
