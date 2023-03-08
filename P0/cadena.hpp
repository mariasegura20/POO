#ifndef CADENA_HPP
#define CADENA_HPP

class Cadena {
    public:
        explicit Cadena(unsigned int t = 0, char c = ' ');
        Cadena(const char * c);
        Cadena(const Cadena& cad);
        int length() const;
        char at (unsigned int indice) const;
        Cadena substr(unsigned int indice, unsigned int t) const;
	operator const char*() const;
        const Cadena& operator+=(const Cadena& cad);
        const Cadena& operator+(const Cadena& cad1);
        friend bool operator==(const Cadena& cad1, const Cadena& cad2);
        friend bool operator==(const char* s, const Cadena& cad);
        friend bool operator==(const Cadena& cad, const char* s);
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

inline int Cadena::length() const { return(tam_); }

inline const Cadena& Cadena::operator+(const Cadena& cad) { return (*this += cad); }

inline bool operator==(const Cadena& cad, const char* s)
{ return s == cad; }

inline bool operator!=(const Cadena& cad1, const Cadena& cad2)
{ return (!(cad1 == cad2)); }

inline bool operator>(const Cadena& cad1, const Cadena& cad2)
{ return (!(cad1 < cad2) && !(cad1 == cad2)); }

inline bool operator>=(const Cadena& cad1, const Cadena& cad2)
{ return (!(cad1 < cad2)); }

inline bool operator<=(const Cadena& cad1, const Cadena& cad2)
{ return ((cad1 < cad2) || (cad1 == cad2)); }

inline char& Cadena::operator[](unsigned int indice) { return(s_[indice]); }

inline char Cadena::operator[](unsigned int indice) const { return(s_[indice]); }

inline Cadena::operator const char*() const {
	return s_;
}

#endif
