#include <iostream>
#include <cstdio>
#include <stdexcept>
#include "cadena.hpp"

using namespace std;

/*** CONSTRUCTORES ***/
// Constructor
Cadena::Cadena(size_t t /* = 0*/, char c /* = ' '*/) : tam_(t), s_(new char[tam_+1])
{
	for (int i = 0 ; i < tam_ ; i++)
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

/*** OPERADORES DE ASIGNACIÓN ***/
// Operador de asignación a partir de cadena
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

// Operador de asignación a partir de cadena de bajo nivel
Cadena& Cadena::operator= (const char * cad)
{
	if (*this != cad) {
		tam_ = strlen(cad);
		delete[] s_;
		s_ = new char[tam_+1];
		strcpy(s_, cad);
	}
	return *this;
}

/*** OBSERVADORES ***/
// Observador at lectura/escritura
char& Cadena::at (int indice)
{
	if (indice < tam_)
		return s_[indice];
	else
		throw out_of_range("ERROR! Índice fuera de rango");
}

// Observador at lectura
const char& Cadena::at (int indice) const
{
	if (indice < tam_)
		return s_[indice];
	else
		throw out_of_range("ERROR! Índice fuera de rango");
}

//Observador subcadena
Cadena Cadena::substr(int indice, int t) const
{

	if (indice + t <= tam_ && indice >= 0 && t >= 0) {
		char * s = new char[t+1];
		int i = 0;
		int fin = indice + t;
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
	else
		throw out_of_range("ERROR! Índice fuera de rango");

}

/*** OPERADORES ARITMÉTICOS ***/
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

// Operador de suma
const Cadena Cadena::operator+(const Cadena& cad) const
{ 
	Cadena copia(*this);
	copia += cad;
	return copia;
}

/*** DESTRUCTOR ***/
Cadena::~Cadena()
{
	delete[] s_;
}
