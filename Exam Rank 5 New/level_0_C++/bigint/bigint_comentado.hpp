#pragma once
#include <string>		// Para manejar números grandes
#include <iostream>		// Para la entrada/salida

class bigint
{
	private:
		std::string num;	// Representación del número como una cadena de caracteres
		void remove_zeros()
		{
			size_t pos = num.find_first_not_of('0');
			// find_first_not_of es una función de la librería estándar de C++ que busca el primer carácter que no sea '0'.
			// Si lo encuentra, devuelve la posición de ese carácter; si no, devuelve npos. npos es un valor especial que 
			// indica que no se encontró ningún carácter. La variable pos guarda la posición obtenida.
			if (pos == std::string::npos)	// Si no se encontraron caracteres no cero...
				num = "0";					// Asegurarse de que el número sea "0"
			else
				num.erase(0, pos);			// Eliminar los ceros a la izquierda
				// erase es una función de la clase std::string que elimina una parte de la cadena.
				// En este caso, elimina desde el inicio (posición 0) hasta la posición pos, que es donde comienza el 
				// primer carácter no cero.
		}
		/* 	Esta función se encarga de eliminar los ceros a la izquierda de la representación del número.
			Si el número es 0, se asegura de que siga siendo 0.
			Si no hay ceros a la izquierda, simplemente deja el número como está.
		*/

	public:
		bigint() : num("0") {}		// Constructor por defecto que inicializa el número a "0" (cadena)
		bigint(const std::string &n) : num(n) { remove_zeros(); }
		/*	Constructor que inicializa el número a partir de una cadena.
			Elimina los ceros a la izquierda para asegurar una representación correcta.
			&n es una referencia constante a una cadena que representa el número. Se usa la referencia para evitar
			copiar la cadena completa, lo que mejora la eficiencia.
			num inicializa la cadena interna con el valor de n
			El cuerpo del constructor se encarga de eliminar los ceros a la izquierda.	*/

		bigint(unsigned int n) : num(std::to_string(n)) {}
		/*	Constructor que inicializa el número a partir de un entero sin signo.
			Convierte el entero a una cadena y la almacena en la representación interna.
			to_string es una función de la biblioteca estándar de C++ que convierte un valor numérico a su 
			representación en cadena.
			No realiza ninguna otra operación ya que el cuerpo del constructor está vacío.	*/

		bigint operator+(const bigint &oth) const {
		/*	Esta función sobrecarga el operador + para permitir la suma de dos objetos bigint.
			Recibe otro objeto bigint como parámetro y devuelve un nuevo objeto bigint que representa la suma.
			El operador + es una función miembro constante, lo que significa que no modifica el objeto actual.
			oth es una referencia constante al otro objeto bigint con el que se va a sumar.
			El resultado de la suma se construye como una nueva cadena de caracteres.
			const en cuanto a oth garantiza que no se modificará el objeto pasado como argumento.
			const al final garantiza que no se modificará el objeto actual.
			Ejemplo: bigint a("123"), b("456"); bigint c = a + b; c será "579", pero ni a ni b se modifican.	*/
			std::string a = num;		// inicializa la variable a igualandola a num
			std::string b = oth.num;	// inicializa la variable b igualandola a num
			// oth es el otro objeto bigint con el que se va a sumar
			// .num es la representación interna del objeto bigint
			// oth.num es la representación interna del otro objeto bigint
			// oth.num significa que se está refiriendo a la representación interna del otro objeto bigint
			std::string result = "";	// inicializa la variable result como una cadena vacía

			while (a.size() < b.size())
				a = '0' + a;
				/*	Esto asegura que ambas cadenas tengan la misma longitud al agregar ceros a la izquierda.	*/
			while (b.size() < a.size())
				b = '0' + b;
				/*	Esto asegura que ambas cadenas tengan la misma longitud al agregar ceros a la izquierda.	*/

			int carry = 0;	// carry es la variable que almacena el acarreo de la suma
			for (int i = a.size() - 1; i >= 0; i--) {
				int sum = (a[i] - '0') + (b[i] - '0') + carry;
				carry = sum / 10;
				sum %= 10;
				result.insert(result.begin(), '0' + sum);
			}
			/*	Este bucle recorre los dígitos de las cadenas a y b de derecha a izquierda, se podría usar b.size() 
				en lugar de a.size() perfectamente dado que ambas cadenas son del mismo tamaño.
				- (a[i] - '0') convierte el carácter a[i] en su valor numérico.
				- (b[i] - '0') convierte el carácter b[i] en su valor numérico.
				- carry es el acarreo de la suma anterior. acarreo significa "el dígito que se lleva a la siguiente 
					posición en caso de que la suma de dos dígitos sea mayor o igual a 10".
				- en carry = sum / 10 el /10 se utiliza para obtener el dígito de acarreo.
				- sum %= 10 obtiene el dígito de la suma que se va a insertar en el resultado. %= es un operador que
					realiza la operación de módulo y asigna el resultado a la variable sum. Módulo es una operación que
					devuelve el residuo de la división de dos números.
				- La última línea result.insert(result.begin(), '0' + sum); inserta el dígito de la suma en el resultado.
					.insert es un método de la clase std::string que permite insertar caracteres en una posición específica.
					.begin es un método de la clase std::string que devuelve un iterador al inicio de la cadena.
			*/
			if (carry)
				result.insert(result.begin(), '0' + carry);
			/*	Si al final del bucle hay un acarreo, se inserta al principio del resultado.
				Esto asegura que si la suma final tiene un dígito adicional (por ejemplo, al sumar 999 + 1),
				el resultado se construya correctamente como 1000.	*/

			bigint res(result);				// Crea un nuevo objeto res con la cadena result
			res.remove_zeros();		// Elimina los ceros a la izquierda de res
			return res;						// Devuelve el objeto res
		}

