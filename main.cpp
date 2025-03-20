#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <regex>
#include <windows.h>


using namespace std;

struct probki {
    string nazwa;
    double stezenie;
    double objetosc;
    string imie_nazwisko;
    string data_probki;
    string data_badania;
    string rodzaj_preparatu;

};





bool czyPoprawnyFormat(string& data) {
    //DD.MM.YYYY 
    regex dateRegex(R"(\b\d{2}\.\d{2}\.\d{4}\b)");

    return regex_match(data, dateRegex);
}






bool czyNazwaIstnieje(const vector<probki>& rekordy, const string& nazwa) {
    for (const auto& pom : rekordy) {
        if (pom.nazwa == nazwa) {
            return false;  
        }
    }
    return true;  
}

void dodajProbke(vector<probki>& rekordy) {
    probki nowyRekord;

    while (true) {
        cout << "Podaj nazwe probki: ";
        getline(cin, nowyRekord.nazwa);

        if (czyNazwaIstnieje(rekordy, nowyRekord.nazwa) && nowyRekord.nazwa.length()<256) {
         
            break;
        } else {
            cout << "Ta nazwa probki juz istnieje. Wprowadz unikalna nazwe.\n";
        }
    }
    while(true){

        cout<<"Podaj stezenie probki: ";
        cin>>nowyRekord.stezenie;
        
        if(nowyRekord.stezenie>0)break;
        else cout<<"Stezenie musi byc liczba dodatnia"<<endl;
    }
    
    while(true){

        cout<<"Podaj objetosc probki: ";
        cin>>nowyRekord.objetosc;
        
        if(nowyRekord.objetosc>0)break;
        else cout<<"Objetosc musi byc liczba dodatnia"<<endl;
    }

    cin.ignore(); //pozbywam sie /n z buforu klawiatury przed uzycia funkcji getline


    while(true){
        cout<<"Podaj imie i nazwisko wlasciela probki: ";
    getline(cin, nowyRekord.imie_nazwisko);
    if(nowyRekord.imie_nazwisko.length()<100) break;

    cout<<"Imie i nazwisko jest zbyt dlugie \n";
    }
    

    
    

   
    while(true){

        cout<<"Podaj date pobrania probki w formacie DD.MM.YYYY: ";
        getline(cin, nowyRekord.data_probki);

        if (czyPoprawnyFormat(nowyRekord.data_probki))break;
        else cout<<"Podaj date w poprawnym formacie"<<endl;
    }


    while(true){

        cout<<"Podaj date badania w formacie DD.MM.YYYY: ";
        getline(cin, nowyRekord.data_badania);

        
        if (czyPoprawnyFormat(nowyRekord.data_badania))break;
        else cout<<"Podaj date w poprawnym formacie"<<endl;
    } 




    

    while(true){
            cout<<"Podaj rodzaj preparatu (wybierz jeden z trzech staly, rozpuszczony, lotny): ";
            getline(cin, nowyRekord.rodzaj_preparatu);

            transform(nowyRekord.rodzaj_preparatu.begin(), nowyRekord.rodzaj_preparatu.end(), nowyRekord.rodzaj_preparatu.begin(), ::tolower); //wielkosc liter nie ma znaczenia

            if(nowyRekord.rodzaj_preparatu=="staly"||nowyRekord.rodzaj_preparatu=="rozpuszczony"||nowyRekord.rodzaj_preparatu=="lotny") break;

            else cout<<"Podaj poprawny rodzaj preparatu"<<endl;
    }


   
    rekordy.push_back(nowyRekord);

    cout<<"Dane probki zostaly zapisane pomyslnie "<<endl;
   

}

void usunProbke(vector<probki>& rekordy,const string& nazwaProbki ){
    vector<probki>::iterator it;
    it=rekordy.begin();
    while(it != rekordy.end()){
        if(it->nazwa==nazwaProbki){
            it = rekordy.erase(it);
            cout<<"Probka zostala pomyslnie usunieta"<<endl;
            return;
        }
            else ++it;

    }
    cout<<"Podana nazwa probki nie istnieje: "<<nazwaProbki;
}

void edytujProbke(vector<probki>& rekordy,const string& nazwaProbki){
     bool znaleziona=false;
     
     //
     
     for(vector<probki>::iterator it = rekordy.begin(); it != rekordy.end();it++){

             if(it->nazwa==nazwaProbki){

                znaleziona=true;
                 
                cout<<"Podaj nowe stezenie probki: ";
                cin>>it->stezenie;
                cout<<endl;
                cout<<"Podaj nowa objetosc probki: ";
                cin>>it->objetosc;
                cout<<endl;
                cout<<"Podaj nowe imie i nazwisko wlasciciela: ";
                cin.ignore();
                getline(cin, it->imie_nazwisko);
                 cout<<endl;
                cout<<"Podaj nowa date pobrania probki w formacie DD.MM.YYYY: ";
                getline(cin, it->data_probki);
                cout<<endl;
                cout<<"Podaj nowa date badania w formacie DD.MM.YYYY: ";
                getline(cin, it->data_badania);
                cout<<endl;
                cout<<"podaj nowy predefiniowany rodzaj preparatu (staly, rozpuszczony, lotny): ";
                getline(cin,it->rodzaj_preparatu);
                cout<<endl;
                cout<<"Dane probki zostaly zaaktualizowane pomyslnie: "<<endl;

                

     }

        
     }
     if(znaleziona==false)cout<<"Probka "<<nazwaProbki<<" nie zostala znaleziona"<<endl;
}


