/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nlgw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 15:29:21 by nlegrand          #+#    #+#             */
/*   Updated: 2022/11/26 01:42:46 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	nlgw_setup(t_nlgw *nlgw, int width, int height, char *title)
{
	nlgw->id = mlx_init();
	if (nlgw->id == NULL)
	{
		ft_dprintf(2, "[ERROR] Failed to establish X server connection.\n");
		perror("nlgw_setup");
		exit(EXIT_FAILURE);
	}
	nlgw->window = mlx_new_window(nlgw->id, width, height, title);
	if (nlgw->window == NULL)
	{
		ft_dprintf(2, "[ERROR] Failed to create new window.\n");
		perror("nlgw_setup");
		exit(EXIT_FAILURE);
	}
	nlgw->width = width;
	nlgw->height = height;
	nlgw->title = title;
	return (0);
}

void	nlgw_terminate(t_nlgw *nlgw)
{
	mlx_destroy_window(nlgw->id, nlgw->window);
}
