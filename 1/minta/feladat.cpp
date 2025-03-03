#include <iostream>
#include <stdexcept>
#include <cassert>

using namespace std;

//=== Teszteles bekapcsolasa kikommentezessel
//
//=== Teszteles bekapcsolas vege


/////////////////////////
//Ide dolgozz!!
////////////////////////

int count_mM() {
  string input;
  cin >> input;
  unsigned mCounter = 0;
  unsigned MCounter = 0;
  for(size_t i = 0; i < input.length(); ++i) {
    if(input[i] == 'M') {
      MCounter++;
    }else if(input[i] == 'm') {
      mCounter++;
    }
  }
  return mCounter + MCounter;
}

string repeater() {
  int szam;
  string szoveg;
  cin >> szam >> szoveg;
  if(szam < 0) {
    return "hiba";
  } else if(szam == 0) {
    return "";
  }
  string visszateres = "";
  for(int i = 0; i < szam; ++i) {
    visszateres.append(szoveg);
  }
  return visszateres;
}

string multiplier(unsigned szam) {
  return to_string(szam * 3);
}

int strmin(string s1, string s2) {
  bool valid1 = true, valid2 = true;
  int integer1 = 0, integer2 = 0;

  try {
    integer1 = stoi(s1);
  } catch (const invalid_argument&) {
    valid1 = false;
  }

  try {
    integer2 = stoi(s2);
  } catch (const invalid_argument&) {
    valid2 = false;
  }

  if (valid1 && valid2) {
    return (integer1 < integer2) ? integer1 : integer2;
  } else if (valid1) {
    return integer1;
  } else if (valid2) {
    return integer2;
  } else {
    return -999;
  }
}



#ifndef TEST_BIRO

int main() {

  /*cout << "1-es feladat tesztelese" << endl;
  int m = count_mM();
  cout << "A beolvasott m és M karaketerk szama: " << m << endl;*/


  /*cout << "2-es feladat tesztelese" << endl;
  string reps = repeater();
  cout << reps << endl;*/

  /*cout << "3-as feladat tesztelese" << endl;
  string multi1 = multiplier(1);
  assert(multi1 == "3");*/

  /*cout << "4-es feladat tesztelese" << endl;
  int min = strmin("3", "4");
  assert(min == 3);
  min = strmin("Harry", "Potter");
  assert(min == -999);
  min = strmin("-3", "szappanos bukta");
  assert(min == -3);*/
  
  return 0;

}
#endif