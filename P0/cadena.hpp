#ifndef CADENA_HPP
#define CADENA_HPP

#include <cstring>

class Cadena {
    public:   
        explicit Cadena(size_t t = 0, char c = ' ');
        Cadena(const char * c);
        Cadena(const Cadena& cad);
        unsigned int length() const noexcept;
        char& at (int indice);
        const char& at (int indice) const;
        Cadena substr(int indice, int t) const;
	explicit operator const char*() const;
	Cadena& operator= (const Cadena& cad);
        Cadena& operator+=(const Cadena& cad);
        const Cadena operator+(const Cadena& cad1) const;
	char& operator[](unsigned int indice); // lectura/escritura
        char operator[](unsigned int indice) const; // lectura
        ~Cadena();
    private:
        int tam_;
        char * s_;
};

bool operator==(const Cadena& cad1, const Cadena& cad2);
bool operator!=(const Cadena& cad1, const Cadena& cad2);
bool operator<(const Cadena& cad1, const Cadena& cad2);
bool operator>(const Cadena& cad1, const Cadena& cad2);
bool operator<=(const Cadena& cad1, const Cadena& cad2);
bool operator>=(const Cadena& cad1, const Cadena& cad2);

// Constructor de copia
inline Cadena::Cadena(const Cadena& cad) : tam_(cad.tam_), s_(new char[tam_+1])
{ strcpy(s_, cad.s_); }

// Observador de tamaño
inline unsigned int Cadena::length() const noexcept{ return(tam_); }

// Operador de conversión
inline Cadena::operator const char*() const
{ return s_; }

// Operador de igualdad
inline bool operator==(const Cadena& cad1, const Cadena& cad2)
{ return(strcmp ((const char*)(cad1.substr(0, cad1.length())), (const char*)(cad2.substr(0, cad2.length()))) == 0); }

// Operador de desigualdad
inline bool operator!=(const Cadena& cad1, const Cadena& cad2)
{ return (!(cad1 == cad2)); }

// Operador de comparación menor que
inline bool operator<(const Cadena& cad1, const Cadena& cad2)
{ return(strcmp ((const char*)(cad1.substr(0, cad1.length())), (const char*)(cad2.substr(0, cad2.length()))) < 0); }

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
