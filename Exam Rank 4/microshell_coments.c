/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-12 08:22:39 by sternero          #+#    #+#             */
/*   Updated: 2024-10-12 08:22:39 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>                 // Used for chdir, fork, pipe, read, write, close, execve, etc.
#include <stdlib.h>                 // Used for malloc, free, exit, etc.
#include <string.h>                 // Used for strcmp, strcpy, strlen, strcat, memset, memcpy, etc.
#include <sys/wait.h>               // Used for waitpid, WIFEXITED, WEXITSTATUS, etc.

void err(char *str)                 // Function to print error messages
{                                   // the message is passed as a string    
	while (*str)                    // and is printed character by character
		write(2, str++, 1);         // on the standard error output. 2 is the file descriptor for stderr,
									// it is used to print the error message on the standard error output. 
									// The difference with 1 is that 2 is used for error messages.
}

int cd(char **argv, int i)          // Function to change directory (cd)
{
	if (i != 2)                     // If the number of arguments is not 2
		return err("error: cd: bad arguments\n"), 1;
	if (chdir(argv[1]) == -1)       // If the directory change fails
		return err("error: cd: cannot change directory to "), err(argv[1]), err("\n"), 1;
	return 0;
}
/*
La función 'cd' en el archivo microshell.c se encarga de cambiar el directorio 
actual del proceso a otro directorio especificado por el usuario. 
A continuación, se explica cómo funciona paso a paso:

   - 'argv'	Es un arreglo de cadenas de caracteres (strings) que contiene los 
   		argumentos pasados a la función.
   - 'i' 	Es un entero que representa el número de argumentos pasados.

   - La función verifica si el número de argumentos es diferente de 2.
   - Si no hay exactamente 2 argumentos, la función imprime un mensaje de error 
   		y retorna 1, indicando que hubo un error.

   - La función intenta cambiar el directorio actual a aquel especificado en 
   		'argv[1]' usando la función 'chdir'
   - Si 'chdir' falla (retorna -1), la función imprime un mensaje de error 
   		indicando que no se pudo cambiar al directorio especificado y retorna 1.
   - Si el cambio de directorio es exitoso, la función retorna 0, indicando que 
   		no hubo errores.

Ejemplos:

1. Cambio exitoso de directorio:
   
   char *args[] = {"cd", "/home/user"};
   int result = cd(args, 2);
   // Si el directorio "/home/user" existe y se puede acceder, result será 0.

2. Error por número incorrecto de argumentos:

   char *args[] = {"cd"};
   int result = cd(args, 1);
   // Como solo hay 1 argumento, se imprimirá "error: cd: bad arguments\n" y 
   		result será 1.

3. Error por directorio inexistente:
   
   char *args[] = {"cd", "/nonexistent"};
   int result = cd(args, 2);
   // Si el directorio "/nonexistent" no existe, se imprimirá 
   		"error: cd: cannot change directory to /nonexistent\n" y result será 1.

En resumen, la función 'cd' verifica que se le pasen exactamente dos argumentos 
	y luego intenta cambiar el directorio actual al especificado. Si algo falla, 
	imprime un mensaje de error y retorna 1; si todo va bien, retorna 0.
*/

void set_pipe(int has_pipe, int *fd, int end)	// Function to set the pipe. 
												// If there is a pipe, it will set the pipe 
												// and close the file descriptors.
{                                               
	if (has_pipe && (dup2(fd[end], end) == -1 || close(fd[0]) == -1 || close(fd[1]) == -1))
		err("error: fatal\n"), exit(1);
}
/*
set_pipe es una función que se encarga de configurar la tubería (pipe) para la comunicación entre procesos.
A continuación, se explica cómo funciona paso a paso:

   - 'has_pipe'	Es un entero que indica si se debe configurar una tubería (pipe) o no. Si su valor es 
   				diferente de cero, significa que se debe configurar una tubería.
   - 'fd'		Es un puntero a un arreglo de enteros que contiene los descriptores de archivo de la tubería. 
   				fd[0] es el descriptor de archivo para leer de la tubería y fd[1] es el descriptor de archivo 
   				para escribir en la tubería.
   - 'end'		Es un entero que indica si se debe cerrar el extremo de lectura (0) o escritura (1) 
   				de la tubería.

   - La función verifica si 'has_pipe' es verdadero (diferente de cero).
   - Si 'has_pipe' es verdadero, la función intenta duplicar el descriptor de archivo 'fd[end]' en el extremo 'end' 
   		de la tubería usando 'dup2'. 'dup2' es una función de la biblioteca unistd.h que duplica un descriptor 
		de archivo.
   - Si 'dup2' falla (retorna -1), la función imprime un mensaje de error y termina el programa.
   - Luego, la función intenta cerrar los descriptores de archivo 'fd[0]' y 'fd[1]' usando 'close'.
   - Si 'close' falla (retorna -1), la función imprime un mensaje de error y termina el programa.
*/

