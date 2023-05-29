#ifndef ARTICULO_HPP
#define ARTICULO_HPP

#include "../P1/cadena.hpp"
#include "../P1/fecha.hpp"

#include <set>

using namespace std;

class Autor {
    public:
        Autor(const Cadena& nombre, const Cadena& apellidos, const Cadena& direccion) : nombre_(nombre), apellidos_(apellidos), direccion_(direccion) {}

        const Cadena& nombre() const noexcept { return nombre_; }
        const Cadena& apellidos() const noexcept { return apellidos_; }
        const Cadena& direccion() const noexcept { return direccion_; }

    private:
        const Cadena nombre_;
        const Cadena apellidos_;
        const Cadena direccion_;
};

class Articulo {
	public:
        typedef set<Autor *> Autores;

		Articulo(Autores autor, const Cadena& referencia, const Cadena& titulo, const Fecha& f_publi, double precio);
		
		const Cadena& referencia() const { return referencia_; }
		const Cadena& titulo() const { return titulo_; }
		const Fecha& f_publi() const { return f_publi_; }
        double precio() const { return precio_; }
		double& precio() { return precio_; }
        const Autores& autores() const { return autor_; }

        void impresion_general(ostream&) const;
        virtual void impresion_especifica(ostream&) const = 0;

        virtual ~Articulo() {}

        class Autores_vacios {};

    protected:
		const Cadena referencia_;
		const Cadena titulo_;
		const Fecha f_publi_;
		double precio_;

        Autores autor_;
};

class ArticuloAlmacenable : public Articulo {
    public:
        explicit ArticuloAlmacenable(Autores autor, const Cadena& referencia, const Cadena& titulo, const Fecha& f_publi, double precio, unsigned int stock = 0) : stock_(stock), Articulo(autor,referencia,titulo,f_publi,precio) {}
        unsigned int& stock() { return stock_; }
        unsigned int stock() const { return stock_; }
        virtual void impresion_especifica(ostream&) const = 0;
    protected:
        unsigned int stock_;
};

class Libro : public ArticuloAlmacenable {
    public:
        Libro(Autores autor, const Cadena& referencia, const Cadena& titulo, const Fecha& f_publi, double precio, int n_pag, unsigned int stock = 0) : n_pag_(n_pag), ArticuloAlmacenable(autor,referencia,titulo,f_publi,precio, stock) {}
        int n_pag() const { return n_pag_; }
        void impresion_especifica(ostream&) const;
    private:
        const int n_pag_;
};

class Revista : public ArticuloAlmacenable {
    public:
        Revista(Autores autor, const Cadena& referencia, const Cadena& titulo, const Fecha& f_publi, double precio, unsigned int numero, int periodicidad, unsigned int stock = 0) : numero_(numero), periodicidad_(periodicidad), ArticuloAlmacenable(autor,referencia,titulo,f_publi,precio, stock) {}
        unsigned int numero() const { return numero_; }
        int periodicidad() const { return periodicidad_; }
        void impresion_especifica(ostream&) const;
    private:
        const unsigned int numero_;
        const int periodicidad_;
};

class LibroDigital : public Articulo {
    public:
        LibroDigital(Autores autor, const Cadena& referencia, const Cadena& titulo, const Fecha& f_publi, double precio, const Fecha& f_expir) : f_expir_(f_expir), Articulo(autor, referencia, titulo, f_publi, precio) {}
        const Fecha& f_expir() const { return f_expir_; }
        void impresion_especifica(ostream&) const;
    private:
        const Fecha f_expir_;
};

ostream& operator<< (ostream& os, const Articulo& art);

#endif
