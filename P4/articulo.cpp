#include <iostream>
#include <iomanip>

#include "articulo.hpp"

using namespace std;

Articulo::Articulo(Autores autor, const Cadena& referencia, const Cadena& titulo, const Fecha& f_publi, double precio) : referencia_(referencia), titulo_(titulo), f_publi_(f_publi), precio_(precio)
{
    if (autor.empty())
        throw Autores_vacios();

    autor_.insert(autor.begin(), autor.end());
}

ostream& operator<< (ostream& os, const Articulo& art)
{
    art.impresion_general(os);
    art.impresion_especifica(os);
    return os;
}

void Articulo::impresion_general(ostream & os) const
{
    os << "[" << referencia() << "] ";
    os << '"' << titulo() << "\", de ";
    auto last = autores().end();
    last--;
    for (auto iter : autores())
    {
        os << (*iter).apellidos();
        if (iter != (*last))
            os << ", ";
        else
            os << ". ";
    }
    os << f_publi().anno() << ". ";
    os << fixed << setprecision(2) << precio() << " €" << endl << "\t";
}

void Libro::impresion_especifica(ostream & os) const
{ os << n_pag_ << " págs., " << stock_ << " unidades."; }

void Revista::impresion_especifica(ostream & os) const
{
    os << "Número: " << numero_ << ", Periodicidad: " << periodicidad_ << " días." << endl;
    os << "\tPróximo número a partir de: " << f_publi_+periodicidad_ << ".";
}

void LibroDigital::impresion_especifica(ostream & os) const
{ os << "A la venta hasta el " << f_expir_ << "."; }