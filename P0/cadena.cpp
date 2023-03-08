#include <iostream>
#include <stdexcept>
#include "cadena.hpp"

using namespace std;

// Constructor
Cadena::Cadena(unsigned int t, char c) : tam_(t), s_(new char[tam_+1])
{
    for (unsigned int i = 0 ; i < tam_ ; i++)
        s_[i] = c;
    s_[tam_] = '\0';
};

// COnstructor de cadena de caracteres
Cadena::Cadena(const char * c) : tam_(0), s_(nullptr)
{
    while (c[tam_] != '\0')
        tam_++;
    s_ = new char[tam_+1];

    for (unsigned int i = 0 ; i < tam_ ; i++)
        s_[i] = c[i];
    s_[tam_] = '\0';
}

// COnstructor de copia
Cadena::Cadena(const Cadena& cad) : s_(cad.s_), tam_(cad.tam_)
{
    for(unsigned int i = 0 ; i <= tam_ ; i++)
        s_[i] = cad.s_[i];
}

// Operador de suma en asignación
const Cadena& Cadena::operator+=(const Cadena& cad)
{
    Cadena concat(tam_+cad.tam_);
    unsigned int i = 0;
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

// Operador de igualdad entre cadenas
bool operator==(const Cadena& cad1, const Cadena& cad2)
{
    if(cad1.tam_ == cad2.tam_) {
        unsigned int i = cad1.tam_;
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

// Operador de igualdad entre cadena y caracteres
bool operator==(const char* s, const Cadena& cad)
{
	Cadena Aux(s);
	return Aux == cad;
}

// Operador de comparación menor o igual
bool operator<(const Cadena& cad1, const Cadena& cad2)
{
    unsigned int i = min(cad1.tam_, cad2.tam_);
    bool menor = true;
    while (i > 0 && menor)
    {
        if(cad1[i] > cad2[i])
            menor = false;
        i--;
    }

    return menor;
}

// Observador at (devuelve el caracter que ocupa la posición índice)
char Cadena::at (unsigned int indice) const
{
    try {
        if (indice < tam_ -1)
            return s_[indice];
        else
            throw out_of_range("ERROR! Índice fuera de rango");
    }
    catch(out_of_range e) {
        cerr << e.what() << endl;
    }
}

//Observador substr (devuelve la cadena que comienza en la posición indice y tiene un tamaño t)
Cadena Cadena::substr(unsigned int indice, unsigned int t) const
{
    try {
        if (indice + t < tam_) {
            char * s = new char[t+1];
            unsigned int i = 0;
            unsigned int fin = indice + t;
            while (indice < fin)
            {
                s[i] = s_[indice];
                i++;
                indice++;
            }
            s[t] = '\0';
            Cadena Return(s);
            delete[] s;
            return Return;
        }
        else {
            throw out_of_range("ERROR! Índice fuera de rango");
        }
    }
    catch(out_of_range e) {
        cerr << e.what() << endl;
    }
}

// Destructor
Cadena::~Cadena()
{
	delete[] s_;
}
