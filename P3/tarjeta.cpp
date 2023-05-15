#include "tarjeta.hpp"

#include <algorithm>
#include <functional>

using namespace std;

/*** CLASE NUMERO ***/
/*** Constructores ***/
bool luhn(const Cadena& numero);	// Declaración adelantada

Numero::Numero(const Cadena& cad)
{
    auto it = remove_if(cad.begin(), cad.end(), EsBlanco());

    if(find_if(cad.begin(), it, EsDigito()) != it)
        throw Incorrecto(DIGITOS);

    Cadena sinEspacios = cad.substr(0, it - cad.begin());

    if (sinEspacios.length() < 13 || sinEspacios.length() > 19)
        throw Incorrecto(LONGITUD);

    num_ = sinEspacios;

    if (!luhn(num_))
    	throw Incorrecto(NO_VALIDO);
}

/*Numero::Numero(const Cadena& cad)
{
    char sinEspacios[21] = {'\0'};
	
	unsigned int i = 0, j = 0;
    while (i < cad.length())
    {
        if (!isspace(cad[i])) {
            if (!isdigit(cad[i]))
                throw Incorrecto(DIGITOS);

            sinEspacios[j] = cad[i];
            j++;
        }
        i++;
    } 

    if (strlen(sinEspacios) < 13 || strlen(sinEspacios) > 19)
        throw Incorrecto(LONGITUD);

    num_ = sinEspacios;

    if (!luhn(num_))
        throw Incorrecto(NO_VALIDO);
}*/


/*** CLASE TARJETA ***/
Tarjeta::Tarjetas Tarjeta::tarjetas_;

/*** Constructores ***/
Tarjeta::Tarjeta(const Numero& numero, Usuario& titular, const Fecha& caducidad) : numero_(numero), titular_(&titular), caducidad_(caducidad), activa_(true)
{
    Fecha hoy;
    if (caducidad_ < hoy)
        throw Caducada(caducidad_);
    if (!tarjetas_.insert(numero).second)
        throw Num_duplicado(numero);
    titular.es_titular_de(*this);
}

/*** Observadores ***/
bool Tarjeta::activa(bool estado)
{
    activa_ = estado;
    return activa_;
}

Tarjeta::Tipo Tarjeta::tipo() const
{
    if (numero_[0] == '3' && (numero_[1] == '4' || numero_[1] == '7'))
        return AmericanExpress;
    else if (numero_[0] == '3')
        return JCB;
    else if (numero_[0] == '4')
        return VISA;
    else if (numero_[0] == '5')
        return Mastercard;
    else if (numero_[0] == '6')
        return Maestro;
    else
        return Otro;
}

/*** Operadores aritméticos ***/
bool operator< (const Tarjeta& t1, const Tarjeta& t2)
{ return (t1.numero_ < t2.numero_); }

/*** Destructores ***/
Tarjeta::~Tarjeta()
{
    if(Usuario * usuario = const_cast<Usuario*>(titular_))
        usuario->no_es_titular_de(*this);
    tarjetas_.erase(numero_);
}

/*** Métodos privados ***/
void Tarjeta::anula_titular()
{
    titular_ = nullptr;
    activa_ = false;
}

/*** Operadores de flujo ***/
ostream& operator<< (ostream& os, Tarjeta::Tipo t)
{
    switch (t) {
        case Tarjeta::Otro: os << "Tipo indeterminado"; break;
        case Tarjeta::VISA: os << "VISA"; break;
        case Tarjeta::Mastercard: os << "Mastercard"; break;
        case Tarjeta::Maestro: os << "Maestro"; break;
        case Tarjeta::JCB: os << "JCB"; break;
        case Tarjeta::AmericanExpress: os << "AmericanExpress"; break;
    }

    return os;
}

ostream& operator<< (ostream& os, const Tarjeta& tarjeta)
{
    Cadena nombre = tarjeta.titular()->nombre();
    Cadena apellidos = tarjeta.titular()->apellidos();
    for(size_t i=0; i< nombre.length(); i++)
        nombre[i] = toupper(nombre[i]);

    for(size_t j=0; j< apellidos.length(); j++)
        apellidos[j] = toupper(apellidos[j]);

    os << tarjeta.tipo() << "\n";
    os << tarjeta.numero() << "\n";
    os << nombre << " " << apellidos << "\n";
    os << "Caduca: " << setfill('0') << setw(2) << tarjeta.caducidad().mes()
    << '/' << setw(2) << (tarjeta.caducidad().anno() % 100)<< "\n";
    return os;
}
