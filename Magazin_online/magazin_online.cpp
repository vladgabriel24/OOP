#include <iostream>

class Produs
{

private:

    std::string denumire;
    float pret;

public:

    Produs(std::string nume="", float pret=0.0f)
    :denumire(nume), pret(pret){}

    void afisare()
    {
        std::cout<<denumire<<'\n'<<pret<<'\n';
    }

    std::string get_denumire(){return this->denumire;}

    float get_pret(){return this->pret;}
};

class Magazin
{

private:

    Produs* V[10];
    int stocuri[10];
    int nr_produse;

public:

    /*
        !!!

        Cand avem deaface cu pointeri sau referinte, citirea referintelor/pointerilor
        se face de la stanga la dreapta!

        Adica:

        int* = pointer de tip int
        int*& = referinta la un pointer de tip int
        int*&* = pointer de tip referinta la un pointer de tip int

        int& = referinta la un int
        int&* = pointer de tip referinta la un int(CEEA CE ESTE ILEGAL IN C++,
        deoarece referinta reprezinta doar un "alias" al unei variabile,
        ei nu i se creeaza o adresa de memorie la declarare!)
        int&*& = referinta la un pointer de tip referinta de tip int(ILEGAL de asemenea)

        Dat fiind ca simbolurile de referinta sau pointer au legatura cu TIPUL variabilei,
        este mai bine sa grupam aceste simboluri cu tipul tipul de baza al variabilei
        si numele variabilei scris dupa un space.
    */

    Magazin(Produs* V[], int stocuri[], int& nr_produse)
    :nr_produse(nr_produse)
    {
        for(int i=0; i<nr_produse; i++) this->V[i] = new Produs(V[i]->get_denumire(), V[i]->get_pret());

        for(int i=0; i<nr_produse; i++) this->stocuri[i] = stocuri[i];
    }

    void afisare()
    {
        for(int i=0; i<nr_produse; i++)
        {
            if(stocuri[i])
            {
                V[i]->afisare();
                std::cout<<stocuri[i]<<'\n';
            }
        }
    }

    int get_stoc_by_name(std::string name)
    {
        for(int i=0; i<nr_produse; i++) if(V[i]->get_denumire() == name) return stocuri[i];

        return -1;
    }

    float get_pret_by_name(std::string name)
    {
        for(int i=0; i<nr_produse; i++) if(V[i]->get_denumire() == name) return V[i]->get_pret();

        return -1.0f;
    }
};

class Cos
{

private:

    Produs *V[10];
    int cantitati[10];
    int nr_produse;

public:

    Cos(Produs* V[], int cantitati[], int nr_produse=0)
    :nr_produse(nr_produse)
    {
        for(int i=0; i<nr_produse; i++) this->V[i] = new Produs(V[i]->get_denumire(), V[i]->get_pret());

        for(int i=0; i<nr_produse; i++) this->cantitati[i] = cantitati[i];
    }

    float total(Magazin &mega)
    {
        float sum = 0.0f;
        for(int i=0; i<nr_produse; i++)
            sum+=cantitati[i]*V[i]->get_pret();

        return sum;
    }

    float get_pret_cos_by_index(int index)
    {
        return V[index]->get_pret();
    }

    int get_nr_produse(){return nr_produse;}

    int get_cantitati_by_index(int index){return cantitati[index];}
};

class Reducere
{

    float procent;
    float high, low;

public:

    Reducere(float procent = 0.0f, float high = 0.0f, float low = 0.0f)
    :procent(procent), high(high), low(low){}

    float get_procent(){return procent;}
    float get_high(){return high;}
    float get_low(){return low;}
};

class Cupoane
{

    Reducere *coduri[10];
    int nr_reduceri;

public:

    Cupoane(Reducere *coduri[], int nr_reduceri = 0)
    :nr_reduceri(nr_reduceri)
    {
        for(int i=0; i<nr_reduceri; i++)
        {
            this->coduri[i] = new Reducere(coduri[i]->get_procent(), coduri[i]->get_high(), coduri[i]->get_low());
        }
    }

