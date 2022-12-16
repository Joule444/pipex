/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:10:04 by jthuysba          #+#    #+#             */
/*   Updated: 2022/12/16 18:21:32 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**find_path(char **env)
{
	int		i;
	char	**arr;
	char	**path;

	i = 0;
	while (env[i])
	{
		arr = ft_split(env[i], '=');
		if (ft_strcmp(arr[0], "PATH"))
		{
			path = ft_split(arr[1], ':');
			return (ft_free_arr(arr), path);
		}
		ft_free_arr(arr);
		i++;
	}
	return (NULL);
}

void	exec_path(char **cmd, char **path, char **env)
{
	int		i;
	char	*full_path;

	i = 0;
	while (path[i])
	{
		full_path = ft_strjoin(path[i], "/");
		full_path = ft_strjoin(full_path, cmd[0]);
		if (execve(full_path, cmd, env) != -1)
			return ;
		free(full_path);
		i++;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;

	if (argc != 5)
		return (0);
	pipex.cmd1 = ft_split(argv[2], ' ');
	pipex.cmd2 = ft_split(argv[3], ' ');
	pipex.path = find_path(env);
	exec_path(pipex.cmd1, pipex.path, env);
	return (ft_free_arr(pipex.cmd1), ft_free_arr(pipex.cmd2),
		ft_free_arr(pipex.path), 0);
}
