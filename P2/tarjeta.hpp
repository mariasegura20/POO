#ifndef TARJETA_HPP
#define TARJETA_HPP

#include <iostream>
#include <iomanip>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <set>

#include "../P1/cadena.hpp"
#include "../P1/fecha.hpp"
#include "usuario.hpp"

using namespace std;

class Usuario;

class Numero {
    public:
        enum Razon {LONGITUD, DIGITOS, NO_VALIDO};

        Numero(const Cadena& cad);
        operator const char * () const;
        friend bool operator<(const Numero& num1, const Numero& num2);

        class Incorrecto {
            public:
                Incorrecto(Razon r): Razon(r) {}
                Razon razon() const;
            private:
                Numero::Razon Razon;
        };

    private:
        Cadena num_;
};

/*** Operador de conversión ***/
inline Numero::operator const char * () const
{ return (const char *) num_; }

/*** Operadores aritméticos ***/
inline bool operator<(const Numero& num1, const Numero& num2)
{ return (num1.num_ < num2.num_); }

/*** Observadores ***/
inline Numero::Razon Numero::Incorrecto::razon() const
{ return Razon; }

/*** CLASE TARJETA ***/
class Tarjeta {
    public:
        enum Tipo {Otro, VISA, Mastercard, Maestro, JCB, AmericanExpress};

        typedef set<Numero> Tarjetas;

        Tarjeta(const Numero& num, Usuario& user, const Fecha& f);
        Tarjeta(const Tarjeta&) = delete;
        void operator=(const Tarjeta& ) = delete;

        const Numero& numero() const;
        const Usuario * titular() const;
        const Fecha& caducidad() const;
        bool activa() const;
        bool activa(bool estado);
        Tipo tipo() const;

        friend bool operator< (const Tarjeta& t1, const Tarjeta& t2);

        ~Tarjeta();

        class Caducada {
            public:
                Caducada(const Fecha& caducidad) : f(caducidad) {}
                const Fecha& cuando() const;
            private:
                Fecha f;
        };

        class Num_duplicado {
            public:
                Num_duplicado(const Numero& num) : Numero(num) {}
                const Numero& que() const;
            private:
                Numero Numero;
        };

    private:
        const Numero numero_;
        const Usuario * titular_;
        const Fecha caducidad_;
        bool activa_;

        static Tarjetas tarjetas_;

        friend class Usuario;
        void anula_titular();
};

ostream& operator<< (ostream& os, const Tarjeta& tarjeta);
ostream& operator<< (ostream& os, Tarjeta::Tipo t);

/*** Observadores ***/
inline const Numero& Tarjeta::numero() const
{ return numero_; }

inline const Usuario * Tarjeta::titular() const
{ return titular_; }

inline const Fecha& Tarjeta::caducidad() const
{ return caducidad_; }

inline bool Tarjeta::activa() const
{ return activa_; }

inline const Fecha& Tarjeta::Caducada::cuando() const
{ return f; }

inline const Numero& Tarjeta::Num_duplicado::que() const
{ return Numero; }

#endif
