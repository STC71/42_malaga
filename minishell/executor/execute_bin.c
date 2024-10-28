/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druiz-ca <druiz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:10:16 by druiz-ca          #+#    #+#             */
/*   Updated: 2024/10/26 13:54:18 by druiz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* Función que construye la ruta completa uniendo la ruta del bin
 con el nombre del comando añadiendo "/" en medio de ambos. Una vez unido, 
 verifica si existe esa ruta con ACCESS y el modo F_OK */
char    **join_binpath_and_cmd(char *cmd, char *bin_path)
{
    char *joined_path;

    joined_path = malloc(ft_strlen(bin_path) + ft_strlen(cmd) + 2);
    if (joined_path == NULL)
        return (NULL);
    ft_strlcpy(joined_path, bin_path, ft_strlen(bin_path) + 1);
    ft_strlcat(joined_path, "/", ft_strlen(bin_path) + 2);
    ft_strlcat(joined_path, cmd, ft_strlen(bin_path) + ft_strlen(cmd) + 2);
    if (access(joined_path, F_OK) == 0)
        return (joined_path);
    else
    {
        free(joined_path);
        return (NULL);
    }
}

/* Función que imprime un mensaje de error según el tipo de error que ocurra.
Pueden ser: para comandos no encontrados, archivos o directorios inexistentes, 
directorios y permisos denegados y retorna un código con el tipo de error */
int    write_bin_error(char *path, t_minishell *shell)
{
    DIR *dir;
    int status;

    status = 0;
    shell->g_status = 1;
    dir = opendir(path);
    write(STDERR_FILENO, path, ft_strlen(path));
    if (ft_strchr(path, '/') == NULL)
        write(STDERR_FILENO, ": command not found", 19);
    else if (access(path, F_OK) == -1)
        write(STDERR_FILENO, ": No such file or directory", 27);
    else if (dir == NULL)
    {
        write(STDERR_FILENO, ": is a directory", 16);
        closedir(dir);
    }
    else if (access(path, X_OK) == -1)
        write(STDERR_FILENO, ": Permission denied", 19);
    if (ft_strchr(path, '/') == NULL || (dir == NULL))
        status = 127;
    else
        status = 126;
    if (dir != NULL)
        closedir(dir);
    write(STDERR_FILENO, "\n", 1);
    return (status);
}

/* Función que busca la ruta de las env y las devuelve en una matrix
separadas por ":" en cada array de la matriz*/
char **get_bin_paths(t_minishell *shell)
{
    int i;

    i = 0;
    while (shell->env && shell->env[i])
    {
        if (ft_strncmp(shell->env[i], "PATH=", 5) == 0)
            return (ft_split(shell->env[i] + 5, ':'));
        i++;
    }
}

/* Función principal que contiene las sub-funciones para la ejecución del 
comando del sistema(bin, no builtin) recibido por el usuario*/
void    execute_bin_cmd_main(t_minishell *shell, t_cmd **commands, int i)
{
    char **bin_paths;
    int j;
    
    j = 0;
    bin_paths = get_bin_paths(shell);
    if (!commands[i]->cmd || !bin_paths)
        return (write_bin_error(commands[i]->cmd, shell));
    while (bin_paths[j])
    {
        shell->cmd_path = join_binpath_and_cmd(commands[i]->cmd, bin_paths[j++]);
        if (shell->cmd_path != NULL)
            break ;
    }
    if (shell->cmd_path != NULL)
        execute_bin_cmd(shell->cmd_path, commands, shell, i);
    else
        execute_bin_cmd(commands[i]->cmd, commands, shell, i);
    ft_str_free(bin_paths);
    free(shell->cmd_path);
}       