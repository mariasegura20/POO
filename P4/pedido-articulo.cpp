#include "pedido-articulo.hpp"
#include <iomanip>

/***** LINEA DE PEDIDO *****/
/*** Operadores de flujo ***/
ostream& operator << (ostream& os, const LineaPedido& LdP)
{
    os << fixed << setprecision(2) << LdP.precio_venta() << " €\t" << LdP.cantidad();
    return os;
}

bool OrdenaPedidos::operator()(const Pedido * ped1, const Pedido * ped2) const
{ return ped1->numero() < ped2->numero(); }

bool OrdenaArticulos::operator()(const Articulo * art1, const Articulo * art2) const
{ return art1->referencia() < art2->referencia(); }


/***** PEDIDO-ARTÍCULO*****/
/*** Enlace de Asociación ***/
void Pedido_Articulo::pedir (Pedido &ped, Articulo &art, double precio, unsigned int cant)
{
    PedArt_[&ped].insert(make_pair(&art, LineaPedido(precio, cant)));
    ArtPed_[&art].insert(make_pair(&ped, LineaPedido(precio, cant)));
}

void Pedido_Articulo::pedir(Articulo &art, Pedido &ped, double precio, unsigned int cant)
{ pedir(ped,art,precio,cant); }

/*** Observadores ***/
Pedido_Articulo::ItemsPedido Pedido_Articulo::detalle (Pedido& ped) const
{
    if(PedArt_.find(&ped) != PedArt_.end())
        return PedArt_.find(&ped)->second;
    else{
        Pedido_Articulo::ItemsPedido vacio;
        return vacio;
    }
}

Pedido_Articulo::Pedidos Pedido_Articulo::ventas (Articulo& art) const
{
    if(ArtPed_.find(&art) != ArtPed_.end())
        return ArtPed_.find(&art)->second;
    else{
        Pedido_Articulo::Pedidos vacio;
        return vacio;
    }
}

ostream& Pedido_Articulo::mostrarDetallePedidos(ostream& os) const
{
    double total = 0;
    for (auto pedido : PedArt_)
    {
        os << "Pedido núm. " << pedido.first->numero() << endl;
        os << "Cliente: " << pedido.first->tarjeta()->titular()->nombre() << "          Fecha: " << pedido.first->fecha() << endl;
        total += pedido.first->total();
        Pedido& ped = *pedido.first;
        os << detalle(ped);
        os << "TOTAL VENTAS          " << fixed << setprecision(2) << total << " € " << endl << endl;
    }

    return os;
}
ostream& Pedido_Articulo::mostrarVentasArticulos(ostream &os) const
{
    for (auto iter : ArtPed_)
    {
        os << "Venta de [" << iter.first->referencia() << "] \"" << iter.first->titulo() << "\"" << endl;
        Articulo& art = *iter.first;
        os << ventas(art) << endl << endl;
    }
    return os;
}

/*** Operadores de flujo ***/
ostream& operator<< (ostream& os, const Pedido_Articulo::ItemsPedido& iP)
{
    double total = 0;

    os << "PVP \tCantidad \tArtículo" << endl;
    os << "==================================================================" << endl;
    for (auto& it : iP)
    {
        os << setprecision(2) << it.second.precio_venta() << " €\t" << it.second.cantidad() << "\t\t[" << it.first->referencia() << "] \"" << it.first->titulo() << "\"" << endl;
        total += (it.second.precio_venta() * it.second.cantidad());
    }
    os << "==================================================================" << endl;
    os << "Total:   " << fixed << setprecision(2) << total << endl;

    return os;
}

ostream& operator<< (ostream& os, const Pedido_Articulo::Pedidos& ped)
{
    double totalImporte = 0;
    int totalCant = 0;

    os << "[Pedidos: " << Pedido::n_total_pedidos() << "]" << endl;
    os << "==================================================================" << endl;
    os << "PVP \tCantidad \tFecha de venta" << endl;
    os << "==================================================================" << endl;
    for (auto& it : ped)
    {
        os << fixed << setprecision(2) << it.second.precio_venta() << " €\t" << it.second.cantidad() << "\t\t" << it.first->fecha() << endl;
        totalImporte += (it.second.precio_venta() * it.second.cantidad());
        totalCant += it.second.cantidad();
    }
    os << "==================================================================" << endl;
    os << fixed << setprecision(2) << totalImporte << " €        " << totalCant << endl;

    return os;
}