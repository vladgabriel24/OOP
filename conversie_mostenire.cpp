#include <iostream>

class CLASA
{

private:
    int x, y;

public:
    CLASA(int x=0, int y=0):x(x), y(y){}

    void functie_baza(){std::cout<<"Functie baza!";}

    virtual void foo(){std::cout<<"Hau!";}

    // virtual ~CLASA();
};

class CLASA1 : public CLASA
{
    int z;

public:
    int k;

    CLASA1(int x=0, int y=0, int z=0):CLASA(x, y), z(z){}

    void functie_clasa1(){std::cout<<"Functie clasa derivata!";}

    void foo(){std::cout<<"Bau!";}
};

int main()
{
    CLASA **p;

    *p = new CLASA1(1,2,3);

    (*p)->
   
   
    /*
        Acest tip de conversie de la o clasa derivata la clasa de baza,
        unde clasa derivata are functii si date membre IN PLUS fata de clasa de baza
        este putin problematica.

        Asta deoarece aceste date suplimentare ce se afla in clasa derivata, in momentul conversiei
        se pierd si deci in pointer-ul p nu mai are acces la int k si functie_clasa1.

        Pentru a rezolva aceasta problema, este necesar IN CLASA DE BAZA sa definim toate aceste
        date membre suplimentare(din clasa derivata).

        Acest fenomen poarta numele de "Downcast"

        "Downcasting is not allowed without an explicit type cast. The reason for this restriction is that the is-a relationship is not, 
        in most of the cases, symmetric. A derived class could add new data members, 
        and the class member functions that used these data members wouldn't apply to the base class."

        Inversul acestui fenomen, de conversie de la o clasa de baza la una derivata
        poarta numele de "Upcast"
    */
    
    return 0;
}