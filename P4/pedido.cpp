#include "pedido.hpp"

int Pedido::N_pedidos = 0;

Pedido::Pedido(Usuario_Pedido& userPed, Pedido_Articulo& pedArt, Usuario& user, const Tarjeta& tarjeta, Fecha fecha)
: num_(N_pedidos + 1), tarjeta_ (&tarjeta), fecha_(fecha), total_(0)
{
    bool carritoVacio = true;
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
        if (ArticuloAlmacenable * artAlm=dynamic_cast<ArticuloAlmacenable*>(art.first)) {
            if(artAlm->stock() < art.second){
                user.vaciar_carro();
                throw SinStock(*art.first);
            }
        }
    }

    for(auto art: user.compra()) {
        if (ArticuloAlmacenable *artAlm = dynamic_cast<ArticuloAlmacenable *>(art.first)) {
            artAlm->stock() -= art.second;
            total_ += art.first->precio() * art.second;
            pedArt.pedir(*this, *art.first, art.first->precio(), art.second);
            carritoVacio = false;
        }
        else {
            LibroDigital * ld = dynamic_cast<LibroDigital *>(art.first);
            if(ld->f_expir() >= fecha) {
                total_ += art.first->precio() * art.second;
                pedArt.pedir(*this, *art.first, art.first->precio(), art.second);
                carritoVacio = false;
            }
        }
    }

    if (carritoVacio)
        throw Vacio(user);

    N_pedidos++;
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