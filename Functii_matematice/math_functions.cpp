#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#include <iomanip>

class MathFunction
{

private:

//date pt clasa Exponential
    const float e;
    float c;
    float coef;

protected:

    std::string f_name;

    //date pt clasa Polynomial
    std::vector<float> p_coef;
    int nr_coef;

    //date pt clasa DiscreteFunction
    std::vector<float> x;
    std::vector<float> y;
    int nr_x, nr_y;

public:
    MathFunction(std::string name="", float e=2.71f, float c=0.0f, float coef=0.0f, int nr_coef=0)
    :f_name(name), e(e), c(c), coef(coef), nr_coef(nr_coef), nr_x(0), nr_y(0){}

    virtual float get_value(int x){std::cout<<'a';}
    virtual float get_max_value(int a, int b){std::cout<<'a';}

    //functii pt clasa Polynomial
    virtual void print_f(){std::cout<<'a';} // functia 

    //functii pt clasa Quadratic
    virtual void print_roots(){std::cout<<"S-a apelat f print roots din clasa de baza!";}

    //functii pt clasa DiscreteFunction
    virtual std::string find_best_approximation(){std::cout<<"a";}

    //functii suplimentare clasa MathFunction
    std::string get_name(){return f_name;}

    float get_c(){return c;}
    float get_coef(){return coef;}

    void set_x_y(std::vector<float> x, std::vector<float> y)
    {
        this->x = x;
        this->y = y;
    }
};

class Polynomial: public MathFunction
{

public:
    // Initializare cu parametru default pt std::vector
    Polynomial(std::string name="", std::vector<float> p_coef = std::vector<float>(0), int nr_coef=0)
    :MathFunction(name)
    {
        this->p_coef = p_coef;
        this->nr_coef = nr_coef;
    }

    void print_f()
    {
        for(int i=0; i<nr_coef; i++)
        {
            if(p_coef[i] == 0) continue;

            if(p_coef[i] < 0) std::cout<<"- ";
            else
                if(i != 0) std::cout<<"+ ";

            if(abs(p_coef[i])!=1) std::cout<<abs(p_coef[i]);

            if(i > 0)
            {
                if(i == 1) std::cout<<'x';
                else std::cout<<"x^"<<i;
            }
            std::cout<<' ';
        }
    }

    void print_roots(){std::cout<<"S-a apelat f print roots din clasa polynomial!";}

    float get_value(int x)
    {
        float val=0;
        for(int i=0; i<nr_coef; i++) val += p_coef[i]*pow(x,i);

        return val;
    }

    float get_max_value(int a, int b)
    {
        float max = get_value(a);

        for(int i=a; i<=b; i++)
            if(get_value(i)>max) max = get_value(i);

        return max;
    }

    std::string find_best_approximation()
    {
        float dif_total = 0;

        for(int i=0; i<x.size(); i++) dif_total+= abs(y[i] - get_value(x[i]));

        return std::to_string(dif_total);
    }
};

class Quadratic: public Polynomial
{

public:

    Quadratic(std::string name="", std::vector<float> p_coef = std::vector<float>(0))
    :Polynomial(name, p_coef)
    {
        this->p_coef = p_coef;
        this->nr_coef = 3;
    }

    void print_f()
    {
        for(int i=0; i<nr_coef; i++)
        {
            if(p_coef[i] == 0) continue;

            if(p_coef[i] < 0) std::cout<<"- ";
            else
                if(i != 0) std::cout<<"+ ";

            std::cout<<abs(p_coef[i]);

            if(i > 0)
            {
                if(i == 1) std::cout<<'x';
                else std::cout<<"x^"<<i;
            }
            std::cout<<' ';
        }
    }

    void print_roots()
    {
        float x1 = ((-p_coef[1])+sqrt(pow(p_coef[1],2) - 4*p_coef[0]*p_coef[2]))/(2*p_coef[2]);
        float x2 = ((-p_coef[1])-sqrt(pow(p_coef[1],2) - 4*p_coef[0]*p_coef[2]))/(2*p_coef[2]);

        if(x1 == x2) std::cout<<std::fixed<<std::setprecision(2)<<"X1 = X2 = "<<x1;
        else std::cout<<std::fixed<<std::setprecision(2)<<"X1 = "<<x1<<'\n'<<"X2 = "<<x2;
    }

    float get_value(int x)
    {
        float val=0;
        for(int i=0; i<nr_coef; i++) 
            val += p_coef[i]*pow((float)x,i);

        return val;
    }

    float get_max_value(int a, int b)
    {
        float max = get_value(a);
        std::cout<<max;
        for(int i=a; i<=b; i++)
            if(get_value(i)>max) max = get_value(i);

        return max;
    }