		bigint &operator+=(const bigint &oth) {
			*this = *this + oth;
			return *this;
		}
		/*	Operador de incremento (prefijo) 	*/

		bigint& operator++() { 
			*this = *this + bigint(1);
			return *this;
		}
		/*	Operador de preincremento (postfijo) ++numero	*/

		bigint operator++(int) { 
			bigint temp = *this;
			++(*this);
			return temp;
		}
		/*	Operador de postincremento (postfijo) numero++	*/

		bigint operator<<(int shift) const {
			if (num == "0")
				return bigint("0");
			return bigint(num + std::string(shift, '0'));
		}
		/*	Añade a num tantos ceros a la derecha como se indique en shift.	
			Esto es equivalente a realizar una multiplicación entera por 10^shift.
			Ejemplo: 42 << 2 = 4200 ; 22 << 10 = 22000000000	*/

		bigint operator>>(int shift) const {
			if (shift >= (int)num.size())	// Si el desplazamiento es mayor o igual al tamaño de num
				return bigint("0");
			bigint res(num.substr(0, num.size() - shift));
			/*	Si el desplazamiento es menor que el tamaño de num, se realiza la división
				por 10^shift, lo que equivale a eliminar los últimos shift dígitos de num.
				- substr es un método de la clase std::string que devuelve una subcadena desde el inicio hasta
					la posición especificada. En este caso, se elimina el número de dígitos especificado por shift.
				- num.size() - shift calcula la nueva longitud de la cadena después del desplazamiento			
			*/ 
			res.remove_zeros();	// Elimina los ceros a la izquierda de res
			return res;
		}
		/*	Desplaza los dígitos de num hacia la derecha en la cantidad indicada por shift.
			Esto es equivalente a realizar una división entera por 10^shift.
			Ejemplo: 4200 >> 2 = 42 ; 22000000000 >> 10 = 22	*/

		bigint &operator<<=(int shift) {
			*this = *this << shift;
			return *this;
		}
		/*	Es igual que el operador << (multiplicación entera por 10^shift) pero se aplica sobre el objeto actual.
			Esto permite modificar el objeto actual en lugar de crear uno nuevo.	*/

		bigint &operator>>=(int shift) {
			*this = *this >> shift;
			return *this;
		}
		/*	Es igual que el operador >> (división entera por 10^shift) pero se aplica sobre el objeto actual.
			Esto permite modificar el objeto actual en lugar de crear uno nuevo.	
			Uso: Cuando tienes un número fijo o una variable entera que indica cuántos dígitos eliminar.	*/

		bigint &operator>>=(const bigint &oth) {
			int shift = std::stoi(oth.num);
			// El objeto oth se convierte a un entero usando std::stoi,
			// oth.num es la representación interna del objeto oth
			*this = *this >> shift;
			return *this;
		}
		/*	Permite desplazar los dígitos de num hacia la derecha en la cantidad indicada por otro objeto bigint oth.
			Esto equivale a realizar una división entera por 10^shift.
			oth.num se convierte a un entero usando std::stoi, que convierte una cadena a un entero.
			Uso: Cuando el número de dígitos a desplazar está almacenado en un objeto bigint, como el resultado de 
			otro cálculo.
			Ejemplo: num = 42 y oth = 2; num >>= oth resultado: 0	*/

