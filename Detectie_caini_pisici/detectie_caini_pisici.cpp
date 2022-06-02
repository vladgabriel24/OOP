#include <iostream>
#include <iomanip>

#define MAX_BOX 10

template<typename T>
T maxim(T x, T y)
{
    if(x > y) return x;
    else return y;
}

template<typename T>
T minim(T x, T y)
{
    if(x < y) return x;
    else return y;
}

template <typename T>
class Punct
{

private:
    T x, y;

public:

    Punct(T x = 0, T y = 0):x(x),y(y){}

    T get_x(){return x;}
    T get_y(){return y;}

    void set_x(T x){this->x = x;}
    void set_y(T y){this->y = y;}
};


template <typename T>
class Box
{

protected:

    Punct<T> p11, p12, p21, p22;

public:

    Box(T x1 = 0, T x2 = 0, T y1 = 0, T y2 = 0)
    {
        p11.set_x(x1);
        p11.set_y(y1);

        p12.set_x(x1);
        p12.set_y(y2);

        p21.set_x(x2);
        p21.set_y(y1);

        p22.set_x(x2);
        p22.set_y(y2);
    }

    virtual void afisare()
    {
        std::cout<<p11.get_x()<<' '<<p21.get_x()<<' '<<p11.get_y()<<' '<<p12.get_y()<<'\n';
    }

    T get_x1() {return p11.get_x();}
    T get_x2() {return p21.get_x();}
    T get_y1() {return p11.get_y();}
    T get_y2() {return p22.get_y();}
};

template <typename T>
class B_box: 
    public Box<T>
{

private:
    std::string denumire;

public:

    B_box(T x1 = 0, T x2 = 0, T y1 = 0, T y2 = 0, std::string denumire = "")
    :Box<T>(x1,x2,y1,y2), denumire(denumire){}

    void afisare() override
    {
        std::cout<<Box<T>::p11.get_x()<<' ';
        std::cout<<Box<T>::p21.get_x()<<' ';
        std::cout<<Box<T>::p11.get_y()<<' ';
        std::cout<<Box<T>::p12.get_y()<<'\n';
        std::cout<<denumire<<std::endl;

        // daca mostenesc o clasa de tip template
        // cand vreau sa ma refer la o functie sau variabila din clasa de baza
        // trebuie sa folosesc operatorul de rezolutie ca sa ii dau parametru de tip template
        // altfel compilatorul nu stie de unde sa ia variabila
    }

    std::string get_denumire(){return denumire;}
};

// pentru ca sa declar o functie template friend unei clase anume,
// trebuie ca acea functie sa fi fost declarata inainte
// iar inauntrul clasei , cand declar sintactic functia friend
// sa pun imediat dupa numele functiei "<>"

template <typename T, typename T2>
T2 IoU(B_box<T> A, B_box<T> B)
{
    B_box<T> C( maxim(A.get_x1(),B.get_x1()),
                minim(A.get_x2(),B.get_x2()),
                maxim(A.get_y1(),B.get_y1()),
                minim(A.get_y2(),B.get_y2())
                );

    T2 S_intersectie = (abs(C.get_x1() - C.get_x2())+1)*(abs(C.get_y1() - C.get_y2())+1);

    T2 S_A = (abs(A.get_x1() - A.get_x2())+1)*(abs(A.get_y1() - A.get_y2())+1);

    T2 S_B = (abs(B.get_x1() - B.get_x2())+1)*(abs(B.get_y1() - B.get_y2())+1);

    T2 S_reuniune = S_A + S_B - S_intersectie;

    return S_intersectie/S_reuniune;
}


template <typename T, typename T2>
class Referinta
{

private:
    B_box<T>* V[MAX_BOX];
    int nr;

public:

    Referinta()
    {
        T x1, x2, y1, y2;
        std::string denumire;

        std::cin>>nr;

        for(int i=0; i<nr; i++)
        {
            std::cin>>x1>>x2>>y1>>y2>>denumire;
            V[i] = new B_box<T>(x1, x2, y1, y2,denumire);
        }
    }

    void afisare()
    {
        for(int i=0; i<nr; i++) V[i]->afisare();
    }

    B_box<T> get_b_index(int index){ return *V[index];}

    int get_nr(){return nr;}

    friend T2 IoU<>(B_box<T> , B_box<T>);
    // adica cum am facut aici

};

template <typename T, typename T2>
class Ipoteza
{

private:
    B_box<T>* V[MAX_BOX];
    int nr;

public:

    Ipoteza()
    {
        T x1, x2, y1, y2;
        std::string denumire;

        std::cin>>nr;

        for(int i=0; i<nr; i++)
        {
            std::cin>>x1>>x2>>y1>>y2>>denumire;
            V[i] = new B_box<T>(x1, x2, y1, y2,denumire);
        }
    }

    void afisare()
    {
        for(int i=0; i<nr; i++) V[i]->afisare();
    }

    B_box<T> get_b_index(int index){ return *V[index];}

    int get_nr(){return nr;}

    friend T2 IoU<>(B_box<T> , B_box<T>);
    // adica cum am facut aici

};

int main()
{
    Referinta<int, float> ip;

    int test;

    std::cin>>test;

    if(test == 1) ip.afisare();

    if(test == 2)
    {
        int x1,x2,y1,y2;
        std::string denumire;

        std::cin>>x1>>x2>>y1>>y2>>denumire;

        B_box<int> test(x1,x2,y1,y2,denumire);

        std::cout<<std::fixed<<std::setprecision(4)<<IoU<int,float>(test,ip.get_b_index(0));
    }

    if(test == 3)
    {
        int x1,x2,y1,y2;
        std::string denumire;

        float prag;

        std::cin>>x1>>x2>>y1>>y2>>denumire;
        std::cin>>prag;

        B_box<int> test(x1,x2,y1,y2,denumire);

        if(IoU<int,float>(test,ip.get_b_index(0)) > prag)
        {
            if(test.get_denumire() == ip.get_b_index(0).get_denumire())
            {
                std::cout<<1;
            }
            else std::cout<<0;
        }
        else std::cout<<0;
    }

    if(test == 6)
    {
        Referinta<int,float> ref;
        int TP=0, FP=0;
        float prag;

        std::cin>>prag;

        for(int i=0; i<ref.get_nr(); i++)
        {
            if(IoU<int,float>(ref.get_b_index(i),ip.get_b_index(i)) > prag)
            {
                if(ref.get_b_index(i).get_denumire() == ip.get_b_index(0).get_denumire())
                {
                    TP++;
                }
                else FP++;
            }
            else FP++;
        }

        std::cout<<(float)TP/(FP+TP);
    }

    return 0;
}