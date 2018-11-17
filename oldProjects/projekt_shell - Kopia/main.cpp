#include <iostream>
#include <cstdlib>
#include <time.h>
#include <cstdio>
#include <iomanip>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <functional>

using namespace std;

int rozmiar;

void drukuj(int * tab, int n){
    cout << endl;
    for(int i = 0; i < n; i++){
        cout << tab[i] << endl;
    }
    cout << endl;
}

void zapelnij(int * tab, int n){
    for (int i = 0; i < n; i++)
                tab[i] = rand()%n;
}

// N^2 zwykly shell
void n2(int * gap, int n){
    int i = 0;
    int temp_n = n;

    while(n > 1){
        gap[i] = n/2;
        n /= 2;
        i++;
    }
    //Dzieki temu, uniwersalne
    for(int j = i; j < temp_n; j++) gap[j] = 0;
}

//Papiernow, Stasiewicz, 1965
void papiernow(int * gap, int n){
    for (int i=0; i<n; ++i){
        if (i==0)
            gap[i]=1;
        else
            gap[i]=pow(2,i)+1;
    }
    while (gap[n]>rozmiar)  n--;
}

//Sedgewick 1986
void sedgewick(int * gap, int n){
    for (int i=0; i<n; ++i){
        if (i==0)
            gap[i]=1;
        else
            gap[i]=pow(4,i)+3*pow(2,i-1)+1;
    }
    while (gap[n]>rozmiar) n--;
}

//wlasny fib
void fibonacci(int * gap, int n){
    gap[0] = 1;
    gap[1] = 1;
    bool flaga = false;
    int last;

    for(int i = 2; i < n ; i++){
        if(gap[i-1] > 40000){ //zabezpieczenie przeciwko za duzym liczbom
            flaga = true;
            last = i;
            break;
        }
        gap[i] = gap[i-1] + gap[i-2];
    }

    if(flaga){ // cd zabezpieczenia
        for(int j = last; j < n; j++) gap[j] = 0;
    }
}

//silnia max n - 15
void silnia(int * gap, int n){
    gap[0] = 1;
    for(int i = 1; i < n; i++){
        if (gap[i-1] * (i+1) > 41000){
            gap[i] = 0;
        }
        else{
            gap[i] = gap[i-1] * (i+1);
        }
    }
}

//potega 3^n, max n - 12
void potega(int * gap, int n){
    gap[0] = 1;
    for(int i = 1; i < n; i++){
        gap[i] = pow(3, i);
    }
}

//sortowanie
void shell (int * tab, int *gap, int n){
    for(int x = 0; x < n; x++){
        if(gap[x] <= 0) return; //Male zabezpieczenie dla zwyklego ciagu shella i fibonacciego
        //cout << "Lece po: " << gap[x] << endl;
        for(int j = rozmiar - gap[x] - 1; j >= 0; j--){
          int temp = tab[j];
          int i = j + gap[x];

          while((i < rozmiar) && (temp > tab[i])){
                //zamiana
                tab[i - gap[x]] = tab[i];
                i += gap[x];
          }
          tab[i - gap[x]] = temp;
        }
    }
}

void quicksort( int * tablica, int x, int y )
{
    int i, j, t, v;
    i = x;
    j = y;
    v = tablica[ x ];
    do
    {
        while( v < tablica[ i ] ) i++;

        while( v > tablica[ j ] ) j--;

        if( i <= j )
        {
            t = tablica[ i ];
            tablica[ i ] = tablica[ j ];
            tablica[ j ] = t;
            i++;
            j--;
        }
    }
    while( i <= j );

    if( x < j ) quicksort( tablica, x, j );

    if( i < y ) quicksort( tablica, i, y );

}

