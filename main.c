/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:10:04 by jthuysba          #+#    #+#             */
/*   Updated: 2023/01/03 19:38:27 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//Retourne la liste des paths possibles
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

//Initialise toutes les data de la struct pipex
void	init_data(t_pipex *pipex, char **argv, char **env)
{
	pipex->cmd1 = ft_split(argv[2], ' ');
	pipex->cmd2 = ft_split(argv[3], ' ');
	pipex->path = find_path(env);
	pipex->infile = malloc(sizeof(char) * ft_strlen(argv[1]) + 1);
	pipex->outfile = malloc(sizeof(char) * ft_strlen(argv[4]) + 1);
	ft_strcpy(pipex->infile, argv[1]);
	ft_strcpy(pipex->outfile, argv[4]);
	pipex->in_fd = open(pipex->infile, O_RDONLY, 0777);
	pipex->out_fd = open(pipex->outfile, O_WRONLY | O_TRUNC | O_CREAT, 0777);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;
	int		pid1;
	int		pid2;

	if (argc != 5)
		return (1);
	init_data(&pipex, argv, env);
	if (pipe(pipex.pipe_fd) == -1)
		return (2);
	pid1 = fork();
	if (pid1 < 0)
		return (3);
	if (pid1 == 0)
		exec_cmd1(pipex, env);
	pid2 = fork();
	if (pid2 < 0)
		return (4);
	if (pid2 == 0)
		exec_cmd2(pipex, env);
	close(pipex.pipe_fd[0]);
	close(pipex.pipe_fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (ft_free_arr(pipex.cmd1), ft_free_arr(pipex.cmd2),
		ft_free_arr(pipex.path), 0);
}
