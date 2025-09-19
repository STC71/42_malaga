#pragma once

#include <iostream>				// para la entrada/salida

class vect2 {

/*	vect2 es una clase que representa un vector bidimensional
	con operaciones básicas como suma, resta, multiplicación por un escalar,
	incremento, decremento, y comparaciones.	*/

	private:
		int x, y;				// coordenadas del vector

	public:
		vect2() : x(0), y(0) {}								// constructor por defecto que inicializa el vector en (0, 0)
		vect2(int x, int y) : x(x), y(y) {}					// constructor que inicializa el vector en (x, y)
		vect2(const vect2 &oth) = default;					// constructor de copia.
		vect2 &operator=(const vect2 &oth) = default;		// operador de asignación por defecto

		int &operator[](int i) { return (i == 0 ? x : y); }
		/*	operador de indexación que permite acceder y modificar las coordenadas del vector, retornando
			una referencia a la coordenada correspondiente, dependiendo de si i es 0 o no, en caso de 0 entonces
			se retorna x, de lo contrario se retorna y. Esto sirve para facilitar el acceso a las coordenadas del vector.	*/
		int operator[](int i) const { return (i == 0 ? x : y); }
		/*	operador de indexación que permite acceder a las coordenadas del vector, retornando
			una copia de la coordenada correspondiente, dependiendo de si i es 0 o no, en caso de 0 entonces
			se retorna x, de lo contrario se retorna y. Esto sirve para facilitar el acceso a las coordenadas del vector.	*/

		/*	La diferencia entre el operador de indexación no constante y el constante radica en que el primero permite
			modificar las coordenadas del vector, mientras que el segundo solo permite la lectura.	*/

		vect2 operator+(const vect2 &oth) const { return vect2(x + oth.x, y + oth.y); }
		/*	operador de suma que permite sumar dos vectores, retornando un nuevo vector con las coordenadas
			resultantes de la suma de las coordenadas correspondientes de los vectores.
			Por ejemplo: si vect2 a(1, 2) y vect2 b(3, 4), entonces a + b = vect2(4, 6)		*/
		vect2 operator-(const vect2 &oth) const { return vect2(x - oth.x, y - oth.y); }
		/*	operador de resta que permite restar dos vectores, retornando un nuevo vector con las coordenadas
			resultantes de la resta de las coordenadas correspondientes de los vectores.
			Por ejemplo: si vect2 a(1, 2) y vect2 b(3, 4), entonces a - b = vect2(-2, -2)	*/
		vect2 &operator+=(const vect2 &oth)
		{
			x += oth.x;
			y += oth.y;
			return *this;
		}
		/*	operador de suma compuesta que permite sumar otro vector al vector actual,
			modificando las coordenadas del vector actual y retornando una referencia al mismo.
			Por ejemplo: si vect2 a(1, 2) y vect2 b(3, 4), entonces a += b modifica a a(4, 6)
			y retorna una referencia a a, lo que permite encadenar operaciones.	*/

		vect2 &operator-=(const vect2 &oth)
		{
			x -= oth.x;
			y -= oth.y;
			return *this;
		}
		/*	operador de resta compuesta que permite restar otro vector al vector actual,
			modificando las coordenadas del vector actual y retornando una referencia al mismo.
			Por ejemplo: si vect2 a(1, 2) y vect2 b(3, 4), entonces a -= b modifica a a(-2, -2)
			y retorna una referencia a a, lo que permite encadenar operaciones.	*/

		vect2 &operator++()
		{
			x++;
			y++;
			return *this;
		}
		/*	operador de incremento que incrementa las coordenadas del vector en 1, ++a,
			modificando las coordenadas del vector actual y retornando una referencia al mismo.
			Por ejemplo: si vect2 a(1, 2), entonces ++a modifica a a(2, 3) y retorna una referencia a a.	*/

		vect2 operator++(int)
		{
			vect2 tmp = *this;
			x++;
			y++;
			return tmp;
		}
		/*	operador de incremento postfijo que incrementa las coordenadas del vector en 1, a++
			modificando las coordenadas del vector actual y retornando una copia del vector antes de la modificación.
			Por ejemplo: si vect2 a(1, 2), entonces a++ modifica a a(2, 3) pero retorna una copia de a(1, 2).	*/

		vect2 &operator--()
		{
			x--;
			y--;
			return *this;
		}
		/*	operador de decremento que decrementa las coordenadas del vector en 1, --a,
			modificando las coordenadas del vector actual y retornando una referencia al mismo.
			Por ejemplo: si vect2 a(1, 2), entonces --a modifica a a(0, 1) y retorna una referencia a a.	*/

		vect2 operator--(int)
		{
			vect2 tmp = *this;
			x--;
			y--;
			return tmp;
		}
		/*	operador de decremento postfijo que decrementa las coordenadas del vector en 1, a--,
			modificando las coordenadas del vector actual y retornando una copia del vector antes de la modificación.
			Por ejemplo: si vect2 a(1, 2), entonces a-- modifica a a(0, 1) pero retorna una copia de a(1, 2).	*/

		vect2 operator-() const { return vect2(-x, -y); }
		/*	operador de negación que retorna un nuevo vector con las coordenadas negadas.
			Por ejemplo: si vect2 a(1, 2), entonces -a = vect2(-1, -2).	*/

		vect2 operator*(int s) const { return vect2(x * s, y * s); }
		/*	operador de multiplicación que permite multiplicar un vector por un escalar,
			retornando un nuevo vector con las coordenadas multiplicadas por el escalar.
			Por ejemplo: si vect2 a(1, 2), entonces a * 3 = vect2(3, 6). s = 3	*/

		vect2 &operator*=(int s)
		{
			x *= s;
			y *= s;
			return *this;
		}
		/*	operador de multiplicación compuesta que permite multiplicar el vector actual por un escalar,
			modificando las coordenadas del vector actual y retornando una referencia al mismo.
			Por ejemplo: si vect2 a(1, 2), entonces a *= 3 modifica a a(3, 6) y retorna una referencia a a.	*/

		friend vect2 operator*(int s, const vect2 &v) { return vect2(v.x * s, v.y * s); }
		/*	operador de multiplicación que permite multiplicar un escalar por un vector para el caso en que el escalar
			esté a la izquierda del vector. Por ejemplo: si vect2 a(1, 2), entonces 3 * a = vect2(3, 6). s = 3
			devuelve un nuevo vector con las coordenadas multiplicadas por el escalar. Es una función amiga 
			que permite acceder a los miembros privados de la clase vect2.	*/

		bool operator==(const vect2 &oth) const { return x == oth.x && y == oth.y; }
		/*	operador de igualdad que compara dos vectores y retorna true si sus coordenadas son iguales,
			de lo contrario retorna false. Por ejemplo: si vect2 a(1, 2) y vect2 b(1, 2), entonces a == b es true.	*/

		bool operator!=(const vect2 &oth) const { return !(*this == oth); }
		/*	operador de desigualdad que compara dos vectores y retorna true si sus coordenadas son diferentes,
			de lo contrario retorna false. Por ejemplo: si vect2 a(1, 2) y vect2 b(1, 2), entonces a != b es false.	*/

		friend std::ostream &operator<<(std::ostream &os, const vect2 &v) {
			os << "{" << v[0] << ", " << v[1] << "}";
			return os;
		}
		/*	operador de inserción que permite imprimir un vector en un flujo de salida,
			formateando las coordenadas del vector como {x, y}. Por ejemplo: si vect2 a(1, 2),
			entonces std::cout << a imprime "{1, 2}". Retorna os que es el flujo de salida.	*/
		
};