int main(){
    int n;

    fstream ciag1;
    fstream ciag2;
    fstream ciag3;
    fstream ciag4;
    fstream ciag5;
    fstream ciag6;

    ciag1.open("ciag1.txt",ios::out | ios::app);
    ciag2.open("ciag2.txt",ios::out | ios::app);
    ciag3.open("ciag3.txt",ios::out | ios::app);
    ciag4.open("ciag4.txt",ios::out | ios::app);
    ciag5.open("ciag5.txt",ios::out | ios::app);
    ciag6.open("ciag6.txt",ios::out | ios::app);

    LARGE_INTEGER freq, start, stop;
    QueryPerformanceFrequency(&freq);
    srand(time(NULL));
    double time1;

    //cout.precision(15);

/*
    cout << "Podaj rozmiar: ";
    cin >> rozmiar;

    cout << "Podaj n: ";
    cin >> n;
*/
        ciag1<< "Zwykly Shell" <<endl;
        ciag2<< "Papiernow" <<endl;
        ciag3<< "Sedgwick" <<endl;
        ciag4<< "Fibonacci" <<endl;
        ciag5<< "Silnia" <<endl;
        ciag6<< "Potega 3^n" <<endl;

    for(int x = 10000; x <= 70000; x += 10000){
        ciag1<< x <<endl;
        ciag2<< x <<endl;
        ciag3<< x <<endl;
        ciag4<< x <<endl;
        ciag5<< x <<endl;
        ciag6<< x <<endl;


       for(int pow = 1; pow <= 5; pow++){

            rozmiar = x;
            n = rozmiar;

            int tab1[rozmiar];
            int tab2[rozmiar];
            int tab3[rozmiar];
            int tab4[rozmiar];
            int tab5[rozmiar];
            int tab6[rozmiar];

            //cout<< "przeszlo1" << endl;
            int gap1[n];
           // cout<< "przeszlo2" << endl;

            int gap2[17];
            int gap3[9];
            int gap4[24];
            int gap5[15];
            int gap6[11];

            zapelnij(tab1, n);

            //kopiowanie
            for(int i = 0; i < rozmiar; i++){
                tab2[i] = tab1[i];
                tab3[i] = tab1[i];
                tab4[i] = tab1[i];
                tab5[i] = tab1[i];
                tab6[i] = tab1[i];
            }

            n2(gap1, rozmiar);
            papiernow(gap2, 17);
            sedgewick(gap3, 9);

            fibonacci(gap4, 24);
            silnia(gap5, 8);
            potega(gap6, 11);

            //Dla sedgewicka, papiernowa, fibonacciego
            sort(gap1, gap1 + n, greater < int >());
            //quicksort( gap1, 0, rozmiar);
            sort(gap2, gap2 + 17, greater < int >());
            sort(gap3, gap3 + 9, greater < int >());
            sort(gap4, gap4 + 24, greater < int >());
            sort(gap5, gap5 + 8, greater < int >());
            sort(gap6, gap6 + 11, greater < int >());

            //drukuj(gap, n);
            QueryPerformanceCounter(&start);
                shell(tab1, gap1, n);
            QueryPerformanceCounter(&stop);
            time1=static_cast<double>(stop.QuadPart-start.QuadPart)/freq.QuadPart;
            cout<<"1. "<<setprecision(16)<<time1<<endl;

            ciag1<<setprecision(16)<<time1<<endl;


            QueryPerformanceCounter(&start);
                shell(tab2, gap2, 17);
            QueryPerformanceCounter(&stop);
            time1=static_cast<double>(stop.QuadPart-start.QuadPart)/freq.QuadPart;
            cout<<"2. "<<setprecision(16)<<time1<<endl;

            ciag2<<setprecision(16)<<time1<<endl;

            QueryPerformanceCounter(&start);
                shell(tab3, gap3, 9);
            QueryPerformanceCounter(&stop);
            time1=static_cast<double>(stop.QuadPart-start.QuadPart)/freq.QuadPart;
            cout<<"3. "<<setprecision(16)<<time1<<endl;

            ciag3<<setprecision(16)<<time1<<endl;

            QueryPerformanceCounter(&start);
                shell(tab4, gap4, 24);
            QueryPerformanceCounter(&stop);
            time1=static_cast<double>(stop.QuadPart-start.QuadPart)/freq.QuadPart;
            cout<<"4. "<<setprecision(16)<<time1<<endl;

            ciag4<<setprecision(16)<<time1<<endl;

            QueryPerformanceCounter(&start);
                shell(tab5, gap5, 8);
            QueryPerformanceCounter(&stop);
            time1=static_cast<double>(stop.QuadPart-start.QuadPart)/freq.QuadPart;
            cout<<"5. "<<setprecision(16)<<time1<<endl;

            ciag5<<setprecision(16)<<time1<<endl;

            QueryPerformanceCounter(&start);
                shell(tab6, gap6, 11);
            QueryPerformanceCounter(&stop);
            time1=static_cast<double>(stop.QuadPart-start.QuadPart)/freq.QuadPart;
            cout<<"6. "<<setprecision(16)<<time1<<endl << endl << endl;

            ciag6<<setprecision(16)<<time1<<endl;

        /*
            for(int y = 0; y < 10; y++){
                cout << "1. " << tab1[y] << endl;
                cout << "2. " << tab2[y] << endl;
                cout << "3. " << tab3[y] << endl;
                cout << "4. " << tab4[y] << endl;
                cout << "5. " << tab5[y] << endl;
                cout << "6. " << tab6[y] << endl << endl;
            }
        */

            //drukuj(tab1, rozmiar);
        }
        ciag1<< endl;
        ciag2<< endl;
        ciag3<< endl;
        ciag4<< endl;
        ciag5<< endl;
        ciag6<< endl;
    }

    ciag1.close();
    ciag2.close();
    ciag3.close();
    ciag4.close();
    ciag5.close();
    ciag6.close();
}
