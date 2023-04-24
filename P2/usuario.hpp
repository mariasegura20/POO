#ifndef USUARIO_HPP
#define USUARIO_HPP

#include <iostream>
#include <map>
#include <unordered_map>
#include <unistd.h>
#include <iomanip>
#include <cstring>
#include <unordered_set>
#include <cstdlib>

#include "../P1/cadena.hpp"
#include "tarjeta.hpp"
#include "articulo.hpp"

using namespace std;

/*** CLASE CLAVE ***/
class Clave {
    public:
        enum Razon{CORTA, ERROR_CRYPT};

        Clave(const char * claro);

        const Cadena& clave() const;
        bool verifica (const char * claro) const;

        class Incorrecta {
            public:
                Incorrecta(Razon razon) : razon_(razon) {}
                Razon razon() const;
            private:
                Razon razon_;
        };
    private:
        Cadena clave_;
        char cifrado[2];
};

/*** Observadores ***/
inline const Cadena& Clave::clave() const
{ return clave_; }

inline Clave::Razon Clave::Incorrecta::razon() const
{ return razon_; }

/*** CLASE USUARIO ***/

class Tarjeta;
class Numero;

class Usuario {
    public:
        typedef map<Numero, Tarjeta*> Tarjetas;
        typedef unordered_map<Articulo*, unsigned int> Articulos;
        typedef unordered_set<Cadena> Usuarios;

        Usuario(const Cadena& id, const Cadena& nombre, const Cadena& apellidos, const Cadena& direccion, const Clave& clave);
        Usuario(const Usuario&) = delete;
        void operator=(const Usuario&) = delete;

        const Cadena& id() const;
        const Cadena& nombre() const;
        const Cadena& apellidos() const;
        const Cadena& direccion() const;
        const Tarjetas& tarjetas() const;
        const Articulos& compra() const;

        void es_titular_de(Tarjeta& t);
        void no_es_titular_de(Tarjeta& t);

        void compra(Articulo& art, unsigned int cantidad = 1);
        void vaciar_carro();
        int n_articulos() const;

        friend ostream& operator<< (ostream& os, const Usuario& user);
        friend ostream& mostrar_carro(ostream& os, const Usuario& user);

        ~Usuario();

        class Id_duplicado {
            public:
                Id_duplicado(const Cadena& cad) : id(cad) {}
                const Cadena& idd() const;
            private:
                Cadena id;
        };
    private:
        const Cadena id_;
        const Cadena nombre_;
        const Cadena apellidos_;
        const Cadena direccion_;
        Clave clave_;
        Tarjetas tarjetas_;
        Articulos compra_;
        static Usuarios ids;
};

/*** OBSERVADORES ***/
inline const Cadena& Usuario::id() const
{ return id_; }

inline const Cadena& Usuario::nombre() const
{ return nombre_; }

inline const Cadena& Usuario:: apellidos() const
{ return apellidos_; }

inline const Cadena& Usuario::direccion() const
{ return direccion_; }

inline const Usuario::Tarjetas& Usuario::tarjetas() const
{ return tarjetas_; }

inline const Usuario::Articulos& Usuario::compra() const
{ return compra_; }

inline const Cadena& Usuario::Id_duplicado::idd() const
{ return id; }

#endif
