#include <iostream>
#include <stdexcept>




template <typename Tip>
class Lista {

public:
    Lista() {}
    virtual ~Lista() {}
    virtual int brojElemenata() const=0;
    virtual const Tip &trenutni() const =0;
    virtual bool prethodni()=0;
    virtual bool sljedeci() =0;
    virtual void pocetak() =0;
    virtual void kraj() =0;
    virtual void obrisi() =0;
    virtual void dodajIspred(const Tip& el) =0;
    virtual void dodajIza(const Tip& el) =0;
    virtual const Tip &operator [](int i) const =0;

};


template< typename Tip >
class NizLista : public Lista<Tip> {
    
    int kapacitet;
    int broj_el;
    int t_index;
    Tip **niz;
    
public:

//KONSTRUKTOR
    NizLista(): kapacitet(1000) , broj_el(0), t_index(-1){
        niz = new Tip* [kapacitet];
    }

//KOPIRAJUCI KONSTRUKTOR
    NizLista(const NizLista &l) {
        niz = new Tip* [l.kapacitet]; 
        kapacitet = l.kapacitet; 
        broj_el = l.broj_el;
        t_index = l.t_index;
         
        for(int i=0; i < l.broj_el; i++){
            niz[i] = new Tip( *l.niz[i] );
        }
    }

//POMIJERAJUCI KONSTRUKTOR
    NizLista(NizLista &&l) : niz(l.niz), kapacitet(l.kapacitet), broj_el(l.broj_el), t_index(l.t_index){
        
        l.niz = nullptr; l.broj_el = 0; l.t_index = -1;
    }

//KOPIRAJUCI OPERATOR DODJELE
    NizLista &operator =(const NizLista &l){
        if(kapacitet != l.kapacitet){
            if( kapacitet < l.kapacitet ){
                Tip** temp;
                temp = new Tip* [l.kapacitet];
                for(int i=0; i<broj_el; i++){
                    temp[i] = niz[i];
                }
                delete[] niz;
                niz = temp;
            }
        }
        
        if(l.broj_el > broj_el){
                
            for(int i=0; i<broj_el; i++){
                *niz[i] = *l.niz[i];
            }
            for(int i=broj_el; i<l.broj_el; i++){
                niz[i] = new Tip(*l.niz[i]);
            }
                
        }else{
            
            for(int i=0; i<l.broj_el; i++){
                *niz[i] = *l.niz[i];
            }
            for(int i = broj_el; i < l.broj_el ; i++) {
                delete niz[i];
            }
        }
        t_index = l.t_index;
        broj_el = l.broj_el;
        
        return *this;
    }
        
//POMIJERAJUCI OPERATOR DODJELE
    NizLista &operator =(NizLista &&l){
        if(&l != this){
            for(int i=0; i<broj_el; i++) delete niz[i];
            delete[] niz;
            broj_el = l.broj_el; niz = l.niz; t_index = l.t_index;
            l.niz = nullptr; l.broj_el = 0; t_index = -1;
        }
        return *this;
    }

//DESTRUKTOR
    ~NizLista() {
        for(int i=0; i<broj_el; i++){
            delete niz[i];
        }
        
        delete[] niz;
    }
    
//BEOJ ELEMENATA

