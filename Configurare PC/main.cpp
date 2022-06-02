#include <iostream>
#include <vector>
#include <algorithm>
#include "echipament_electronic.h"

class PC
{
    Placa_de_baza *p1;
    CPU* p2;
    GPU* p3;
    Stocare* p4;
    int buget;
    
public:

    PC(Placa_de_baza* p1 = nullptr, CPU* p2 = nullptr, GPU* p3 = nullptr, Stocare* p4=nullptr, int buget = 0)
    :p1(p1), p2(p2), p3(p3), p4(p4), buget(buget){}
    
    float suma(){return (p1->get_pret() + p2->get_pret() + p3->get_pret() + p4->get_pret());}
    
    void afisare()
    {
        p1->display();
        p2->display();
        p3->display();
        p4->display();
    }
    
    void set_cpu(CPU* cpu){p2 = cpu;}
    void set_gpu(GPU* gpu){p3 = gpu;}
    void set_stocare(Stocare* hard){p4 = hard;}
};

template<typename T>
bool dupa_r_calitate_pret(T lhs, T rhs)
{
    if(lhs->raport_calitate_pret() < rhs->raport_calitate_pret()) return true;
    else return false;
}

template<typename T>
bool dupa_pret(T lhs, T rhs)
{
    if(lhs->get_pret() > rhs->get_pret()) return true;
    else return false;
}

class Manager
{
    std::vector<Placa_de_baza*> v1; 
    std::vector<CPU*> v2;
    std::vector<GPU*> v3;
    std::vector<Stocare*> v4;
    
public:

    Manager(std::vector<Placa_de_baza*> v1 = std::vector<Placa_de_baza*>(0),
    std::vector<CPU*> v2 = std::vector<CPU*>(0),
    std::vector<GPU*> v3 = std::vector<GPU*>(0),
    std::vector<Stocare*> v4 = std::vector<Stocare*>(0))
    :v1(v1), v2(v2), v3(v3), v4(v4){}
    
    void afisare()
    {
        for(auto& i : v1) i->display();
        for(auto& i : v2) i->display();
        for(auto& i : v3) i->display();
        for(auto& i : v4) i->display();
    }
    
    CPU* cautare_cpu(std::string nume)
    {
        for(auto& i:v2)
            if(i->get_nume() == nume) return i;

        return nullptr;
    }
    
    GPU* cautare_gpu(std::string nume)
    {
        for(auto& i:v3)
            if(i->get_nume() == nume) return i;

        return nullptr;
    }
    
    Stocare* cautare_stocare(std::string nume)
    {
        for(auto& i:v4)
            if(i->get_nume() == nume) return i;

        return nullptr;
    }
    
    PC* configuratie_PC(std::string cpu, std::string gpu, std::string stocare)
    {
        PC* p = new PC(v1[0], cautare_cpu(cpu), cautare_gpu(gpu), cautare_stocare(stocare));
        return p;
    }
    
    PC* configuratie_optima_PC(int buget)
    {
        std::sort(v2.begin(), v2.end(), dupa_r_calitate_pret<CPU*>);
        std::sort(v3.begin(), v3.end(), dupa_r_calitate_pret<GPU*>);
        std::sort(v4.begin(), v4.end(), dupa_r_calitate_pret<Stocare*>);
        
        PC* p = new PC(v1[0], *std::max_element(v2.begin(), v2.end(), dupa_pret<CPU*>), *std::max_element(v3.begin(), v3.end(), dupa_pret<GPU*>), *std::max_element(v4.begin(), v4.end(), dupa_pret<Stocare*>));    
        
        auto it_cpu = std::max_element(v2.begin(), v2.end(), dupa_pret<CPU*>);
        auto it_gpu = std::max_element(v3.begin(), v3.end(), dupa_pret<GPU*>);
        auto it_stocare = std::max_element(v4.begin(), v4.end(), dupa_pret<Stocare*>);
        
        int flag_gpu=0, flag_cpu=0, flag_stocare=0;
        while(true)
        {
            if(it_gpu != --v3.end() && flag_gpu == 0)
            {
                it_gpu++;
                p->set_gpu(*it_gpu);
            
                if(p->suma() > buget)
                {
                    it_gpu--;
                    p->set_gpu(*it_gpu);
                    flag_gpu=1;
                }
            }
            else flag_gpu=1;
            
            if(it_cpu != --v2.end() && flag_cpu == 0)
            {
                it_cpu++;
                p->set_cpu(*it_cpu);
            
                if(p->suma() > buget)
                {
                    it_cpu--;
                    p->set_cpu(*it_cpu);
                    flag_cpu=1;
                }
            }
            else flag_cpu=1;
            
            if(it_stocare != --v4.end() &&  flag_stocare == 0)
            {
                it_stocare++;
                p->set_stocare(*it_stocare);
            
                if(p->suma() > buget)
                {
                    it_stocare--;
                    p->set_stocare(*it_stocare);
                    flag_stocare=1;
                }
            }
            else flag_stocare=1;
            
            if(flag_cpu == 1 && flag_gpu == 1 && flag_stocare == 1) break;
        }
        return p;
    }
    
};

int main()
{
    std::vector<Placa_de_baza*> v1; 
    std::vector<CPU*> v2;
    std::vector<GPU*> v3;
    std::vector<Stocare*> v4;
    
    std::string nume;
    std::string tip;
    float pret;
    std::string socket;
    int frecventa;
    int memorie_GPU;
    float memorie;
    
    Manager* vlad;
    
    int comanda;
    
    while(true)
    {
        std::cin>>comanda;
        if(comanda == 1) // citire
        {
            std::cin>>pret;
            std::cin>>nume;
            std::cin>>tip;
            
            if(tip == "placa_baza")
            {
                std::cin>>socket;
                
                Placa_de_baza* tmp = new Placa_de_baza(pret, nume, tip, socket);
                v1.push_back(tmp);
            }
            if(tip == "cpu")
            {
                std::cin>>socket;
                std::cin>>frecventa;
                
                CPU* tmp = new CPU(pret, nume, tip, socket, frecventa);
                v2.push_back(tmp);
            }
            if(tip == "gpu")
            {
                std::cin>>memorie_GPU;
                
                GPU* tmp = new GPU(pret, nume, tip, memorie_GPU);
                v3.push_back(tmp);
            }
            if(tip == "stocare")
            {
                std::cin>>memorie;
                
                Stocare* tmp = new Stocare(pret, nume, tip, memorie);
                v4.push_back(tmp);
            }
        }
        
        vlad = new Manager(v1, v2, v3, v4);
        
        if(comanda == 2) {vlad->afisare();}
        if(comanda == 3)
        {
            std::string cpu, gpu, stocare;
            
            std::cin>>cpu>>gpu>>stocare;
        
            PC* asus = vlad->configuratie_PC(cpu, gpu, stocare);
            
            asus->afisare();
            std::cout<<asus->suma()<<'\n';
        }
        
        if(comanda == 4)
        {
            int buget;
            std::cin>>buget;
            
            PC *asus = vlad->configuratie_optima_PC(buget);
            
            asus->afisare();
        }
        
        if(comanda == 5) break;
    }
    return 0;
}