    float utilizare_cod(Cos &vlad, int index)
    {
        float reduc=0;

        for(int i=0; i<vlad.get_nr_produse(); i++)
        {
            if(coduri[index]->get_high() >= vlad.get_pret_cos_by_index(i) && vlad.get_pret_cos_by_index(i) >= coduri[index]->get_low())
            {
                reduc += (vlad.get_pret_cos_by_index(i)*vlad.get_cantitati_by_index(i))*(coduri[index]->get_procent()/100);
            }
        }
        return reduc;
    }

    float cod_singular(Cos &vlad)
    {
        float maxim = 0;
        float reduc;
        for(int i=0; i<nr_reduceri; i++)
        {
            for(int j=0; j<vlad.get_nr_produse(); j++)
            {
                if(coduri[i]->get_high() >= vlad.get_pret_cos_by_index(j) && vlad.get_pret_cos_by_index(j) >= coduri[i]->get_low())
                {
                    reduc = vlad.get_pret_cos_by_index(j)*((float)coduri[i]->get_procent()/100);

                    if(reduc*vlad.get_cantitati_by_index(j) > maxim)
                    {
                        maxim = reduc*vlad.get_cantitati_by_index(j);
                    }
                }
            }
        }

        return maxim;
    }

    float coduri_per_produs(Cos &vlad)
    {
        int maxim=0;
        float reduc;
        float maxim_total=0;

        for(int i=0; i<vlad.get_nr_produse(); i++)
        {
            maxim=0;
            for(int j=0; j<nr_reduceri; j++)
            {
                if(coduri[j]->get_high() >= vlad.get_pret_cos_by_index(i) && vlad.get_pret_cos_by_index(i) >= coduri[j]->get_low())
                {
                    reduc = vlad.get_pret_cos_by_index(i)*((float)coduri[j]->get_procent()/100);

                    if(reduc*vlad.get_cantitati_by_index(i) > maxim) 
                    {
                        maxim = reduc*vlad.get_cantitati_by_index(i);
                    }
                }
            }
            maxim_total+=maxim;
        }
        return maxim_total;
    }
};

