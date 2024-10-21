/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-18 12:58:41 by sternero          #+#    #+#             */
/*   Updated: 2024-10-18 12:58:41 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
    La función signal_ctrl_c_parent() inicializa la estructura sigaction ctrl_c
    para esto se le asigna el manejador handle_sigint_parent, se le asigna la
    bandera SA_RESTART, lo que significa que si una llamada al sistema es
    interrumpida por una señal, la llamada al sistema se reiniciará. Después se
    limpia el conjunto de señales y se llama a la función sigaction() para
    establecer la acción para la señal SIGINT. En resumen: esta función se
    encarga de manejar la señal SIGINT (Ctrl+C) en el proceso padre.
*/

void	ft_signal_ctrl_c_parent(void)
{
	struct sigaction	ctrl_c;

	ctrl_c.sa_handler = ft_handle_sigint_parent;
	ctrl_c.sa_flags = SA_RESTART;
	sigemptyset(&ctrl_c.sa_mask);
	sigaction(SIGINT, &ctrl_c, NULL);
}

/*
    La función handle_sigint_parent() maneja la señal SIGINT (Ctrl+C) en el
    proceso padre. Si la señal recibida es SIGINT, se escribe "^C\n" en la
    salida estándar, se llama a la función rl_on_new_line() para colocar el
    cursor en una nueva línea y se llama a la función rl_replace_line() para
    reemplazar la línea actual con una cadena vacía.
*/

void	ft_handle_sigint_parent(int sig_num)
{
	if (sig_num == SIGINT)
	{
		write(1, "^C\n", 3);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

/*
    La función signals_parent() llama a las funciones signal_ctrl_c_parent() y
    signal_ctrl_backslash() para manejar las señales SIGINT (Ctrl+C) y SIGQUIT
    (Ctrl+\) en el proceso padre. De este modo, se establecen los manejadores
    de señales para el proceso padre. signal_ctrl_c_parent() maneja la señal
    SIGINT (Ctrl+C) y signal_ctrl_backslash() maneja la señal SIGQUIT (Ctrl+\).
*/

void	ft_signals_parent(void)
{
	ft_signal_ctrl_c_parent();
	ft_signal_ctrl_backslash();
}

/*  The signal_ctrl_c_parent() function initializes the ctrl_c sigaction 
    structure for this the SIG_DFL handler is assigned, which causes the signal
    to be handled in the default way by the system. After that, the SA_RESTART
    flag is assigned, which means that if a system call is interrupted by a
    signal, the system call will be restarted. Then the signal set is cleared
    and the sigaction() function is called to set the action for the SIGINT
    signal. In summary: this function is responsible for handling the SIGINT
    (Ctrl+C) signal in the parent process. */

/*  The handle_sigint_parent() function handles the SIGINT (Ctrl+C) signal in the
    parent process. If the received signal is SIGINT, "^C\n" is written to the
    standard output, rl_on_new_line() function is called to place the cursor on
    a new line, and rl_replace_line() function is called to replace the current
    line with an empty string. */

/*  The signals_parent() function calls the signal_ctrl_c_parent() and
    signal_ctrl_backslash() functions to handle the SIGINT (Ctrl+C) and SIGQUIT
    (Ctrl+\) signals in the parent process. This way, the signal handlers are
    set for the parent process. signal_ctrl_c_parent() handles the SIGINT 
    (Ctrl+C) signal and signal_ctrl_backslash() handles the SIGQUIT (Ctrl+\) 
    signal. */