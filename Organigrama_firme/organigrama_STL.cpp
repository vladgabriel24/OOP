#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Angajat
{
protected:
    std::string nume;
    float salariu_baza;
    std::string functie;
    float procent_taxe_salariu;

    // Date Programator
    float procent_deducere_salariu;

    // Date LiderEchipaProgramare
    float bonus_vechime_functie;
    int vechime_functie;

public:
    Angajat(std::string nume="", float salariu_baza=0.0f, std::string functie="", float procent_taxe_salariu=0.0f
    , float procent_deducere_salariu=0.0f, float bonus_vechime_functie=0.0f, int vechime_functie = 0)
    :nume(nume), salariu_baza(salariu_baza), functie(functie), procent_taxe_salariu(procent_taxe_salariu)
    , procent_deducere_salariu(procent_deducere_salariu), bonus_vechime_functie(bonus_vechime_functie), vechime_functie(vechime_functie){}

    virtual float get_salariu_net(float tmp){return -1.0f;}
    virtual float get_salariu_brut(){return -1.0f;}
    std::string get_nume(){return nume;}
    std::string get_functie(){return functie;}
    void marire_salariu(float procent)
    {
        std::cout<<"Salariu de baza vechi: "<<salariu_baza<<'\n';
        salariu_baza += (procent/100)*salariu_baza;
        std::cout<<"Salariu de baza nou: "<<salariu_baza<<'\n';
    }

    virtual ~Angajat(){std::cout<<"Destructor Angajat\n";}
};

class Analist:public Angajat
{

public:
    Analist(std::string nume="", float salariu_baza=0.0f, std::string functie="", float procent_taxe_salariu=0.0f
    , float procent_deducere_salariu=0.0f, float bonus_vechime_functie=0.0f, int vechime_functie = 0)
    :Angajat(nume, salariu_baza, functie, procent_taxe_salariu, procent_deducere_salariu, bonus_vechime_functie, vechime_functie){}

    float get_salariu_brut(){return salariu_baza;}
    float get_salariu_net(float tmp){return salariu_baza * (100-procent_taxe_salariu)/100;}

    ~Analist(){std::cout<<"Destructor Analist\n";}
};

class Programator:public Analist
{

public:
    Programator(std::string nume="", float salariu_baza=0.0f, std::string functie="", float procent_taxe_salariu=0.0f
    , float procent_deducere_salariu=0.0f, float bonus_vechime_functie=0.0f, int vechime_functie = 0)
    :Analist(nume, salariu_baza, functie, procent_taxe_salariu, procent_deducere_salariu, bonus_vechime_functie, vechime_functie){}

    float get_salariu_brut(){return salariu_baza;}
    float get_salariu_net(float tmp){return salariu_baza * (100-procent_taxe_salariu+procent_deducere_salariu)/100;}

    ~Programator(){std::cout<<"Destructor Programator\n";}
};

class LiderEchipaProgramare:public Programator
{

public:
    LiderEchipaProgramare(std::string nume="", float salariu_baza=0.0f, std::string functie="", float procent_taxe_salariu=0.0f
    , float procent_deducere_salariu=0.0f, float bonus_vechime_functie=0.0f, int vechime_functie = 0)
    :Programator(nume, salariu_baza, functie, procent_taxe_salariu, procent_deducere_salariu, bonus_vechime_functie, vechime_functie){}

    float get_salariu_brut(){return (salariu_baza + bonus_vechime_functie*vechime_functie);}
    float get_salariu_net(float tmp){return (salariu_baza + bonus_vechime_functie*vechime_functie) * (100-procent_taxe_salariu+procent_deducere_salariu)/100;}

    ~LiderEchipaProgramare(){std::cout<<"Destructor LiderEchipaProgramare\n";}
};

class FirmaProgramare
{
    std::vector<Angajat*> V;

public:
    FirmaProgramare(std::vector<Angajat*> V = std::vector<Angajat*>(0)):V(V){}

    void afiseaza_angajati()
    {
        for(auto& i : V)
        {
            std::cout<<i->get_nume()<<'\n';
            std::cout<<i->get_functie()<<'\n';
        }
    }

    void afiseaza_salarii()
    {
        for(auto& i : V)
        {
            std::cout<<i->get_nume()<<'\n';
            std::cout<<"Salariu brut: "<<i->get_salariu_brut()<<'\n';
            std::cout<<"Salariu Net: "<<i->get_salariu_net(0.0f)<<'\n';
        }
    }

    void mareste_salarii(float analist, float programator, float lider_programare)
    {
        for(auto& i : V)
        {
            if(i->get_functie() == "Analist") {std::cout<<i->get_nume()<<'\n'; i->marire_salariu(analist);}
            if(i->get_functie() == "Programator") {std::cout<<i->get_nume()<<'\n'; i->marire_salariu(programator);}
            if(i->get_functie() == "LiderEchipaProgramare") {std::cout<<i->get_nume()<<'\n'; i->marire_salariu(lider_programare);}
        }
    }
    void promoveaza(std::string nume, std::string functie)
    {
        Angajat* tmp;
        for(auto& i : V)
        {
            if(i->get_nume() == nume)
            {
                if(functie == "Analist")
                {
                    tmp = new Angajat(i->get_nume(), 0.0f, functie);
                    delete i;
                    i = new Analist(tmp->get_nume(), 0.0f, functie);
                }

                if(functie == "Programator")
                {
                    tmp = new Angajat(i->get_nume(), 0.0f, functie);
                    delete i;
                    i = new Programator(tmp->get_nume(), 0.0f, functie);
                }

                if(functie == "LiderEchipaProgramare")
                {
                    tmp = new Angajat(i->get_nume(), 0.0f, functie);
                    delete i;
                    i = new LiderEchipaProgramare(tmp->get_nume(), 0.0f, functie);
                }
                break;  
            }
        }
    }

};

int main()
{
    int nr_angajati;
    std::cin>>nr_angajati;
    std::cin.ignore(1);

    std::vector<Angajat*> V;

    std::string nume;
    std::string functie;
    float salariu_baza;
    int vechime;

    Angajat* p;

    for(int i=0 ; i<nr_angajati; i++)
    {
        getline(std::cin, nume);
        std::cin>>functie;
        std::cin>>salariu_baza;
        std::cin.ignore(1);

        if(functie == "Analist")
        {
            p = new Analist(nume, salariu_baza, functie, 40);

            V.push_back(p);
        }
        if(functie == "Programator")
        {
            p = new Programator(nume, salariu_baza, functie, 40, 10);

            V.push_back(p);
        }
        if(functie == "LiderEchipaProgramare")
        {
            std::cin>>vechime;
            std::cin.ignore(1);
            p = new LiderEchipaProgramare(nume, salariu_baza, functie, 40, 10, vechime, 500);

            V.push_back(p);
        }
    }

    FirmaProgramare *vlad = new FirmaProgramare(V);

    int comanda;
    std::cin>>comanda;
    std::cin.ignore(1);

    if(comanda == 1)
    {
        vlad->afiseaza_angajati();
    }

    if(comanda == 2)
    {
        vlad->afiseaza_salarii();
    }

    if(comanda == 3)
    {
        int analist, programator, lider;
        
        std::cin>>functie;
        std::cin>>analist;

        std::cin>>functie;
        std::cin>>programator;

        std::cin>>functie;
        std::cin>>lider;

        vlad->mareste_salarii(analist, programator, lider);
    }

    if(comanda == 4)
    {
        getline(std::cin, nume);
        std::cin>>functie;

        vlad->promoveaza(nume, functie);
        vlad->afiseaza_angajati();
    }

    return 0;
}