void wyszukajProbke(vector<probki>& rekordy,const string& nazwaProbki){
    vector<probki>::iterator it=find_if(rekordy.begin(), rekordy.end(), [&](const probki& p){return p.nazwa == nazwaProbki;});
    it=rekordy.begin();

    if(it != rekordy.end()){
       cout<<"nazwa: "<<it->nazwa<<endl;
       cout<<"stezenie: "<<it->stezenie<<endl;
       cout<<"objetosc: "<<it->objetosc<<endl;
       cout<<"imie i nazwisko wlasciciela: "<<it->imie_nazwisko<<endl;
       cout<<"data pobrania probki:  "<<it->data_probki<<endl;
       cout<<"data badania: "<<it->data_badania<<endl;
       cout<<"rodzaj preparatu: "<<it->rodzaj_preparatu<<endl;
      

    }
else cout<<"Nie ma takiej probki "<<endl;

}

void wyszukajProbkeRegex(vector<probki>& rekordy,const string& nazwaProbki){
   
    regex pattern(nazwaProbki);
    vector<probki>::iterator it=find_if(rekordy.begin(), rekordy.end(), [&](const probki& p){return regex_search(p.nazwa, pattern);});
    
    
    if(it != rekordy.end()){
       cout<<"nazwa: "<<it->nazwa<<endl;
       cout<<"stezenie: "<<it->stezenie<<endl;
       cout<<"objetosc: "<<it->objetosc<<endl;
       cout<<"imie i nazwisko wlasciciela: "<<it->imie_nazwisko<<endl;
       cout<<"data pobrania probki:  "<<it->data_probki<<endl;
       cout<<"data badania: "<<it->data_badania<<endl;
       cout<<"rodzaj preparatu: "<<it->rodzaj_preparatu<<endl;
      

    }
else cout<<"Nie ma takiej probki "<<endl;

}


void zapiszDoPliku(vector<probki>& rekordy,const string& nazwaPliku){
    ofstream plik(nazwaPliku);
    vector<probki>::const_iterator it;

    if(!plik.is_open()){
        cerr<<"Blad przy otwieraniu pliku"<<endl;
        return;
    }

    for(it=rekordy.begin();it!=rekordy.end();it++){
        plik<< it->nazwa<<endl;
        plik<< it->stezenie<<endl;
        plik<< it->objetosc<<endl;
        plik<< it->imie_nazwisko<<endl;
        plik<< it->data_probki<<endl;
        plik<< it->data_badania<<endl;
        plik<< it->rodzaj_preparatu<<endl;
    }
    plik.close();
    cout<<"Dane zapisane w pliku: "<<nazwaPliku<<endl;
}

void wczytajzPliku(vector<probki>& rekordy,const string& nazwaPliku){
    ifstream plik(nazwaPliku);
    vector<probki>::const_iterator it;

    if(!plik.is_open()){
        cerr<<"Blad przy otwieraniu pliku"<<endl;
        return;
    }

    rekordy.clear();

    while(plik>>ws && !plik.eof()){
        probki probka;

        plik>> probka.nazwa >> probka.stezenie >> probka.objetosc >> probka.imie_nazwisko >> probka.data_probki >> probka.data_badania >> probka.rodzaj_preparatu;

        rekordy.push_back(probka);
    }
    plik.close();

    cout<<"Dane z pliku "<<nazwaPliku<<" zostaly wczytane pomyslnie"<<endl;
    

}



int main(){
    
   // system("color 1B");
    vector<probki> rekordy;
    string nazwa;
    int wybor;
    string nazwaPliku;
   
    do{
    cout<<"\nMenu: \n 1. Dodaj probke \n 2. Usun probke \n 3. Edytuj probke \n 4. Wyszukaj probke \n 5. Wyszukaj probke (regex) \n 6. Zapisz do pliku \n 7. Wczytaj z pliku \n 8. Wyjdz\n";

    cout<<"Wybierz operacje: ";
    
    cin>>wybor;
    cout<<endl;
    cin.ignore();
    switch(wybor){
        
       

        case 1:
        system("cls");
        dodajProbke(rekordy);
        cout<<endl;
        system("pause");
        system("cls");
        break;

        case 2:
        system("cls");
        cout<<"Wpisz nazwe probki do usuniecia: ";
        getline(cin, nazwa);
        cout<<endl;
        usunProbke(rekordy, nazwa);
        cout<<endl;
        system("pause");
        system("cls");
        break;

        case 3:
        system("cls");
        cout<<"Wpisz nazwe probki do edycii: ";
        getline(cin, nazwa);
        cout<<endl;
        edytujProbke(rekordy, nazwa);
        cout<<endl;
        system("pause");
        system("cls");
        break;
        
        case 4:
        system("cls");
        cout<<"Wyszukaj probke: ";
        getline(cin, nazwa);
        cout<<endl;
        wyszukajProbke(rekordy, nazwa);
        cout<<endl;
        system("pause");
        system("cls");
        break;

          case 5:
        system("cls");
        cout<<"Wyszukaj probke: ";
        getline(cin, nazwa);
        cout<<endl;
        wyszukajProbkeRegex(rekordy, nazwa);
        cout<<endl;
        system("pause");
        system("cls");
        break;

        case 6:
        system("cls");
        cout<<"Wpisz nazwe pliku do zapisania: ";
        getline(cin,nazwaPliku);
        cout<<endl;
        zapiszDoPliku(rekordy, nazwaPliku);
        cout<<endl;
        system("pause");
        system("cls");
        break;

        case 7:
        system("cls");
        cout<<"Wpisz nazwe pliku do wczytania: ";
        getline(cin, nazwaPliku);
        cout<<endl;
        wczytajzPliku(rekordy,nazwaPliku);
        cout<<endl;
        system("pause");
        system("cls");

        break;

        case 8:
        cout<<"ZAMYKANIE"<<endl;
        break;
        
        
        default:
        cout<<"Wybierz z listy"<<endl;
    }
    } while(wybor != 9);

    return 0;
}