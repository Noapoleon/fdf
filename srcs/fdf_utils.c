/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 21:12:00 by nlegrand          #+#    #+#             */
/*   Updated: 2022/11/28 20:44:55 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_setup(t_fdf *fdf, t_window *win, t_map *map)
{
	fdf->id = mlx_init();
	if (fdf->id == NULL)
	{
		destroy_map(map);
		ft_dprintf(2, "[ERROR] Failed to establish X server connection.\n");
		perror("fdf_setup");
		exit(EXIT_FAILURE);
	}
	win->id = mlx_new_window(fdf->id, win->width, win->height, win->title);
	if (win->id == NULL)
	{
		destroy_map(map);
		ft_dprintf(2, "[ERROR] Failed to create new window.\n");
		perror("nlgw_setup");
		exit(EXIT_FAILURE);
	}
	fdf->win = win;
	fdf->map = map;
}

void win_init(t_window *win, int width, int height, char *title)
{
	win->width = width;
	win->height = height;
	win->title = title;
}

void	fdf_terminate(t_fdf *fdf)
{
	mlx_destroy_window(fdf->id, fdf->win->id);
	destroy_map(fdf->map);
}
