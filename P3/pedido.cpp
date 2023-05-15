#include "pedido.hpp"

int Pedido::N_pedidos = 0;

Pedido::Pedido(Usuario_Pedido& userPed, Pedido_Articulo& pedArt, Usuario& user, const Tarjeta& tarjeta, Fecha fecha)
: num_(N_pedidos + 1), tarjeta_ (&tarjeta), fecha_(fecha), total_(0)
{
    if (user.compra().empty())
        throw Vacio(user);
    if (&user != tarjeta.titular())
        throw Impostor(user);
    if (tarjeta.caducidad() < fecha)
        throw Tarjeta::Caducada(tarjeta.caducidad());
    if (!tarjeta.activa())
        throw Tarjeta::Desactivada();

    for (auto art: user.compra())
    {
        if(art.first->stock() < art.second){
            user.vaciar_carro();
            throw SinStock(*art.first);
        }
    }

    N_pedidos++;

    for(auto art: user.compra()){
        total_ += art.first->precio() * art.second;
        art.first->stock() -= art.second;
        pedArt.pedir(*this, *art.first, art.first->precio(), art.second);
    }

    userPed.asocia(*this, user);

    user.vaciar_carro();
}

ostream& operator << (ostream& os, const Pedido& ped)
{
    os << "Núm. pedido: \t" << ped.numero() << endl;
    os << "Fecha: \t\t" << ped.fecha() << endl;
    os << "Pagado con: \t" << ped.tarjeta()->tipo() << " n.º: " << ped.tarjeta()->numero() << endl;
    os << "Importe: \t" << fixed << setprecision(2) << ped.total() << " €" << endl;
    return os;
}