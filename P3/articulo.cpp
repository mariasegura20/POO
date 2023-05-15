#include <iostream>
#include <iomanip>

#include "articulo.hpp"

using namespace std;

ostream& operator<< (ostream& os, Articulo& art)
{
	os << "[" << art.referencia() << "] ";
    os << '"' << art.titulo() << "\", ";
    os << art.f_publi().anno() << ". ";
    os << setprecision(2) << art.precio() << " €";
    return os;
}
