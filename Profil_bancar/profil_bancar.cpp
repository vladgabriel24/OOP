#include <iostream>

class UI_Profil
{

protected:

    std::string nume;
    std::string instrument_1;
    std::string instrument_2;

    float suma_card;
    float suma_econ;

    float dobanda;

public:

    virtual void afisare() = 0;
    virtual void transfer(float) = 0;
    // virtual int acumul_dobanda() = 0;

    virtual std::string get_nume() = 0;
    virtual void set_nume(std::string nume) = 0;

    virtual std::string get_instrument_1() = 0;
    virtual void set_instrument_1(std::string instrument_1) = 0;

    virtual std::string get_instrument_2() = 0;
    virtual void set_instrument_2(std::string instrument_2) = 0;

    virtual float get_suma_card() = 0;
    virtual void set_suma_card(float suma) = 0;

    virtual float get_suma_econ() = 0;
    virtual void set_suma_econ(float suma) = 0;

    virtual float get_dobanda() = 0;
    virtual void set_dobanda(float dobanda) = 0;

    virtual void foo(){std::cout<<"a";}
};

class Profil: private UI_Profil
{

// Cand mostenesc o clasa abstracta, se vor mostenii
// doar functiile FALS

// ele se mostenesc, dar nu pot folosii o lista de initializare
// pentru o clasa derivata deoarece variabilele, pana in momentul
// intrarii in ctor nu au fost mostenite, deci nu vor fi recunoscute de compilator

// Mostenirea dintr-o clasa abstracta este private orice as declara eu!
// Asadar, voi declara explicit datele membre de tip protected

protected:

    std::string nume;
    std::string instrument_1;
    std::string instrument_2;

    float suma_card;
    float suma_econ;

    float dobanda;

public:

    Profil( std::string nume = "", 
            std::string instrument_1 = "",
            std::string instrument_2 = "",
            float suma_card = 0.0f,
            float suma_econ = 0.0f,
            float dobanda = 0.0f
            ):  nume(nume),
                instrument_1(instrument_1),
                instrument_2(instrument_2),
                suma_card(suma_card),
                suma_econ(suma_econ),
                dobanda(dobanda){}

    std::string get_nume (){return nume;}
    void set_nume(std::string nume){this->nume = nume;}

    std::string get_instrument_1(){return instrument_1;}
    void set_instrument_1(std::string instrument_1){this->instrument_1 = instrument_1;}

    std::string get_instrument_2(){return instrument_2;}
    void set_instrument_2(std::string instrument_2){this->instrument_2 = instrument_2;}

    float get_suma_card(){return suma_card;}
    void set_suma_card(float suma){this->suma_card = suma;}

    float get_suma_econ(){return suma_econ;}
    void set_suma_econ(float suma){this->suma_econ = suma;}

    float get_dobanda(){return dobanda;}
    void set_dobanda(float dobanda){this->dobanda = dobanda;}

    void afisare()
    {
        std::cout<<nume<<'\n';
        std::cout<<instrument_1<<'\n';
        std::cout<<suma_card<<'\n';
        std::cout<<instrument_2<<'\n';
        std::cout<<suma_econ<<'\n';
        std::cout<<dobanda<<'\n';
    }

    void transfer(float suma)
    {
        if(suma > suma_card)
        {
            std::cout<<"EROARE:fonduri insuficiente\n";
            exit(0);
        }

        this->suma_card -= suma;
        this->suma_econ += suma;

        // aplicarea dobanzii
        this->suma_econ += (this->suma_econ * dobanda)/100;

    }

    void foo2(){std::cout<<"b";}
};

class Card: protected Profil
{

/*
    De data aceasta, nu este nevoie sa folosesc o mostenire de tip virtual
    deoarece NU sunt in cazul mostenirii "multipath".
    Acesta este cazul mostenirii ierarhice.

    Mostenirea multipath are loc in momentul in care, de ex,
    mai am o clasa Conturi si care mosteneste, in cazul meu,
    ambele clase Economii si Card.

    In momentul in care se mosteneste in acest mod, clasa Conturi
    va instantia o legatura cu clasa Economii care instantiaza o legatura cu clasa Profil
    apoi se va instantia inca o legatura cu clasa Card care instantiaza o legatura cu clasa Profil.

    Astfel , clasa Conturi va avea cate 2 copii pt fiecare data membra a clasei Profil.

    Ca sa remediem acest lucru, folosim mostenirea virtuala, adica ne folosim de v_table
    ca sa stocam un pointer catre clasa Profil care va fii "impartasit" cu toate clasele
    derivate si care va "da acces"(adica v_table ul va oferii o copie primei clase derivate
    ca mai apoi urmatoarele clase derivate , vor accesa prin v_table acele copii din clasa derivata initial)
    tuturor derivatelor catre datele membre ale clasei Profil si astfel nu se vor mai creea 2 copii 
    si se va folosii doar un singur set de variabile.

    Aici nu este cazul de asa ceva, deoarece eu nu am o a 3a clasa de tip Conturi.
    Eu am 2 clase care deriva din una singura si(in mod clar este necesar) ca clasele
    mele sa aiba fiecare cate o copie a datelor membre ale clasei de baza(deoarece nu exista
    nicio legatura intre cele 2 clase derivate).

    Daca as fii "legat" aceste clase intre ele cu o clasa de tip COnturi, atunci da, am mostenire multipath
    si voi avea nevoie de o singura copie ale clasei cele mai de baza.
*/

public:

