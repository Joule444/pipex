/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 19:34:47 by jules             #+#    #+#             */
/*   Updated: 2023/01/10 14:04:32 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//Child process 1 -> cmd1
void	child1(t_pipex pipex, char **env)
{
	close(pipex.pipe_fd[0]);
	dup2(pipex.cmd1.fd, STDIN_FILENO);
	close(pipex.cmd1.fd);
	dup2(pipex.pipe_fd[1], STDOUT_FILENO);
	close(pipex.pipe_fd[1]);
	execve(pipex.cmd1.path, pipex.cmd1.cmd, env);
}

//Child process 2 -> cmd2
void	child2(t_pipex pipex, char **env)
{
	dup2(pipex.cmd2.fd, STDOUT_FILENO);
	close(pipex.cmd2.fd);
	dup2(pipex.pipe_fd[0], STDIN_FILENO);
	close(pipex.pipe_fd[0]);
	close(pipex.pipe_fd[1]);
	execve(pipex.cmd2.path, pipex.cmd2.cmd, env);
}
