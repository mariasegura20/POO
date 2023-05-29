#ifndef PEDIDO_HPP
#define PEDIDO_HPP

#include <iostream>

#include "tarjeta.hpp"
#include "../P1/fecha.hpp"
#include "usuario-pedido.hpp"
#include "pedido-articulo.hpp"
#include "usuario.hpp"

using namespace std;

class Pedido_Articulo;

class Pedido {
    public:
        Pedido(Usuario_Pedido& userPed, Pedido_Articulo& pedArt, Usuario& user, const Tarjeta& tarjeta, Fecha fecha = Fecha());

        int numero() const { return num_; }
        const Tarjeta * tarjeta() const { return tarjeta_; }
        const Fecha& fecha() const { return fecha_; }
        double total() const { return total_; }
        static int n_total_pedidos() { return N_pedidos; }

        class Vacio {
            public:
                Vacio(const Usuario& user) : usuario_(&user) {}
                const Usuario& usuario() const { return *usuario_; }
            private:
                const Usuario * usuario_;
        };

        class Impostor {
            public:
                Impostor(const Usuario& user) : usuario_(&user) {}
                const Usuario& usuario() const { return *usuario_; }
            private:
                const Usuario * usuario_;
        };

        class SinStock {
            public:
                SinStock(const Articulo& articulo) : articulo_(&articulo) {}
                const Articulo& articulo() const { return *articulo_; }
            private:
                const Articulo * articulo_;
        };

    private:
        static int N_pedidos;
        int num_;
        const Tarjeta * tarjeta_;
        Fecha fecha_;
        double total_;
};

ostream& operator << (ostream& os, const Pedido& ped);

#endif