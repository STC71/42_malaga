/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-16 16:25:52 by sternero          #+#    #+#             */
/*   Updated: 2024-10-16 16:25:52 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// SIGINT(2) = CTRL + 'C' = cerramos proceso y creamos nueva linea.
// SIGKILL(9) = CTRL + 'D' = termina el shell forzosamente (no se puede manejar)
// SIGQUIT(3) = CTRL + '\' = salida de teclado (no hace nada).
void	handler(int sig)
{	// pq pone que recibe un int si cuando se llama a esta ft no se envía nada????
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("  ", 1);
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_replace_line("  ", 0);
		rl_redisplay();
	}
}

/* Configura el manejo de señales: 
cómo el programa debe responder a ciertas señales.*/
void	if_signal(void)
{
	struct sigaction sig;

	sig.sa_handler = &handler;
		// se llama a una función x referencia y sin envir nada????
		// guardo en una var la funcion handler x ref¿¿¿¿¿¿¿¿
		// se llama cuando reciba una señal específica??
	sig.sa_flags = SA_RESTART; 
		// reinicia la llamada al sistema si se interrumpe por una señal.??
	sigemptyset(&sig.sa_mask); 
		// inicializa la máscara de señales sa_mask a un conjunto vacío. ??
		//Esto significa que no se bloquearán otras señales mientras se maneja 
		// la señal actua
	sigaction(SIGINT, &sig, NULL);
		//se utiliza para cambiar la acción que se toma cuando se recibe la 
		//señal SIGINT (Interrupción, generalmente generada por Ctrl+C). 
		//Se pasa la estructura sig para especificar el nuevo manejador de señales.
	sigaction(SIGQUIT, &sig, NULL);
		//se utiliza para cambiar la acción que se toma cuando se recibe la señal 
		//SIGQUIT (Salida, generalmente generada por Ctrl+)
}