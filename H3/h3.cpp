#include <iostream>
#include <vector> 
#include <algorithm>
#include <stdexcept>
#include <deque> 


using namespace std;




void ispisiVector(vector<int> v){
    cout << "Vector: ";
    for(int i=0; i<v.size(); i++){
        if(i != 0){
            cout << ", "; 
        }
        cout << v[i];
    }
    cout << ".\n";
}





//Radix sort

void radixSort(vector<int> &a){
    
    std::vector<std::deque<int>> cifre(10);
    
    int k(1);
    
    while(true){
        
        for(int element : a){
            cifre[(element/k)%10].push_back(element);
        }
        
        int j(0);
        
        for(int i=0; i<cifre.size(); i++){
            while(cifre[i].size() != 0){
                a[j] = cifre[i].front();
                cifre[i].pop_front();
                j++;
            }  
            
            if(j == a.size() && i==0) return;
        }
        
        k *= 10;
        
    }
    
}


//Da li je list

bool daLiJeList(int i, int duzina){
    return ( i < duzina && i >= (duzina/2) );
}




// Popravi dolje

void popravi_dolje(vector<int> &a, int i, int duzina){
    
    while( !daLiJeList(i,duzina) ){
        
        int veci = 2*i + 1;
        int desno = 2*i + 2;
        
        if( desno < duzina && a[desno] > a[veci] ){
            veci = desno;
        }
        
        if(a[veci] < a[i]) return;
        
        swap(a[i], a[veci]);
        i = veci;
    }
}





//Stvori gomilu 

void stvoriGomilu(vector<int> &a){
    
    int duzina(a.size());
    
    for(int i=((duzina-1)/2); i>=0; i--){
        popravi_dolje(a, i, duzina);
    }
}




void popravi_gore(vector<int> &a, int i){
    int roditelj = (i-1)/2;
    
    while (i>0 && a[i] > a[roditelj]) {
        swap( a[i], a[roditelj] );
        i=roditelj;
        roditelj = (i-1)/2;
    }
    
}




//Umetnuti u gomilu

void umetniUGomilu(vector<int> &a, int umetnuti, int &velicina){
    a.push_back(umetnuti);
    velicina++;
    popravi_gore(a, velicina-1);    
}



//Izbaci prvi

int izbaciPrvi(vector<int> &a, int &velicina){
    if(a.size() == 0)
        throw ("Gomila prazna!");
        
    velicina--;
    swap(a[0], a[velicina]);
    
    if(velicina != 0)
        popravi_dolje(a, 0, velicina);
    
    return a[velicina];
}


//Gomila sort

void gomilaSort(vector<int> &a){
    stvoriGomilu(a);
    int velicina = a.size();
    
    for(int i=0; i<a.size()-1; i++){
        izbaciPrvi(a, velicina);
    }
    
}



int main() {
    
    vector<int> v = {248, 820, 788, 643, 347, 329, 673, 174, 293, 455, 271, 625};
    
    radixSort(v);
    
    ispisiVector(v);
    
    vector<int> v1 = v;
    
    gomilaSort(v1);
    
    ispisiVector(v1);
    
    return 0;
}
