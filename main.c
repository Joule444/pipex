/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:10:04 by jthuysba          #+#    #+#             */
/*   Updated: 2023/01/09 18:09:20 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//Initialise toutes les data de la struct pipex
int	init_data(t_pipex *pipex, char **argv, char **env)
{
	pipex->cmd1.cmd = ft_split(argv[2], ' ');
	pipex->cmd2.cmd = ft_split(argv[3], ' ');
	if (!pipex->cmd1.cmd || !pipex->cmd2.cmd)
		return (print_error("Split error\n", pipex), 1);
	pipex->path = get_path(env);
	pipex->cmd1.path = find_path(pipex->cmd1.cmd, pipex->path);
	pipex->cmd2.path = find_path(pipex->cmd2.cmd, pipex->path);
	if (pipex->path == NULL || pipex->cmd1.path == NULL || pipex->cmd2.path == NULL)
		return (print_error("Path error\n", pipex), 1);
	pipex->cmd1.file = malloc(sizeof(char) * ft_strlen(argv[1]) + 1);
	pipex->cmd2.file = malloc(sizeof(char) * ft_strlen(argv[4]) + 1);
	if (!pipex->cmd1.file || !pipex->cmd2.file)
		return (print_error("Malloc error\n", pipex), 1);
	ft_strcpy(pipex->cmd1.file, argv[1]);
	ft_strcpy(pipex->cmd2.file, argv[4]);
	pipex->cmd1.fd = open(pipex->cmd1.file, O_RDONLY, 0777);
	pipex->cmd2.fd = open(pipex->cmd2.file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (pipex->cmd1.fd < 0 || pipex->cmd2.fd < 0)
		return (print_error("Open error\n", pipex), 1);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;
	pid_t		pid1;
	pid_t		pid2;

	if (argc != 5)
		return (print_error("Args error\n", &pipex), 1);
	if (init_data(&pipex, argv, env))
		return (print_error("Data error\n", &pipex), 5);
	if (pipe(pipex.pipe_fd) == -1)
		return (print_error("Pipe error\n", &pipex), 2);
	pid1 = fork();
	if (pid1 < 0)
		return (print_error("Fork error\n", &pipex), 3);
	if (pid1 == 0)
		child1(pipex, env);
	pid2 = fork();
	if (pid2 < 0)
		return (print_error("Fork error\n", &pipex), 4);
	if (pid2 == 0)
		child2(pipex, env);
	close(pipex.pipe_fd[0]);
	close(pipex.pipe_fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	close(pipex.cmd1.fd);
	close(pipex.cmd2.fd);
	free_all(&pipex);
	return (0);
}
