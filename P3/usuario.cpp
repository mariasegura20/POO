#include "usuario.hpp"
#include "tarjeta.hpp"
#include "articulo.hpp"

#include <random>

using namespace std;

/*** CLASE CLAVE ***/
/*** Constructores ***/
Clave::Clave(const char* claro) {
    if (strlen(claro) < 5)
        throw Clave::Incorrecta(CORTA);
    else {
        const char * semilla = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789./";

        random_device rd;
        uniform_int_distribution<int> dist(0,strlen(semilla));

        char cifrado[3];
        cifrado[0] = semilla[dist(rd)];
        cifrado[1] = semilla[dist(rd)];
        cifrado[2] = '\0';

        char * pass = crypt(claro, cifrado);
        if (pass == nullptr)
            throw Clave::Incorrecta(ERROR_CRYPT);
        clave_ = Cadena(pass);
    }
}

/*** Observadores ***/
bool Clave::verifica (const char * claro) const
{
    return (crypt(claro, clave_.operator const char *()) == clave_);
}

/*** CLASE USUARIO ***/
Usuario::Usuarios Usuario::ids;

/*** Constructores ***/
Usuario::Usuario(const Cadena& id, const Cadena& nombre, const Cadena& apellidos, const Cadena& direccion, const Clave& clave) : id_(id), nombre_(nombre), apellidos_(apellidos), direccion_(direccion), clave_(clave)
{
	if (!ids.insert(id).second)
		throw Id_duplicado(id);
}

/*** Asociación con Tarjetas ***/
void Usuario::es_titular_de(Tarjeta& T){
    if (this == T.titular())
        tarjetas_.insert(std::make_pair(T.numero(), &T));
}

void Usuario::no_es_titular_de(Tarjeta& T){
    T.anula_titular();
    tarjetas_.erase(T.numero());
}

/*** Asociación con Articulo ***/
void Usuario::compra(Articulo& art, unsigned int cantidad)
{
	if (cantidad == 0)
		compra_.erase(&art);
	else
        compra_[&art] = cantidad;
}

void Usuario::vaciar_carro()
{ compra_.clear(); }

int Usuario::n_articulos() const
{ return compra_.size(); }

/*** Operadores ***/
ostream& operator<< (ostream& os, const Usuario& user)
{
	os << user.id() << " [" << user.clave_.clave() << "] " << user.nombre() << " " << user.apellidos() << "\n";
	os << user.direccion() << "\n";
	os << "Tarjetas:" << "\n";
	for (auto& t:user.tarjetas_)
		os << t.second->numero() << "\n";
	return os;
}

ostream& mostrar_carro(ostream& os, const Usuario& user){
	os << "Carrito de la compra de " <<user.id_<<"[Artículos: " << user.n_articulos() << "]\n";
    for(auto& art:user.compra_)
        os << art.second << " [" << art.first->referencia() << "] \"" << art.first->titulo() << "\", " << art.first->f_publi().anno() << ". " << fixed << setprecision(2) << art.first->precio() << " €" << endl;

    os << endl;
    return os;
}

/*** Destructores ***/
Usuario::~Usuario()
{
    for (auto& t:tarjetas_)
    	t.second->anula_titular();
    ids.erase(id_);
}