    int brojElemenata() const override { return broj_el; }
   
//TRENUTNI 
    Tip &trenutni() {
        if(broj_el == 0 || t_index == -1) throw std::domain_error("Prazna lista!");
    
        return *(niz[t_index]);
    }
    
//CONST TRENUTNI 
    const Tip &trenutni() const override {
        if(broj_el == 0 || t_index == -1) throw std::domain_error("Prazna lista!");
    
        return *(niz[t_index]);
    }

//PRETHODNI   
    bool prethodni() override {
        if(broj_el == 0) throw std::domain_error("Prazna lista!");
        if(t_index == 0){
            return false;
        }
        t_index--;
        return true;
    }

//SLJEDECI   
    bool sljedeci() override {
        
        if(broj_el == 0) throw std::domain_error("Prazna lista!");
        if(t_index == broj_el-1){
            return false;
        }
        t_index++;
        return true;
    }

//POCETAK
    void pocetak() override {
        if(broj_el == 0) throw std::domain_error("Prazna lista!");
        t_index = 0;
    }
    
//KRAJ
   void kraj() override {
        if(broj_el == 0) throw std::domain_error("Prazna lista!");
        t_index = broj_el - 1;
    }
    
//OBRISI   
    void obrisi() override {
        if(broj_el == 0 || t_index == -1) throw std::domain_error("Prazna lista!");
        
        if( t_index == broj_el-1 ){
            t_index--;
            delete niz[broj_el-1];
        }else{
            delete niz[t_index];
            for(int i=t_index+1; i<broj_el; i++){
                niz[i-1]=niz[i];
            }
        }
        broj_el--;
    }
    
//FUNKCIJA ZA PROVJERU KAPACITETA
    void funkcijaZaProvjeruKapaciteta(){
            
        if(broj_el == kapacitet){
            kapacitet *= 100;
            Tip **temp;
            temp = new Tip*[kapacitet];
            
            for(int i=0; i<broj_el; i++){
                temp[i] = niz[i];
            }
            delete[] niz;
            niz = temp;
        }   
    }
    
    
//DODAJ ISPRED 
    void dodajIspred(const Tip& el) override {
        funkcijaZaProvjeruKapaciteta();
        
        if(broj_el == 0){
            niz[0] = new Tip(el);
        }else{
            for(int i=broj_el; i>t_index; i--){
                niz[i]=niz[i-1];
            }
            niz[t_index] = new Tip(el);
        }
        t_index++;
        broj_el++;
    }
    
//DODAJ IZA
    void dodajIza(const Tip& el) override {
        funkcijaZaProvjeruKapaciteta();
        
        if(broj_el == 0){
            niz[broj_el] = new Tip(el);
            t_index++;
            
        }else{
            for(int i = broj_el ; i>t_index+1; i--){
                niz[i] = niz[i-1];
            }
            niz[t_index+1] = new Tip(el);
        }
        broj_el++;
        
    }
    
//OPERATOR []
    Tip &operator [](int i) {
        if(i<0 || i>=broj_el ) throw std::domain_error("Pogresan argument!");
        return *niz[i];
    }
    
//CONST OPERATOR []
    const Tip &operator [](int i) const override {
        if(i<0 || i>=broj_el ) throw std::domain_error("Pogresan argument!");
        return *niz[i];
    }
   
};



template< typename Tip >
class Stek{
    
    NizLista<Tip> stek;
    
    public:
    Stek(){}
    
    Stek(const Stek &s) : stek(s.stek) {}
    
    Stek &operator =(const Stek &s){
        if( this != &s)
            stek = s.stek;
        
        return *this;
    }
    
    void brisi(){
        int n(stek.brojElemenata());
    
        for(int i=0; i<n; i++){
            stek.obrisi();
        }
    }
    
    void stavi(const Tip &el){
        stek.dodajIza(el);
        stek.kraj();
    }
    
    Tip skini(){
        if( !stek.brojElemenata() ) throw std::domain_error("Prazna stek!");
        
        Tip obrisani = stek.trenutni();
        stek.obrisi();
        
        return obrisani;
    }
    
    Tip &vrh(){
        if( !stek.brojElemenata() ) throw std::domain_error("Prazna stek!");
        
        return stek.trenutni();    
    }
    
    int brojElemenata(){
        return (stek.brojElemenata());
    }
    
};








template< typename Tip >
class Red{
    struct Cvor{
        Tip element;
        Cvor* sljedeci;
        Cvor() : sljedeci(nullptr){}
        Cvor(const Tip &el, Cvor *sljedeci) : element(el), sljedeci(sljedeci) {} 
    };
    
    int br_elemenata;
    Cvor* pocetak;
    Cvor* kraj;
    
    public: 
    
    Red(): br_elemenata(0), pocetak(nullptr), kraj(nullptr) {}
    
    Red(const Red &r){
        br_elemenata = r.br_elemenata;
        Cvor* p = r.pocetak;
        Cvor* q;
        
        while (p != nullptr) {
            q = new Cvor();
            
            if(p == r.pocetak){
                pocetak = q;
                kraj = q;
            }else{
                
                kraj->sljedeci = q;
                kraj = kraj->sljedeci;
                
            }
            
            q->element = p->element;
            kraj->sljedeci = nullptr;
            p = p->sljedeci;
        }
    }
    
