#ifndef UI_H
#define UI_H

#include <string>
#include <cstring>
#include <list>

class Pagina_Web_UI
{
    
protected:

    std::string url;
    std::string titlu;
    std::string continut;
    
public:

    Pagina_Web_UI(std::string url = "", std::string titlu = "", std::string continut = "")
    : url(url), titlu(titlu), continut(continut){}
    
    virtual std::string get_url()=0;
    virtual std::string get_titlu()=0;
    virtual std::string get_continut()=0;
    
    
    virtual void set_url(std::string url)=0;
    virtual void set_titlu(std::string titlu)=0;
    virtual void set_continut(std::string continut)=0;
    
    virtual void display()=0;
    
};

class Browser_UI
{
    
public:

    Browser_UI(){};
    
    virtual void back()=0;
    virtual void forward()=0;
};

#endif