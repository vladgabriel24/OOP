#include "echipament_electronic.h"
#include <iostream>

// Echipament_electronic = UI
Echipament_electronic::Echipament_electronic(float pret = 0.0f, std::string nume = "", std::string tip = ""
, std::string socket="", int frecventa = 0, int memorie_GPU = 0, float memorie = 0.0f)
:nume(nume), pret(pret), tip(tip), socket(socket), frecventa(frecventa), memorie_GPU(memorie_GPU), memorie(memorie){}

// Placa de baza
Placa_de_baza::Placa_de_baza(float pret = 0.0f, std::string nume="", std::string tip="", std::string socket="")
:Echipament_electronic(pret, nume, tip, socket){}

void Placa_de_baza::display(){std::cout<<tip<<", "<<nume<<", "<<socket<<", "<<pret<<'\n';}
float Placa_de_baza::raport_calitate_pret(){return 0.0f;}

// CPU
CPU::CPU(float pret = 0.0f, std::string nume = "", std::string tip = "", std::string socket="", int frecventa=0)
:Echipament_electronic(pret, nume, tip, socket, frecventa){}

void CPU::display(){std::cout<<tip<<", "<<nume<<", "<<socket<<", "<<frecventa<<", "<<pret<<'\n';}
float CPU::raport_calitate_pret(){return (float)frecventa/pret;}

//GPU

GPU::GPU(float pret = 0.0f, std::string nume="", std::string tip="", int memorie_GPU=0)
:Echipament_electronic(pret, nume, tip, "", 0, memorie_GPU){}
    
void GPU::display(){std::cout<<tip<<", "<<nume<<", "<<memorie_GPU<<", "<<pret<<'\n';}
float GPU::raport_calitate_pret(){return (float)memorie_GPU/pret;}

// Stocare
Stocare::Stocare(float pret=0.0f, std::string nume="", std::string tip="", float memorie=0.0f)
:Echipament_electronic(pret, nume, tip, "", 0, 0, memorie){}
    
void Stocare::display(){std::cout<<tip<<", "<<nume<<", "<<memorie<<", "<<pret<<'\n';}
float Stocare::raport_calitate_pret(){return memorie/pret;}