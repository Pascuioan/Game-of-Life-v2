#ifndef GAME_H
#define GAME_H

#include <iostream>

#include <stdlib.h>

using namespace std;

class Tabla;

class Individ {
    static
    const int VARTSA_MAX = 50;
    static
    const int ENERGIE_DEFAULT = 10;
    int i, j, varsta;
    char tip;
    double energie;
    unsigned char viu;
    Tabla * tabla;

    //metode private
    void hraneste();
    void inmulteste();
    void ataca();
    void imbatraneste();
    void moare();
    int getDistantaDeVarstaMijlocie();

    public:

    //constructori
    Individ();
    Individ(char);
    Individ(int, int, char, Tabla & );
    Individ(int, int, char, Tabla * );

    //constructorul default de copiere este bun

    //setter: pt varsta, energie si viu nu avem nevoie pt ca sunt manipulate intern
    void setTabla(Tabla * );
    void setI(int);
    void setJ(int);
    void setTip(char);

    //getteri
    int getI();
    int getJ();
    int getVarsta();
    char getTip();
    double getEnergie();
    unsigned char getViu();
    Tabla * getTabla();

    //metode publice
    void actualizeaza();

    //supraincarcare operatori
    Individ operator = (Individ);
    friend std::ostream & operator << (std::ostream & , Individ & );
    friend std::istream & operator >> (std::istream & , Individ & );
};

class Tabla {
    Individ ** * indivizi;
    static
    const int INALTIME = 20, LATIME = 70;

    public:

    //constuctori
    Tabla();
    Tabla(Individ ** * );
    ~Tabla();

    //consturcotr de copiere
    Tabla(const Tabla & );

    //setteri
    void setIndivizi(Individ ** * );

    //getteri
    Individ ** * getIndivizi();
    int getInaltime();
    int getLatime();

    //metode publice
    void putIndivid(Individ * , int, int);
    void afiseaza();
    void actualizeaza();
    int getAportEnergetic(int, int);

    //supraincarcare operatori
    Tabla operator = (Tabla);
    friend std::ostream & operator << (std::ostream & , Tabla & );
};

Individ::Individ() {
    viu = 1;
    varsta = 0;
    energie = ENERGIE_DEFAULT;
    tabla = 0;
}

Individ::Individ(char tip) {
    viu = 1;
    varsta = 0;
    energie = ENERGIE_DEFAULT;
    tabla = 0;
    this -> tip = tip;
}

Individ::Individ(int i, int j, char tip, Tabla & tabla) {
    viu = 1;
    varsta = 0;
    energie = ENERGIE_DEFAULT;
    this -> i = i;
    this -> j = j;
    this -> tip = tip;
    this -> tabla = & tabla;
}

Individ::Individ(int i, int j, char tip, Tabla * tabla) {
    viu = 1;
    varsta = 0;
    energie = ENERGIE_DEFAULT;
    this -> i = i;
    this -> j = j;
    this -> tip = tip;
    this -> tabla = tabla;
}

void Individ::setTabla(Tabla * tabla) {
    this -> tabla = tabla;
}

void Individ::setI(int i) {
    this -> i = i;
}

void Individ::setJ(int j) {
    this -> j = j;
}

void Individ::setTip(char t) {
    tip = t;
}

int Individ::getI() {
    return i;
}

int Individ::getJ() {
    return j;
}

int Individ::getVarsta() {
    return varsta;
}

char Individ::getTip() {
    return tip;
}

double Individ::getEnergie() {
    return energie;
}

unsigned char Individ::getViu() {
    return viu;
}

Tabla * Individ::getTabla() {
    return tabla;
}

