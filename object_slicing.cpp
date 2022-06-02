#include <iostream>
#include <vector>

class A
{
    int x;

public:
    A(int x=0):x(x){}

    virtual void foo(){std::cout<<"A!";}
    void f_A(){std::cout<<"f_A";}
};

class B : public A
{
    int y;

public:
    B(int x=0, int y=0):A(x), y(y){}

    void foo(){std::cout<<"B!";}
    void f_B(){std::cout<<"f_B";}
};

int main()
{

    A vlad;
    B teo;

    vlad = (A)teo;

    vlad.foo(); 
    // aici apare fenomenul de object-slicing datorita static-linkage ului
    // https://en.wikipedia.org/wiki/Object_slicing

    A* vlad1;
    
    vlad1 = new B(1,2);
    // Alocarea dinamica rezolva aceasta problema datorita dynamic linkage-ului

    /*
        Vtable-ul poate fi "transmis" doar prin alocare dinamica. Alocarea statica
        produce o conversie a vtable-ului la vtable-ul unde se face assignarea 
        si deci si comportamentul f virtuale se pierde.

        Fenomenul de object-slicing are loc insa si la "downcast", in momentul in care
        informatia in plus(nevirtuala) se pierde cand dau cast de la o clasa derivata la
        cea de baza.

        In acest caz, folosirea dynamic_cast - ului previne acest lucru, dar va trebuii
        sa avem mereu un pointer de "gestiune" pentru obiectul ce sufera de "downcast".
    */
    vlad1->foo();

    return 0;
}