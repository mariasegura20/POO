#include <iostream>
#include <locale>
#include "fecha.hpp"

using namespace std;

// Constructor
Fecha::Fecha(int d, int m, int a) : dia_(d), mes_(m), anno_(a)
{
    if (d == 0 || m == 0 || a == 0) {
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
    sscanf(s, "%i/%i/%i", &nuevoDia, &nuevoMes, &nuevoAnno);
    try {
        dia_ = nuevoDia;
        mes_ = nuevoMes;
        anno_ = nuevoAnno;
        valida();
    }
    catch(Fecha::Invalida e) {
        cerr << e.por_que() << endl;
    }
}

// Constructor de copia
Fecha::Fecha(const Fecha& f) : dia_(f.dia_), mes_(f.mes_), anno_(f.anno_) {};

// Operador de asignación
Fecha& Fecha::operator= (const Fecha& fecha)
{
    this->dia_ = fecha.dia_;
    this->mes_ = fecha.mes_;
    this->anno_ = fecha.anno_;
    return *this;
}

// Operador de postincremento
Fecha Fecha::operator++ (int d)
{
	Fecha f(*this);
	d = 1;
	f += d;
	return f;
}

// Operador de preincremento
Fecha& Fecha::operator++ ()
{
	*this += 1;
	return *this;
}

// Operador de postdecremento
Fecha Fecha::operator-- (int d)
{
	Fecha f(*this);
	d = 1;
	f += d;
	return f;
}

// Operador de predecremento
Fecha& Fecha::operator-- ()
{
	*this -= 1;
	return *this;
}

// Operador de suma en asignación
Fecha& Fecha::operator+= (int d)
{
    struct tm when;
    when.tm_mday = dia_;
    when.tm_mon = mes_ - 1;
    when.tm_year = anno_ - 1900;
    when.tm_mday = when.tm_mday + d;
    
    this->dia_ = when.tm_mday;
    this->mes_ = when.tm_mon+1;
    this->anno_ = when.tm_year + 1900;  
    
    try {   
        Fecha f(*this);
        return *this;
    }
    catch (Fecha::Invalida e) {
        cerr << e.por_que() << endl;
    }
}

// Operador de suma (const)
Fecha Fecha::operator+ (int d) const
{
	Fecha f(*this);
	f+= d;
	return f;
}

// Operador de resta (const)
Fecha Fecha::operator- (int d) const
{
	Fecha f(*this);
	f-= d;
	return f;
}

// Operador de inserción de flujo
/*ostream& operator<<(ostream& os, const Fecha& fecha) {
    setlocale(LC_ALL, "es_ES.UTF-8");
    time_t t = time(nullptr);
    struct tm f = *localtime(&t);
    f.tm_mday = fecha.dia_;
    f.tm_mon = fecha.mes_ - 1;
    f.tm_year = fecha.anno_ - 1900;
    mktime(&f);
    char fecha_str[80];
    strftime(fecha_str, 80, "%A %e de %B de %Y", &f);
    os << fecha_str;
    return os;
}*/

Fecha::operator const char*()
{
	char * fecha_str = new char[11];
	sprintf(fecha_str, "%02d/%02d/%04d", dia_, mes_, anno_);
	return fecha_str;
}

// Métodos privados
void Fecha::valida()
{
    if (anno_ < AnnoMinimo)
        throw Invalida("ERROR! Desbordamiento inferior en la fecha");
    else if (anno_ > AnnoMaximo)
        throw Invalida("ERROR! Desbordamiento superior en la fecha");
    
    if (mes_ < 1 || mes_ > 12)
        throw Invalida("ERROR! El mes no es válido");
    
    if (mes_ == 1 || mes_ == 3 || mes_ == 5 || mes_ == 7 || mes_ == 8 || mes_ == 10 || mes_ == 12) {
        if (dia_ < 1 || dia_ > 31)
            throw Invalida("ERROR! El día no es válido");
    }
    else if (mes_ == 4 || mes_ == 6 || mes_ == 9 || mes_ == 11) {
        if (dia_ < 1 || dia_ > 30)
            throw Invalida("ERROR! El día no es válido");
    }
    else if (mes_ == 2) {
        if (anno_ % 4 == 0 && (anno_ % 400 == 0 || anno_ % 100 != 0)) {
            if (dia_ < 1 || dia_ > 29)
                throw Invalida("ERROR! El día no es válido");
        }
        else {
            if (dia_ < 1 || dia_ > 28)
                throw Invalida("ERROR! El día no es válido");
        }
    }
}