void Individ::hraneste() {
    if (tabla == 0) {
        cout << "Individul nu apartine unei table!";
        return;
    }
    //se face suma aporturilor energetice a fiecarei casute invecinate
    int ae = 0;
    Individ ** * ind = tabla -> getIndivizi();
    if (ind[max(i - 1, 0)][j] == 0) {
        ae += tabla -> getAportEnergetic(i - 1, j);
    }
    if (ind[i][min(j + 1, tabla -> getLatime() - 1)] == 0) {
        ae += tabla -> getAportEnergetic(i, j + 1);
    }
    if (ind[min(i + 1, tabla -> getInaltime() - 1)][j] == 0) {
        ae += tabla -> getAportEnergetic(i + 1, j);
    }
    if (ind[i][max(j - 1, 0)] == 0) {
        ae += tabla -> getAportEnergetic(i, j - 1);
    }
    energie += (ae - getDistantaDeVarstaMijlocie());
}

void Individ::inmulteste() {
    if (tabla == 0) {
        cout << "Individul nu apartine unei table!";
        return;
    }
    //numarul maxim de fii este in [0,4] si este maxim la jumatatea varstei
    int maxFii = this -> getDistantaDeVarstaMijlocie();
    Individ ** * indivizi = tabla -> getIndivizi();

    //se verifica daca locurile invecinate sunt libere si eventual se populeaza
    if (indivizi[max(i - 1, 0)][j] == 0) {
        if ((maxFii > 0) && (energie >= 25)) {
            indivizi[max(i - 1, 0)][j] = new Individ(i - 1, j, tip, tabla);
            maxFii--;
            energie -= 10;
        }
    }
    if (indivizi[i][min(j + 1, tabla -> getLatime() - 1)] == 0) {
        if (maxFii > 0 && energie >= 25) {
            indivizi[i][min(j + 1, tabla -> getLatime() - 1)] = new Individ(i, j + 1, tip, tabla);
            maxFii--;
            energie -= 10;
        }
    }
    if (indivizi[min(i + 1, tabla -> getInaltime() - 1)][j] == 0) {
        if (maxFii > 0 && energie >= 25) {
            indivizi[min(i + 1, tabla -> getInaltime() - 1)][j] = new Individ(i + 1, j, tip, tabla);
            maxFii--;
            energie -= 10;
        }
    }
    if (indivizi[i][max(j - 1, 0)] == 0) {
        if (maxFii > 0 && energie >= 25) {
            indivizi[i][max(j - 1, 0)] = new Individ(i, j - 1, tip, tabla);
            maxFii--;
            energie -= 10;
        }
    }
}

void Individ::ataca() {
    Individ ** * ind = tabla -> getIndivizi();

    //se verfifica locurile invecinate si se ataca indivizii de tip diferit
    if (ind[max(i - 1, 0)][j] != 0) {
        if (tip != ind[max(i - 1, 0)][j] -> getTip()) {
            if (energie > ind[max(i - 1, 0)][j] -> getEnergie()) {
                energie -= ind[max(i - 1, 0)][j] -> getEnergie();
                ind[max(i - 1, 0)][j] -> moare();
            }
        }
    }
    if (ind[i][min(j + 1, tabla -> getLatime() - 1)] != 0) {
        if (tip != ind[i][min(j + 1, tabla -> getLatime() - 1)] -> getTip()) {
            if (energie > ind[i][min(j + 1, tabla -> getLatime() - 1)] -> getEnergie()) {
                energie -= ind[i][min(j + 1, tabla -> getLatime() - 1)] -> getEnergie();
                ind[i][min(j + 1, tabla -> getLatime() - 1)] -> moare();
            }
        }
    }
    if (ind[min(i + 1, tabla -> getInaltime() - 1)][j] != 0) {
        if (tip != ind[min(i + 1, tabla -> getInaltime() - 1)][j] -> getTip()) {
            if (energie > ind[min(i + 1, tabla -> getInaltime() - 1)][j] -> getEnergie()) {
                energie -= ind[min(i + 1, tabla -> getInaltime() - 1)][j] -> getEnergie();
                ind[min(i + 1, tabla -> getInaltime() - 1)][j] -> moare();
            }
        }
    }
    if (ind[i][max(j - 1, 0)] != 0) {
        if (tip != ind[i][max(j - 1, 0)] -> getTip()) {
            if (energie > ind[i][max(j - 1, 0)] -> getEnergie()) {
                energie -= ind[i][max(j - 1, 0)] -> getEnergie();
                ind[i][max(j - 1, 0)] -> moare();
            }
        }
    }
}

