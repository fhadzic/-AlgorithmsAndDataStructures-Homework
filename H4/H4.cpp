#include <iostream>
#include <utility>
#include <random>
#include <ctime>


using namespace std;


template < typename TipKljuc, typename TipVrijednost >
class Mapa{
    
public:

    Mapa(){}
    virtual ~Mapa() {}
    virtual int brojElemenata() const=0;
    virtual void obrisi() =0;
    virtual void obrisi(const TipKljuc& kljuc) =0;
    virtual TipVrijednost& operator [](const TipKljuc &k) =0;
    virtual const TipVrijednost operator [](const TipKljuc &k) const =0;
    
};



/*


template< typename TipKljuc, typename TipVrijednost >
class BinStabloCvor {
    
public:


    BinStabloCvor *lijevo, *desno, *roditelj;
    TipKljuc kljuc;
    TipVrijednost value = TipVrijednost();

    BinStabloCvor() { lijevo=desno=roditelj = nullptr; }
    
    BinStabloCvor(const TipKljuc& key, const TipVrijednost&  v, BinStabloCvor* r){
        kljuc = key;
        value = v;
        roditelj = r;
        lijevo = nullptr;
        desno = nullptr;
    }
    
};





template <typename TipKljuc, typename TipVrijednost>
class BinStabloMapa : public Mapa<TipKljuc, TipVrijednost> {
    
   BinStabloCvor<TipKljuc, TipVrijednost>* korijen;
   int broj_el=0;
   
   void obrisiStablo(BinStabloCvor<TipKljuc, TipVrijednost>* korijen);
   void kopirajStablo(BinStabloCvor<TipKljuc, TipVrijednost>*& k, BinStabloCvor<TipKljuc, TipVrijednost>* sKorijen , BinStabloCvor<TipKljuc, TipVrijednost>* r );
   
public:


    BinStabloMapa() : korijen(nullptr), broj_el(0) {
        
    }   
    
    
//Kopirajuci konstruktor

    BinStabloMapa(const BinStabloMapa& s){
        kopirajStablo(korijen, s.korijen, nullptr);
    }
    
    
//Kopirajuci operator dodjele

    BinStabloMapa &operator =(const BinStabloMapa &s){
        if(this != &s){
            obrisiStablo(korijen);
            korijen = nullptr;
            broj_el = 0;
            kopirajStablo(korijen, s.korijen, nullptr);
        }
        return *this;
    }
    
    
    
//Destruktor    
    
    ~BinStabloMapa() {
        
        obrisiStablo(korijen);
        
    }
    

// Broj elemenata
    
    int brojElemenata() const override {
        return broj_el;
    }
    
    
//Obrisi sve

    
    void obrisi(){
        obrisiStablo(korijen);
        korijen = nullptr;
        broj_el = 0;
    }
    
    
//Obrisi cvor sa kljucem k   
    
    void obrisi(const TipKljuc& k){
        
        BinStabloCvor<TipKljuc, TipVrijednost>* p(korijen),* pret(nullptr), * temp(nullptr), * pm(nullptr), *tmp(nullptr);
        
        while( p != nullptr && k != p->kljuc ){
            
            pret = p;
            
            if( k < p->kljuc ){
                p = p->lijevo;
            }else{
                p = p->desno;
            }
        }
        
        if(p == nullptr) return;
        
        if(p->lijevo == nullptr){
            temp = p->desno;
        }else{
            
            if(p->desno == nullptr){
                temp = p->lijevo;
            }else{
                
                pm = p;
                temp = p->lijevo;
                tmp = temp->desno;
                
                while (tmp != nullptr) {
                    pm = temp;
                    temp=tmp;
                    tmp = temp->desno;
                }
                
                if(pm != p){
                    pm->desno = temp->lijevo;
                    temp -> lijevo =  p->lijevo;
                }
                
                temp -> desno = p -> desno;
                
            }
            
        }
        
        
        if(pret == nullptr){
            korijen = temp;
        }else{
            if(p == pret -> lijevo){
                pret->lijevo = temp;
            }else{
                pret->desno = temp;
            }
        }
        
        delete p;
        broj_el--;
        
    }
    

//Operator []    
    
    TipVrijednost& operator [](const TipKljuc &k) override {
        
        if(korijen == nullptr){
            korijen = new BinStabloCvor< TipKljuc, TipVrijednost >();
            korijen -> kljuc = k;
            korijen -> lijevo = nullptr;
            korijen -> desno = nullptr;
            korijen -> roditelj = nullptr;
            broj_el++;
            
            return korijen -> value;
        }
        
        BinStabloCvor<TipKljuc, TipVrijednost>* poc(korijen),* pret(korijen);
        bool right;
        
        while( poc != nullptr ){
            
            pret = poc;
            
            if( k == poc -> kljuc ){
                return poc -> value;
            }else if(k < poc -> kljuc){
                poc = poc -> lijevo;
                right = false;
            }else{
                poc = poc -> desno;
                right = true;
            }
            
        }
        
        poc = new BinStabloCvor< TipKljuc, TipVrijednost >();
        poc -> kljuc = k;
        poc -> lijevo = nullptr;
        poc -> desno = nullptr;
        poc -> roditelj = pret;
        broj_el++;
        
        if(right){
            pret->desno = poc;
        }else{
            pret->lijevo = poc;
        }
        return poc -> value;
    }
    
    
 
//CONST Operator []

    const TipVrijednost operator [](const TipKljuc &k) const {
        
        BinStabloCvor<TipKljuc, TipVrijednost>* poc = korijen;
        while( poc != nullptr ){
            
            if( k == poc->kljuc){
                return poc->value;
            }else if(k < poc->kljuc){
                poc = poc->lijevo;
            }else{
                poc = poc->desno;
            }
        }
        
        return TipVrijednost();
    }

};


template< typename TipKljuc, typename TipVrijednost >
void BinStabloMapa<TipKljuc, TipVrijednost>::obrisiStablo(BinStabloCvor<TipKljuc, TipVrijednost>* cvor){
    
    if(cvor == nullptr) return;
    
    obrisiStablo(cvor->lijevo);
    obrisiStablo(cvor->desno);
    
    delete cvor;
}



template< typename TipKljuc, typename TipVrijednost >
void BinStabloMapa<TipKljuc, TipVrijednost>::kopirajStablo(BinStabloCvor<TipKljuc, TipVrijednost>*& cvor, BinStabloCvor<TipKljuc, TipVrijednost>* sCvor, 
                                                           BinStabloCvor<TipKljuc, TipVrijednost>* r){
    
    if(sCvor == nullptr){
        return;
    }
    
    cvor = new BinStabloCvor<TipKljuc, TipVrijednost>( sCvor->kljuc, sCvor->value, r );
    kopirajStablo(cvor->lijevo, sCvor->lijevo, cvor);
    kopirajStablo(cvor->desno, sCvor->desno, cvor);
    
    broj_el++;
}

*/



