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
		operator const char*() const;
		bool operator==(const Fecha& fecha) const;
		bool operator!=(const Fecha& fecha) const;
		bool operator<(const Fecha& fecha) const;
		bool operator>(const Fecha& fecha) const;
		bool operator>=(const Fecha& fecha) const;
		bool operator<=(const Fecha& fecha) const;
		    
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
inline int Fecha::dia() const noexcept
{ return dia_; }

// Observador del mes
inline int Fecha::mes() const noexcept
{ return mes_; }

// Observador del año
inline int Fecha::anno() const noexcept
{ return anno_; }

// Operador de igualdad
inline bool Fecha::operator==(const Fecha& fecha) const
{ return (dia_ == fecha.dia() && mes_ == fecha.mes() && anno_ == fecha.anno()); }

// Operador de desigualdad
inline bool Fecha::operator!=(const Fecha& fecha) const
{ return (!(*this == fecha)); }

// Operador de comparación menor que
inline bool Fecha::operator<(const Fecha& fecha) const
{ return (anno_ < fecha.anno() || (anno_ == fecha.anno() && mes_ < fecha.mes()) || (anno_ == fecha.anno() && mes_ == fecha.mes() && dia_ < fecha.dia())); }

// Operador de comparación mayor que
inline bool Fecha::operator>(const Fecha& fecha) const
{ return (!(*this < fecha) && !(*this == fecha)); }

// Operador de comparación menor o igual que
inline bool Fecha::operator<=(const Fecha& fecha) const
{ return (*this < fecha || *this == fecha); }

// Operador de comparación mayor o igual que
inline bool Fecha::operator>=(const Fecha& fecha) const
{ return (!(*this < fecha)); }

/*** Clase Invalida ***/
inline const char * Fecha::Invalida::por_que() const
{ return (motivo); }

#endif
