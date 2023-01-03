/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:10:04 by jthuysba          #+#    #+#             */
/*   Updated: 2023/01/03 15:00:04 by jthuysba         ###   ########.fr       */
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

//Execute la commande avec le bon path
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
	int		pipe_fd[2];
	int		in_fd;
	int		out_fd;
	int		pid1;
	int		pid2;

	if (argc != 5)
		return (1);
	pipex.cmd1 = ft_split(argv[2], ' ');
	pipex.cmd2 = ft_split(argv[3], ' ');
	pipex.path = find_path(env);

	pipex.infile = malloc(sizeof(char) * ft_strlen(argv[1]) + 1);
	ft_strcpy(pipex.infile, argv[1]);

	pipex.outfile = malloc(sizeof(char) * ft_strlen(argv[4]) + 1);
	ft_strcpy(pipex.outfile, argv[4]);

	in_fd = open(pipex.infile, O_RDONLY, 0777);
	out_fd = open(pipex.outfile, O_WRONLY | O_TRUNC| O_CREAT, 0777);

	if (pipe(pipe_fd) == -1)
		return (2);
		
	pid1 = fork();
	if (pid1 < 0)
		return (3);
		
	if (pid1 == 0) //Child process (cmd1)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);	//Car le fd de stdout correspond a celui la dorenavant 
		close(pipe_fd[0]);	//Car on n'a pas besoin de read
		exec_path(pipex.cmd1, pipex.path, env);
	}
	pid2 = fork();
	if (pid2 < 0)
		return (4);

	if (pid2 == 0) //Child process 2 (cmd2)
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
		dup2(pipe_fd[0], STDIN_FILENO);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		exec_path(pipex.cmd2, pipex.path, env);
	} 
	close(pipe_fd[0]);
	close(pipe_fd[1]);

	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);

	return (ft_free_arr(pipex.cmd1), ft_free_arr(pipex.cmd2),
		ft_free_arr(pipex.path), 0);
}