template< typename TipKljuc, typename TipVrijednost >
class Cvor {
    
public:


    Cvor *lijevo, *desno, *roditelj;
    TipKljuc kljuc;
    TipVrijednost value = TipVrijednost();
    int balans = 0;

    Cvor() { lijevo=desno=roditelj = nullptr; }
    
    Cvor(const TipKljuc& key, const TipVrijednost&  v, Cvor* r){
        kljuc = key;
        value = v;
        roditelj = r;
        lijevo = nullptr;
        desno = nullptr;
    }
    
};








template <typename TipKljuc, typename TipVrijednost>
class AVLStabloMapa : public Mapa<TipKljuc, TipVrijednost> {
    
   Cvor<TipKljuc, TipVrijednost>* korijen;
   int broj_el=0;
   
   void obrisiStablo(Cvor<TipKljuc, TipVrijednost>* korijen);
   void kopirajStablo(Cvor<TipKljuc, TipVrijednost>*& k, Cvor<TipKljuc, TipVrijednost>* sKorijen , Cvor<TipKljuc, TipVrijednost>* r );
   void azurirajBalans(Cvor<TipKljuc, TipVrijednost>* novi);
   void lijevaRotacija(Cvor<TipKljuc, TipVrijednost>* cvor);
   void desnaRotacija(Cvor<TipKljuc, TipVrijednost>* cvor);
   
public:


