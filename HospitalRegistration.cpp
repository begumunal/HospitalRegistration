// HospitalRegistration.cpp : Bu dosya 'main' işlevi içeriyor. Program yürütme orada başlayıp biter.
//

#include <iostream>
#include <queue>
#include <list>
using namespace std;

int main()
{
    Insan insanlar[] = {
        Insan ("Arif", 30),
        Insan ("Ahmet", 35, 1),
        Insan ("mehmet", 70),
        Insan ("veli", 75, 1),
        Insan ("ayşe", 65,1),
        Insan ("ferdi", 45)
    };
    
    HastaKayit banko;
    banko.kayit(insanlar[0]);
    banko.kayit(insanlar[3]);
    banko.kayit(insanlar[1]);
    banko.kayit(insanlar[2]);
    banko.kayit(insanlar[5]);
    banko.kayit(insanlar[4]);
    banko.kayitSirasiYazdir();
    
    banko.muayeneSirasiYazdir();
    banko.hastaCagir();
    banko.hastaCagir();
    banko.hastaCagir();
    banko.hastaCagir();
    banko.hastaCagir();
    banko.hastaCagir();
    banko.hastaCagir();
}

class Insan
{
protected:
    string ad;
    int yas;
    bool engelliMi;

public:
    Insan(string ad,int yas,bool engelliMi=false):ad(ad),yas(yas),engelliMi(engelliMi){}
    void yazdir()const {
        cout << "Ad: " << ad << endl
            << "Yaş: " << yas << endl
            << "Engellilik durumu: ";
        if (engelliMi)
            cout << "Evet";
        else
            cout << "Hayır"<<endl;
    }
};

class Hasta :public Insan {
    int hastaNo, oncelikPuani;
public:
    Hasta(int hastaNo,Insan& i):hastaNo(hastaNo),Insan(i),oncelikPuani(0){}
    Hasta(int hastaNo, string ad, int yas, bool engelliMi=false ) :hastaNo(hastaNo), Insan(ad, yas, engelliMi),oncelikPuani(0) {
        oncelikPuaniHesapla();
    }

    void oncelikPuaniHesapla() {
        if (engelliMi)
            oncelikPuani += 30;
        if (yas > 65)
            oncelikPuani += yas - 65;
    }

    bool operator <(const Hasta& h)const {
        return oncelikPuani < h.oncelikPuani;
    }

    void yazdir()const {
        cout << "Hasta no: " << hastaNo << endl;
        Insan::yazdir();
        cout << "Öncelik puani: " << oncelikPuani << endl;
    }
};

class HastaKayit {
    list<Hasta> kayiySirası;
    priority_queue<Hasta> muayeneSirasi;
public:void kayit(Insan& i) {
    Hasta hasta(kayiySirası.size() + 1, i);
    kayiySirası.push_back(hasta);
    muayeneSirasi.push(hasta);
}
      void kayitSirasiYazdir() {
          if (kayiySirası.empty())
              cout << "kayitli hasta yok" << endl;
          else {
              list<Hasta>::iterator iter = kayiySirası.begin();
              while (iter != kayiySirası.end()) {
                  Hasta hasta = *iter;
                  hasta.yazdir();
                  iter++;
                  if(iter!=kayiySirası.end())
                     cout << endl;
              }
              cout << endl;
          }

      }

      void muayeneSirasiYazdir() {
          if (muayeneSirasi.empty())
              cout << "kayitli hasta yok" << endl;
          else {
              
              priority_queue<Hasta> kuyruk = muayeneSirasi;
              while (!kuyruk.empty()) {
                  Hasta hasta = kuyruk.top();
                  hasta.yazdir();
                  kuyruk.pop();
                  if (!kuyruk.empty())
                      cout << endl;
              }
              
          }

      }

      void hastaCagir() {
          cout << "muayeneye çagirilen hasta bilgileri";
          if (muayeneSirasi.empty())
              cout << "muayene için bekleyen hasta yok" << endl;
          else {
               Hasta hasta = muayeneSirasi.top();
               hasta.yazdir();
               muayeneSirasi.pop();
          }
         
      }
};
