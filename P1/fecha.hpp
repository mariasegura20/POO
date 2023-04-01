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
		int dia() const noexcept;
		int mes() const noexcept;
		int anno() const noexcept;
		Fecha operator++ (int);
		Fecha& operator++ ();
		Fecha operator-- (int);
		Fecha& operator-- ();
		Fecha operator+ (int n) const;
		Fecha operator- (int n) const;
		Fecha& operator += (int n);
		Fecha& operator -= (int n);
		const char * cadena() const;
		    
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

std::ostream& operator<<(std::ostream& os, const Fecha& f);
std::istream& operator>>(std::istream& is, Fecha& f);

bool operator==(const Fecha& fecha1, const Fecha& fecha2);
bool operator!=(const Fecha& fecha1, const Fecha& fecha2);
bool operator<(const Fecha& fecha1, const Fecha& fecha2);
bool operator>(const Fecha& fecha1, const Fecha& fecha2);
bool operator<=(const Fecha& fecha1, const Fecha& fecha2);
bool operator>=(const Fecha& fecha1, const Fecha& fecha2);

// Observador del día
inline int Fecha::dia() const noexcept
{ return dia_; }

// Observador del mes
inline int Fecha::mes() const noexcept
{ return mes_; }

// Observador del año
inline int Fecha::anno() const noexcept
{ return anno_; }

// Operador de igualdad
inline bool operator==(const Fecha& fecha1, const Fecha& fecha2)
{ return (fecha1.dia() == fecha2.dia() && fecha1.mes() == fecha2.mes() && fecha1.anno() == fecha2.anno()); }

// Operador de desigualdad
inline bool operator!=(const Fecha& fecha1, const Fecha& fecha2)
{ return (!(fecha1 == fecha2)); }

// Operador de comparación menor que
inline bool operator<(const Fecha& fecha1, const Fecha& fecha2)
{ return (fecha1.anno() < fecha2.anno() || (fecha1.anno() == fecha2.anno() && fecha1.mes() < fecha2.mes()) || (fecha1.anno() == fecha2.anno() && fecha1.mes() == fecha2.mes() && fecha1.dia() < fecha2.dia())); }

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
inline const char * Fecha::Invalida::por_que() const
{ return (motivo); }

#endif
