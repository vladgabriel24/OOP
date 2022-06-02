#include "Clase.cpp"

int main()
{
    Browser vlad;
    
    std::list<Pagina_Web> P;
    int comanda;
    
    std::string url, titlu, content;
    
    while(true)
    {
        std::cin>>comanda;
        
        if(comanda == 1)
        {
            std::cin>>url>>titlu;
            std::cin.get();
            getline(std::cin, content);
            
            P.push_back(Pagina_Web(url, titlu, content));
        }
        
        if(comanda == 2)
        {
            std::cin>>url;
            vlad.link(P, url);
        }
        
        if(comanda == 3) vlad.afisare_pagina();
        
        if(comanda == 4) vlad.back();
        
        if(comanda == 5) vlad.forward();
    
        if(comanda == 6) break;
    }
        
    return 0;
}