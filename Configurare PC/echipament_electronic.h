#ifndef ECHIPAMENT_ELECTRONIC_H
#define ECHIPAMENT_ELECTRONIC_H

#include <string>

class Echipament_electronic
{
protected:
    std::string nume;
    std::string tip;
    float pret;
    std::string socket;
    int frecventa;
    int memorie_GPU;
    float memorie;
    
public:
    Echipament_electronic(float, std::string, std::string, std::string, int, int, float);
    
    virtual void display() = 0;
    virtual float raport_calitate_pret() = 0;
    
    std::string get_socket(){return socket;}
    float get_pret(){return pret;}
    std::string get_nume(){return nume;}
};

class Placa_de_baza:public Echipament_electronic
{

public:
    Placa_de_baza(float, std::string, std::string, std::string);
    
    void display();
    float raport_calitate_pret();
};

class CPU:public Echipament_electronic
{
    
public:
    CPU(float, std::string, std::string, std::string, int);
    
    void display();
    float raport_calitate_pret();
};

class GPU:public Echipament_electronic
{
    
public:
    GPU(float, std::string, std::string, int);
    
    void display();
    float raport_calitate_pret();
};

class Stocare:public Echipament_electronic
{
    
public:
    Stocare(float, std::string, std::string, float);
    
    void display();
    float raport_calitate_pret();
};

#endif