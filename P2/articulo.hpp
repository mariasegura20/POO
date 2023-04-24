#ifndef ARTICULO_HPP
#define ARTICULO_HPP

#include "../P1/cadena.hpp"
#include "../P1/fecha.hpp"

using namespace std;

class Articulo {
	public:
		Articulo(const Cadena& referencia, const Cadena& titulo, const Fecha& f_publi, float precio, int stock = 0) : referencia_(referencia), titulo_(titulo), f_publi_(f_publi), precio_(precio), stock_(stock) {}
		
		const Cadena& referencia() const;
		const Cadena& titulo() const;
		const Fecha& f_publi() const;
		float& precio();
		int& stock();

	private:
		const Cadena referencia_;
		const Cadena titulo_;
		const Fecha f_publi_;
		float precio_;
		int stock_;
};

ostream& operator<< (ostream& os, Articulo& art);

/*** OBSERVADORES ***/
inline const Cadena& Articulo::referencia() const
{ return referencia_; }

inline const Cadena& Articulo::titulo() const
{ return titulo_; }

inline const Fecha& Articulo::f_publi() const
{ return f_publi_; }

inline float& Articulo::precio()
{ return precio_; }

inline int& Articulo::stock()
{ return stock_; }

#endif
