#include "game.h"

void testIndividConstructors() {
    Tabla t1, * t2;
    Individ i1, i2('#'), i3(3, 7, '`', t1), i4(10, 20, '$', t2);
    cout << i1 << i2 << i3 << i4;
}

void testIndividGettersAndGetters() {
    Individ i, j;
    i.setI(10);
    i.setJ(10);
    i.setTip('*');
    cout << "coord = " << i.getI() << ' ' << i.getJ() << " energeie = " << i.getEnergie() << endl;
    j = i;
    cout << j;
}

void testTabla() {
    Tabla t1, t2;
    t2.putIndivid(new Individ('#'), 7, 10);
    Tabla tab(t1.getIndivizi());
    cout << tab;
    tab.setIndivizi(t2.getIndivizi());
    cout << tab;
    t1 = t2;
    cout << t1;
}