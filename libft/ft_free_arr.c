/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuysba <jthuysba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 16:38:16 by jthuysba          #+#    #+#             */
/*   Updated: 2023/01/09 17:42:33 by jthuysba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//Free completement un char**
void	ft_free_arr(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{	
		while (arr[i])
		{
			free(arr[i]);
			i++;
		}
	}
	free(arr[i]);
	free(arr);
}
