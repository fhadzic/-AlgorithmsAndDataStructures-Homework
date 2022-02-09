#include <iostream>
#include <stdexcept>


template <typename Tip>
class Iterator; // Predefinisana klasa iterator

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
class DvostrukaLista : public Lista<Tip> {
 
    struct Cvor {
        Tip element;
        Cvor *prethodni;
        Cvor *sljedeci;
        Cvor (): prethodni(nullptr), sljedeci(nullptr){}
        Cvor (const Tip &el, Cvor *prethodni, Cvor *sljedeci) : element(el), sljedeci(sljedeci) {}
    };
    
    int broj_el=0;
    Cvor* poc;
    Cvor* tren;
    Cvor* krajListe;
    
public:

//KONSTRUKTOR
    DvostrukaLista(): broj_el(0), poc(nullptr), tren(nullptr), krajListe(nullptr){}
    
//KOPIRAJUCI KONSTRUKTOR
    DvostrukaLista(const DvostrukaLista &l) : broj_el(l.broj_el) {
    
        Cvor* p = l.poc;
        Cvor* q;
        Cvor* prosli;
        bool nijePrvi(false);
        
        while(p != nullptr){
        
            q = new Cvor;
            
            if(nijePrvi){
                q -> prethodni = prosli;
                prosli -> sljedeci = q;
            }else{
                poc = q;
                q->prethodni = nullptr;

                nijePrvi = true;
            }
            
            if(p == l.tren){
                tren = q;
            }
            if(p == l.krajListe){
                krajListe = q;
            }
            
            q->element = p->element;
            q->sljedeci = nullptr;
            prosli = q;
            
            p = p->sljedeci;
        }
        
    }
//POMJERAJUCI KONSTRUKTOR

//KOPIRAJUCI OPERATOR DODJELE
    DvostrukaLista &operator =(const DvostrukaLista &l) {
        
        Cvor* pl = l.poc;
        Cvor* pn = poc;
        Cvor* prosli;
        
        if(&l != this){

            if(broj_el == l.broj_el){
            
                while ( pl != nullptr ){
                    if( l.tren == pl ){
                        tren = pn;
                    }
                    pn->element = pl->element;
                    pl = pl->sljedeci;
                    pn = pn->sljedeci;
                }
            
            }else if (broj_el < l.broj_el){
            
            
                prosli = pn;
                while ( pn != nullptr) {
                
                    if( l.poc == pl ){
                        pn->prethodni = nullptr;
                    }
                
                    if( l.tren == pl ){
                        tren = pn;
                    }
                
                    pn->element = pl->element;
                    pl = pl->sljedeci;
                    prosli = pn;
                    pn = pn->sljedeci;
                }
                
                while ( pl != nullptr) {
                
                    pn = new Cvor;
                
                    if(l.poc == pl){
                        poc = pn;
                        pn->prethodni = nullptr;
                    }else{
                        prosli->sljedeci = pn;
                        pn -> prethodni = prosli;
                    }
                
                    if( l.tren == pl ){
                        tren = pn;
                    }
                
                    if( l.krajListe == pl ){
                        krajListe = pn;
                    }
                
                    pn->sljedeci = nullptr;
                    pn->element = pl->element;
                    pl = pl->sljedeci;
                    prosli = pn;
                }
            
            }else{
                while ( pl != nullptr) {
                
                    if( l.tren == pl ){
                        tren = pn;
                    }
                
                    if( l.krajListe == pl ){
                        krajListe = pn;
                    }
                
                    pn->element = pl->element;
                    pl = pl->sljedeci;;
                    pn = pn->sljedeci;
                }
            
                krajListe->sljedeci = nullptr;
                prosli = pn;
                while(pn != nullptr){
                    pn = pn->sljedeci;
                    delete prosli;
                    prosli = pn;
                }
            
                krajListe -> sljedeci = nullptr;
            
            }
            broj_el = l.broj_el;
            
        }
        
        return *this;
    }

//POMJERAJUCI OPERATOR DODJELE

//DESTRUKTOR
    ~DvostrukaLista(){
        
        Cvor* p = poc;
        while(p != nullptr){
            Cvor* q = p;
            p = p -> sljedeci;
            delete q;
        }
        
    }

//BROJ ELEMENEATA  
    int brojElemenata() const override {
        return broj_el;
    }
    
    
//TRENUTNI    
    Tip &trenutni() {
        if(!poc) throw std::domain_error("Prazna lista!");
        
        return (tren->element);
    }
    
//CONST TRENUTNI
    const Tip &trenutni() const override {
        if(!poc) throw std::domain_error("Prazna lista!");
        
        return (tren->element);
    }
    
//PRETHODNI
    bool prethodni() override {
        if(!poc) throw std::domain_error("Prazna lista!");
        
        if(poc == tren){
            return false;
        }
        
        tren = tren->prethodni;
        
        return true;
    }
    
//SLJEDECI
    bool sljedeci() override {
        if(!poc) throw std::domain_error("Prazna lista!");
        
        if(tren->sljedeci == nullptr){
            return false;
        }
        
        tren = tren->sljedeci;
        
        return true;
    }
   
//POCETAK
    void pocetak() override {
        if(!poc) throw std::domain_error("Prazna lista!");
        tren = poc;
        
    }
//KRAJ
   void kraj() override {
       if(!poc) throw std::domain_error("Prazna lista!");
       
       tren = krajListe;
   }

//OBRISI
    void obrisi() override {
        if(!poc) throw std::domain_error("Prazna lista!");
        
        if( poc->sljedeci == nullptr ){
            tren = nullptr;
            krajListe = nullptr;
            
            delete poc;
            poc = nullptr;
        }else if( poc == krajListe){
            
            delete poc;
            poc = nullptr;
            tren = nullptr;
            krajListe = nullptr;
            
        } else if(poc == tren && poc->sljedeci != nullptr){
            
            tren = poc->sljedeci;
            delete poc;
            poc = tren;
            poc->prethodni = nullptr;
            
        } else if(tren == krajListe){
            
                tren = krajListe->prethodni;
                delete krajListe;
                krajListe = tren;
                krajListe->sljedeci = nullptr;
            
            
        }else{
            Cvor* bivsi_tren;
            bivsi_tren = tren;
            tren = tren->sljedeci;
            (bivsi_tren->prethodni)->sljedeci = tren;
            tren->prethodni = bivsi_tren->prethodni;
            delete bivsi_tren;
            
        }
        broj_el--;
    }
  
//DODAJ ISPRED
    void dodajIspred(const Tip& el) override {
        
        if( !poc ){
            poc = new Cvor;
            
            poc->element = el;
            poc->prethodni = nullptr;
            poc->sljedeci = nullptr;
            
            tren = poc;
            krajListe = poc;
            
        }else if( poc == tren ){
            poc = new Cvor;
            
            poc -> prethodni = nullptr;
            poc -> element = el;
            poc -> sljedeci = tren;
            tren->prethodni = poc;
        }else{
             (tren->prethodni)->sljedeci = new Cvor;
             
             ((tren->prethodni)->sljedeci)->prethodni = tren->prethodni;
             ((tren->prethodni)->sljedeci)->sljedeci = tren;
             tren->prethodni = (tren->prethodni)->sljedeci;
             
             (tren -> prethodni) -> element = el;
            
             
        }
        broj_el++;
    }
    
//DODAJ IZA    
    void dodajIza(const Tip& el) override {
        
        if(!poc){
            poc = new Cvor;
            
            poc->element = el;
            poc->prethodni = nullptr;
            poc->sljedeci = nullptr;
            
            tren = poc;
            krajListe = poc;
            
        }else if( tren->sljedeci == nullptr ){
            krajListe = new Cvor;
            
            tren->sljedeci = krajListe;
            krajListe->prethodni = tren;
            krajListe->sljedeci = nullptr;
            krajListe->element = el;
            
        }else{
            (tren->sljedeci)->prethodni = new Cvor;
            
            ((tren->sljedeci)->prethodni)->sljedeci = tren->sljedeci;
            tren->sljedeci = (tren->sljedeci)->prethodni;
            (tren->sljedeci)->prethodni = tren;
            
            (tren->sljedeci)->element = el;
        }
    
        broj_el++;
    }
    
//OPERATOR []
    Tip &operator [](int i) {
        if(i<0 || i>=broj_el) throw std::domain_error("Nelegalan index!");
        int j=0;
        Cvor* p = poc;
        while (p != nullptr) {
            if(i==j) break;
            p = p->sljedeci;
            j++;
        }
        return (p->element);
    }
    
// CONST OPERATOR []
    const Tip &operator [](int i) const override {
        if(i<0 || i>=broj_el) throw std::domain_error("Nelegalan index!");
        int j=0;
        Cvor* p = poc;
        while (p != nullptr) {
            if(i==j) break;
            p = p->sljedeci;
            j++;
        }
        return (p->element);
    }
    
//Iterator
    friend class Iterator<Tip>;
    
};









