/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 19:48:04 by jthuysba          #+#    #+#             */
/*   Updated: 2023/01/10 12:32:28 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_cmd(t_cmd *cmd)
{
	cmd->cmd = NULL;
	cmd->file = NULL;
	cmd->path = NULL;
	cmd->fd = 0;
}

void	init_data(t_pipex *pipex)
{
	pipex->path = NULL;
	init_cmd(&pipex->cmd1);
	init_cmd(&pipex->cmd2);
}
