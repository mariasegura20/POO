#ifndef FECHA_HPP_
#define FECHA_HPP_
#include <ctime>

using namespace std;

class Fecha {
    public:
        Fecha(int d = 0, int m = 0, int a = 0);
        explicit Fecha(int) {}
        Fecha(const Fecha& f) : dia_(f.dia_), mes_(f.mes_), anno_(f.anno_) {};
        Fecha(const char * s);
        int dia() const;
        int mes() const;
        int anno() const;
        const Fecha& operator= (const Fecha& fecha);
        const Fecha& operator++ ();
        const Fecha& operator-- ();
        const Fecha& operator+ (int d);
        const Fecha& operator- (int d);
        const Fecha& operator+= (int d);
        const Fecha& operator-= (int d);
        friend ostream& operator<<(ostream& os, const Fecha& fecha);
        friend bool operator==(const Fecha& fecha1, const Fecha& fecha2);
        friend bool operator!=(const Fecha& fecha1, const Fecha& fecha2);
        friend bool operator<(const Fecha& fecha1, const Fecha& fecha2);
        friend bool operator>(const Fecha& fecha1, const Fecha& fecha2);
        friend bool operator>=(const Fecha& fecha1, const Fecha& fecha2);
        friend bool operator<=(const Fecha& fecha1, const Fecha& fecha2);
        
        class Invalida {
            public:
                Invalida(const char * fallo):motivo(fallo){}
                const char * por_que() const;
            private:
                const char * motivo;
        };

    private:
        int dia_, mes_, anno_;
        static const int AnnoMinimo = 1902;
        static const int AnnoMaximo = 2037;
        void valida();
};

// Observadores "inline"
inline int Fecha::dia() const { return dia_; }

inline int Fecha::mes() const { return mes_; }

inline int Fecha::anno() const { return anno_; }

// Sobrecarga de operadores aritméticos "inline"
inline const Fecha& Fecha::operator++ () { return (*this += 1); }

inline const Fecha& Fecha::operator-- () { return (*this += -1); }

inline const Fecha& Fecha::operator+ (int d) { return (*this += d); }

inline const Fecha& Fecha::operator- (int d) { return (*this += -d); }

inline const Fecha& Fecha::operator-= (int d) { return (*this += -d); }

// Sobrecarga de operadores comparadores "inline"
inline bool operator==(const Fecha& fecha1, const Fecha& fecha2)
{ return (fecha1.dia_ == fecha2.dia_ && fecha1.mes_ == fecha2.mes_ && fecha1.anno_ == fecha2.anno_); }

inline bool operator!=(const Fecha& fecha1, const Fecha& fecha2)
{ return (!(fecha1 == fecha2)); }

inline bool operator<(const Fecha& fecha1, const Fecha& fecha2)
{ return (fecha1.anno_ < fecha2.anno_ || (fecha1.anno_ == fecha2.anno_ && fecha1.mes_ < fecha2.mes_) || (fecha1.anno_ == fecha2.anno_ && fecha1.mes_ == fecha2.mes_ && fecha1.dia_ < fecha2.dia_)); }

inline bool operator>(const Fecha& fecha1, const Fecha& fecha2)
{ return (!(fecha1 < fecha2) && !(fecha1 == fecha2)); }

inline bool operator<=(const Fecha& fecha1, const Fecha& fecha2)
{ return (fecha1 < fecha2 || fecha1 == fecha2); }

inline bool operator>=(const Fecha& fecha1, const Fecha& fecha2)
{ return (!(fecha1 < fecha2)); }

/*** Clase Invalida ***/
inline const char * Fecha::Invalida::por_que() const { return (motivo); }

#endif