    std::string find_best_approximation()
    {
        float dif_total = 0;

        for(int i=0; i<x.size(); i++) dif_total+= abs(y[i] - get_value(x[i]));

        return std::to_string(dif_total);
    }
};

class Exponential: public MathFunction
{

public:
    Exponential(std::string name="", const float e=2.71, float c=0.0f, float coef=0.0f)
    :MathFunction(name, e, c, coef){}

    void print_f()
    {
        std::cout<<MathFunction::get_c()<<' ';
        if(MathFunction::get_coef()>0) std::cout<<"+ ";
        else std::cout<<"- ";

        std::cout<<abs(MathFunction::get_coef());
        std::cout<<"e^x";
    }

    float get_value(int x)
    {
        return (MathFunction::get_c()+MathFunction::get_coef()*pow(2.71, x));
    }

    float get_max_value(int a, int b)
    {
        float max = get_value(a);
        for(int i=a; i<=b; i++)
            if(get_value(i)>max) max = get_value(i);

        return max;
    }

    std::string find_best_approximation()
    {
        float dif_total = 0;

        for(int i=0; i<x.size(); i++) dif_total+= abs(y[i] - get_value(x[i]));

        return std::to_string(dif_total);
    }
};

class DiscreteFunction: public MathFunction
{

public:
    DiscreteFunction(std::string name="", std::vector<float> x = std::vector<float>(0), std::vector<float>y=std::vector<float>(0))
    :MathFunction(name)
    {
        this->x = x;
        this->y = y;
        this->nr_x=this->nr_y=3;
    }

    void print_f(){std::cout<<':P';}
    float get_value(int x){std::cout<<x;}

    float get_max_value(int a, int b){std::cout<<'a';}

    std::string find_best_approximation(){return std::to_string(0);}
};

class Program
{

    std::vector<MathFunction*> V;
    int nr;

public:
    Program(std::vector<MathFunction*> V = std::vector<MathFunction*>(0), int nr=0)
    :V(V), nr(nr){}

    void afisare_functii()
    {
        for(int i=0; i<nr; i++)
        {
            std::cout<<"f(x) = ";
            V[i]->print_f();
            std::cout<<'\n';
        }
    }

    void afisare_radacini()
    {
        for(int i=0; i<nr; i++)
            if(V[i]->get_name() == "Quadratic") V[i]->print_roots();
    }

    void afisare_maxime(int a, int b)
    {
        for(int i=0; i<nr; i++)
        {
            std::cout<<std::fixed<<std::setprecision(2)<<V[i]->get_max_value(a,b);
            std::cout<<'\n';
        }
    }

    void aproximare(std::vector<float> x, std::vector<float> y)
    {
        std::string max = std::to_string(0);
        int index=0;
        float eroare = 0.0f;

        for(int i=0; i<nr ; i++)
        {
            V[i]->set_x_y(x, y);

            if(V[i]->find_best_approximation() > max)
            {
                max = V[i]->find_best_approximation();
                index = i;
                eroare = std::stof(max);
            }
        }

        std::cout<<"f(x) = ";
        V[index]->print_f();
        std::cout<<'\n'<<eroare;
    }
};

int main()
{
    int nr;
    std::string nume;

    std::vector<float> p_coef = std::vector<float>(10, 0.0f);

    int nr_p_coef;

    float c, coef;

    int comanda;

    std::cin>>nr;
    std::vector<MathFunction*> v(nr);

    for(int i=0; i<nr; i++)
    {
        std::cin>>nume;
        if(nume == "Polynomial")
        {
            std::cin>>nr_p_coef;
            p_coef.resize(nr_p_coef);

            for(int i=0; i<p_coef.size(); i++)
                std::cin>>p_coef[i];

            v[i] = new Polynomial(nume, p_coef, nr_p_coef);
        }

        if(nume == "Quadratic")
        {
            p_coef.resize(3);
            for(int i=0; i<3; i++)
                std::cin>>p_coef[i];

            v[i] = new Quadratic(nume, p_coef);
        }

        if(nume == "Exponential")
        {
            std::cin>>c>>coef;
            v[i] = new Exponential(nume, 2.71f, c, coef);
        }
    }

    Program vlad(v, nr);

    std::cin>>comanda;

    if(comanda == 1)
        vlad.afisare_functii();

    if(comanda == 2)
        vlad.afisare_radacini();

    if(comanda == 3)
    {
        int a, b;
        std::cin>>a>>b;

        vlad.afisare_maxime(a,b);
    }

    if(comanda == 4)
    {
        std::vector<float> x = std::vector<float>(3);
        std::vector<float> y = std::vector<float>(3);

        for(int i=0; i<3; i++) std::cin>>x[i];
        for(int i=0; i<3; i++) std::cin>>y[i];

        vlad.aproximare(x,y);
    }    

    return 0;
}