/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 17:57:35 by jthuysba          #+#    #+#             */
/*   Updated: 2023/01/10 14:05:33 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	my_strcat(char *dest, char *src, int j)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[j] = src[i];
		i++;
		j++;
	}
	return (j);
}

//Join le path et la commande avec un '/'
char	*path_join(char *path, char *cmd)
{
	char	*full_path;
	int		j;

	j = 0;
	full_path = malloc(sizeof(char) * ft_strlen(path) + ft_strlen(cmd) + 2);
	if (!full_path)
		return (NULL);
	j = my_strcat(full_path, path, j);
	full_path[j] = '/';
	j++;
	j = my_strcat(full_path, cmd, j);
	full_path[j] = '\0';
	return (full_path);
}

//Retourne la liste des paths possibles
char	**get_path(char **env)
{
	int		i;
	char	**arr;
	char	**path;

	i = 0;
	while (env[i])
	{
		arr = ft_split(env[i], '=');
		if (!arr)
			return (NULL);
		if (ft_strcmp(arr[0], "PATH"))
		{
			path = ft_split(arr[1], ':');
			if (!path)
				return (ft_free_arr(arr), NULL);
			return (ft_free_arr(arr), path);
		}
		ft_free_arr(arr);
		i++;
	}
	return (NULL);
}

//Retourne le path absolu
char	*abs_path(char **cmd)
{
	char	*abs_path;

	abs_path = malloc(sizeof(char) * (ft_strlen(cmd[0]) + 1));
	ft_strcpy(abs_path, cmd[0]);
	if (access(abs_path, F_OK) == 0)
		return (abs_path);
	else
		return (free(abs_path), NULL);
}

//Retourne le path de la commande
char	*find_path(char **cmd, char **path)
{
	int		i;
	char	*full_path;

	i = 0;
	if (cmd[0][0] == '/')
		return (abs_path(cmd));
	while (path[i])
	{
		full_path = path_join(path[i], cmd[0]);
		if (full_path == NULL)
			return (NULL);
		if (access(full_path, F_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}
