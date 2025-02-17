/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-13 14:26:33 by sternero          #+#    #+#             */
/*   Updated: 2024-10-13 14:26:33 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>			// to use strcmp
#include <unistd.h>			// to use write, dup2, close, execve, fork, exit
#include <sys/wait.h>		// to use waitpid in exec
#include <stdlib.h>			// to use exit

void err(char *str)
{
	while (*str)
		write(2, str++, 1); // 2 is the file descriptor for stderr (standard error)
}

int cd(char **argv, int i)
{
	if (i != 2)
		return err("error: cd: bad arguments\n"), 1;
	if (chdir(argv[1]) == -1)
		return err("error: cd: cannot change directory to "), err(argv[1]), err("\n"), 1;
	return 0;
}

void set_pipe(int has_pipe, int *fd, int end)
{
	if (has_pipe && (dup2(fd[end], end) == -1 || close(fd[0]) == -1 || close(fd[1]) == -1))
		err("error: fatal\n"), exit(1);
}

int	exec(char **argv, int i, char **envp)
{
	int has_pipe, fd[2], pid, status;
	has_pipe = argv[i] && !strcmp(argv[i], "|"); // check if the command has a pipe. If it does, set has_pipe to 1

	if (!has_pipe && !strcmp(*argv, "cd"))	// if the command does not have a pipe and is cd,
		return cd(argv, i);					// call the cd function and return the result
	if (has_pipe && pipe(fd) == -1)		// if the command has a pipe, create a pipe to communicate between the parent and child processes,
		err("error: fatal\n"), exit(1); // if the pipe fails to create, print an error message and exit
	if ((pid = fork()) == -1)			// if pid is -1, the fork failed to create a new process, 
		err("error: fatal\n"), exit(1); // if this happens, print an error message and exit
	if (!pid)	// if the process is the child process, if pid is 0, the child process will execute the command
	{
		argv[i] = 0;
		set_pipe(has_pipe, fd, 1); // set the pipe for the child process. 1 is the write end of the pipe. fd is the file descriptor for the pipe
		if (!strcmp(*argv, "cd"))
			exit(cd(argv, i));
		execve(*argv, argv, envp);		// execute the command to replace the current process with the command, 
		err("error: cannot execute "), err(*argv), err("\n"), exit(1);  // if the command fails to execute, print an error message and exit
	}
	waitpid(pid, &status, 0);
	set_pipe(has_pipe, fd, 0);
	return WIFEXITED(status) && WEXITSTATUS(status);
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	int i = 0, status = 0;

	while (argv[i])
	{
		argv += i + 1;	// move the pointer to the next argument
		i = 0;			// reset the index for the next command
		while (argv[i] && strcmp(argv[i], "|") && strcmp(argv[i], ";"))
			i++;
		if (i)
			status = exec(argv, i, envp);
	}
	return status;
}

/*

To compile the program, run the following command:

    gcc -Wall -Wextra -Werror microshell.c -o microshell

To run the program, run the following command:

    ./microshell "the command you want to run"

Examples:

    ./microshell ls -l ; echo "hello world"
    ./microshell ls -l | grep microshell
    ./microshell cd ..

********************************************************************************

El programa microshell es una shell simple que puede ejecutar comandos con
tuberías y punto y coma (las tuberías y los puntos y coma son los únicos
caracteres especiales que la shell puede manejar). La shell también puede
cambiar de directorio con el comando cd.

La función principal iterará sobre los argumentos y llamará a la función exec.
Inicializará un bucle while que iterará sobre los argumentos hasta que
encuentre una tubería o un punto y coma. Si el bucle encuentra una tubería o
un punto y coma, llamará a la función exec con los argumentos, el índice y las
variables de entorno. La función exec ejecutará el comando.

La función exec comprobará si el comando es cd, si lo es, llamará a la función
cd para cambiar el directorio. Si el comando no es cd, la función exec creará
un nuevo proceso con fork y ejecutará el comando con execve. El proceso padre
esperará a que el proceso hijo termine con waitpid, y la tubería se cerrará
para evitar fugas de memoria.

La función cd comprobará si el número de argumentos es correcto, y si lo es,
cambiará el directorio con chdir. Si no se puede cambiar el directorio, se
imprimirá un mensaje de error.

La función set_pipe configurará la tubería para el proceso hijo. Si la tubería
falla al configurarse, se imprimirá un mensaje de error y el programa se
cerrará.

La función err se utiliza para imprimir mensajes de error carácter por carácter
en la salida de error estándar.

El programa contiene sesenta y siete líneas de código y se divide en cinco
funciones.

********************************************************************************

The microshell program is a simple shell that can execute commands with pipes 
and semicolons (pipes and semicolons are the only special characters that the 
shell can handle). The shell can also change directories with the cd command.

The main function will iterate over the arguments and call the exec function.
It will initialize a while loop that will iterate over the arguments until it
finds a pipe or a semicolon. If the loop finds a pipe or a semicolon, it will
call the exec function with the arguments, the index, and the environment
variables. The exec function will execute the command.

The exec function will check if the command is cd, if it is, it will call the
cd function to change the directory. If the command is not cd, the exec 
function will create a new process with fork, and execute the command with
execve. The parent process will wait for the child process to finish with
waitpid, and the pipe will be closed to avoid memory leaks.

The cd function will check if the number of arguments is correct, and if it is,
it will change the directory with chdir. If the directory cannot be changed,
an error message will be printed.

The set_pipe function will set up the pipe for the child process. If the pipe
fails to set up, an error message will be printed and the program will exit.

The err function is used to print error messages character by character on the
standard error output.

The program contains sixty seven lines of code, and is split into five functions.

*/