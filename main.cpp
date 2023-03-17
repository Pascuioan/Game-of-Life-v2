#include "tester.h"
#include "game.h"
#include <ctime>
#include <windows.h>

int main(){
    Tabla t;
    srand(time(0));
    for(int i = 0; i < 3; i++){
        int x = double (rand()) * ( double (t.getInaltime()) / RAND_MAX);
        int y = double (rand()) * ( double (t.getLatime()) / RAND_MAX);
        t.putIndivid(new Individ('+'), x, y);
    }
    for(int i = 0; i < 3; i++){
        int x = double (rand()) * ( double (t.getInaltime()) / RAND_MAX);
        int y = double (rand()) * ( double (t.getLatime()) / RAND_MAX);
        t.putIndivid(new Individ('o'), x, y);
    }
    
    while(true){
        system("cls");
        cout<<t;
        t.actualizeaza();
        // cin.get();
        Sleep(50);
    }
}