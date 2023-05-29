#ifndef PEDIDO_ARTICULO_HPP
#define PEDIDO_ARTICULO_HPP

#include <iostream>
#include <map>

#include "pedido.hpp"

class Articulo;
class Pedido;

using namespace std;

/***** LINEA DE PEDIDO *****/
class LineaPedido {
    public:
        explicit LineaPedido(double precio, unsigned int cantidad = 1) : precio_venta_(precio), cantidad_(cantidad) {}
        double precio_venta() const { return precio_venta_; }
        unsigned int cantidad() const { return cantidad_; }
    private:
        double precio_venta_;
        unsigned int cantidad_;
};

ostream& operator << (ostream& os, const LineaPedido& LdP);

/***** PEDIDO-ARTÍCULO*****/

class OrdenaArticulos {
    public:
        bool operator() (const Articulo * art1, const Articulo * art2) const;
};

class OrdenaPedidos {
    public:
        bool operator() (const Pedido * ped1, const Pedido * ped2) const;
};

class Pedido_Articulo {
    public:
        typedef map<Articulo *, LineaPedido, OrdenaArticulos> ItemsPedido;
        typedef map<Pedido *, LineaPedido, OrdenaPedidos> Pedidos;

        void pedir (Pedido& ped, Articulo& art, double precio, unsigned int cant = 1);
        void pedir (Articulo& art, Pedido& ped, double precio, unsigned int cant = 1);

        ItemsPedido detalle (Pedido& ped) const;
        Pedidos ventas (Articulo& art) const;

        ostream& mostrarDetallePedidos(ostream& os) const;
        ostream& mostrarVentasArticulos(ostream& os) const;

    private:
        map<Pedido *, ItemsPedido, OrdenaPedidos> PedArt_;
        map<Articulo *, Pedidos, OrdenaArticulos> ArtPed_;
};

ostream& operator<< (ostream& os, const Pedido_Articulo::ItemsPedido& iP);
ostream& operator<< (ostream& os, const Pedido_Articulo::Pedidos& ped);

#endif