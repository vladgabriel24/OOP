#include <iostream>

class Baza_abs
{
private:
    int x;
    int y;

    
public:
    Baza_abs(int x = 0):x(x){}
    virtual void functie_baza(){std::cout<<"aaa";}
    void functie_vlad(){std::cout<<"123!";}

};

class Vlad : public Baza_abs
{
private:
    int y;

public:
    Vlad(int x=0, int y=0):Baza_abs(x), y(y){}
    void functie_baza(){std::cout<<"Vlad!";}
    void functie_vlad(){std::cout<<"Masina!";}
    void foo(){std::cout<<"sdasda";}
};

int main()
{
    // downcast => pierd informatia din clasa derivata
    Baza_abs *p = new Vlad(1,2);

    // upcast => castig informatia din clasa derivata
    Vlad *q = (Vlad*)p;

    q->foo();

    /*
        Vezi:
        https://stackoverflow.com/questions/23414090/what-is-the-difference-between-up-casting-and-down-casting-with-respect-to-class
    */
    
    return 0;
}