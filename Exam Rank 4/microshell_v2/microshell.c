/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sternero <sternero@student.42malaga.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-02-17 09:24:26 by sternero          #+#    #+#             */
/*   Updated: 2025-02-17 09:24:26 by sternero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

void err(char *str)								// función para imprimir errores
{
    while (*str)
        write(2, str++, 1);
}

int cd(char **argv)								// función para cambiar de directorio
{
    if (argv[2] != 0) 							// si tiene más de un argumento
    {
        err("error: cd: bad arguments\n");
        return 1;
    }
    chdir(argv[1]);								// cambia de directorio
    return 0;
}

void set_pipe(int has_pipe, int *fd, int end)	// función para redirigir la salida
{
    if (has_pipe != 0)							// si hay un pipe
    {
        dup2(fd[end], end);						// duplica el descriptor de archivo
        close(fd[0]);							// cierra el descriptor de archivo
        close(fd[1]);							// cierra el descriptor de archivo
    }
}

int exec(char **argv, int i, char **envp)		// función para ejecutar comandos
{
    int has_pipe;								// variable para saber si hay un pipe
    int fd[2];									// variable para los descriptores de archivo
    int pid;									// variable para el proceso hijo
    int status;									// variable para el estado del proceso hijo
    has_pipe = 0;								// inicializa la variable para saber si hay un pipe
    if (argv[i] && strcmp(argv[i], "|") == 0)	// si el argumento es un pipe
        has_pipe = 1;
    if (has_pipe == 0 && strcmp(argv[0], "cd") == 0)	// si el argumento es cd
        return cd(argv);
    pipe(fd);									// crea un pipe para la comunicación entre procesos
    pid = fork();								// crea un proceso hijo
    if (pid == 0)								// si es el proceso hijo
    {
        argv[i] = NULL; 						// el último argumento es NULL
        set_pipe(has_pipe, fd, 1);				// redirige la salida
        if (execve(argv[0], argv, envp) == -1)	// ejecuta el comando
        {
            err("error: cannot execute ");		// si no se puede ejecutar el comando
            err(argv[0]);						// imprime el error
            err("\n");							// imprime el error con un salto de línea
            exit(1);							// sale del programa
        }
    }
    else
    {
        set_pipe(has_pipe, fd, 0);				// redirige la salida
        waitpid(pid, &status, 0);				// espera a que el proceso hijo termine
    }
    return 0;
}

/*
int main(int argc, char **argv, char **envp)
{
    int i;
    int j;
    i = 1;
    while (i < argc)
    {
        j = i;
        while (j < argc && strcmp(argv[j], ";") != 0 && strcmp(argv[j], "|") != 0)
            j++;
        if (j > i)
            exec(argv + i, j - i, envp); // argv + i!!!
        i = j + 1;
    }
    return 0;
}
*/