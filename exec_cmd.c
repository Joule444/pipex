/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 19:34:47 by jules             #+#    #+#             */
/*   Updated: 2023/01/03 19:36:03 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//Execute la commande en trouvant le path correspondant
void	exec_cmd(char **cmd, char **path, char **env)
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

//Child process 1 -> cmd1
void	exec_cmd1(t_pipex pipex, char **env)
{
	dup2(pipex.in_fd, STDIN_FILENO);
	close(pipex.in_fd);
	dup2(pipex.pipe_fd[1], STDOUT_FILENO);
	close(pipex.pipe_fd[1]);
	close(pipex.pipe_fd[0]);
	exec_cmd(pipex.cmd1, pipex.path, env);
}

//Child process 2 -> cmd2
void	exec_cmd2(t_pipex pipex, char **env)
{
	dup2(pipex.out_fd, STDOUT_FILENO);
	close(pipex.out_fd);
	dup2(pipex.pipe_fd[0], STDIN_FILENO);
	close(pipex.pipe_fd[0]);
	close(pipex.pipe_fd[1]);
	exec_cmd(pipex.cmd2, pipex.path, env);
}
