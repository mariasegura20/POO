#ifndef FECHA_HPP_
#define FECHA_HPP_
#include <ctime>

using namespace std;

class Fecha {
    public:
    	static const int AnnoMinimo = 1902;
        static const int AnnoMaximo = 2037;
    
        explicit Fecha(int d = 0, int m = 0, int a = 0);
        Fecha(const char * s);
        Fecha(const Fecha& f);
        int dia() const;
        int mes() const;
        int anno() const;
        Fecha& operator= (const Fecha& fecha);
        Fecha operator++ (int d);
        Fecha& operator++ ();
        Fecha operator-- (int d);
        Fecha& operator-- ();
        Fecha operator+ (int d) const;
        Fecha operator- (int d) const;
        Fecha& operator += (int d);
        Fecha& operator -= (int d);
        operator const char*();
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
        void valida();
};

// Observador del día
inline int Fecha::dia() const { return dia_; }

// Observador del mes
inline int Fecha::mes() const { return mes_; }

// Observador del año
inline int Fecha::anno() const { return anno_; }

// Operador de resta en asignación
inline Fecha& Fecha::operator-= (int d) { return (*this += -d); }

// Operador de igualdad
inline bool operator==(const Fecha& fecha1, const Fecha& fecha2)
{ return (fecha1.dia_ == fecha2.dia_ && fecha1.mes_ == fecha2.mes_ && fecha1.anno_ == fecha2.anno_); }

// Operador de desigualdad
inline bool operator!=(const Fecha& fecha1, const Fecha& fecha2)
{ return (!(fecha1 == fecha2)); }

// Operador de comparación menor que
inline bool operator<(const Fecha& fecha1, const Fecha& fecha2)
{ return (fecha1.anno_ < fecha2.anno_ || (fecha1.anno_ == fecha2.anno_ && fecha1.mes_ < fecha2.mes_) || (fecha1.anno_ == fecha2.anno_ && fecha1.mes_ == fecha2.mes_ && fecha1.dia_ < fecha2.dia_)); }

// Operador de comparación mayor que
inline bool operator>(const Fecha& fecha1, const Fecha& fecha2)
{ return (!(fecha1 < fecha2) && !(fecha1 == fecha2)); }

// Operador de comparación menor o igual que
inline bool operator<=(const Fecha& fecha1, const Fecha& fecha2)
{ return (fecha1 < fecha2 || fecha1 == fecha2); }

// Operador de comparación mayor o igual que
inline bool operator>=(const Fecha& fecha1, const Fecha& fecha2)
{ return (!(fecha1 < fecha2)); }

/*** Clase Invalida ***/
inline const char * Fecha::Invalida::por_que() const { return (motivo); }

#endif
