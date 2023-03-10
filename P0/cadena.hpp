#ifndef CADENA_HPP
#define CADENA_HPP

#include <cstring>

class Cadena {
    public:   
        Cadena(unsigned int t = 0, char c = ' ');
        Cadena(const char * c);
        Cadena(const Cadena& cad);
        int length() const;
        char& at (unsigned int indice);
        const char& at (unsigned int indice) const;
        Cadena substr(unsigned int indice, unsigned int t) const;
        Cadena& operator= (const Cadena& cad);
	explicit operator const char*() const;
        Cadena& operator+=(const Cadena& cad);
        const Cadena operator+(const Cadena& cad1) const;
        friend bool operator==(const Cadena& cad1, const Cadena& cad2);
        friend bool operator!=(const Cadena& cad1, const Cadena& cad2);
        friend bool operator<(const Cadena& cad1, const Cadena& cad2);
        friend bool operator>(const Cadena& cad1, const Cadena& cad2);
        friend bool operator<=(const Cadena& cad1, const Cadena& cad2);
        friend bool operator>=(const Cadena& cad1, const Cadena& cad2);
	char& operator[](unsigned int indice); // lectura/escritura
        char operator[](unsigned int indice) const; // lectura
        ~Cadena();
    private:
        char * s_;
        unsigned int tam_;
};

// Constructor de copia
inline Cadena::Cadena(const Cadena& cad) : tam_(cad.tam_), s_(new char[tam_+1])
{ strcpy(s_, cad.s_); }

// Observador de tamaño
inline int Cadena::length() const { return(tam_); }

// Operador de conversión
inline Cadena::operator const char*() const
{ return s_; }

// Operador de suma
inline const Cadena Cadena::operator+(const Cadena& cad) const
{ 
    Cadena copia(*this);
    copia += cad;
    return copia;
}

// Operador de igualdad
inline bool operator==(const Cadena& cad1, const Cadena& cad2)
{ return(strcmp(cad1.s_, cad2.s_) == 0); }

// Operador de desigualdad
inline bool operator!=(const Cadena& cad1, const Cadena& cad2)
{ return (!(cad1 == cad2)); }

// Operador de comparación menor que
inline bool operator<(const Cadena& cad1, const Cadena& cad2)
{ return(strcmp(cad1.s_, cad2.s_) < 0); }

// Operador de comparación mayor que
inline bool operator>(const Cadena& cad1, const Cadena& cad2)
{ return (!(cad1 < cad2) && !(cad1 == cad2)); }

// Operador de comparación menor o igual que
inline bool operator<=(const Cadena& cad1, const Cadena& cad2)
{ return ((cad1 < cad2) || (cad1 == cad2)); }

// Operador de comparación mayor o igual que
inline bool operator>=(const Cadena& cad1, const Cadena& cad2)
{ return (!(cad1 < cad2)); }

// Operador [] 
inline char& Cadena::operator[](unsigned int indice) { return(s_[indice]); }

inline char Cadena::operator[](unsigned int indice) const { return(s_[indice]); }

#endif
