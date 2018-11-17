#include <iostream>
#include <unordered_set>
#include <cstring>
#include <fstream>
#include <time.h>
#include <random>
#include <vector>

using namespace std;

clock_t start, stop;
int skok = 0;
size_t tab_size = 2000000;

struct Node
{
    public:
    size_t key;
    string  value;
    Node *next;
};

class Lancuch{
    public:
        Node **tab;

        Lancuch(){
            tab = new Node*[tab_size];
            for (int i = 0; i < tab_size; i++){
                tab[i] = NULL;
            }
        }

        ~Lancuch(){
            delete [] tab;
        }

		size_t HashDJB2(string &str){
			start = clock();
            unsigned int hash = 5381;
            for (unsigned int i = 0; i < str.length(); i++){
                hash = ((hash << 5) + hash) + (str[i]);
                i += skok;
            }
            stop = clock();
            return hash % tab_size;
		}

		size_t HashFnv(string &str){
			start = clock();
            size_t hash = 2166136261;
            for(size_t i = 0; i < str.length(); i++){
                hash = hash ^ (str[i]);
                hash = hash * 16777619;
                i += skok;
            }
            stop = clock();
            return hash % tab_size;
		}

		size_t HashMod(string &str){
			start = clock();
            int i=0;
            int hash=0;
            while(i < str.length()){
                hash = ( hash * 256 + str[i] ) % str.length();
                i += skok;
                i++;
            }
            stop = clock();
            return hash % tab_size;
		}

        void dodaj(string str){
            size_t hash = HashDJB2(str);
            //size_t hash = HashFnv(str);
            //size_t hash = HashMod(str);

            Node *nowy = tab[hash];
            if (nowy == NULL){
                nowy = new Node;
                nowy->value = str;
                nowy->key = hash;
                nowy->next = NULL;
                tab[hash] = nowy;
            }
            else{
                while (nowy != NULL) nowy = nowy->next;
                nowy = new Node;
                nowy->value = str;
                nowy->key = hash;
                nowy->next = NULL;
            }
        }

        void usun(string str){
			size_t hash = HashMod(str);
            if (tab[hash] != NULL){
                Node *wagon = tab[hash];
                Node *prev = NULL;
                while (wagon->next != NULL && wagon->key != hash){
                    prev = wagon;
                    wagon = wagon->next;
                }
                if (wagon->key == hash){
                    //usuniecie pierwszego
                    if (prev == NULL){
                        Node *next = wagon->next;
                        delete wagon;
                        tab[hash] = next;
                    }
                    //srodkowego
                    else{
                        Node *next = wagon->next;
                        delete wagon;
                        prev->next = next;
                    }
                }
            }

        }

        void szukaj(string str){
            size_t hash = HashMod(str);
            bool flag = false;
            Node* wagon = tab[hash];
            if (wagon != NULL){
                while (wagon != NULL){
                    if (wagon->key == hash){
						cout << "Znaleziono, hasz - " << hash << ": ";
                        cout << wagon->value << endl;
                        flag = true;
                    }
                    wagon = wagon->next;
                }
            }
            if (!flag)
                cout << "Nie znaleziono" << endl;
        }
};

struct DJB2 {
    public:
        size_t operator()(const string & str) const {
            start = clock();
            unsigned int hash = 5381;
            for (unsigned int i = 0; i < str.length(); i++){
                hash = ((hash << 5) + hash) + (str[i]);
                i += skok;
            }
            //cout << "Hasz: " << hash << endl;
            stop = clock();
            //cout << "Czas: " << ((stop - start)/(double)CLOCKS_PER_SEC) << endl << "-------" << endl;
            return hash;
        }
};

struct FNV {
    public:
        size_t operator()(const string & str) const {
            start = clock();
            size_t hash = 2166136261;
            for(size_t i = 0; i < str.length(); i++){
                hash = hash ^ (str[i]);
                hash = hash * 16777619;
                i += skok;
            }

            //cout << "Hasz: " << hash << endl;
            stop = clock();
            //cout << "Czas: " << ((stop - start)/(double)CLOCKS_PER_SEC) << endl << "-------" << endl;
            return hash;
        }
};

struct MOD {
    public:
        size_t operator()(const string & str) const {
            start = clock();
            int i=0;
            int hash=0;
            while(i < str.length()){
                hash = ( hash * 256 + str[i] ) % str.length();
                i += skok;
                i++;
            }
            //cout << "Hasz: " << hash << endl;
            stop = clock();
            //cout << "Czas: " << ((stop - start)/(double)CLOCKS_PER_SEC) << endl << "-------" << endl;
            return hash;
        }
};


string generuj_los(int n){
    string s;
    static const char alfa[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

    int dl = sizeof(alfa) - 1;

    for(int i = 0; i < n; i++){
        s += alfa[rand() % dl];
    }
    //cout << s << endl;
    return s;
}

string generuj_ciag(int n){
    string s;
    vector <string> tab = {
        "Lorem",
        "ipsum",
        "dolor",
        "sit",
        "amet",
        "consectetur",
        "adipiscing",
        "elit",
        "Nulla",
        "magna",
        "congue",
        "rutrum",
        "et",
        "placerat",
        "sit",
        "amet",
        "urna"};
    int dl = sizeof(tab) - 1;

    while(s.length() < n){
        s += tab[rand() % dl];
        s += " ";
    }
    s.resize(n);
    //cout << s << " Dl: " << s.length() << endl;

    return s;
}

int main()
{
    fstream wyniki1;
    cout.precision(16);
    wyniki1.precision(16);

    vector <string> ciagi;
    unordered_set <string, MOD> setOfStrs;

    //for (string s : setOfStrs) cout << s << endl << endl;

    int dlugosc_ciagu = 1000;
    wyniki1.open("wyniki_stala_dl_skok_0.txt", ios::out | ios::app);
    wyniki1 << skok << endl;
    clock_t start1, stop1;
    start1 = clock();

    Lancuch l;
        for(int j = 1; j <= 20000; j+=1){
            //setOfStrs.insert(generuj_los(dlugosc_ciagu));
            //setOfStrs.insert(generuj_ciag(dlugosc_ciagu));
            //l.dodaj(generuj_los(dlugosc_ciagu));
            l.dodaj(generuj_ciag(dlugosc_ciagu));
        }

    stop1 = clock();
    //cout << endl << "-------" << endl << "Czas przy stalej dlugosci ciagu: " << ((stop1 - start1)/(double)CLOCKS_PER_SEC) << endl;
    wyniki1 << dlugosc_ciagu << " " << ((stop1 - start1)/(double)CLOCKS_PER_SEC) << endl;
    wyniki1.close();


    wyniki1.open("wyniki_zmienna_dl_skok_0.txt", ios::out | ios::app);
    wyniki1 << skok << endl;
        for(int j = 1000000; j <= 20000000; j+=1000000){
            start1 = clock();
            //setOfStrs.insert(generuj_los(j));
            //setOfStrs.insert(generuj_ciag(j));
            //l.dodaj(generuj_los(j));
            l.dodaj(generuj_ciag(j));

            stop1 = clock();
            //cout << endl << "-------" << endl << "Czas: " << ((stop1 - start1)/(double)CLOCKS_PER_SEC) << endl;
            wyniki1 << j << " " << ((stop1 - start1)/(double)CLOCKS_PER_SEC) << endl;
        }
    wyniki1.close();

    setOfStrs.clear();

     return 0;
}
