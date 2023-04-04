#include <iostream>
#include <locale>
#include <cstdio>
#include "fecha.hpp"

using namespace std;

/*** CONSTRUCTORES ***/
// Constructor
Fecha::Fecha(int d, int m, int a) : dia_(d), mes_(m), anno_(a)
{
	if (d == 0 || m == 0 || a == 0)
	{
		std::time_t tiempo_calendario = std::time(nullptr);
		std::tm* tiempo_descompuesto = std::localtime(&tiempo_calendario);
		int dia = tiempo_descompuesto->tm_mday;
		int mes = tiempo_descompuesto->tm_mon + 1; // tm_mon: 0 (ene)..11 (dic)
		int anno = tiempo_descompuesto->tm_year + 1900; // tm_year: a~nos desde 1900

		if(dia_ == 0)
			dia_ = dia;
		if(mes_ == 0)
			mes_ = mes;
		if(anno_ == 0)
			anno_ = anno;
	}

	valida();
}

// Constructor de cadena de caracteres
Fecha::Fecha(const char * s)
{
	int nuevoDia, nuevoMes, nuevoAnno;
	int n = sscanf(s, "%d/%d/%d", &nuevoDia, &nuevoMes, &nuevoAnno);
	if (n != 3)
		throw Fecha::Invalida("ERROR! Formato incorrecto");
	else
	{
		Fecha f(nuevoDia, nuevoMes, nuevoAnno);
		dia_ = f.dia();
		mes_ = f.mes();
		anno_ = f.anno();
	}
}

/*** OPERADOR DE CONVERSIÓN ***/
const char* Fecha::cadena() const
{
	setlocale(LC_ALL, "es_ES.UTF-8");
	struct tm f = {};
	f.tm_mday = dia_;
	f.tm_mon = mes_ - 1;
	f.tm_year = anno_ - 1900;
	
	mktime(&f);
	
	static char * fecha_str = new char [80];
	strftime(fecha_str, 80, "%A %e de %B de %Y", &f);
	return fecha_str;
}

/*** OPERADORES ARITMÉTICOS ***/
// Operador de postincremento
Fecha Fecha::operator++ (int) 
{
	Fecha t;
	t = *this;
	*this += 1;
	return t;
}

// Operador de preincremento
Fecha& Fecha::operator++ () 
{
	*this += 1;
	return *this;
}

// Operador de postdecremento
Fecha Fecha::operator-- (int) 
{
	Fecha t;
	t = *this;
	*this += -1;
	return t;
}

// Operador de predecremento
Fecha& Fecha::operator-- () 
{
	*this += -1;
	return *this;
}

// Operador de suma
Fecha Fecha::operator+ (int n) const
{
	Fecha t;
	t = *this;
	t += n;
	return t;
}

// Operador de resta
Fecha Fecha::operator- (int n) const
{
	Fecha t;
	t = *this;
	t += -n;
	return t;
}

// Operador de suma en asignación
Fecha& Fecha::operator+= (int n)
{
	struct tm when = {};
	when.tm_mday = dia_;
	when.tm_mon = mes_ - 1;
	when.tm_year = anno_ - 1900;
	when.tm_mday += n;

	mktime(&when);

	this->dia_ = when.tm_mday;
	this->mes_ = when.tm_mon + 1;
	this->anno_ = when.tm_year + 1900;

	valida();
	return *this;
}

// Operador de resta en asignación
Fecha& Fecha::operator-= (int n)
{
	*this += -n;
	return *this;
}

/*** OPERADORES DE FLUJO ***/
// Operador de extracción
istream& operator>>(istream& is, Fecha& f)
{
	char entrada[80];
	is >> entrada;
	int nuevoDia, nuevoMes, nuevoAnno;
	int n = sscanf(entrada, "%02d/%02d/%04d", &nuevoDia, &nuevoMes, &nuevoAnno);
	if (n != 3) {
		is.setstate(ios::failbit);
		throw Fecha::Invalida("ERROR! Formato incorrecto");
	}
	else
	{
		try {
			Fecha Aux (entrada);
			f = Aux;
		}
		catch (const Fecha::Invalida& e){
			is.setstate(ios::failbit);
			throw e;
		}
		return is;
	}
}

// Operador de inserción
ostream& operator<<(ostream& os, const Fecha& f)
{
    os << f.cadena();
    return os;
}

/*** MÉTODO PRIVADO ***/
void Fecha::valida()
{
	if (anno_ < AnnoMinimo)
		throw Invalida("ERROR! Desbordamiento inferior en la fecha");
	else if (anno_ > AnnoMaximo)
		throw Invalida("ERROR! Desbordamiento superior en la fecha");

	if (mes_ < 1 || mes_ > 12)
		throw Invalida("ERROR! El mes no es válido");

	if (mes_ == 1 || mes_ == 3 || mes_ == 5 || mes_ == 7 || mes_ == 8 || mes_ == 10 || mes_ == 12)
	{
		if (dia_ < 1 || dia_ > 31)
			throw Invalida("ERROR! El día no es válido");
	}
	else if (mes_ == 4 || mes_ == 6 || mes_ == 9 || mes_ == 11)
	{
		if (dia_ < 1 || dia_ > 30)
			throw Invalida("ERROR! El día no es válido");
	}
	else if (mes_ == 2)
	{
		if (anno_ % 4 == 0 && (anno_ % 400 == 0 || anno_ % 100 != 0))
		{
			if (dia_ < 1 || dia_ > 29)
				throw Invalida("ERROR! El día no es válido");
		}
		else
		{
			if (dia_ < 1 || dia_ > 28)
				throw Invalida("ERROR! El día no es válido");
		}
	}
}
