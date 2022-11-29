/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlegrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 21:12:00 by nlegrand          #+#    #+#             */
/*   Updated: 2022/11/29 18:34:07 by nlegrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_setup(t_fdf *fdf, int ac, char **av, t_map *map)
{
	if (ac != 2 && ac != 4)
	{
		ft_printf("Usage: %s <filename> [case_size z_size]\n", av[0]);
		exit(EXIT_FAILURE);
	}
	fdf->id = mlx_init();
	if (fdf->id == NULL)
		(perror("fdf_setup[fdf init]"), exit(EXIT_FAILURE));
	if (parse_map(map, av[1]) == -1)
		(perror("fdf_setup[map]"), exit(EXIT_FAILURE));
	fdf->win = mlx_new_window(fdf->id, WIN_WIDTH, WIN_HEIGHT, WIN_TITLE);
	if (fdf->win == NULL)
		(perror("fdf_setup[win]"), exit(EXIT_FAILURE));
	fdf->map = map;
	fdf->width = WIN_WIDTH;
	fdf->height = WIN_HEIGHT;
	fdf->title = WIN_TITLE;
}

void	fdf_terminate(t_fdf *fdf)
{
	mlx_destroy_window(fdf->id, fdf->win);
	destroy_map(fdf->map);
}
