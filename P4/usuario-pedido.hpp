#ifndef USUARIO_PEDIDO_HPP
#define USUARIO_PEDIDO_HPP

#include <iostream>
#include <map>
#include <set>

using namespace std;

class Usuario;
class Pedido;

class Usuario_Pedido  {
    public:
        typedef set<Pedido *> Pedidos;

        void asocia(Usuario& user, Pedido& ped);
        void asocia(Pedido& ped, Usuario& user);

        Pedidos pedidos (Usuario& user) const;
        Usuario * cliente (Pedido& ped) const;

    private:
        typedef map<Usuario *, Pedidos> UsuariosPedidos;
        typedef map<Pedido *, Usuario *> PedidosUsuarios;

        UsuariosPedidos usuarios_;
        PedidosUsuarios pedidos_;
};

#endif