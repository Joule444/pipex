/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 16:12:43 by jthuysba          #+#    #+#             */
/*   Updated: 2023/01/03 19:37:35 by jules            ###   ########.fr       */
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

typedef struct s_pipex
{
	char	*infile;
	char	*outfile;
	char	**cmd1;
	char	**cmd2;
	char	**path;
	int		in_fd;
	int		out_fd;
	int		pipe_fd[2];
}	t_pipex;

//Exec cmd
void	exec_cmd1(t_pipex pipex, char **env);
void	exec_cmd2(t_pipex pipex, char **env);

#endif