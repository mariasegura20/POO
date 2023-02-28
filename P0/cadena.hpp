#ifndef CADENA_HPP
#define CADENA_HPP

class Cadena {
    public:
        Cadena(unsigned t, const char* c);
        explicit Cadena(int) {}
        Cadena(const Cadena& cad);
        int length() const;
        const Cadena& operator+=(const Cadena& cad);
        const Cadena& operator+(const Cadena& cad1);
        friend bool operator==(const Cadena& cad1, const Cadena& cad2);
        friend bool operator!=(const Cadena& cad1, const Cadena& cad2);
        friend bool operator<(const Cadena& cad1, const Cadena& cad2);
        friend bool operator>(const Cadena& cad1, const Cadena& cad2);
        friend bool operator<=(const Cadena& cad1, const Cadena& cad2);
        friend bool operator>=(const Cadena& cad1, const Cadena& cad2);
        char operator[](unsigned indice); // lectura
        char operator[](unsigned indice) const; // lectura/escritura
        const Cadena& substr(unsigned indice, unsigned t);
    private:
        char * s_;
        unsigned tam_;
};

inline int Cadena::length() const { return(tam_); }

inline const Cadena& Cadena::operator+(const Cadena& cad) { return (*this += cad); }

inline bool operator!=(const Cadena& cad1, const Cadena& cad2)
{ return (!(cad1 == cad2)); }

inline bool operator>(const Cadena& cad1, const Cadena& cad2)
{ return (!(cad1 < cad2) && !(cad1 == cad2)); }

inline bool operator>=(const Cadena& cad1, const Cadena& cad2)
{ return (!(cad1 < cad2)); }

inline bool operator<=(const Cadena& cad1, const Cadena& cad2)
{ return ((cad1 < cad2) || (cad1 == cad2)); }

inline char Cadena::operator[](unsigned indice) { return(s_[indice]); }

inline char Cadena::operator[](unsigned indice) const { return(s_[indice]); }

#endif