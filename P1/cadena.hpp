#ifndef CADENA_HPP
#define CADENA_HPP

#include <cstring>

using namespace std;

class Cadena {
	public:   
		explicit Cadena(size_t t = 0, char c = ' ');
		Cadena(const char * c);
		Cadena(const Cadena& cad);
		Cadena(Cadena&& cad);
		
		Cadena& operator= (const Cadena& cad);
		Cadena& operator= (const char * cad);
		Cadena& operator= (Cadena&& cad);
		
		explicit operator const char*() const;
		
		unsigned int length() const noexcept;
		char& at (int indice);
		const char& at (int indice) const;
		Cadena substr(int indice, int t) const;
		char& operator[](unsigned int indice);
		char operator[](unsigned int indice) const;
		
		Cadena& operator+=(const Cadena& cad);
		const Cadena operator+(const Cadena& cad1) const;
		
		typedef char * iterator;
		typedef const char * const_iterator;
		typedef std::reverse_iterator<iterator> reverse_iterator;
		typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
		iterator begin() const;
		iterator end() const;
		const_iterator cbegin() const;
		const_iterator cend() const;
		reverse_iterator rbegin() const;
		reverse_iterator rend() const;
		const_reverse_iterator crbegin() const;
		const_reverse_iterator crend() const;
		
		~Cadena();
	private:
		int tam_;
		char * s_;
};

ostream& operator<<(ostream& os, const Cadena& cad);
istream& operator>>(istream& is, Cadena& cad);

bool operator==(const Cadena& cad1, const Cadena& cad2);
bool operator!=(const Cadena& cad1, const Cadena& cad2);
bool operator<(const Cadena& cad1, const Cadena& cad2);
bool operator>(const Cadena& cad1, const Cadena& cad2);
bool operator<=(const Cadena& cad1, const Cadena& cad2);
bool operator>=(const Cadena& cad1, const Cadena& cad2);

/*** CONSTRUCTORES ***/
// Constructor de copia
inline Cadena::Cadena(const Cadena& cad) : tam_(cad.tam_), s_(new char[tam_+1])
{ strcpy(s_, cad.s_); }


/*** OPERADOR DE CONSERVIÓN ***/
inline Cadena::operator const char*() const
{ return s_; }

/*** OBSERVADORES ***/
// Observador de tamaño
inline unsigned int Cadena::length() const noexcept{ return(tam_); }

// Operador [] lectura/escritura
inline char& Cadena::operator[](unsigned int indice) { return(s_[indice]); }

// Operador [] lectura
inline char Cadena::operator[](unsigned int indice) const { return(s_[indice]); }

/*** OPERADORES DE COMPARACIÓN ***/
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

/*** ITERADORES ***/
inline Cadena::iterator Cadena::begin() const
{ return s_; }

inline Cadena::iterator Cadena::end() const
{ return s_ + length(); }

inline Cadena::const_iterator Cadena::cbegin() const
{ return s_; }

inline Cadena::const_iterator Cadena::cend() const
{ return s_ + length();}

inline Cadena::reverse_iterator Cadena::rbegin() const
{ return reverse_iterator(end()); }

inline Cadena::reverse_iterator Cadena::rend() const
{ return reverse_iterator(begin()); }

inline Cadena::const_reverse_iterator Cadena::crbegin() const
{ return const_reverse_iterator(end()); }

inline Cadena::const_reverse_iterator Cadena::crend() const
{ return const_reverse_iterator(begin()); }

#endif
