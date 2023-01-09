/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:12:43 by jthuysba          #+#    #+#             */
/*   Updated: 2023/01/09 17:58:36 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "./libft/libft.h"

typedef struct s_cmd
{
	char	**cmd;
	char	*path;
	char	*file;
	int		fd;
}	t_cmd;

typedef struct s_pipex
{
	t_cmd	cmd1;
	t_cmd	cmd2;
	int		pipe_fd[2];
	char	**path;
}	t_pipex;

//Find path
char	**get_path(char **env);
char	*find_path(char **cmd, char **path);

//Child proccess
void	child1(t_pipex pipex, char **env);
void	child2(t_pipex pipex, char **env);

//Free all
void	free_all(t_pipex *pipex);
void	print_error(char *msg, t_pipex *pipex);

#endif