    AVLStabloMapa() : korijen(nullptr), broj_el(0) {
        
    }   
    
    
//Kopirajuci konstruktor

    AVLStabloMapa(const AVLStabloMapa& s){
        kopirajStablo(korijen, s.korijen, nullptr);
    }
    
    
//Kopirajuci operator dodjele

    AVLStabloMapa &operator =(const AVLStabloMapa &s){
        if(this != &s){
            obrisiStablo(korijen);
            korijen = nullptr;
            broj_el = 0;
            kopirajStablo(korijen, s.korijen, nullptr);
        }
        return *this;
    }
    
    
    
//Destruktor    
    
    ~AVLStabloMapa() {
        
        obrisiStablo(korijen);
        
    }
    

// Broj elemenata
    
    int brojElemenata() const override {
        return broj_el;
    }
    
    
//Obrisi sve

    
    void obrisi(){
        obrisiStablo(korijen);
        korijen = nullptr;
        broj_el = 0;
    }
    
    
//Obrisi cvor sa kljucem k   
    
    void obrisi(const TipKljuc& k){
        
        Cvor<TipKljuc, TipVrijednost>* p(korijen),* pret(nullptr), * temp(nullptr), * pm(nullptr), *tmp(nullptr);
        
        while( p != nullptr && k != p->kljuc ){
            
            pret = p;
            
            if( k < p->kljuc ){
                p = p->lijevo;
            }else{
                p = p->desno;
            }
        }
        
        if(p == nullptr) return;
        
        if(p->lijevo == nullptr){
            temp = p->desno;
        }else{
            
            if(p->desno == nullptr){
                temp = p->lijevo;
            }else{
                
                pm = p;
                temp = p->lijevo;
                tmp = temp->desno;
                
                while (tmp != nullptr) {
                    pm = temp;
                    temp=tmp;
                    tmp = temp->desno;
                }
                
                if(pm != p){
                    pm->desno = temp->lijevo;
                    temp -> lijevo =  p->lijevo;
                }
                
                temp -> desno = p -> desno;
                
            }
            
        }
        
        
        if(pret == nullptr){
            korijen = temp;
        }else{
            if(p == pret -> lijevo){
                pret->balans--;
                pret->lijevo = temp;
            }else{
                pret->balans++;
                pret->desno = temp;
            }
        }
        
        delete p;
        broj_el--;
        
    }
    

//Operator []    
    
    TipVrijednost& operator [](const TipKljuc &k) override {
        
        if(korijen == nullptr){
            korijen = new Cvor< TipKljuc, TipVrijednost >();
            korijen -> kljuc = k;
            korijen -> lijevo = nullptr;
            korijen -> desno = nullptr;
            korijen -> roditelj = nullptr;
            korijen -> balans = 0;
            broj_el++;
            
            return korijen -> value;
        }
        
        Cvor<TipKljuc, TipVrijednost>* p(korijen),* pret(korijen);
        bool right;
        
        while( p != nullptr ){
            
            pret = p;
            
            if( k == p -> kljuc ){
                return p -> value;
            }else if(k < p -> kljuc){
                p = p -> lijevo;
                right = false;
            }else{
                p = p -> desno;
                right = true;
            }
            
        }
        
        p = new Cvor< TipKljuc, TipVrijednost >();
        p -> kljuc = k;
        p -> lijevo = nullptr;
        p -> desno = nullptr;
        p -> roditelj = pret;
        p -> balans = 0;
        broj_el++;
        
        if(right){
            pret->desno = p;
            
            if(pret->lijevo != nullptr){
                pret->balans = 0;
            }else{
                azurirajBalans(p);
            }
        }else{
            pret->lijevo = p;
            
            if(pret->desno != nullptr){
                pret->balans = 0;
            }else{
                azurirajBalans(p);
            }
        }
        
        return p -> value;
    }
    
    
 
//CONST Operator []

