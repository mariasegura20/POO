#include <iostream>
#include "cadena.hpp"

using namespace std;

Cadena::Cadena(unsigned t = 0, const char* c = " ") : tam_(t), s_(new char[tam_+1])
{
    for (int i = 0 ; i < tam_ ; i++)
        s_[i] = c[i];
    s_[tam_] = '\0';
};

Cadena::Cadena(const Cadena& cad) : s_(cad.s_), tam_(cad.tam_)
{
    for(int i = 0 ; i <= tam_ ; i++)
        s_[i] = cad.s_[i];
}

// Sobrecarga de operadores
const Cadena& Cadena::operator+=(const Cadena& cad)
{
    Cadena concat(tam_+cad.tam_);
    unsigned i = 0;
    while (i < tam_)
    {
        concat.s_[i] = s_[i];
        i++;
    }
    while (i < tam_ + cad.tam_)
    {
        concat.s_[i] = cad.s_[i-cad.tam_];
        i++;
    }

    *this = concat;
    return *this;
}

bool operator==(const Cadena& cad1, const Cadena& cad2)
{
    if(cad1.tam_ == cad2.tam_) {
        unsigned i = cad1.tam_;
        bool iguales = true;
        while (i > 0 && iguales) {
            if(cad1[i] != cad2[i])
                iguales = false;
            i--;
        }

        return iguales;
    }
    else
        return false;
}

bool operator<(const Cadena& cad1, const Cadena& cad2)
{
    unsigned i = min(cad1.tam_, cad2.tam_);
    bool menor = true;
    while (i > 0 && menor)
    {
        if(cad1[i] > cad2[i])
            menor = false;
        i--;
    }

    return menor;
}

const Cadena& Cadena::substr(unsigned indice, unsigned t)
{
    try {
        if (indice >= 0 && indice + t < tam_) {
            char * s;
            unsigned i = 0;
            unsigned fin = indice + t;
            while (indice < fin)
            {
                s[i] = s_[indice];
                i++;
                indice++;
            }
        }
        else {
            throw out_of_range("ERROR! Índice fuera de rango");
        }
    }
    catch(out_of_range e) {
        cerr << e.what() << endl;
    }
}