    Card(float suma)
    {
        /*
            Daca mostenesc clasa Profil, ea nefiind clasa abstracta,
            de data aceasta voi mostenii toate datele membre dar,
            nu pot folosii o lista de initializare unde accesez datele membre
            mostenite.
            Asta se intampla deoarece, la momentul parcurgerii listei de initializare
            doar datele membre ale clasei in sine sunt vizibile, nu si cele mostenite
            deoarece cele mostenite devin vizibile abia dupa ce se intra in ctor
            si in restul functiilor membre. CU alte cuvinte, datele membre ce le 
            mostenesc "nu sunt gata" in momentul folosirii listei de initializare,
            ci dupa.
        */

        this->nume = "";
        this->instrument_1 = "card_bancar";
        this->instrument_2 = "";
        this->suma_card = suma;
        this->suma_econ = 0.0f;
        this->dobanda = 0.0f;
    }

    void afisare() override
    {
        std::cout<<this->instrument_1<<"\n";
        std::cout<<suma_card<<"\n";
    }

    void depunere_bani(float suma)
    {
        if(suma < 0)
        {
            std::cout<<"EROARE: depunere suma negativa\n";
            exit(0);
        }
        this->suma_card += suma;

    }

    void extragere_bani(float suma)
    {
        if(suma > this->suma_card)
        {
            std::cout<<"EROARE: fonduri insuficiente\n";
            exit(0);
        }

        this->suma_card -= suma;
    }
};

class Economii: protected Profil
{


public:

    Economii(float suma, float dobanda)
    {
        this->nume = "";
        this->instrument_1 = "";
        this->instrument_2 = "cont_economii";
        this->suma_card = 0.0f;
        this->suma_econ = suma;
        this->dobanda = dobanda;
    }

    void aplicare_dobanda(){suma_econ += suma_econ*dobanda/100;}

    void afisare()
    {
        std::cout<<this->instrument_2<<"\n";
        std::cout<<suma_econ<<"\n";
        std::cout<<dobanda<<"\n";
    }

    int acumulare_dobanda(float suma)
    {
        int counter=0;
        float tmp = suma_econ;
        while(tmp <= suma)
        {
            tmp += (tmp*dobanda)/100;
            counter++;
        }

        return counter;
    }
};

int main()
{
    std::string detinator;
    float sold_card, sold_econ, dobanda;

    int test;

    getline(std::cin, detinator);
    std::cin>>sold_card>>sold_econ>>dobanda;

    Profil vlad(detinator,
                    "card_bancar",
                    "cont_economii",
                    sold_card,
                    sold_econ,
                    dobanda);
    
    Card visa(sold_card);
    Economii ron(sold_econ, dobanda);

    std::cin>>test;

    if(test == 1)
    {
        vlad.afisare();
        // vlad.foo(); 
        // clasa Profil nu poate accesa nimic din clasa UI_Profil
        // daca am nevoie de ceva din clasa UI_Profil, acel ceva trebuie sa fie pur virtual
        // si dupa sa il redefinesc in clasa Profil
    }

    if(test == 2)
    {
        float depunere;
        std::cin>>depunere;

        visa.depunere_bani(depunere);

        visa.afisare();
    }

    if(test == 3)
    {
        float extragere;
        std::cin>>extragere;

        visa.extragere_bani(extragere);
        ron.aplicare_dobanda();

        visa.afisare();
        ron.afisare();
    }

    if(test == 4)
    {
        float suma_transfer;
        std::cin>>suma_transfer;

        vlad.transfer(suma_transfer);

        vlad.afisare();

        std::cout<<'\n';
    }

    if(test == 5)
    {
        float suma_tinta;
        std::cin>>suma_tinta;

        std::cout<<ron.acumulare_dobanda(suma_tinta);
    }

    return 0;
}