template< typename Tip >
class Iterator {
    const DvostrukaLista<Tip>* dlista;
    typename DvostrukaLista<Tip>::Cvor* trenutniLista;
    
    public:
    
    Iterator(const DvostrukaLista<Tip> &l){ 
        dlista = &l;
        trenutniLista = dlista->poc;
    }
    
    Tip &trenutni(){
        if(!(dlista->poc)) throw std::domain_error("Prazna lista!");
        
        return (trenutniLista->element);
    }
    
    bool prethodni() {
        if(!(dlista->poc)) throw std::domain_error("Prazna lista!");
        
        if(dlista->poc == trenutniLista){
            return false;
        }
        
        trenutniLista = trenutniLista->prethodni;
        
        return true;
    }
    
    bool sljedeci(){
        if(!dlista->poc) throw std::domain_error("Prazna lista!");
        
        if(trenutniLista->sljedeci == nullptr){
            return false;
        }
        
        trenutniLista = trenutniLista->sljedeci;
        
        return true;
    }
   
    void pocetak(){
        if(!dlista->poc) throw std::domain_error("Prazna lista!");
        trenutniLista = dlista->poc;
        
    }


   void kraj(){
       if(!dlista->poc) throw std::domain_error("Prazna lista!");
       
       trenutniLista = dlista -> krajListe;
   }
    
};





