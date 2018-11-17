#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <fstream>

#include <conio.h>


/*
Michal Blaszczyk
nr 345096
*/
using namespace std;

void drukuj(int * t, int n){
    for(int i=0;i<n;i++){
        cout << i << ": " << t[i] << endl;
    }
    cout << endl;
}

void wypelnij(int * t, int n, int z){
    for(int i=0; i<n; i++){
        t[i] = rand() % z;
    }
}

void pierwszy(unsigned int n,int z, ofstream& plik){
    plik << "Algorytm pierwszy" << endl;
    plik << "N, MS" << endl;
   // do{
        clock_t start = clock();

        int * t = new int[n];
        //int * tablica2 = new int[z];

        wypelnij(t, n, z);
        int licznik = 0;
        int wartosc = 0;
        int ile = 0;

        //drukuj(t, n);
            for(int i = 0; i < n; i++){
                for(int j = 0; j < n; j++){
                    if(t[i] == t[j]){
                        licznik++;
                    }
                }
                if( (licznik*2) > n){
                    wartosc = t[i];
                    ile = licznik;
                    //cout << "Najwiecej wartosci: " << wartosc << ", w liczbie: " << ile << endl;
                }
                licznik = 0;
            }

                if( (ile*2) > n){
                        cout << "Najwiecej wartosci: " << wartosc << ", w liczbie: " << ile << endl;
                        cout << "Jest wartoscia dominujaca." << endl;
                }else{
                    cout << "Nie ma wartosci dominujacej." << endl;
                }
            plik << n << "," << (clock() - start) << endl;
            cout << "Czas : " << clock() - start << " ms" << endl;
          //  cout << "Aby wyjsc nacisnij ESC.\n________________________________" << endl;

            delete [] t;

   // }while(getch() != 27);

}


void drugi(unsigned int n,int z, ofstream& plik){
   //plik << "Algorytm drugi:" << endl;
    //plik << "N, MS" << endl;
   // do{

    clock_t start = clock();

    int * tablica = new int[n];
    int * tablica2 = new int[z];

            wypelnij(tablica, n, z);

            for(int i=0; i<z; i++){
                tablica2[i] = 0;
            }
               // drukuj(tablica2, z);
            for(int i=0; i<z; i++){
                for(int k=0; k<n; k++){
                    if(i == tablica[k]){
                        tablica2[i] += 1;
                        //cout << "id " << tablica[i] << ": + 1" << endl;
                    }
                }
            }
            //drukuj(tablica, n);
            //drukuj(tablica2, z);
            int naj_czego = 0;
            int ile = 0;

            for(int i=0; i<z; i++){
                    if( tablica2[i] > ile ){
                        naj_czego = i;
                        ile = tablica2[i];
                    }
            }
            cout << "Najwiecej wartosci: " << naj_czego << ", w liczbie: " << ile << endl;
            if( (ile*2) > n){
                cout << "Jest wartoscia dominujaca." << endl;
            }else{
                cout << "Nie ma wartosci dominujacej." << endl;
            }
            plik << z << "," << (clock() - start) << endl;
            cout << "Czas : " << clock() - start << " ms" << endl;
       //     cout << "Aby wyjsc nacisnij ESC.\n________________________________" << endl;

           delete [] tablica;
           delete [] tablica2;

   // }while(getch() != 27);

}

void trzeci(unsigned int n,int z, ofstream& plik){
    //plik << "Algorytm trzeci:" << endl;
   // plik << "N, MS" << endl;
    //do{
        clock_t start = clock();
        int * t = new int[n];

        wypelnij(t, n, z);
        int licznik = 0;
        int wartosc = 0;
        int ile = 0;

        //drukuj(t, n);
           for(int i = 0; i < z; i++){
                for(int j = 0; j < n; j++){
                    if(i == t[j]){
                        licznik++;
                    }
                }
                if( (licznik*2) > n){
                    wartosc = t[i];
                    ile = licznik;
                    //cout << "Najwiecej wartosci: " << wartosc << ", w liczbie: " << ile << endl;
                }
                licznik = 0;
            }
                if( (ile*2) > n){
                        cout << "Najwiecej wartosci: " << wartosc << ", w liczbie: " << ile << endl;
                        cout << "Jest wartoscia dominujaca." << endl;
                }else{
                    cout << "Nie ma wartosci dominujacej." << endl;
                }
            plik << z << "," << (clock() - start) << endl;
            cout << "Czas : " << clock() - start << " ms" << endl;
          //  cout << "Aby wyjsc nacisnij ESC.\n________________________________" << endl;

            delete [] t;

   // }while(getch() != 27);

}

void czwarty(unsigned int n,int z, ofstream& plik){
    //plik << "Algorytm czwarty:" << endl;
    //plik << "N, MS" << endl;
    //do{
        clock_t start = clock();
        int * t = new int[n];
        int * t2 = new int[z];

        for(int i=0; i<z; i++){
                t2[i] = 0;
            }

        int k = 0;
        wypelnij(t, n, z);
        int x = n / z ;
        int temp_z = z;

                while(k < n){
                    //cout << "Sprawdzam: ";
                     for(int l = 0; l < z ; l++){
                            if( (k+l) < n ){  // Zabezpieczenie zeby nie wyjechalo poza zakres tablicy
                           // cout <<"[" <<k+l<<"]" << ": " << t[k+l] << "   ";
                            t2[t[k+l]] += 1;
                            }
                    }
                   // cout << endl;
                    k += z;
                }
                //drukuj(t2, z);
                int naj_czego = 0;
                int ile = 0;

                for(int i=0; i<z; i++){
                        if( t2[i] > ile ){
                            naj_czego = i;
                            ile = t2[i];
                        }
                }
                cout << "Najwiecej wartosci: " << naj_czego << ", w liczbie: " << ile << endl;
                if( (ile*2) > n){
                    cout << "Jest wartoscia dominujaca." << endl;
                }else{
                    cout << "Nie ma wartosci dominujacej." << endl;
                }
            plik << z << "," << (clock() - start) << endl;
            cout << "Czas : " << clock() - start << " ms" << endl;
         //   cout << "Aby wyjsc nacisnij ESC.\n________________________________" << endl;

    delete [] t;
    delete [] t2;
    //}while(getch() != 27);
}


int main()
{
    ofstream plik;
    plik.open( "wyniki.txt" );
    srand( time( NULL ) );
    unsigned int n = 5000000;
    int z = 2;

    if( plik.good() == true ) {
       // plik << "N: " << n << endl;
        plik << "Z: " << z << endl;
        cout << "Jest dostep do pliku wynikow" << endl;
    }
    else{
        cout << "Nie ma dostepu do pliku wynikow" << endl;

    }

   int x;
    cout << "Podaj numer funkcji (1/2/3/4): ";
    cin >> x;
    switch(x){
        case 1:
            //for(m=1;m<50;m++){
                pierwszy(n,z, plik);
              //  n += 1000000;
            //}
            break;
        case 2:
            for(int m=1;m<=10;m++){
                drugi(n,z,plik);
                // n += 1000000;
                 //z += 2;
            }
            break;
        case 3:
            for(int m=1;m<=10;m++){
                trzeci(n,z,plik);
               //  n += 1000000;
                // z += 2;
            }
            break;
        case 4:
            for(int m=1;m<=10;m++){
                czwarty(n,z,plik);
                // n += 1000000;
                // z += 2;
            }
            break;
       // case 5:
         //   piaty(n,z);
          //  break;

    }


    plik.close();
    return 0;
}