    const TipVrijednost operator [](const TipKljuc &k) const {
        
        Cvor<TipKljuc, TipVrijednost>* poc = korijen;
        while( poc != nullptr ){
            
            if( k == poc->kljuc){
                return poc->value;
            }else if(k < poc->kljuc){
                poc = poc->lijevo;
            }else{
                poc = poc->desno;
            }
        }
        
        return TipVrijednost();
    }

};






//Obrisi stablo

template< typename TipKljuc, typename TipVrijednost >
void AVLStabloMapa<TipKljuc, TipVrijednost>::obrisiStablo(Cvor<TipKljuc, TipVrijednost>* cvor){
    
    if(cvor == nullptr) return;
    
    obrisiStablo(cvor->lijevo);
    obrisiStablo(cvor->desno);
    
    delete cvor;
}





//Kopiraj stablo

template< typename TipKljuc, typename TipVrijednost >
void AVLStabloMapa<TipKljuc, TipVrijednost>::kopirajStablo(Cvor<TipKljuc, TipVrijednost>*& cvor, Cvor<TipKljuc, TipVrijednost>* sCvor, 
                                                           Cvor<TipKljuc, TipVrijednost>* r){
    
    if(sCvor == nullptr){
        return;
    }
    
    cvor = new Cvor<TipKljuc, TipVrijednost>( sCvor->kljuc, sCvor->value, r );
    kopirajStablo(cvor->lijevo, sCvor->lijevo, cvor);
    kopirajStablo(cvor->desno, sCvor->desno, cvor);
    
    broj_el++;
}






//Azuriranje balansa


template< typename TipKljuc, typename TipVrijednost >
void AVLStabloMapa<TipKljuc, TipVrijednost>::azurirajBalans(Cvor<TipKljuc, TipVrijednost>* novi){
    
    if(novi->roditelj == nullptr) return;
    
    Cvor<TipKljuc, TipVrijednost>* p = novi->roditelj;
    
    if(p->lijevo == novi) p->balans++;
    else p->balans--;
    
    if(p->balans > 1) desnaRotacija(p);
    else if(p->balans < -1) lijevaRotacija(p);
    
 //   azurirajBalans(p);
}





//Desna rotacija

template< typename TipKljuc, typename TipVrijednost >
void AVLStabloMapa<TipKljuc, TipVrijednost>::desnaRotacija(Cvor<TipKljuc, TipVrijednost>* cvor){
    if(cvor->balans * cvor->lijevo->balans < 0) lijevaRotacija(cvor->lijevo);
    
    Cvor<TipKljuc, TipVrijednost>* p = cvor->lijevo;
    p->roditelj = cvor->roditelj;
    cvor->lijevo = nullptr;
    p->desno = cvor;
    cvor->roditelj = p;
    p->balans = 0;
    cvor->balans = 0;
}






//Lijeva rotacija

template< typename TipKljuc, typename TipVrijednost >
void AVLStabloMapa<TipKljuc, TipVrijednost>::lijevaRotacija(Cvor<TipKljuc, TipVrijednost>* cvor){
    if(cvor->balans * cvor->desno->balans < 0) desnaRotacija(cvor->desno);
    
    Cvor<TipKljuc, TipVrijednost>* p = cvor->desno;
    p->roditelj = cvor->roditelj;
    cvor->desno = nullptr;
    p->lijevo = cvor;
    cvor->roditelj = p;
    p->balans = 0;
    cvor->balans = 0;
    
}










int main() {
      
    AVLStabloMapa<std::string, std::string> m;
    m["Sarajevo"]="BIH";
    m["Zagreb"]="HRV";
    cout<<"dodana su 2 elementa:"<<endl;
    
    if(m.brojElemenata()==2)//2 elementa
    cout<<"U stablu su 2 elementa.Tacno: Da"<<endl;
    else 
    cout<<"U stablu su 2 elementa.Tacno: NE"<<endl;
    
    m.obrisi("Sarajevo");
    cout <<"izbacen 1 element\n";
    
    if(m.brojElemenata()==1)//1 elementa
    cout << "U stablu je 1 element.Tacno: Da"<<endl;
    else 
    cout << "U stablu je 1 element.Tacno: NE"<<endl;
    
    cout << "ispisi sa [operatorom]\nZa grad Zagreb : " << m["Zagreb"];
    
    return 0;
}