int main()
{
    std::string denumire;
    float pret;
    int nr_produse;
    int nr_produse_magazin=0;

    int comanda;

    Produs *input[10];
    int stocuri[10];

    while(true)
    {
        getline(std::cin, denumire);
        if(denumire == "STOP") {denumire=""; break;}

        std::cin>>pret>>nr_produse;
        std::cin.get();

        input[nr_produse_magazin] = new Produs(denumire, pret);
        stocuri[nr_produse_magazin] = nr_produse;

        nr_produse_magazin++;
    }

    Magazin mega(input, stocuri, nr_produse_magazin);

    std::cin>>comanda;

    if(comanda == 1) mega.afisare();
    if(comanda == 2)
    {
        Produs *input_cos[10];
        int produse_cos[10];

        int nr_produse_cos=0;
        while(true)
        {
            std::cin.get();
            getline(std::cin, denumire);
            if(denumire == "STOP") {denumire=""; break;}

            std::cin>>nr_produse;

            if(nr_produse > mega.get_stoc_by_name(denumire))
            {
                std::cout<<"Produsul "<<denumire<<" mai are doar "<<mega.get_stoc_by_name(denumire)<<" bucati in stoc\n";
                exit(0);
            }

            input_cos[nr_produse_cos] = new Produs(denumire, mega.get_pret_by_name(denumire));
            produse_cos[nr_produse_cos] = nr_produse;

            nr_produse_cos++;
        }

        Cos vlad(input_cos, produse_cos, nr_produse_cos);

        std::cout<<"Total de plata\n";
        std::cout<<vlad.total(mega)<<'\n';
    }

    if(comanda == 3)
    {
        Reducere *coduri[10];

        int nr_coduri_reducere = 1;
        float procent, high, low;

        for(int i=0; i<nr_coduri_reducere; i++)
        {
            std::cin>>procent;
            std::cin>>low;
            std::cin>>high;
            coduri[i] = new Reducere(procent, high, low);
        }

        Cupoane X(coduri, nr_coduri_reducere);

        Produs *input_cos[10];
        int produse_cos[10];

        int nr_produse_cos=0;
        while(true)
        {
            std::cin.get();
            getline(std::cin, denumire);
            if(denumire == "STOP") {denumire=""; break;}

            std::cin>>nr_produse;

            if(nr_produse > mega.get_stoc_by_name(denumire))
            {
                std::cout<<"Produsul "<<denumire<<" mai are doar "<<mega.get_stoc_by_name(denumire)<<" bucati in stoc\n";
                exit(0);
            }

            input_cos[nr_produse_cos] = new Produs(denumire, mega.get_pret_by_name(denumire));
            produse_cos[nr_produse_cos] = nr_produse;

            nr_produse_cos++;
        }

        Cos vlad(input_cos, produse_cos, nr_produse_cos);

        if(!X.utilizare_cod(vlad, nr_coduri_reducere-1))
        {
            std::cout<<"Niciun produs nu e eligibil pentru reducere\n";
            std::cout<<"Total de plata\n";
            std::cout<<vlad.total(mega)<<'\n';
        }
        else std::cout<<"Total de plata\n"<<vlad.total(mega)-X.utilizare_cod(vlad, nr_coduri_reducere-1)<<'\n';
    }

    if(comanda == 4)
    {
        Reducere *coduri[10];

        int nr_coduri_reducere = 3;
        float procent, high, low;

        for(int i=0; i<nr_coduri_reducere; i++)
        {
            std::cin>>procent;
            std::cin>>low;
            std::cin>>high;
            coduri[i] = new Reducere(procent, high, low);
        }

        Cupoane X(coduri, nr_coduri_reducere);

        Produs *input_cos[10];
        int produse_cos[10];

        int nr_produse_cos=0;
        while(true)
        {
            std::cin.get();
            getline(std::cin, denumire);
            if(denumire == "STOP") {denumire=""; break;}

            std::cin>>nr_produse;

            if(nr_produse > mega.get_stoc_by_name(denumire))
            {
                std::cout<<"Produsul "<<denumire<<" mai are doar "<<mega.get_stoc_by_name(denumire)<<" bucati in stoc\n";
                exit(0);
            }

            input_cos[nr_produse_cos] = new Produs(denumire, mega.get_pret_by_name(denumire));
            produse_cos[nr_produse_cos] = nr_produse;

            nr_produse_cos++;
        }

        Cos vlad(input_cos, produse_cos, nr_produse_cos);

        if(!X.cod_singular(vlad)) std::cout<<"Niciun produs nu e eligibil pentru reducere\n";

        std::cout<<"Total de plata\n";
        std::cout<<vlad.total(mega) - X.cod_singular(vlad)<<'\n';
    }

    if(comanda == 5)
    {
        Reducere *coduri[10];

        int nr_coduri_reducere = 3;
        float procent, high, low;

        for(int i=0; i<nr_coduri_reducere; i++)
        {
            std::cin>>procent;
            std::cin>>low;
            std::cin>>high;
            coduri[i] = new Reducere(procent, high, low);
        }

        Cupoane X(coduri, nr_coduri_reducere);

        Produs *input_cos[10];
        int produse_cos[10];

        int nr_produse_cos=0;
        while(true)
        {
            std::cin.get();
            getline(std::cin, denumire);
            if(denumire == "STOP") {denumire=""; break;}

            std::cin>>nr_produse;

            if(nr_produse > mega.get_stoc_by_name(denumire))
            {
                std::cout<<"Produsul "<<denumire<<" mai are doar "<<mega.get_stoc_by_name(denumire)<<" bucati in stoc\n";
                exit(0);
            }

            input_cos[nr_produse_cos] = new Produs(denumire, mega.get_pret_by_name(denumire));
            produse_cos[nr_produse_cos] = nr_produse;

            nr_produse_cos++;
        }

        Cos vlad(input_cos, produse_cos, nr_produse_cos);

        std::cout<<vlad.total(mega)<<'\n';
        std::cout<<"Total de plata\n";
        std::cout<<vlad.total(mega) - X.coduri_per_produs(vlad)<<'\n';
    }
    return 0;
}