    Red &operator =(const Red &r){
        
        if(&r != this){
            
            if(br_elemenata == r.br_elemenata){
                Cvor* p = r.pocetak;
                Cvor* q = pocetak;
                while (p != nullptr) {
                    
                    q->element = p->element;
                    
                    q = q->sljedeci;
                    p = p->sljedeci;
                }
                
            }else if(br_elemenata < r.br_elemenata){
                
                Cvor *p = r.pocetak;
                Cvor *q = pocetak;
                
                while (q != nullptr) {
                    
                    if(p == r.pocetak){
                        pocetak = q;
                        kraj = q;
                    }else{
                        kraj->sljedeci = q;
                        kraj = kraj->sljedeci;
                    }
                    
                    q->element = p->element;
                    kraj->sljedeci = nullptr;
                    p = p->sljedeci;
                    q = q->sljedeci;
                }
                
                
                while (p != nullptr) {
                    
                    q = new Cvor();
                    
                    if(p == r.pocetak){
                        pocetak = q;
                        kraj = q;
                    }else{
                        kraj->sljedeci = q;
                        kraj = kraj->sljedeci;
                    }
                    
                    q->element = p->element;
                    kraj->sljedeci = nullptr;
                    p = p->sljedeci;
                }
            }else{
                
            }
            
        }
        br_elemenata = r.br_elemenata;
        return *this;
    }
    
    ~Red(){
        while(pocetak != nullptr){
            kraj = pocetak;
            pocetak = pocetak->sljedeci;
            delete kraj;
        }
    }
    
    void brisi(){
        while(pocetak != nullptr){
            kraj = pocetak;
            pocetak = pocetak->sljedeci;
            delete kraj;
        }
        pocetak = nullptr;
        kraj = nullptr;
        br_elemenata = 0;
    }
    
    void stavi(const Tip& el){
        if(!pocetak){
            pocetak = new Cvor();
            pocetak->element = el;
            kraj = pocetak;
            kraj->sljedeci = nullptr;
        }else{
            kraj->sljedeci = new Cvor();
            kraj = kraj->sljedeci;
            kraj->element = el;
            kraj->sljedeci = nullptr;
        }
        br_elemenata++;
    }
    
    Tip skini(){
        if( br_elemenata == 0 ) throw std::domain_error("Red prazan!");
        
        Tip el = pocetak->element;
        Cvor* brisi;
        brisi = pocetak;
        pocetak = pocetak->sljedeci;
        delete brisi;
        br_elemenata--;
        
        return el;
    }
    
    Tip &celo(){
        if( br_elemenata == 0 ) throw std::domain_error("Red prazan!");
        
        return pocetak->element;
    }
    
    int brojElemenata(){
        return br_elemenata;
    }
    
};











template<typename Tip>
class DvostraniRed{
private:    
     struct Cvor {
         Tip element;
         Cvor *sljedeci;
         Cvor *prethodni;
         Cvor(const Tip &el, Cvor *sljedeci, Cvor *prethodni) :
                element(el), sljedeci(sljedeci), prethodni(prethodni){}
         
     };
     
     Cvor *pocetak;
     Cvor *kraj;
     int br_elemenata;
     void Unisti();
     void Kopiraj(const DvostraniRed &r);
     
     
public:

    DvostraniRed():  pocetak(nullptr), kraj(nullptr), br_elemenata(0) {}
    
    
    DvostraniRed(const DvostraniRed &r) : pocetak(nullptr), kraj(nullptr), br_elemenata(0) {
        Kopiraj(r);
    }
    
    DvostraniRed &operator =(const DvostraniRed &r){
        
        if(&r != this){
            Unisti();
            Kopiraj(r);
            
        }
        
        return *this;
        
    }
    
    ~DvostraniRed(){
        Unisti();
    }
    
    void brisi(){
        Unisti();
    }

    void staviNaVrh(const Tip& el){
        Cvor *p (new Cvor(el,nullptr,nullptr));
        if(br_elemenata == 0){
            pocetak = kraj = p;
        }else{
            kraj -> sljedeci = p;
            p -> prethodni = kraj;
            kraj = kraj->sljedeci;
        }
        br_elemenata++;
    }

    Tip skiniSaVrha(){
        if( br_elemenata == 0 ) throw std::domain_error("Red prazan!");
        
        Tip el = kraj->element;
        Cvor* brisi = kraj;
        
        if(pocetak == kraj){
            pocetak = kraj = nullptr;
        }else{
            kraj = kraj ->prethodni;
            kraj ->sljedeci = nullptr;
        }

        delete brisi;
        br_elemenata--;
        
        return el;
    }
    