void Individ::imbatraneste() {
    if (varsta < VARTSA_MAX) {
        varsta++;
        energie -= 4;
        if (energie <= 0) {
            moare();
        }
        return;
    }
    moare();
}

void Individ::moare() {
    viu = 0;
}

int Individ::getDistantaDeVarstaMijlocie() {
    //returneaza 4 daca se aflta in jurul varstei mijlocii si scade pana la 0 la varstele minime si maxime
    double procent = double(varsta) / VARTSA_MAX * 100;
    if (procent < 10) {
        return 0;
    } else if (procent < 20) {
        return 1;
    } else if (procent < 30) {
        return 2;
    } else if (procent < 40) {
        return 3;
    } else if (procent < 60) {
        return 4;
    } else if (procent < 70) {
        return 3;
    } else if (procent < 80) {
        return 2;
    } else if (procent < 90) {
        return 1;
    } else {
        return 0;
    }
}

void Individ::actualizeaza() {
    hraneste();
    inmulteste();
    ataca();
    imbatraneste();
}

Individ Individ::operator = (Individ ind) {
    //se face o copie identica
    i = ind.i;
    j = ind.j;
    varsta = ind.varsta;
    tip = ind.tip;
    energie = ind.energie;
    viu = ind.viu;
    tabla = ind.tabla;
    return * this;
}

std::ostream & operator << (std::ostream & out, Individ & ind) {
    if (!ind.viu) {
        out << "Individul este mort." << endl;

    } else if (!ind.tabla) {
        out << "Individul de tipul " << ind.tip << " are " << ind.varsta <<
            " ani si " << ind.energie << " energie si nu apartine de vreo tabla." << endl;
    } else {
        out << "Individul de tipul " << ind.tip << " are " << ind.varsta <<
            " ani si " << ind.energie << " energie si se afla la coordonatele (" << ind.i << "," << ind.j << ")." << endl;
    }
}

std::istream & operator >> (std::istream & in, Individ & ind) {
    in >> ind.tip;
}

Tabla::Tabla() {
    //se creeaza dinamic o matrice de pointeri care se initizlizeaza cu NULL
    indivizi = new Individ ** [INALTIME];
    for (int i = 0; i < INALTIME; i++) {
        indivizi[i] = new Individ * [LATIME];
    }
    for (int i = 0; i < INALTIME; i++) {
        for (int j = 0; j < LATIME; j++) {
            indivizi[i][j] = NULL;
        }
    }
}

Tabla::Tabla(Individ ** * ind) {
    //se creeaza o matrice de pointeri in care se compiaza valorile din argument
    indivizi = new Individ ** [INALTIME];
    for (int i = 0; i < INALTIME; i++) {
        indivizi[i] = new Individ * [LATIME];
    }
    for (int i = 0; i < INALTIME; i++) {
        for (int j = 0; j < LATIME; j++) {
            indivizi[i][j] = ind[i][j];
        }
    }
}

Tabla::~Tabla() {
    delete indivizi;
}

Tabla::Tabla(const Tabla & t) {
    //se creeaza o matrice noua, se copiaza indivizii care sunt in ea si pt fiecare individ se schimba tabla parinte
    this -> indivizi = new Individ ** [INALTIME];
    for (int i = 0; i < INALTIME; i++) {
        this -> indivizi[i] = new Individ * [LATIME];
    }
    for (int i = 0; i < INALTIME; i++) {
        for (int j = 0; j < LATIME; j++) {
            if (t.indivizi[i][j] == 0) {
                this -> indivizi[i][j] = 0;
            } else {
                this -> indivizi[i][j] = new Individ( * t.indivizi[i][j]);
                this -> indivizi[i][j] -> setTabla(this);
            }

        }
    }
}

