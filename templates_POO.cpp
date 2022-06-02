#include <iostream>

struct Vlad
{
    char nume[20];
};

using vlad = int; // o alta metoda de a redefinii tipuri
                  // alta pe langa typedef

// Template de structura(non tip)
template <int T>
struct Teo
{
    int x = T;
};

Teo<2> h;

// Template cu parametru template
template <template<int> typename teo>
struct Alex
{
    teo<2> y;
};

// Template de variabila(tip)
template <typename T>
T l;

// cu specializarea
template <>
char l<bool>;


// Template de variabila(non tip)
template <int T>
double g = T;

// cu specializarea
template <>
double g<34> = 69;


// Template de functie(non tip)
template <int T>
int foo()
{
    int x = T;

    return x;
}

// cu specializarea
template<>
int foo<3>()
{
    return 4;
}

// Template de functie (tip , dar si cu paramteru template)
template <template<int> typename teo, typename T>
T foo1()
{
    T x = 2.3;

    teo<2> y;

    y.x=5;

    return y.x;
}

// specializarea
template<>
foo1<Teo, int>()
{
    // ATENTIE: In momentul in care incerc sa specializez o functie
    // si unul din parametrii template-ului specializat modifica tipul functiei
    // ca template-ul initial sa fie recunoscut, trebuie ca ce specializez eu
    // sa aiba acelasi tip cu ce returneaza functia din sablonul specializat

    /*
        Asta deoarece cand modific tipul functiei, compilatorul va cauta in memorie
        o functie de tipul specificat de mine care RETURNEAZA o variabila de acel tip

        Daca eu in template-ul initial, returnez o variabila de alt tip decat tipul functiei 
        specializat, acel template nu va fii gasit de compilator
    */

    std::cout<<"T\n";
}

// Template de functie(tip)
template<typename T>
T foo2()
{
    std::cout<<"A\n";

    return 1;
}

// specializarea
template<>
foo2<int>()
{
    std::cout<<"B\n";

    int x=2;

    return 1;
}

// template <auto T>
// struct Mihai
// {
//     auto x = T;
// };

// NU este permis asa ceva!

/*
    Motivatia utilizarii keyword-ului "typename":

    Ca si la namespace-uri sau clase, cand vrem sa ne referim la o data exact din acel "scope", folosim operatorul de rezolutie "::".
    Acest operator are ca sintaxa "scope" :: "variabila".

    Problema intervine in momentul in care avem "scope-uri" imbricate, deoarece compilatorul nu stie care este scope-ul si care este variabila.
    De ex:

    A::B *p - aici compilatorul poate sa interpreteze ca o variabila B din scope-ul a , inmultita cu variabila p. Ceea ce este gresit.
    Noi aici vrem, de fapt, sa declaram un pointer la un TIP DE DATA A::B.

    Aici intervine keyword-ul "typename". Cand il folosim, compilatorul stie clar ca dupa ce scriem "typename" si dam un spatiu,
    tot ce va urma sa scriem pana la urmatorul spatiu va insemna UN TIP DE DATA. Ce se va afla la urmatorul spatiu va insemna o variabila.

    Asadar, pentru exemplul de mai sus, ca sa fie corect, voi scrie typename A::B* p.

    In mare, cam aceasta este si diferenta dintre keyword-ul "class" si "typename". "Class" defineste un tip de date definit de utilizator,
    iar typename LA FEL, numai ca ajuta mai mult compilatorul in momentul in care folosim operatorii de rezolutie pentru "scope"-uri imbricate.
*/

int main()
{
    return 0;
}