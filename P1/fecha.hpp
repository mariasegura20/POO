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
		
		bool operator==(const Fecha& fecha) const;
		bool operator!=(const Fecha& fecha) const;
		bool operator<(const Fecha& fecha) const;
		bool operator>(const Fecha& fecha) const;
		bool operator>=(const Fecha& fecha) const;
		bool operator<=(const Fecha& fecha) const;
		
		friend ostream& operator<<(ostream& os, const Fecha& f);
		friend istream& operator>>(istream& is, Fecha& f);
		
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

bool operator==(const char * s, const Fecha& f);
bool operator!=(const char * s, const Fecha& f);
bool operator<(const char * s, const Fecha& f);
bool operator>(const char * s, const Fecha& f);
bool operator<=(const char * s, const Fecha& f);
bool operator>=(const char * s, const Fecha& f);

/***** OBSERVADORES *****/
// Dia
inline int Fecha::dia() const noexcept
{ return dia_; }

// Mes
inline int Fecha::mes() const noexcept
{ return mes_; }

// Año
inline int Fecha::anno() const noexcept
{ return anno_; }

/***** OPERADORES DE COMPARACIÓN *****/
// Operador de igualdad
inline bool Fecha::operator==(const Fecha& fecha) const
{ return (dia_ == fecha.dia() && mes_ == fecha.mes() && anno_ == fecha.anno()); }

inline bool operator==(const char * s, const Fecha& f)
{ return Fecha(s) == f; }

// Operador de desigualdad
inline bool Fecha::operator!=(const Fecha& fecha) const
{ return (!(*this == fecha)); }

inline bool operator!=(const char * s, const Fecha& f)
{ return Fecha(s) != f; }

// Operador de comparación menor que
inline bool Fecha::operator<(const Fecha& fecha) const
{ return (anno_ < fecha.anno() || (anno_ == fecha.anno() && mes_ < fecha.mes()) || (anno_ == fecha.anno() && mes_ == fecha.mes() && dia_ < fecha.dia())); }

inline bool operator<(const char * s, const Fecha& f)
{ return Fecha(s) < f; }

// Operador de comparación mayor que
inline bool Fecha::operator>(const Fecha& fecha) const
{ return (!(*this < fecha) && !(*this == fecha)); }

inline bool operator>(const char * s, const Fecha& f)
{ return Fecha(s) > f; }

// Operador de comparación menor o igual que
inline bool Fecha::operator<=(const Fecha& fecha) const
{ return (*this < fecha || *this == fecha); }

inline bool operator<=(const char * s, const Fecha& f)
{ return Fecha(s) <= f; }

// Operador de comparación mayor o igual que
inline bool Fecha::operator>=(const Fecha& fecha) const
{ return (!(*this < fecha)); }

inline bool operator>=(const char * s, const Fecha& f) 
{ return Fecha(s) >= f; }

/***** CLASE INVALIDA *****/
inline const char * Fecha::Invalida::por_que() const
{ return (motivo); }

#endif