int	exec(char **argv, int i, char **envp)			// Function to execute the command
													// ./microshell ls -l ; echo hello
													// 1. argv = "ls" "-l", i = 3, envp
{
	int has_pipe, fd[2], pid, status;				// Initializing the variables:
													// has_pipe is used to check if there is a pipe
													// fd[2] is an array of file descriptors for the pipe
													// 2 because there are two file descriptors for the pipe
													// one for reading fd[0] and one for writing fd[1]
													// pid is the process id, its value will be 0 for the child process 
													// and the process id for the parent process
													// status is the status of the child process after it finishes, 
													// it will be used to check if the child process exited normally,
													// and to get the exit status of the child process
													// status can be 0 or 1. 0 means that the child process exited normally,
													// and 1 means that the child process did not exit normally
													// has_pipe = 0, fd[2] = {0, 0}, pid = 0, status = 0
	has_pipe = argv[i] && !strcmp(argv[i], "|");	// has_pipe = 0

	if (!has_pipe && !strcmp(*argv, "cd"))			// If there is no pipe and the command is cd
		return cd(argv, i);							// then change the directory
	if (has_pipe && pipe(fd) == -1)					// If there is a pipe, and the pipe fails to create the pipe 
		err("error: fatal\n"), exit(1);				// then print an error message and exit the program
	if ((pid = fork()) == -1)						// If the fork fails to create a new process
													// fork is used to create a new process, and pid will be the process id
		err("error: fatal\n"), exit(1);				// then print an error message and exit the program
	if (!pid)										// If the process is a child process, because the pid is 0
	{
		argv[i] = 0;								// Set the value of argv[i] to 0 to terminate the command
													// argv = "ls", "-l", 0 deleting the semicolon
		set_pipe(has_pipe, fd, 1);					// In the example there is no pipe, so the pipe will be set to 0
		if (!strcmp(*argv, "cd"))					// If the command is cd
			exit(cd(argv, i));						// exit is called with the return value of the cd function
													// and the child process will exit
		execve(*argv, argv, envp);					// If the command is not cd, then execve will be called
													// execve is used to execute a program
													// *argv = "ls", argv = "ls", "-l", 0, envp
		err("error: cannot execute "), err(*argv), err("\n"), exit(1);
													// If the command fails to execute, an error message will be printed
	}
	waitpid(pid, &status, 0);						// The parent process will wait for the child process to finish
													// waitpid is used to wait for a child process to finish
													// pid is the process id of the child process
													// status is the status of the child process
													// 0 is the options, which means that the parent process will wait for the child process to finish
	set_pipe(has_pipe, fd, 0);						// The pipe will be set to 0 to close the file descriptors of the pipe and avoid memory leaks
	return WIFEXITED(status) && WEXITSTATUS(status);// The exit status of the child process will be returned
													// WIFEXITED is a macro that returns true (1) if the child process exited normally or false (0) otherwise
													// WEXITSTATUS is a macro that returns the exit status of the child process. 
}

int main(int argc, char **argv, char **envp)	// ./microshell "ls", "-l", ";", "echo", "hello"
{												// argv[0] = "./microshell", argv[1] = "ls", argv[2] = "-l", argv[3] = ";", argv[4] = "echo", argv[5] = "hello"
	(void)argc;									// Ignoring the number of arguments
	int i = 0, status = 0;						// Initializing the index and status

	while (argv[i])								// if i = 0 => argv[0] = "./microshell"
												// if i = 1 => argv[1] = "ls"
												// if i = 2 => argv[2] = "-l"
												// if i = 3 => argv[3] = ";"
												// if i = 4 => argv[4] = "echo"
												// if i = 5 => argv[5] = "hello"
	{
		argv += i + 1;							// To begin the value of argv is 1 (argv[1] = "ls")
												// In the second loop, i = 3, so argv will be 4 (argv[4] = "echo")
		i = 0;									
		while (argv[i] && strcmp(argv[i], "|") && strcmp(argv[i], ";"))	// The loop will run until it finds a pipe or a semicolon, until strcmp returns 0.
			i++;								// 1. When the lop finds ";" i will be 3

		if (i)									// If i is not 0, then it means that the loop has found a pipe or a semicolon.
			status = exec(argv, i, envp);		// 1. i = 3, then exec(argv, 3, envp) will be called. argv = "ls", "-l", ";" and status will be 0
	}											// 2. i = 2, then exec(argv, 2, envp) will be called. argv = "echo", "hello"; and status will be 0
	return status;								// The status will be returned with the exit code of the last command executed. status = 0
}