#include <iostream>
#include <vector>

class Card_calatorie
{
protected:
    int id_card;
    int moment_validare;

    int sold_card;
    int nr_calatorii;

public:
    Card_calatorie(int id_card = 0, int sold_card=0, int nr_calatorii=0, int moment_validare=0)
    :id_card(id_card), sold_card(sold_card), nr_calatorii(nr_calatorii), moment_validare(moment_validare){}

    virtual void display()
    {
        std::cout<<id_card;
    }

    virtual int get_id(){return id_card;}

    virtual void incr_val(int val){};
    virtual char get_tip(){return 0;}
    
    int get_moment_validare(){return moment_validare;}
    int get_sold_card(){return sold_card;}
    int get_nr_calatorii(){return nr_calatorii;}

    void set_moment_validare(int val){moment_validare = val;}

};

class Card_autobuz: public Card_calatorie
{

public:
    Card_autobuz(int id_card=0, int sold_card=0, int moment_validare=0)
    :Card_calatorie(id_card, sold_card, 0, moment_validare){}

    virtual void display()
    {
        std::cout<<id_card<<' '<<"a "<<sold_card<<' '<<moment_validare<<'\n';
    }

    int get_id(){return id_card;}

    void incr_val(int val){sold_card += val;}

    char get_tip(){return 'a';}

};


class Card_metrou: public Card_calatorie
{

public:
    Card_metrou(int id_card=0, int nr_calatorii=0, int moment_validare=0)
    :Card_calatorie(id_card, 0, nr_calatorii, moment_validare){}

    virtual void display()
    {
        std::cout<<id_card<<' '<<"m "<<nr_calatorii<<' '<<moment_validare<<'\n';
    }

    int get_id(){return id_card;}

    void incr_val(int val){nr_calatorii += val;}

    char get_tip(){return 'm';}
};

class Carduri
{

private:
    int nr_carduri;
    std::vector<Card_calatorie*> V;

public:

    Carduri(std::vector<Card_calatorie*> v, int nr_carduri)
    :nr_carduri(nr_carduri)
    {
        V = v;
    }

    void afisare()
    {
        for(int i=0; i<nr_carduri; i++)
        {
            V[i]->display();
        }
    }

    void incarcare_card(int id, int val)
    {
        for(int i=0; i<nr_carduri; i++)
        {
            if(V[i]->get_id() == id)
            {
                V[i]->incr_val(val);
                break;
            }
        }
    }

    void validare(int id, int moment)
    {
        for(auto i : V)
        {
            if(i->get_id() == id)
            {
               if(i->get_tip() == 'a')
               {
                    if(i->get_moment_validare() == 0 || (moment - i->get_moment_validare()) >=90)
                    {
                        if(i->get_sold_card() >= 3){i->incr_val(-3); i->set_moment_validare(moment);}
                        else
                        {
                            std::cout<<"Sold insuficient\n";
                            break;
                        }
                    }
               }

               if(i->get_tip() == 'm')
               {
                    if(i->get_moment_validare() == 0 || (moment - i->get_moment_validare()) >=90)
                    {
                        if(i->get_nr_calatorii() >= 1){i->incr_val(-1); i->set_moment_validare(moment);}
                        else
                        {
                            std::cout<<"Numar calatorii insuficient\n";
                            break;
                        }
                    }
               }
            }
        }
    }

    void transfer(int id1, int id2, int val)
    {
        int index1=0, index2=0;

        for(int i=0; i<nr_carduri; i++)
        {
            if(V[i]->get_id() == id1)
            {
                index1 = i;
                break;
            }
        }

        for(int i=0; i<nr_carduri; i++)
        {
            if(V[i]->get_id() == id2)
            {
                index2 = i;
                break;
            }
        }

        if(V[index1]->get_tip() == V[index2]->get_tip())
        {
            if(V[index1]->get_tip() == 'm')
            {
                if(V[index1]->get_nr_calatorii() >= val)
                {
                    V[index1]->incr_val(-val);
                    V[index2]->incr_val(val);
                }
                else std::cout<<"Transfer nereusit\n";
            }

            if(V[index1]->get_tip() == 'a')
            {
                if(V[index1]->get_sold_card() >= val)
                {
                    V[index1]->incr_val(-val);
                    V[index2]->incr_val(val);
                }
                else std::cout<<"Transfer nereusit\n";
            }
        }
        else std::cout<<"Transfer nereusit\n";
    }
};


int main()
{
    int n;

    char tip;
    int id;
    int sold;
    int nr_calatorii;
    int moment_validare;

    int val;

    int comanda;

    std::cin>>n;
    std::vector<Card_calatorie*> vlad(n);

    // citire date
    auto it = vlad.begin();
    for(int i=0; i<n; i++)
    {
        std::cin>>tip;
        std::cin>>id;
        if(tip == 'a')
        {
            std::cin>>sold;
            *(it+i) = new Card_autobuz(id, sold, 0);
        }

        if(tip == 'm')
        {
            std::cin>>nr_calatorii;
            *(it+i) = new Card_metrou(id, nr_calatorii, 0);
        }
    }

    vlad.shrink_to_fit(); // o prostie

    Carduri Vlad(vlad, n);

    while(true)
    {
        std::cin>>comanda;

        if(comanda == 1)
        {
            Vlad.afisare();
        }

        if(comanda == 2)
        {
            std::cin>>id;
            std::cin>>val;

            Vlad.incarcare_card(id,val);
        }

        if(comanda == 3)
        {
            std::cin>>id;
            std::cin>>moment_validare;

            Vlad.validare(id, moment_validare);
        }

        if(comanda == 4)
        {
            int id1, id2;
            std::cin>>id1>>id2>>val;
            Vlad.transfer(id1, id2, val);
        }

        if(comanda == 5) break;
    }

    return 0;
}
