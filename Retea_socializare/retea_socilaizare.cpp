/*
class Profil
{
    int ID;
    std::string nume;
    int an, luna, zi;
    static int an_c, luna_c, zi_c;


    int age();
    bool verify_age();
};

class Post
{
    int ID_user;
    int M_age, m_age;
    std::string continut;

    bool can_see(Profil &p);
};

class Website
{
    Profil **users;
    Post **posts;

    void display_users();

};
*/
#include <iostream>

class Profil
{
    int ID;
    std::string nume;
    int an, luna, zi;
    static int an_c, luna_c, zi_c;

public:

    Profil(int ID = -1, std::string nume = "", int an=0, int luna=0, int zi=0)
    :ID(ID), nume(nume), an(an), luna(luna), zi(zi){}

    int get_ID()
    {
        return ID;
    }

    std::string get_nume()
    {
        return nume;
    }

    int get_zi()
    {
        return zi;
    }

    int get_luna()
    {
        return luna;
    }

    int get_an()
    {
        return an;
    }

    bool verify_age()
    {
        if(zi >= 1 && zi <= 30)
        {
            if(luna >= 1 && luna <= 12)
            {
                if(an >= 1900 && an <= 2021)
                {
                    return true;
                }
                else return false;
            }
            else return false;
        }
        else return false;
    }

    static void set_current_date(int &an, int &luna, int &zi)
    {
        an_c = an;
        luna_c = luna;
        zi_c = zi;
    }


    int age()
    {
        int days1 = an_c*360 + luna_c*30 + zi_c;
        int days2 = an*360 + luna*30 + zi;

        int age = (days1 - days2)/360;

        return age;
    }

    bool is_adult()
    {
        if(age() >= 18) return true;
        else return false;
    }
};

class Post
{
    int ID_user;
    int M_age, m_age;
    std::string continut;

public:

    Post(int ID_user = -1, int M_age = 0, int m_age = 0, std::string continut = "")
    :ID_user(ID_user), M_age(M_age), m_age(m_age), continut(continut){}

    int get_ID()
    {
        return ID_user;
    }

    std::string get_continut()
    {
        return continut;
    }

    int get_M_age()
    {
        return M_age;
    }

    int get_m_age()
    {
        return m_age;
    }
};

class Website
{
    Profil **users;
    int nr_utilizatori;

    Post **posts;
    int nr_postari;

public:

    Website(Profil **users = nullptr, Post **posts = nullptr, int nr_users=0, int nr_post=0)
    :nr_utilizatori(nr_users), nr_postari(nr_post)
    {

        this->users = new Profil* [nr_utilizatori];
        this->posts = new Post* [nr_postari];

        for(int i=0; i<nr_utilizatori; i++)
            *(this->users + i) = new Profil(
                                    users[i]->get_ID(), 
                                    users[i]->get_nume(), 
                                    users[i]->get_an(), 
                                    users[i]->get_luna(), 
                                    users[i]->get_zi()
                                );

    }

    void set_posts(Post **posts, int nr_postari)
    {
        this->nr_postari = nr_postari;
        this->posts = new Post* [nr_postari];
        
        for(int i=0; i<nr_postari; i++)
            *(this->posts + i) = new Post(posts[i]->get_ID(), posts[i]->get_M_age(), posts[i]->get_m_age(), posts[i]->get_continut());
    }

    void display_users()
    {
        for(int i=0; i<nr_utilizatori; i++)
        {
            std::cout<<users[i]->get_ID()<<'\n';
            std::cout<<users[i]->get_nume()<<'\n';
            std::cout<<users[i]->get_an()<<' '<<users[i]->get_luna()<<' '<<users[i]->get_zi()<<'\n';
        }
    }

    void display_cu_varsta_corecta()
    {
        for(int i=0; i<nr_utilizatori; i++)
        {
            std::cout<<users[i]->get_ID()<<'\n';

            if(users[i]->verify_age()) 
                std::cout<<users[i]->get_an()<<' '<<users[i]->get_luna()<<' '<<users[i]->get_zi()<<'\n';
            else std::cout<<"EROARE: Data de nastere introdusa nu e valida\n";
        }
    }

    void afisare_varste_majori()
    {
        for(int i=0; i<nr_utilizatori; i++)
        {
            if(users[i]->is_adult())
            { 
                std::cout<<users[i]->get_nume()<<'\n';
                std::cout<<users[i]->age()<<'\n';
            }
        }
    }

    std::string get_nume_dupa_ID(int ID)
    {
        return users[ID]->get_nume();
    }

    void see_posts(int ID)
    {
        int flag=1;

        std::cout<<"News Feed\n";

        for(int i=0; i<nr_postari; i++)
        {
            if((users[ID]->age() >= posts[i]->get_m_age() && users[ID]->age() <= posts[i]->get_M_age()) || posts[i]->get_ID() == ID)
            {
                flag = 0;
                std::cout<<get_nume_dupa_ID(posts[i]->get_ID())<<'\n';
                std::cout<<posts[i]->get_continut()<<'\n';
            }
        }
        if(flag) std::cout<<"No posts for you\n";
    }
};

int Profil::an_c=0, Profil::luna_c=0, Profil::zi_c=0;

int main()
{
    int nr_util=0;

    std::string nume;
    int an, luna, zi;

    int nr_postari=0;

    int comanda;

    std::cin>>nr_util;

    Profil **users = nullptr;
    Post **posts = nullptr;

    users = new Profil* [nr_util];

    for(int i=0; i<nr_util; i++)
    {
        std::cin.get();
        getline(std::cin, nume);

        std::cin>>an>>luna>>zi;

        users[i] = new Profil(i, nume, an, luna, zi);
    }

    Website vlad(users, posts, nr_util, nr_postari);

    std::cin>>comanda;

    if(comanda == 1) vlad.display_users();

    if(comanda == 2) vlad.display_cu_varsta_corecta();

    if(comanda == 3)
    {
        std::cin>>an>>luna>>zi;
        Profil::set_current_date(an, luna, zi);

        vlad.afisare_varste_majori();
    }

    if(comanda == 4)
    {
        int ID_util_postare;
        int m_age, M_age;
        std::string continut;

        std::cin>>an>>luna>>zi;
        Profil::set_current_date(an, luna, zi);

        std::cin>>nr_postari;

        posts = new Post*[nr_postari];

        for(int i=0; i<nr_postari; i++)
        {
            std::cin>>ID_util_postare;
            std::cin>>m_age>>M_age;
            std::cin.get();

            getline(std::cin, continut);

            posts[i] = new Post(ID_util_postare, M_age, m_age, continut);
        }
        vlad.set_posts(posts, nr_postari);

        vlad.see_posts(0);
    }
    return 0;
}