		/*	La diferencia entre bigint &operator>>=(int shift) y bigint &operator>>=(const bigint &oth)
			es que en el primer caso se desplaza un número entero fijo, mientras que en el segundo caso
			se desplaza un número que puede ser arbitrariamente grande, representado como un objeto bigint.
			De este modo, se pueden realizar desplazamientos más grandes que el tamaño de un entero estándar.	*/

		bool operator<(const bigint &oth) const {
			if (num.size() != oth.num.size())
				return num.size() < oth.num.size();
			return num < oth.num;
		}
		/*	Compara dos objetos bigint para determinar si el objeto actual es menor que el otro.
			- Primero compara el tamaño de las cadenas num y oth.num. Si son diferentes, el número con menos dígitos es menor.
			- Si tienen el mismo tamaño, compara las cadenas lexicográficamente.
			Ejemplo: bigint a("123"), b("456"); a < b devuelve true porque 123 es menor que 456.
			No se modifica el objeto actual ni el otro objeto bigint, ya que const lo impide, y además no es necesario.	*/
		bool operator>(const bigint &oth) const { return oth < *this; }
		/*	Compara dos objetos bigint para determinar si el objeto actual es mayor que el otro.
			- Utiliza la función operator< para invertir la comparación.
			Ejemplo: bigint a("456"), b("123"); a > b devuelve true porque 456 es mayor que 123.
			No se modifica el objeto actual ni el otro objeto bigint, ya que const lo impide, y además no es necesario.	*/
		bool operator<=(const bigint &oth) const { return !(*this > oth); }
		/*	Compara dos objetos bigint para determinar si el objeto actual es menor o igual que el otro.
			- Utiliza la función operator> para invertir la comparación.
			Ejemplo: bigint a("123"), b("456"); a <= b devuelve true porque 123 es menor o igual que 456.
			Si comparamos a("123") > b("456") devuelve false. Pero con !(*this > oth) devuelve true.
			No se modifica el objeto actual ni el otro objeto bigint, ya que const lo impide, y además no es necesario.	*/
		bool operator>=(const bigint &oth) const { return !(*this < oth); }
		/*	Compara dos objetos bigint para determinar si el objeto actual es mayor o igual que el otro.
			- Utiliza la función operator< para invertir la comparación.
			Ejemplo: bigint a("456"), b("123"); a >= b devuelve true porque 456 es mayor o igual que 123.
			Si comparamos a("456") < b("123") devuelve false. Pero con !(*this < oth) devuelve true.
			No se modifica el objeto actual ni el otro objeto bigint, ya que const lo impide, y además no es necesario.	*/
		bool operator==(const bigint &oth) const { return num == oth.num; }
		/*	Compara dos objetos bigint para determinar si son iguales.
			- Compara las cadenas num y oth.num directamente.
			Ejemplo: bigint a("123"), b("123");
			Si a("123") y b("456") devolvería false.	*/
		bool operator!=(const bigint &oth) const { return !(*this == oth); }
		/*	Compara dos objetos bigint para determinar si son diferentes.
			- Utiliza la función operator== para invertir la comparación.
			Ejemplo: bigint a("123"), b("456"); a != b devuelve true porque 123 es diferente de 456.
			Si comparamos a("123") == b("456") devuelve false. Pero con !(*this == oth) devuelve true.
			No se modifica el objeto actual ni el otro objeto bigint, ya que const lo impide, y además no es necesario.	*/

		friend std::ostream &operator<<(std::ostream &os, const bigint &b) {
			os << b.num;
			return os;
		}
		/*	Permite imprimir un objeto bigint en un flujo de salida (como std::cout).
			- Utiliza el operador de inserción << para enviar la cadena num al flujo os.
			- ostream es un tipo de flujo de salida en C++ que permite enviar datos a la consola o a archivos. Aquí se
				utiliza para imprimir el valor de un objeto bigint en la consola.
			Ejemplo: bigint a("123"); std::cout << a; imprimirá "123" en la consola.
			No se modifica el objeto bigint ni el flujo de salida, ya que const lo impide, y además no es necesario.	*/
};
