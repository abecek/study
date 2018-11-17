#include <iostream>
#include <cstring>
#include <fstream>
#include <windows.h>
#include <time.h>
#include <random>

#include <vector>

using namespace std;

clock_t start1, start2;
clock_t stop1, stop2;
string text, pattern, pom;


class AbstractSearchBase
{
public:
    virtual double search()=0;
    virtual const vector<int> & get_result() = 0;
    virtual ~AbstractSearchBase() {};
};

class StringSearch : public AbstractSearchBase
{
protected:
    string T;
    string P;
    vector<int> Occ;

public:
    clock_t start, stop;

    StringSearch(const string & T, const string & P);
    const vector<int> & get_result();
    bool matchesAt(int i);
    int getOccNumber();
};

StringSearch::StringSearch(const string & text, const string & pattern)
{
    this->T = text;
    this->P = pattern;
}

const vector<int> & StringSearch::get_result()
{
    return this->Occ;
}

int StringSearch::getOccNumber()
{
    return this->Occ.size();
}


bool StringSearch::matchesAt(int poz)
{
    for(size_t j = 0; j < P.size(); j++)
    {
        if(poz+j >= T.size() )
        {
            return false;
        }
        if(T[poz+j] != P[j])
        {
            return false;
        }
    }
    return true;
}

class SundaySearch : public StringSearch
{
protected:
    //vector < int > Oracle;
    int *Oracle;

public:
    SundaySearch(const string & text, const string  & pattern) : StringSearch(T,P)
    {
        T = text;
        P = pattern;

        Oracle = new int[256];

        for (int i=0; i < 256; i++)
           Oracle[i]=-1;

        for (int j=0; j < P.size(); j++)
        {
            Oracle[P[j]] = j;
        }

    }

    double search();
};


double SundaySearch::search()
{
    //Second version
    int i = 0;
    int x = 0;

    start = clock();

    while ( i <= T.size() - P.size())
    {
        if (matchesAt(i)) x++;//cout << "Pozycja: " << i << endl;

        i += P.size();

        if (i < T.size()) i -= Oracle[T[i]];
    }

    stop = clock();
    /*
    cout << endl << "--------------------------------" << endl << "Czas Sunday'a: " << (stop-start)/(double)CLOCKS_PER_SEC << endl
         <<"--------------------------------" << endl << endl;
    */
    return (stop-start)/(double)CLOCKS_PER_SEC;
}

class MorrisPrattSearch : public StringSearch{
protected:
    //vector <int> PI;
    int wsk;
    int * PI;

public:
    MorrisPrattSearch(const string & text, const string & pattern) : StringSearch(T,P)//, PI(P.size()+1, 0)
    {

        T = text;
        P = pattern;

        PI = new int[pattern.size()+1];
        wsk = -1;
        PI[0] = -1;

        for(int i = 1; i <= P.size(); i++)
        {
            while((wsk > -1) and (P[wsk] != P[i - 1]))
                wsk = PI[wsk];
            PI[i] = ++wsk;
        }

    };

    double search();
};



// z zajec
double MorrisPrattSearch::search(){

    int i = 0;
    int j = 0;

    start = clock();
    while (i <= T.size() - P.size())
    {
        while ((j < P.size()-1) and (P[j+1] == T[i+j+1]))
            j++;
        if (j == P.size() -1)
        {
            //cout << "Pozycja: " << i << endl;
            j = 0;
            i++;
        }
        else
        {
            i = i+j - PI[j];
            if(PI[j]<0)
                j = 0;
            else
                j = PI[j];
        }
    }

    stop = clock();
    /*
    cout << endl << "--------------------------------" << endl << "Czas Morrisa-Pratta: " << ((stop - start)/(double)CLOCKS_PER_SEC) << endl
         <<"--------------------------------" << endl << endl;
    */
    return (stop-start)/(double)CLOCKS_PER_SEC;
}

void wczytaj_tekst()
{
    string ci;

    cout << "Podaj text: ";
    getline(cin, ci);
    text.assign(ci.c_str());

}

void wczytaj_wzorzec(){
    string wz;

    cout << "Podaj wzorzec, ktorego bedziemy szukac: ";
    getline(cin, wz);
    pattern.assign(wz.c_str());
}

void wczytaj_z_pliku()
{
    string ci;
    fstream plik;

    plik.open("ciag.txt", ios::in);
    for(int i=0; !plik.eof(); i++)
    {
        getline(plik,ci);
        //text.assign(ci.c_str());
        text.append(ci.c_str());
    }
    plik.close();
}

void generuj(int n, double wartosc_ocz, double roz){
    mt19937 gen( time(NULL) );
    normal_distribution <> N(wartosc_ocz, roz);

        for(int i = text.size(); i < n; i++){
            double d = N( gen );
            char t = lround(d);
            text.push_back(t);
        }
    /*
    char t = lround(wartosc_ocz);
    cout << "Wartosc ocz: " << wartosc_ocz << " - char: " << t << endl;
    */
}

int dodaj(int n){
        int ile = n / pom.size();

        for(int i = text.size() / pom.size();  i < ile; i++){
            text += pom;
        }

    return text.size();
}

void wypisz(string tab){
    for(int i = 0; i < tab.size(); i++){
        cout << tab[i];
    }
    cout << endl << "Dlugosc tablicy: " << tab.size() << endl;
}

int main()
{
    fstream wyniki1;
    cout.precision(20);
    wyniki1.precision(20);

    //wczytaj_tekst();
    wczytaj_wzorzec();

    //wczytaj_z_pliku();
    //pom.append(text);

    //wypisz(text);
    //wypisz(pattern);

    wyniki1.open("wyniki.txt",ios::out | ios::app);

    for (int main=1000000; main<=20000000; main+=500000){
        //dodaj(main);
        generuj(main, 160.0, 2.0);

        MorrisPrattSearch test1(text, pattern);
        SundaySearch test2(text, pattern);

        //cout << text.size() << " " << pattern.size() << " " << test1.search() << " " << test2.search() << endl;
        wyniki1 << text.size() << " " << pattern.size() << " " << test1.search() << " " << test2.search() << endl;
    }


    wyniki1.close();

    return 0;
}