template<typename Tip>
Tip dajMaksimum(const Lista<Tip>& n){
    
    const DvostrukaLista<Tip> &dlista = dynamic_cast< const DvostrukaLista<Tip> &> (n);
    
    Iterator<Tip> iterator = Iterator<Tip> (dlista);
    
     Tip max = iterator.trenutni();
     Tip temp;
     while(iterator.sljedeci()){
         temp = iterator.trenutni();
         
         if(temp > max) max = temp;
     }
     
     return max;
}

















//Testna funkcija klase DvostrukaLista za konstruktor bez parametara, te metode: broj elemenata, dodaj iza, trenutni, prethodni, sljedeci, pocetak i kraj. 
bool testnaFunkcija1(){
    DvostrukaLista<int> lista;
    for(int i=0; i<4; i++){
        lista.dodajIza(i+2);
    }
    if( lista.brojElemenata() == 4 ){
        if( lista.trenutni() == 2 && ! lista.prethodni() ){
            if( lista.sljedeci() && lista.sljedeci() ){
                if( lista.trenutni() == 4){ 
                    lista.pocetak();
                    if( lista.trenutni() == 2 ){
                        lista.kraj();
                        if(lista.trenutni() == 3){
                            return true;
                            
                        }
                        return false;
                    }
                }
                return false;
            }
            return false;
        }
        return false;
    }
    return false;
}

//Testna funkcija klase DvostrukaLista za konstruktor bez parametara, te metode: broj elemenata, dodaj iza, trenutni, prethodni, sljedeci, pocetak i kraj.
bool testnaFunkcija2(){
    
    DvostrukaLista<int> lista;
    for(int i=0; i<4; i++){
        lista.dodajIza(i+2);
    }
    
    if( lista.brojElemenata() == 4 ){
        if( lista.trenutni() == 2 && ! lista.prethodni() ){
            if( lista.sljedeci() && lista.sljedeci() ){
                if( lista.trenutni() == 4){ 
                    lista.pocetak();
                    if( lista.trenutni() == 2 ){
                        lista.kraj();
                        if(lista.trenutni() == 3){
                            return true;
                            
                        }
                        return false;
                    }
                }
                return false;
            }
            return false;
        }
        return false;
    }
    return false;
}

//Testna f-ja za klasu DvostrukaLista. Testira: kopirajuci operator dodjele. Te metode: dodaj ispred, obrisi, operator[].
//Kao i dodatne provjere za metodu kraj i trenutni.
bool testnaFunkcija3(){
    DvostrukaLista<int> lista;
    
    for(int i=0; i<4; i++){
        lista.dodajIspred(i+3);
    }
    
    DvostrukaLista<int> nova_lista;
    nova_lista = lista;
    for(int i=0; i<4; i++){
        if( lista[i] != nova_lista[i] ) return false;
    }
    
    for(int i=0; i<4; i++){
        nova_lista.obrisi();
        if(i==0) nova_lista.pocetak();
    }
    
    if( nova_lista.brojElemenata() == 0 && lista.brojElemenata() != 4) return false;
    
    int broj_el_liste(lista.brojElemenata());
    lista[broj_el_liste-1] = 1000;
    lista.kraj();
    
    if( lista.trenutni() != 1000 ) return false;
    
    return true;
}


    //Testna f-ja za klasu DvostrukaLista. Testira: kopirajuci operator dodjele. Te metode: dodaj ispred, obrisi, operator[].
