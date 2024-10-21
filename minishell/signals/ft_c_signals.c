/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_c_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-18 12:59:27 by sternero          #+#    #+#             */
/*   Updated: 2024-10-18 12:59:27 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	La función signal_ctrl_c_child() inicializa la estructura sigaction ctrl_c
	para esto se le asigna el manejador SIG_DFL que hace que la señal se maneje 
	de la forma predeterminada por el sistema. Después, se le asigna la bandera
	SA_RESTART, lo que significa que si una llamada al sistema es interrumpida
	por una señal, la llamada al sistema se reiniciará. Posteriormente, se 
	limpia el conjunto de señales y se llama a la función sigaction(), con los
	parámetros: SIGINT, que es la señal de interrupción (Ctrl+C); &ctrl_c, que
	es la estructura sigaction que se ha inicializado; y NULL, que es un puntero
	a la estructura sigaction que se utiliza para almacenar la acción anterior
	para la señal. En resumen: esta función se encarga de manejar la señal SIGINT
	(Ctrl+C) en el proceso hijo.
*/

void	ft_signal_ctrl_c_child(void)
{
	struct sigaction	ctrl_c;

	ctrl_c.sa_handler = SIG_DFL;
	ctrl_c.sa_flags = SA_RESTART;
	sigemptyset(&ctrl_c.sa_mask);
	sigaction(SIGINT, &ctrl_c, NULL);
}

/*
	La función signal_ctrl_backslash_child() inicializa la estructura sigaction
	ctrl_back_slash para esto se le asigna el manejador SIG_DFL que hace que la
	señal se maneje de la forma predeterminada por el sistema. Después, se le
	asigna la bandera SA_RESTART, lo que significa que si una llamada al sistema
	es interrumpida por una señal, la llamada al sistema se reiniciará. 
	Posteriormente, se limpia el conjunto de señales y se llama a la función
	sigaction(), con los parámetros: SIGQUIT, que es la señal de salida (Ctrl+\);
	&ctrl_back_slash, que es la estructura sigaction que se ha inicializado; y
	NULL, que es un puntero a la estructura sigaction que se utiliza para 
	almacenar la acción anterior para la señal. En resumen: esta función se 
	encarga de manejar la señal SIGQUIT (Ctrl+\) en el proceso hijo.
*/

void	ft_signal_ctrl_backslash_child(void)
{
	struct sigaction	ctrl_back_slash;

	ctrl_back_slash.sa_handler = SIG_DFL;
	ctrl_back_slash.sa_flags = SA_RESTART;
	sigemptyset(&ctrl_back_slash.sa_mask);
	sigaction(SIGQUIT, &ctrl_back_slash, NULL);
}

/*
	La función signals_child() llama a las funciones signal_ctrl_c_child() y
	signal_ctrl_backslash_child() para manejar las señales SIGINT (Ctrl+C) y
	SIGQUIT (Ctrl+\) en el proceso hijo. De este modo, se establecen los
	manejadores de señales para el proceso hijo. signal_ctrl_c_child() maneja
	la señal SIGINT (Ctrl+C) y signal_ctrl_backslash_child() maneja la señal
	SIGQUIT (Ctrl+\). struct termios *mirror_termios es una estructura que
	almacena los atributos del terminal, dicha estructura se utiliza para
	restaurar los atributos del terminal después de que el proceso hijo haya
	terminado de ejecutarse; se declara aquí y no en el .h porque es una
	estructura que solo se utiliza en este archivo; y se pasa como argumento
	a la función para que pueda ser utilizada en la función tcsetattr().
*/

void	ft_signals_child(struct termios *mirror_termios)
{
	tcsetattr(1, TCSAFLUSH, mirror_termios);
	ft_signal_ctrl_backslash();
	ft_signal_ctrl_c_child();
}

/*	The signal_ctrl_c_child() function initializes the ctrl_c sigaction 
	structure for this the SIG_DFL handler is assigned, which causes the signal
	to be handled in the default way by the system. Then, the SA_RESTART flag is
	assigned, which means that if a system call is interrupted by a signal, the
	system call will be restarted. Subsequently, the signal set is cleared and
	the sigaction() function is called, with the parameters: SIGINT, which is
	the interrupt signal (Ctrl+C); &ctrl_c, which is the sigaction structure 
	that has been initialized; and NULL, which is a pointer to the sigaction
	structure that is used to store the previous action for the signal. In
	summary: this function is responsible for handling the SIGINT (Ctrl+C) 
	signal in the child process. */

/*	The signal_ctrl_backslash_child() function initializes the ctrl_back_slash
	sigaction structure for this the SIG_DFL handler is assigned, which causes
	the signal to be handled in the default way by the system. Then, the
	SA_RESTART flag is assigned, which means that if a system call is 
	interrupted by a signal, the system call will be restarted. Subsequently,
	the signal set is cleared and the sigaction() function is called, with the
	parameters: SIGQUIT, which is the quit signal (Ctrl+\); &ctrl_back_slash,
	which is the sigaction structure that has been initialized; and NULL, which
	is a pointer to the sigaction structure that is used to store the previous
	action for the signal. In summary: this function is responsible for handling
	the SIGQUIT (Ctrl+\) signal in the child process. */

/*	The signals_child() function calls the signal_ctrl_c_child() and
	signal_ctrl_backslash_child() functions to handle the SIGINT (Ctrl+C) and
	SIGQUIT (Ctrl+\) signals in the child process. This way, the signal handlers
	are set for the child process. signal_ctrl_c_child() handles the SIGINT
	(Ctrl+C) signal and signal_ctrl_backslash_child() handles the SIGQUIT
	(Ctrl+\) signal. struct termios *mirror_termios is a structure that stores
	the terminal attributes, this structure is used to restore the terminal
	attributes after the child process has finished executing it; it is declared
	here and not in the .h because it is a structure that is only used in this
	file; and it is passed as an argument to the function so that it can be used
	in the tcsetattr() function. */