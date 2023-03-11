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

// Constructor de cadena de caracteres
Cadena::Cadena(const char * c)
{
    tam_ = strlen(c);
    s_ = new char[tam_+1];
    strcpy(s_,c);
    s_[tam_] = '\0';
}

// Operador de asignación
Cadena& Cadena::operator= (const Cadena& cad)
{
    if (*this != cad) {
    	tam_ = cad.tam_;
    	delete[] s_;
    	s_ = new char[tam_+1];
    	strcpy(s_, cad.s_);
    }
    return *this;
}

// Operador de suma en asignación
Cadena& Cadena::operator+=(const Cadena& cad)
{
    if (tam_ != 0 && cad.tam_ != 0) {
	char * concat = new char[tam_ + cad.tam_ + 1];
	    
	strcpy(concat, s_);
	strcat(concat, cad.s_);
	   
	tam_ = tam_ + cad.tam_;
	delete[] s_;
	s_ = new char[tam_ + 1];
	strcpy(s_, concat);
	s_[tam_] = '\0';
	delete[] concat;
    }
    return *this;
}

// Observador at (devuelve el caracter que ocupa la posición índice)
char& Cadena::at (unsigned int indice)
{
    if (indice < tam_)
        return s_[indice];
    else
        throw out_of_range("ERROR! Índice fuera de rango");
}

const char& Cadena::at (unsigned int indice) const
{
    if (indice < tam_)
        return s_[indice];
    else
        throw out_of_range("ERROR! Índice fuera de rango");
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
