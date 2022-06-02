#include "UI.h"
#include <iostream>

class Pagina_Web: protected Pagina_Web_UI
{
    
protected:    
    
public:

    Pagina_Web(std::string url = "", std::string titlu = "", std::string continut = "")
    :Pagina_Web_UI(url, titlu, continut){}
    
    std::string get_url(){return this->url;}
    std::string get_titlu(){return this->titlu;}
    std::string get_continut(){return this->continut;}
    
    
    void set_url(std::string url){this->url = url;}
    void set_titlu(std::string titlu){this->titlu = titlu;}
    void set_continut(std::string continut){this->continut = continut;}
    
    void display()
    {
        std::cout<<this->url<<'\n'<<this->titlu<<'\n'<<this->continut<<'\n';
    }
};

class Browser: protected Browser_UI
{
  
protected:

    std::list<Pagina_Web> V;
    std::list<Pagina_Web>::iterator pos;
    
public:

    Browser()=default;

    void link(std::list<Pagina_Web> P, std::string url)
    {
        
        if(V.empty())
        {
            for(auto it = P.begin(); it!=P.end(); it++)
            {
                if(it->get_url() == url){ V.push_back(*it); pos = V.begin();}
            }
        }
        
        else if(pos == --V.end())
        {
            for(auto it = P.begin(); it!=P.end(); it++)
            {
                if(it->get_url() == url) V.push_back(*it);
            }
            
            pos++;
        }
        else if(pos != --V.end())
        {
            while(pos != --V.end()) V.pop_back();
            
            for(auto it = P.begin(); it!=P.end(); it++)
            {
                if(it->get_url() == url) V.push_back(*it);
            }
            pos++;
        }
    }
    
    void back()
    {
        if(pos != V.begin()) pos--;
    }
    
    void forward()
    {
        if(pos != --V.end()) pos++;
    }
    
    void afisare_pagina()
    {
        pos->display();
    }

};