    void staviNaCelo(const Tip &el){
        
        Cvor * p = new Cvor(el, nullptr, nullptr);
        
        if( br_elemenata == 0 )
             pocetak = kraj = p;
        else{
            pocetak -> prethodni = p;
            p -> sljedeci = pocetak;
            pocetak = p;
        }
        br_elemenata++;
    }
  
    
    Tip skiniSaCela(){
        if( br_elemenata == 0 ) throw std::domain_error("Red prazan!");
        
        Tip el = pocetak->element;
        Cvor* brisi = pocetak;
        if(pocetak == kraj){
            pocetak = kraj = nullptr;
        }else{
            pocetak = pocetak -> sljedeci;
            pocetak -> prethodni = nullptr;
        }

        delete brisi;
        br_elemenata--;
        
        return el;
    }
    
    
      
    int brojElemenata(){
        return br_elemenata;
    }
    
    Tip &vrh(){
        if( br_elemenata == 0 ) throw std::domain_error("Red prazan!");
        
        return kraj->element;
    }
    
    Tip &celo(){
        if( br_elemenata == 0 ) throw std::domain_error("Red prazan!");
        
        return pocetak->element;
    }
    
    
};



template <typename Tip>
void DvostraniRed<Tip>::Kopiraj(const DvostraniRed &r){
    Cvor* p = r.pocetak;
        
    while (p != nullptr) {
            
        staviNaVrh(p -> element);
        p = p->sljedeci;
    }
}




template <typename Tip>
void DvostraniRed<Tip>::Unisti(){
    
    while (br_elemenata != 0) {
        skiniSaVrha();
    }
    
}

// Prva testna f-ja testira metode: staviNaVrh, brojElelmenata, vrh, skiniSaVrha; 

bool testnaFunkcija1(){
    DvostraniRed<int> red;
    for(int i=0; i<3; i++){
        red.staviNaVrh(i+2);
    }
    int n(red.vrh());
    if( n != 4 && red.brojElemenata() != 3) return false;
    
    red.staviNaVrh(10);
    
    int obrisani(red.skiniSaVrha());
    if( obrisani != 10 && red.brojElemenata() != 3) return false;
    
    return true;
}


// Druga testna f-ja testira konstruktor, kopirajuci konstruktor, destruktivnu samododjelu i kopirajuci operator dodjele. Te metodu obrisi i staviNaCelo.

bool testnaFunkcija2(){
    DvostraniRed<int> red;
    for(int i=0; i<5; i++){
        red.staviNaCelo(i+5);
    }
    
    DvostraniRed<int> r1(red);
    DvostraniRed<int> r2;
    
    if(r1.brojElemenata() != red.brojElemenata()) return false;
    
    r1.brisi();
    
    if(r1.brojElemenata() == red.brojElemenata() || r1.brojElemenata() != 0) return false;
    
    r2 = red;
    
    if(r2.brojElemenata() != red.brojElemenata()) return false;
    
    r2.brisi();
    
    if(r2.brojElemenata() == red.brojElemenata() || r2.brojElemenata() != 0) return false;
    
    red = red; 
    
    if(red.brojElemenata() != 5) return false;
    
    red.brisi();
    
    if(red.brojElemenata() != 0) return false;
   
    return true;
}

// Druga testna f-ja testira da li je klasa DvostraniRed generička; 

bool testnaFunkcija3(){
    DvostraniRed<float> red;
    for(int i=0; i<3; i++){
        red.staviNaVrh(i+2.15);
    }
    int n(red.vrh());
    if( abs(n - 4.15) < 0.000001 && red.brojElemenata() != 3) return false;
    
    red.staviNaVrh(10.0675);
    
    int obrisani(red.skiniSaVrha());
    
    if( abs(obrisani - 10.0675) < 0.000001 && red.brojElemenata() != 3) return false;

    DvostraniRed<char> r1; 
    for(int i=0; i<3; i++){
        r1.staviNaVrh('A'+1);
    }
    
    char v( r1.vrh() );
    if( v != 'D' && r1.brojElemenata() != 3) return false;
   
    r1.staviNaVrh('Z');
    
    int bivsi(r1.skiniSaVrha());
    if( bivsi != 'Z' && r1.brojElemenata() != 3) return false;
   
    return true;
}




int main() {
    
    if( testnaFunkcija1() ){
       std::cout << "Test 1 je ispravan!" << std::endl;
   }else{
       std::cout << "Test 1 Nije ispravan!" << std::endl;
   }
   
   if(testnaFunkcija2()){
       std::cout << "Test 2 je ispravan!" << std::endl;
   }else{
       std::cout << "Test 2 Nije ispravan!" << std::endl;
   }
   
   if(testnaFunkcija3()){
       std::cout << "Test 3 je ispravan!" << std::endl;
   }else{
       std::cout << "Test 3 Nije ispravan!" << std::endl;
   }
    
    
    return 0;
}
