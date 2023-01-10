/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:10:04 by jthuysba          #+#    #+#             */
/*   Updated: 2023/01/10 14:19:08 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//Set les commandes
int	set_cmd(t_pipex *pipex, char **argv)
{
	pipex->cmd1.cmd = ft_split(argv[2], ' ');
	pipex->cmd2.cmd = ft_split(argv[3], ' ');
	if (!pipex->cmd1.cmd || !pipex->cmd2.cmd)
		return (print_error("Split error\n"), 1);
	return (0);
}

//Set toutes les data de la struct pipex
int	set_data(t_pipex *pipex, char **argv, char **env)
{
	if (set_cmd(pipex, argv) == 1)
		return (1);
	pipex->path = get_path(env);
	if (pipex->path == NULL)
		return (print_error("Path error\n"), 1);
	pipex->cmd1.path = find_path(pipex->cmd1.cmd, pipex->path);
	pipex->cmd2.path = find_path(pipex->cmd2.cmd, pipex->path);
	if (pipex->cmd1.path == NULL || pipex->cmd2.path == NULL)
		return (print_error("Command path error\n"), 1);
	pipex->cmd1.file = malloc(sizeof(char) * ft_strlen(argv[1]) + 1);
	pipex->cmd2.file = malloc(sizeof(char) * ft_strlen(argv[4]) + 1);
	if (!pipex->cmd1.file || !pipex->cmd2.file)
		return (print_error("Malloc error\n"), 1);
	ft_strcpy(pipex->cmd1.file, argv[1]);
	ft_strcpy(pipex->cmd2.file, argv[4]);
	pipex->cmd1.fd = open(pipex->cmd1.file, O_RDONLY, 0777);
	if (pipex->cmd1.fd < 0)
		return (print_error("Infile error\n"), 1);
	pipex->cmd2.fd = open(pipex->cmd2.file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (pipex->cmd2.fd < 0)
		return (print_error("Outfile error\n"), 1);
	if (pipe(pipex->pipe_fd) == -1)
		return (print_error("Pipe error\n"), 1);
	return (0);
}

//Verifie les arguments
int	check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc != 5)
		return (1);
	while (argv[i])
	{
		if (argv[i][0] == 0)
			return (1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_pipex		pipex;

	if (check_args(argc, argv) == 1)
		return (print_error("Args error\n"), 1);
	init_data(&pipex);
	if (set_data(&pipex, argv, env))
		return (free_all(&pipex), 5);
	pipex.cmd1.pid = fork();
	if (pipex.cmd1.pid < 0)
		return (print_error("Fork error\n"), free_all(&pipex), 3);
	if (pipex.cmd1.pid == 0)
		child1(pipex, env);
	pipex.cmd2.pid = fork();
	if (pipex.cmd2.pid < 0)
		return (print_error("Fork error\n"), free_all(&pipex), 4);
	if (pipex.cmd2.pid == 0)
		child2(pipex, env);
	close(pipex.pipe_fd[0]);
	close(pipex.pipe_fd[1]);
	waitpid(pipex.cmd1.pid, NULL, 0);
	waitpid(pipex.cmd2.pid, NULL, 0);
	close(pipex.cmd1.fd);
	close(pipex.cmd2.fd);
	free_all(&pipex);
	return (0);
}