void Tabla::setIndivizi(Individ ** * ind) {
    indivizi = ind;
}

Individ ** * Tabla::getIndivizi() {
    return indivizi;
}

int Tabla::getInaltime() {
    return INALTIME;
}

int Tabla::getLatime() {
    return LATIME;
}

void Tabla::putIndivid(Individ * ind, int i, int j) {
    //se updateaza campurile corespunzatoare din Individul ind
    ind -> setI(i);
    ind -> setJ(j);
    ind -> setTabla(this);
    indivizi[i][j] = ind;
}

void Tabla::afiseaza() {
    for (int i = 0; i < LATIME + 2; i++) {
        cout << char(196);
    }
    cout << endl << '|';
    for (int i = 0; i < INALTIME; i++) {
        for (int j = 0; j < LATIME; j++) {
            if (indivizi[i][j] == 0) {
                cout << ' ';
            } else {
                cout << indivizi[i][j] -> getTip();
            }
        }
        if (i != INALTIME - 1) {
            cout << '|' << endl << '|';
        } else {
            cout << '|' << endl;
        }
    }
    for (int i = 0; i < LATIME + 2; i++) {
        cout << char(196);
    }
    cout << endl;
}

void Tabla::actualizeaza() {
    //se face un buffer de actualizare pt a evita actualizarea eventualilor fii creati
    int trebuieActualizat[INALTIME][LATIME];
    for (int i = 0; i < INALTIME; i++) {
        for (int j = 0; j < LATIME; j++) {
            if (indivizi[i][j] != 0) {
                trebuieActualizat[i][j] = 1;
            } else {
                trebuieActualizat[i][j] = 0;
            }

        }
    }
    //actulizarea indivzilor originali
    for (int i = 0; i < INALTIME; i++) {
        for (int j = 0; j < LATIME; j++) {
            if (trebuieActualizat[i][j] != 0) {
                indivizi[i][j] -> actualizeaza();
            }
        }
    }
    //se inlatura indivizii morti
    for (int i = 0; i < INALTIME; i++) {
        for (int j = 0; j < LATIME; j++) {
            if (indivizi[i][j] != 0) {
                if (!indivizi[i][j] -> getViu()) {
                    delete indivizi[i][j];
                    indivizi[i][j] = NULL;
                }
            }
        }
    }
}

int Tabla::getAportEnergetic(int i, int j) {
    if (indivizi[i][j] != 0) {
        cout << "Exception: pozitia nu este libera!";
        return 0;
    }
    //aportul energetic = 1 + nr de casute libere
    int ae = 1;
    if (indivizi[max(i - 1, 0)][j] == 0) {
        ae++;
    }
    if (indivizi[i][min(j + 1, LATIME - 1)] == 0) {
        ae++;
    }
    if (indivizi[min(i + 1, INALTIME - 1)][j] == 0) {
        ae++;
    }
    if (indivizi[i][max(j - 1, 0)] == 0) {
        ae++;
    }
    return ae;
}

Tabla Tabla::operator = (Tabla t) {
    //se creeaza o matrice noua, se copiaza indivizii care sunt in ea si pt fiecare individ se schimba tabla parin
    this -> indivizi = new Individ ** [INALTIME];
    for (int i = 0; i < INALTIME; i++) {
        this -> indivizi[i] = new Individ * [LATIME];
    }
    for (int i = 0; i < INALTIME; i++) {
        for (int j = 0; j < LATIME; j++) {
            if (t.indivizi[i][j] == 0) {
                this -> indivizi[i][j] = 0;
            } else {
                this -> indivizi[i][j] = new Individ( * t.indivizi[i][j]);
                this -> indivizi[i][j] -> setTabla(this);
            }

        }
    }
    return * this;
}

std::ostream & operator << (std::ostream & out, Tabla & tabla) {
    tabla.afiseaza();
}

#endif