//Kao i dodatne provjere za metode kraj i trenutni.
bool testnaFunkcija4(){
    DvostrukaLista<int> lista;
    for(int i=0; i<4; i++){
        lista.dodajIspred(i+3);
    }
    DvostrukaLista<int> nova_lista;
    nova_lista = lista;
    for(int i=0; i<4; i++){
        if( lista[i] != nova_lista[i] ) return false;
    }
    
    for(int i=0; i<4; i++){
        nova_lista.obrisi();
        if(i==0) nova_lista.pocetak();
    }
    
    if( nova_lista.brojElemenata() == 0 && lista.brojElemenata() != 4) return false;
    
    int broj_el_liste(lista.brojElemenata());
    lista[broj_el_liste-1] = 1000;
    lista.kraj();
    
    if( lista.trenutni() != 1000 ) return false;
    
    return true;
}

//Testna f-ja za klase NizLista i JednostrukaLista. Testira da li su klase genericke.
//Kao i dodatne provjere za neke od metoda.

bool testnaFunkcija5(){
    Lista<double>* lista;
    lista = new DvostrukaLista<double>;
    for(int i=0; i<4; i++){
        lista->dodajIspred(i+0.15);
    }
    
    if( abs(lista->trenutni() - 0.15) < 0.0001 && lista->brojElemenata() != 4) return false;
    
    delete lista;
    
    DvostrukaLista<char>* l;
    l = new DvostrukaLista<char>;
    for(int i=0; i < 4; i++){
        l->dodajIza('a' + i);
    }
    
    if( l->trenutni() != 'a' && lista->brojElemenata() != 4) return false;
    
    delete l;
    
    return true;
}


//Testna f-ja za f-ju dajMximum(Tip = double).

bool testnaFunkcija6(){
    
    Lista<double>* lista;
    lista = new DvostrukaLista<double>;
    
    for(int i=0; i<10; i++){
        lista->dodajIspred(i+0.15);
    }
    
    if( abs(dajMaksimum(*lista) - 9.15) < 0.0001 && lista->brojElemenata() != 10) return false;
    
    delete lista;
    
    return true;
}




//Testna f-ja za f-ju dajMaximum(tip = Char)

bool testnaFunkcija7(){
    
    DvostrukaLista<char>* l;
    l = new DvostrukaLista<char>;
    
    for(int i=0; i < 10; i++){
        l->dodajIza('a' + i);
    }
    
    if( dajMaksimum(*l) != 'j' && l->brojElemenata() != 10) return false;

    delete l;
    
    return true;
}

//Testna f-ja za  f-ju dajMaksimum (performanse)

bool testnaFunkcija8(){
    
    DvostrukaLista<int>* l;
    l = new DvostrukaLista<int>;
    
    for(int i=0; i < 1000000; i++){
        l->dodajIza(10 + i);
    }
    
    if( dajMaksimum(*l) != 1000009 ) return false;

    delete l;
    
    return true;
}


int main() {
    
    if(testnaFunkcija1()){
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
   
    if(testnaFunkcija4()){
        std::cout << "Test 4 je ispravan!" << std::endl;
    }else{
        std::cout << "Test 4 Nije ispravan!" << std::endl;
    }
   
    if(testnaFunkcija5()){
         std::cout << "Test 5 je ispravan!" << std::endl;
    }else{
         std::cout << "Test 5 Nije ispravan!" << std::endl;
    }
    
    if(testnaFunkcija6()){
         std::cout << "Test 6 je ispravan!" << std::endl;
    }else{
         std::cout << "Test 6 Nije ispravan!" << std::endl;
    }
    
    if(testnaFunkcija7()){
         std::cout << "Test 7 je ispravan!" << std::endl;
    }else{
         std::cout << "Test 7 Nije ispravan!" << std::endl;
    }
    
    
    if(testnaFunkcija8()){
         std::cout << "Test 8 je ispravan!" << std::endl;
    }else{
         std::cout << "Test 8 Nije ispravan!" << std::endl;
    }
    
    return 0;
}
