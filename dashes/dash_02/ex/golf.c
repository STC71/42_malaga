/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   golf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-22 11:05:34 by sternero          #+#    #+#             */
/*   Updated: 2025-05-22 11:05:34 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*	El objetivo en este dash es crear un programa que reciba por argumentos un
	string con una operación aritmética y muestre por pantalla el resultado.

	Ejemplos:
		%> ./golf "8 * (5 + 3) - 22" | cat -e
		42$
		%> ./golf "8 * " "(5 + 3)" "- 22" | cat -e
		Error: Arguments are incorrect$
		%> ./golf "8+23" | cat -e
		Error: Arguments are incorrect$
		%> ./golf "8 * 4a + b" | cat -e
		Error: Arguments are incorrect$
	
	Ojo! No hay normas de las que preocuparse.	*/

#include <stdio.h>		// Para printf...
#include <stdlib.h>		// Para exit...
#include <ctype.h>		// Para isdigit, isspace...
#include <string.h>		// Para strlen...

// Prototipos de funciones
void trim_whitespace(char *str);
int is_valid_expression(const char *expr);
int parse_factor(const char *expr, int *pos);
int parse_term(const char *expr, int *pos);
int parse_expression(const char *expr, int *pos);
int evaluate_expression(const char *expr);

/*	La siguiente función comprueba que exisan espacios en blanco entre los 
	números y los operadores.	*/
void trim_whitespace(char *str) {
    char *end;
    while (isspace(*str)) str++;		// Elimina espacios al principio
    if (*str == 0) return;				// Si la cadena está vacía, no hay nada que hacer
    end = str + strlen(str) - 1;		// Encuentra el último carácter
    while (end > str && isspace(*end)) end--;	// Elimina espacios al final
    end[1] = '\0';						// Termina la cadena	
}

/*	La siguiente función comprueba que la expresión sea válida.	*/
int is_valid_expression(const char *expr) {
    int paren_count = 0;
    int expect_num_or_paren = 1;

    for (int i = 0; expr[i]; i++) {
        if (isspace(expr[i])) continue;
        
        if (isdigit(expr[i])) {
            if (!expect_num_or_paren) return 0;
            while (isdigit(expr[i])) i++;
            i--;
            expect_num_or_paren = 0;
        }
        else if (expr[i] == '(') {
            if (!expect_num_or_paren) return 0;
            // Verificar que '(' esté precedido por espacio o inicio, y seguido por espacio o dígito
            if (i > 0 && !isspace(expr[i-1]) && expr[i-1] != '(') return 0;
            if (expr[i+1] && !isspace(expr[i+1]) && !isdigit(expr[i+1]) && expr[i+1] != '(') return 0;
            paren_count++;
            expect_num_or_paren = 1;
        }
        else if (expr[i] == ')') {
            if (expect_num_or_paren || paren_count == 0) return 0;
            // Verificar que ')' esté precedido por dígito o ')', y seguido por espacio, operador o fin
            if (i > 0 && !isdigit(expr[i-1]) && expr[i-1] != ')') return 0;
            if (expr[i+1] && !isspace(expr[i+1]) && expr[i+1] != '+' && expr[i+1] != '-' && 
                expr[i+1] != '*' && expr[i+1] != '/' && expr[i+1] != ')') return 0;
            paren_count--;
            expect_num_or_paren = 0;
        }
        else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/') {
            if (expect_num_or_paren) return 0;
            // Verificar que el operador esté rodeado de espacios
            if (i == 0 || i == (int)strlen(expr)-1) return 0;
            if (!isspace(expr[i-1]) || !isspace(expr[i+1])) return 0;
            expect_num_or_paren = 1;
        }
        else {
            return 0;
        }
    }
    return paren_count == 0 && !expect_num_or_paren;
}

/*	La siguiente función analiza un factor en la expresión. 
	Un factor puede ser un número o una expresión entre paréntesis.	
	Si no se encuentra un número o una expresión válida, se imprime un mensaje de 
	error, en caso contrario se devuelve el valor del número.	*/
int parse_factor(const char *expr, int *pos) {
    while (isspace(expr[*pos])) (*pos)++;
    
    if (expr[*pos] == '(') {
        (*pos)++;
        int value = parse_expression(expr, pos);
        if (expr[*pos] != ')') {
            printf("Error: Mismatched parentheses\n");
            exit(1);
        }
        (*pos)++;
        return value;
    }
    
    if (isdigit(expr[*pos])) {
        int value = 0;
        while (isdigit(expr[*pos])) {
            value = value * 10 + (expr[*pos] - '0');
            (*pos)++;
        }
        return value;
    }
    
    printf("Error: Invalid expression\n");
    exit(1);
}

/*	La siguiente función analiza un término en la expresión. 
	Un término puede ser un factor seguido de multiplicación o división.	
	Si no se encuentra un número o una expresión válida, se imprime un mensaje de 
	error, en caso contrario se devuelve el valor del número.	*/
int parse_term(const char *expr, int *pos) {
    int result = parse_factor(expr, pos);
    
    while (1) {
        while (isspace(expr[*pos])) (*pos)++;
        
        if (expr[*pos] == '*' || expr[*pos] == '/') {
            char op = expr[*pos];
            (*pos)++;
            int next_factor = parse_factor(expr, pos);
            if (op == '*') result *= next_factor;
            else result /= next_factor;
        } else {
            break;
        }
    }
    
    return result;
}

/*	La siguiente función analiza la expresión. 
	Una expresión puede ser un término seguido de suma o resta.	
	Si no se encuentra un número o una expresión válida, se imprime un mensaje de 
	error, en caso contrario se devuelve el resultado de la expresión.	*/
int parse_expression(const char *expr, int *pos) {
    int result = parse_term(expr, pos);
    
    while (1) {
        while (isspace(expr[*pos])) (*pos)++;
        
        if (expr[*pos] == '+' || expr[*pos] == '-') {
            char op = expr[*pos];
            (*pos)++;
            int next_term = parse_term(expr, pos);
            if (op == '+') result += next_term;
            else result -= next_term;
        } else {
            break;
        }
    }
    
    return result;
}

/*	La siguiente función evalúa la expresión. 
	Si no se encuentra un número o una expresión válida, se imprime un mensaje de 
	error, en caso contrario se devuelve el resultado de la expresión.	*/
int evaluate_expression(const char *expr) {
    int pos = 0;
    int result = parse_expression(expr, &pos);
    
    while (isspace(expr[pos])) pos++;
    if (expr[pos] != '\0' && expr[pos] != ')') {
        printf("Error: Invalid expression\n");
        exit(1);
    }
    
    return result;
}

/*	La siguiente función es la función principal del programa. 
	Recibe un argumento de línea de comandos, que es la expresión a evaluar. 
	Si no se encuentra un número o una expresión válida, se imprime un mensaje de 
	error, en caso contrario se devuelve el resultado de la expresión.	*/
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Error: Arguments are incorrect\n");
        return 1;
    }
    
    char *expr = argv[1];
    trim_whitespace(expr);
    
    if (!is_valid_expression(expr)) {
        printf("Error: Arguments are incorrect\n");
        return 1;
    }
    
    int result = evaluate_expression(expr);
    printf("%d\n", result);
    
    return 0;
}