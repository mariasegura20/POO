#include <map>
#include <set>

#include "usuario-pedido.hpp"
#include "usuario.hpp"
#include "pedido.hpp"

using namespace std;

void Usuario_Pedido::asocia(Usuario &user, Pedido &ped)
{
    usuarios_[&user].insert(&ped);
    pedidos_[&ped] = &user;
}

void Usuario_Pedido::asocia(Pedido &ped, Usuario &user)
{ asocia(user, ped); }

Usuario_Pedido::Pedidos Usuario_Pedido::pedidos(Usuario &user) const
{
    if (usuarios_.find(&user) != usuarios_.end())
        return usuarios_.find(&user)->second;
    else
        return Pedidos();
}

Usuario * Usuario_Pedido::cliente(Pedido &ped) const
{
    if (pedidos_.find(&ped) != pedidos_.end())
        return pedidos_.find(&ped)->second;
    else
        return nullptr;
}