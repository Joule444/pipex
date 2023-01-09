/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 17:57:35 by jthuysba          #+#    #+#             */
/*   Updated: 2023/01/09 18:34:02 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*path_join(char *path, char *cmd)
{
	char	*full_path;
	int		i;
	int		j;

	i = 0;
	j = 0;
	full_path = malloc(sizeof(char) * ft_strlen(path) + ft_strlen(cmd) + 2);
	if (!full_path)
		return (NULL);
	while (path[i])
	{
		full_path[j] = path[i];
		i++;
		j++;
	}
	full_path[j] = '/';
	j++;
	i = 0;
	while (cmd[i])
	{
		full_path[j] = cmd[i];
		i++;
		j++;
	}
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

//Retourne le path de la commande
char	*find_path(char **cmd, char **path)
{
	int		i;
	char	*full_path;

	i = 0;
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
