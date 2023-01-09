/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 17:53:48 by jthuysba          #+#    #+#             */
/*   Updated: 2023/01/09 19:52:44 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//Free toute la structure cmd
void	free_cmd(t_cmd *cmd)
{
	if (cmd->cmd != NULL)
		ft_free_arr(cmd->cmd);
	if (cmd->path != NULL)
		free(cmd->path);
	if (cmd->file != NULL)
		free(cmd->file);
}

//Free toute la structure pipex
void	free_all(t_pipex *pipex)
{
	if (pipex->path)
		ft_free_arr(pipex->path);
	free_cmd(&pipex->cmd1);
	free_cmd(&pipex->cmd2);
}

//Affiche un message d'erreur et free all
void	print_error(char *msg)
{
	int	i;

	i = 0;
	while (msg[i])
	{
		write(1, &msg[i],1);
		i++;
	}
}
